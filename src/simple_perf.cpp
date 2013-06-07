//! File: simple_perf.cpp

#include "simple_perf.hpp"

simple_perf::simple_perf(sc_core::sc_module_name name, int size)
   : sc_core::sc_channel(name)
   , max_size(size)
{
   // noop
}

void simple_perf::write(char c)
{
   if(data.size() == max_size)
   {
      wait(read_event);
   }
   data.push_back(c);
   write_event.notify();
}

void simple_perf::reset()
{
   data.clear();
}

void simple_perf::read(char& c)
{
   if(data.empty())
   {
      wait(write_event);
   }
   c = data.front();
   data.erase(data.begin());
}

int simple_perf::num_available()
{
   return data.size();
}
