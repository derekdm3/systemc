//! \file simple_bus.cpp

#include "simple_bus.hpp"
using namespace sc_core;

simple_bus::simple_bus(sc_module_name name, bool verbose)
   : sc_module(name)
   , m_verbose(verbose)
   , m_current_request(0)
{
   SC_HAS_PROCESS(simple_bus);
   SC_METHOD(main_action);
   dont_initialize();
   sensitive << clock.neg();
}

void simple_bus::end_of_elaboration()
{
   bool no_overlap;
   for(int i = 1 ; i < slave_port.size() ; i++)
   {
      simple_bus_slave_if* slave1 = slave_port[i];
      for(int j = 0 ; j < i ; j++)
      {
         simple_bus_slave_if* slave2 = slave_port[j];
         no_overlap = (slave1->end_address() < slave2->start_address()) ||
                      (slave1->start_address() > slave2->end_address());
         if(!no_overlap)
         {
            SC_REPORT_FATAL("/accellera/examples", "overlapping address spaces");
            exit(0);
         }
      }
   }
}

void simple_bus::main_action()
{
   if(!m_current_request)
   {
      m_current_request = get_next_request();
   }
   if(m_current_request)
   {
      handle_request();
   }
   if(!m_current_request)
   {
      clear_locks();
   }
}

bool simple_bus::direct_read(int* data, unsigned int address)
{
   if(address % 4 != 0)
   {
      SC_REPORT_WARNING("/accellera/examples", "address not word aligned");
      return false;
   }
   simple_bus_slave_if* slave = get_slave(address);
   if(!slave)
   {
      return false;
   }
   return slave->direct_read(data, address);
}

bool simple_bus::direct_write(int* data, unsigned int address)
{
   if(address % 4 != 0)
   {
      SC_REPORT_WARNING("/accellera/examples", "address not word aligned");
      return false;
   }
   simple_bus_slave_if* slave = get_slave(address);
   if(!slave)
   {
      return false;
   }
   return slave->direct_write(data, address);
}

void simple_bus::read(unsigned int unique_priority,
                      int* data,
                      unsigned int address,
                      bool lock)
{
   simple_bus_request* request = get_request(unique_priority);
   sc_assert(request->status == SIMPLE_BUS_OK ||
             request->status == SIMPLE_BUS_ERROR);
   request->do_write = false;
   request->address = address;
   request->end_address = address;
   request->data = data;
   if(lock)
   {
      request->lock = (request->lock == SIMPLE_BUS_LOCK_SET)
         ? SIMPLE_BUS_LOCK_GRANTED
         : SIMPLE_BUS_LOCK_SET;
   }
   request->status = SIMPLE_BUS_REQUEST;
}

void simple_bus::write(unsigned int unique_priority,
                       int* data,
                       unsigned int address,
                       bool lock)
{
   simple_bus_request* request = get_request(unique_priority);
   sc_assert(request->status == SIMPLE_BUS_OK ||
             request->status == SIMPLE_BUS_ERROR);
   request->do_write = false;
   request->address = address;
   request->end_address = address;
   request->data = data;
   if(lock)
   {
      request->lock = (request->lock == SIMPLE_BUS_LOCK_SET)
         ? SIMPLE_BUS_LOCK_GRANTED
         : SIMPLE_BUS_LOCK_SET;
   }
   request->status = SIMPLE_BUS_REQUEST;
}

simple_bus_status simple_bus::get_status(unsigned int unique_priority)
{
   return get_request(unique_priority)->status;
}

simple_bus_status simple_bus::burst_read(unsigned int unique_priority,
                                         int* data,
                                         unsigned int start_address,
                                         unsigned int length,
                                         bool lock)
{
   simple_bus_request* request = get_request(unique_priority);
   request->do_write = false;
   request->address = start_address;
   request->end_address = start_address + (length - 1) * 4;
   request->data = data;
   if(lock)
   {
      request->lock = (request->lock == SIMPLE_BUS_LOCK_SET)
         ? SIMPLE_BUS_LOCK_GRANTED
         : SIMPLE_BUS_LOCK_SET;
   }
   request->status = SIMPLE_BUS_REQUEST;
   wait(request->transfer_done);
   wait(clock->posedge_event());
   return request->status;
}

