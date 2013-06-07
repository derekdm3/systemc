//! \file simple_bus.cpp

#include "simple_bus.hpp"

simple_bus::simple_bus(sc_core::sc_module_name name, bool verbose)
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
   else if(m_verbose)
   {
      SC_REPORT_INFO("/accellera/examples", "TBD");
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
