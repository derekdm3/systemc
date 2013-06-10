//! \file simple_bus_test.cpp

#include <vector>
#include <iostream>
#include <sstream>
#include "simple_bus.hpp"
using namespace sc_core;

class simple_bus_master_blocking
   : public sc_module
{
private:
   unsigned int m_unique_priority;
   unsigned int m_address;
   bool m_lock;
   int m_timeout;

public:
   sc_in_clk clock;
   sc_port<simple_bus_blocking_if> bus_port;

   simple_bus_master_blocking(sc_module_name name,
                              unsigned int unique_priority,
                              unsigned int address,
                              bool lock,
                              int timeout)
      : sc_module(name)
      , m_unique_priority(unique_priority)
      , m_address(address)
      , m_lock(lock)
      , m_timeout(timeout)
   {
      SC_HAS_PROCESS(simple_bus_master_blocking);
      SC_THREAD(main_action);
      sensitive << clock.pos();
   }

   void main_action()
   {
      const unsigned int mylength = 0x10;
      int mydata[mylength];
      simple_bus_status status;
      while(true)
      {
         wait();
         status = bus_port->burst_read(m_unique_priority,
                                       mydata,
                                       m_address,
                                       mylength,
                                       m_lock);
         if(status == SIMPLE_BUS_ERROR)
         {
            SC_REPORT_WARNING("/accellera/examples", "blocking-read failed");
         }
         for(unsigned int i = 0 ; i < mylength ; i++)
         {
            mydata[i] += i;
            wait();
         }
         status = bus_port->burst_write(m_unique_priority,
                                        mydata,
                                        m_address,
                                        mylength,
                                        m_lock);
         if(status == SIMPLE_BUS_ERROR)
         {
            SC_REPORT_WARNING("/accellera/examples", "blocking-write failed");
         }
         wait(m_timeout, SC_NS);
      }
   }
};

