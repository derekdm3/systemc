//! File: simple_fifo.cpp

#include "simple_fifo.hpp"

simple_fifo::simple_fifo(sc_core::sc_module_name name)
   : sc_channel(name)
   , num_elements(0)
   , first(0)
{
   // noop
}

void simple_fifo::write(char c)
{
   if(MAX == num_elements)
   {
      wait(read_event);
   }
   data[(first + num_elements) % MAX] = c;
   num_elements++;
   write_event.notify();
}

void simple_fifo::read(char& c)
{
   if(0 == num_elements)
   {
      wait(write_event);
   }
   c = data[first];
   num_elements--;
   first = (first + 1) % MAX;
   read_event.notify();
}

void simple_fifo::reset()
{
   num_elements = first = 0;
}

int simple_fifo::num_available()
{
   return num_elements;
}
