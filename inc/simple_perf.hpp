//! File: simple_perf.hpp

#include <systemc>
#include <vector>

class write_if
   : virtual public sc_core::sc_interface
{
   public:
      virtual void write(char) = 0;
      virtual void reset() = 0;
};

class read_if
   : virtual public sc_core::sc_interface
{
   public:
      virtual void read(char&) = 0;
      virtual int num_available() = 0;
};

class simple_perf
   : public sc_core::sc_channel
   , public write_if
   , public read_if
{
public:
   simple_perf(sc_core::sc_module_name, int);
   void write(char);
   void reset();
   void read(char&);
   int num_available();
private:
   std::vector<char> data;
   int max_size;
   sc_core::sc_event write_event;
   sc_core::sc_event read_event;
};
