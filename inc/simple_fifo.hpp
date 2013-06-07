//! File: simple_fifo.hpp

#include <systemc.h>

class write_if
   : virtual public sc_interface
{
   public:
      virtual void write(char) = 0;
      virtual void reset() = 0;
};

class read_if
   : virtual public sc_interface
{
   public:
      virtual void read(char&) = 0;
      virtual int num_available() = 0;
};

class simple_fifo
   : public sc_channel
   , public write_if
   , public read_if
{
private:
   const static int MAX = 10;
   char data[MAX];
   int num_elements;
   int first;

   sc_event write_event;
   sc_event read_event;

public:
   simple_fifo(sc_module_name);

   void write(char c);
   void read(char& c);
   void reset();
   int num_available();
};