simple_bus_status simple_bus::burst_write(unsigned int unique_priority,
                                          int* data,
                                          unsigned int start_address,
                                          unsigned int length,
                                          bool lock)
{
   simple_bus_request* request = get_request(unique_priority);
   request->do_write = true;
   request->address = start_address;
   request->end_address = start_address + (length - 1) * 4;
   request->data = data;
   if(lock)
   {
      request->lock = (request->lock == SIMPLE_BUS_LOCK_SET)
         ? SIMPLE_BUS_LOCK_GRANTED
         : SIMPLE_BUS_LOCK_SET;
   }
   request->status = SIMPLE_BUS_REQUEST;
   wait(request->transfer_done);
   wait(clock->posedge_event());
   return request->status;
}

void simple_bus::handle_request()
{
   m_current_request->status = SIMPLE_BUS_WAIT;
   simple_bus_slave_if* slave = get_slave(m_current_request->address);
   if(m_current_request->address % 4 != 0)
   {
      SC_REPORT_ERROR("/accellera/examples", "address not word aligned");
      m_current_request->status = SIMPLE_BUS_ERROR;
      m_current_request = reinterpret_cast<simple_bus_request*>(0);
   }
   else if(!slave)
   {
      SC_REPORT_ERROR("/accellera/examples", "no slave for address");
      m_current_request->status = SIMPLE_BUS_ERROR;
      m_current_request = reinterpret_cast<simple_bus_request*>(0);
   }
   else
   {
      simple_bus_status slave_status = SIMPLE_BUS_OK;
      if(m_current_request->do_write)
      {
         slave_status = slave->write(m_current_request->data,
                                     m_current_request->address);
      }
      else
      {
         slave_status = slave->read(m_current_request->data,
                                    m_current_request->address);
      }
      switch(slave_status)
      {
      case SIMPLE_BUS_ERROR:
         m_current_request->status = SIMPLE_BUS_ERROR;
         m_current_request->transfer_done.notify();
         m_current_request = reinterpret_cast<simple_bus_request*>(0);
         break;
      case SIMPLE_BUS_OK:
         m_current_request->address += 4;
         m_current_request->data++;
         if(m_current_request->address > m_current_request->end_address)
         {
            m_current_request->status = SIMPLE_BUS_OK;
            m_current_request->transfer_done.notify();
         }
         m_current_request = reinterpret_cast<simple_bus_request*>(0);
         break;
      case SIMPLE_BUS_WAIT:
         break;
      default:
         break;
      }
   }
}

simple_bus_slave_if* simple_bus::get_slave(unsigned int address)
{
   simple_bus_slave_if* slave = reinterpret_cast<simple_bus_slave_if*>(0);
   unsigned int i = 0;
   while(reinterpret_cast<simple_bus_slave_if*>(0) == slave &&
         slave_port.size() > i)
   {
      if(slave_port[i]->start_address() <= address &&
         address <= slave_port[i]->end_address())
      {
         slave = slave_port[i];
      }
      else
      {
         i++;
      }
   }
   return slave;
}

simple_bus_request* simple_bus::get_request(unsigned int priority)
{
   simple_bus_request* request = reinterpret_cast<simple_bus_request*>(0);
   unsigned int i = 0;
   while(reinterpret_cast<simple_bus_request*>(0) == request
         && m_requests.size() > i)
   {
      if(reinterpret_cast<simple_bus_request*>(0) != m_requests[i] &&
         m_requests[i]->priority == priority)
      {
         request = m_requests[i];
      }
      else
      {
         i++;
      }
   }
   if(reinterpret_cast<simple_bus_request*>(0) == request)
   {
      request = new simple_bus_request;
      request->priority = priority;
      m_requests.push_back(request);
   }
   return request;
}

simple_bus_request* simple_bus::get_next_request()
{
   simple_bus_request_vec Q;
   for(unsigned int i = 0 ; i < m_requests.size() ; i++)
   {
      simple_bus_request* request = m_requests[i];
      if(request->status == SIMPLE_BUS_REQUEST ||
         request->status == SIMPLE_BUS_WAIT)
      {
         Q.push_back(request);
      }
   }
   return (Q.size() > 0)
      ? arbiter_port->arbitrate(Q)
      : reinterpret_cast<simple_bus_request*>(0);
}

void simple_bus::clear_locks()
{
   for(unsigned int i = 0 ; i < m_requests.size() ; i++)
   {
      m_requests[i]->lock = (m_requests[i]->lock == SIMPLE_BUS_LOCK_GRANTED)
         ? SIMPLE_BUS_LOCK_SET
         : SIMPLE_BUS_LOCK_NO;
   }
}