class simple_bus_master_non_blocking
   : public sc_module
{
private:
   unsigned int m_unique_priority;
   unsigned int m_start_address;
   bool m_lock;
   int m_timeout;

public:
   sc_in_clk clock;
   sc_port<simple_bus_non_blocking_if> bus_port;

   simple_bus_master_non_blocking(sc_module_name name,
                                  unsigned int unique_priority,
                                  unsigned int start_address,
                                  bool lock,
                                  int timeout)
      : sc_module(name)
      , m_unique_priority(unique_priority)
      , m_start_address(start_address)
      , m_lock(lock)
      , m_timeout(timeout)
   {
      SC_HAS_PROCESS(simple_bus_master_non_blocking);
      SC_THREAD(main_action);
      sensitive << clock.pos();
   }

   void main_action()
   {
      int mydata;
      int cnt = 0;
      unsigned int addr = m_start_address;
      wait();
      while(true)
      {
         bus_port->read(m_unique_priority, &mydata, addr, m_lock);
         while(bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK &&
               bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR)
         {
            wait();
         }
         if(bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
         {
            SC_REPORT_ERROR("/accellera/examples", "cannot read");
         }
         mydata += cnt;
         cnt++;
         bus_port->write(m_unique_priority, &mydata, addr, m_lock);
         while(bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK &&
               bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR)
         {
            wait();
         }
         if(bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR)
         {
            SC_REPORT_ERROR("/accellera/examples", "cannot write");
         }
         wait(m_timeout, SC_NS);
         wait();
         addr += 4;
         if(addr > (m_start_address + 0x80))
         {
            addr = m_start_address;
            cnt = 0;
         }
      }
   }
};

class simple_bus_master_direct
   : public sc_module
{
private:
   unsigned int m_address;
   int m_timeout;
   bool m_verbose;

public:
   sc_in_clk clock;
   sc_port<simple_bus_direct_if> bus_port;

   simple_bus_master_direct(sc_module_name name,
                            unsigned int address,
                            int timeout,
                            bool verbose = false)
      : sc_module(name)
      , m_address(address)
      , m_timeout(timeout)
      , m_verbose(verbose)
   {
      SC_HAS_PROCESS(simple_bus_master_direct);
      SC_THREAD(main_action);
   }

   void main_action()
   {
      int mydata[4];
      while(true)
      {
         bus_port->direct_read(&mydata[0], m_address);
         bus_port->direct_read(&mydata[1], m_address + 4);
         bus_port->direct_read(&mydata[2], m_address + 8);
         bus_port->direct_read(&mydata[3], m_address + 12);
         if(m_verbose)
         {
            fprintf(stdout,
                    "%08d %s : mem[%03x:%03x] = (%03x, %03x, %03x, %03x)\n",
                    static_cast<int>(sc_time_stamp().to_double()),
                    name(),
                    m_address,
                    m_address + 15,
                    mydata[0],
                    mydata[1],
                    mydata[2],
                    mydata[3]);
         }
         wait(m_timeout, SC_NS);
      }
   }
};

class simple_bus_slow_mem
   : public simple_bus_slave_if
   , public sc_module
{
private:
   std::vector<int> MEM;
   unsigned int m_start_address;
   unsigned int m_end_address;
   unsigned int m_nr_wait_states;
   int m_wait_count;

public:
   sc_in_clk clock;

   simple_bus_slow_mem(sc_module_name name,
                       unsigned int start_address,
                       unsigned int end_address,
                       unsigned int nr_wait_states)
      : sc_module(name)
      , m_start_address(start_address)
      , m_end_address(end_address)
      , m_nr_wait_states(nr_wait_states)
      , m_wait_count(-1)
   {
      SC_HAS_PROCESS(simple_bus_slow_mem);
      SC_METHOD(wait_loop);
      dont_initialize();
      sensitive << clock.pos();
      sc_assert(m_start_address <= m_end_address);
      sc_assert((m_end_address - m_start_address + 1) % 4 == 0);
      unsigned int size = (m_end_address - m_start_address + 1) / 4;
      MEM.reserve(size);
      for(unsigned int i = 0 ; i < size ; i++)
      {
         MEM.push_back(0);
      }
   }

   void wait_loop()
   {
      if(m_wait_count >= 0)
      {
         m_wait_count--;
      }
   }

   bool direct_read(int* data, unsigned int address)
   {
      *data = MEM.at((address - m_start_address) / 4);
      return true;
   }

   bool direct_write(int* data, unsigned int address)
   {
      MEM.at((address - m_start_address) / 4) = *data;
      return true;
   }

   simple_bus_status read(int* data, unsigned int address)
   {
      simple_bus_status status = SIMPLE_BUS_WAIT;
      if(m_wait_count < 0)
      {
         m_wait_count = m_nr_wait_states;
      }
      else if(m_wait_count == 0)
      {
         *data = MEM.at((address - m_start_address) / 4);
         status = SIMPLE_BUS_OK;
      }
      return status;
   }

   simple_bus_status write(int* data, unsigned int address)
   {
      simple_bus_status status = SIMPLE_BUS_WAIT;
      if(m_wait_count < 0)
      {
         m_wait_count = m_nr_wait_states;
      }
      else if(m_wait_count == 0)
      {
         MEM.at((address - m_start_address) / 4) = *data;
         status = SIMPLE_BUS_OK;
      }
      return status;
   }

   unsigned int start_address() const
   {
      return m_start_address;
   }

   unsigned int end_address() const
   {
      return m_end_address;
   }
};

class simple_bus_fast_mem
   : public simple_bus_slave_if
   , public sc_module
{
private:
   std::vector<int> MEM;
   unsigned int m_start_address;
   unsigned int m_end_address;

public:
   simple_bus_fast_mem(sc_module_name name,
                       unsigned int start_address,
                       unsigned int end_address)
      : sc_module(name)
      , m_start_address(start_address)
      , m_end_address(end_address)
   {
      sc_assert(m_start_address <= m_end_address);
      sc_assert((m_end_address - m_start_address + 1) % 4 == 0);
      unsigned int size = (m_end_address - m_start_address + 1) / 4;
      MEM.reserve(size);
      for(unsigned int i = 0 ; i < size ; i++)
      {
         MEM.push_back(0);
      }
   }

   bool direct_read(int* data, unsigned int address)
   {
      return(read(data, address) == SIMPLE_BUS_OK);
   }

   bool direct_write(int* data, unsigned int address)
   {
      return(write(data, address) == SIMPLE_BUS_OK);
   }

   simple_bus_status read(int* data, unsigned int address)
   {
      *data = MEM.at((address - m_start_address) / 4);
      return SIMPLE_BUS_OK;
   }

   simple_bus_status write(int* data, unsigned int address)
   {
      MEM.at((address - m_start_address) / 4) = *data;
      return SIMPLE_BUS_OK;
   }

   unsigned int start_address() const
   {
      return m_start_address;
   }

   unsigned int end_address() const
   {
      return m_end_address;
   }
};

class simple_bus_arbiter
   : public simple_bus_arbiter_if
   , public sc_module
{
private:
   bool m_verbose;

public:
   simple_bus_arbiter(sc_module_name name,
                      bool verbose = false)
      : sc_module(name)
      , m_verbose(verbose)
   {}

   simple_bus_request* arbitrate(const simple_bus_request_vec& requests)
   {
      simple_bus_request* best_request = 0;
      unsigned int i = 0;
      while(0 == best_request && i < requests.size())
      {
         if(requests[i]->status == SIMPLE_BUS_WAIT &&
            requests[i]->lock == SIMPLE_BUS_LOCK_SET)
         {
            if(m_verbose)
            {
               SC_REPORT_INFO("/accellera/examples", "rule 1");
            }
            best_request = requests[i];
         }
         else
         {
            i++;
         }
      }
      i = 0;
      while(0 == best_request && i < requests.size())
      {
         if(requests[i]->lock == SIMPLE_BUS_LOCK_GRANTED)
         {
            if(m_verbose)
            {
               SC_REPORT_INFO("/accellera/examples", "rule 2");
            }
            best_request = requests[i];
         }
         else
         {
            i++;
         }
      }
      if(0 == best_request)
      {
         best_request = requests[0];
         i = 1;
         while(i < requests.size())
         {
            sc_assert(requests[i]->priority != best_request->priority);
            if(requests[i]->priority < best_request->priority)
            {
               best_request = requests[i];
            }
            i++;
         }
         if(best_request->lock != SIMPLE_BUS_LOCK_NO)
         {
            best_request->lock = SIMPLE_BUS_LOCK_GRANTED;
         }
         if(m_verbose)
         {
            SC_REPORT_INFO("/accellera/examples", "rule 3");
         }
      }
      return best_request;
   }
};

class simple_bus_test
   : public sc_module
{
public:
   sc_clock C1;

   simple_bus_master_blocking     master_b;
   simple_bus_master_non_blocking master_nb;
   simple_bus_master_direct       master_d;
   simple_bus_slow_mem            mem_slow;
   simple_bus_fast_mem            mem_fast;
   simple_bus_arbiter             arbiter;
   simple_bus                     bus;

   simple_bus_test(sc_module_name name)
      : C1("C1")
      , master_b("master_b", 4, 0x4c, false, 300)
      , master_nb("master_nb", 3, 0x38, false, 20)
      , master_d("master_d", 0x78, 100, true)
      , mem_slow("mem_slow", 0x80, 0xff, 1)
      , mem_fast("mem_fast", 0x00, 0x7f)
      , arbiter("arbiter")
      , bus("bus")
   {
      master_d.clock(C1);
      bus.clock(C1);
      master_b.clock(C1);
      master_nb.clock(C1);
      mem_slow.clock(C1);
      master_d.bus_port(bus);
      master_b.bus_port(bus);
      master_nb.bus_port(bus);
      bus.arbiter_port(arbiter);
      bus.slave_port(mem_slow);
      bus.slave_port(mem_fast);
   }
};

int sc_main(int argc, char* argv[])
{
   try{
   simple_bus_test top("top");
   sc_start(10000, SC_NS);
   sc_stop();
   } catch(...)
   {
      std::cout << "exception\n";
   }
   return 0;
}
