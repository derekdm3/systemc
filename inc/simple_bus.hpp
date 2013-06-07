//! \file simple_bus.hpp

#ifndef __simple_bus_hpp
#define __simple_bus_hpp

#include <systemc>
#include <vector>

typedef enum simple_bus_status
{
   SIMPLE_BUS_OK = 0,
   SIMPLE_BUS_REQUEST,
   SIMPLE_BUS_WAIT,
   SIMPLE_BUS_ERROR
} simple_bus_status;

typedef enum simple_bus_lock_status
{
   SIMPLE_BUS_LOCK_NO = 0,
   SIMPLE_BUS_LOCK_SET,
   SIMPLE_BUS_LOCK_GRANTED
} simple_bus_lock_status;

class simple_bus_request
{
   public:
      // parameters
      unsigned int priority;
      // request parameters
      bool do_write;
      unsigned int address;
      unsigned int end_address;
      int* data;
      simple_bus_lock_status lock;
      // request status
      sc_core::sc_event transfer_done;
      simple_bus_status status;
      // default constructor
      simple_bus_request()
         : priority(0)
         , do_write(false)
         , address(0)
         , end_address(0)
         , data(reinterpret_cast<int*>(0))
         , lock(SIMPLE_BUS_LOCK_NO)
         , status(SIMPLE_BUS_OK)
      {
      }
};

typedef std::vector<simple_bus_request*> simple_bus_request_vec;

class simple_bus_direct_if
   : public virtual sc_core::sc_interface
{
   public:
      virtual bool direct_read(int* data, unsigned int address) = 0;
      virtual bool direct_write(int* data, unsigned int address) = 0;
};

class simple_bus_non_blocking_if
   : public virtual sc_core::sc_interface
{
   public:
      virtual void read(unsigned int unique_priority,
                        int* data,
                        unsigned int address,
                        bool lock = false) = 0;
      virtual void write(unsigned int unique_priority,
                         int* data,
                         unsigned int address,
                         bool lock = false) = 0;
      virtual simple_bus_status get_status(unsigned int unique_priority) = 0;
};

class simple_bus_blocking_if
   : public virtual sc_core::sc_interface
{
      virtual simple_bus_status burst_read(unsigned int unique_priority,
                                           int* data,
                                           unsigned int start_address,
                                           unsigned int length = 1,
                                           bool lock = false) = 0;
      virtual simple_bus_status burst_write(unsigned int unique_priority,
                                            int* data,
                                            unsigned int start_address,
                                            unsigned int length = 1,
                                            bool lock = false) = 0;
};

class simple_bus_arbiter_if
   : public virtual sc_core::sc_interface
{
   public:
      virtual simple_bus_request*
      arbitrate(const simple_bus_request_vec& requests) = 0;
};

class simple_bus_slave_if
   : public simple_bus_direct_if
{
   public:
      virtual simple_bus_status read(int* data, unsigned int address) = 0;
      virtual simple_bus_status write(int* data, unsigned int address) = 0;

      virtual unsigned int start_address() const = 0;
      virtual unsigned int end_address() const = 0;
};

class simple_bus
   : public simple_buf_direct_if
   , public simple_bus_non_blocking_if
   , public simple_bus_blocking_if
   , public sc_module
{
private:
   bool m_verbose;
   simple_bus_request_vec m_requests;
   simple_bus_request* m_current_request;

   void handle_request();
   void end_of_elaboration();
   simple_bus_slave_if* get_slave(unsigned int address);
   simple_bus_request* get_request(unsigned int priority);
   simple_bus_request* get_next_request();
   void clear_locks();

public:
   sc_core::sc_in_clk clock;
   sc_core::sc_port<simple_bus_arbiter_if> arbiter_port;
   sc_core::sc_port<simple_bus_slave_if, 0> slave_port;
   
   simple_bus(sc_module_name name, bool verbose = false);
   void main_action();
   bool direct_read(int* data, unsigned int address);
   bool direct_write(int* data, unsigned int address);

   void read(unsigned int unique_priority,
             int* data,
             unsigned int address,
             bool lock = false);
   void write(unsigned int unique_priority,
              int* data,
              unsigned int address,
              bool lock = false);
   simple_bus_status get_status(unsigned int unique_priority);
   simple_bus_status burst_read(unsigned int unique_priority,
                                int* data,
                                unsigned int start_address,
                                unsigned int length = 1,
                                bool lock = false);
   simple_bus_status burst_write(unsigned int unique_priority,
                                int* data,
                                unsigned int start_address,
                                unsigned int length = 1,
                                bool lock = false);
};

#endif
