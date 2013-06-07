//! \file simple_perf_test.cpp

#include "simple_perf.hpp"
#include <string>

class producer
   : public sc_core::sc_module
{
   public:
      sc_core::sc_port<write_if> out;

      producer(sc_core::sc_module_name name)
         : sc_module(name)
      {
         SC_HAS_PROCESS(producer);
         SC_THREAD(run);
      }

      void run()
      {
         for(char c = 'A' ; c <= 'Z' ; c++)
         {
            out->write(c);
         }
         wait(1, sc_core::SC_US);
      }
};

class consumer
   : public sc_core::sc_module
{
   public:
      sc_core::sc_port<read_if> in;

      consumer(sc_core::sc_module_name name)
         : sc_core::sc_module(name)
      {
         SC_HAS_PROCESS(consumer);
         SC_THREAD(run);
      }

      void run()
      {
         while(true)
         {
            char c[2];
            in->read(c[0]);
            c[1] = 0;
            SC_REPORT_WARNING("/accellera/examples", c);
            wait(100, sc_core::SC_NS);
         }
      }
};

class top
   : public sc_core::sc_module
{
   private:
      simple_perf simple_perf1;
      producer producer1;
      consumer consumer1;

   public:
      top(sc_core::sc_module_name name, int size)
         : sc_core::sc_module(name)
         , simple_perf1("simple_perf1", size)
         , producer1("producer1")
         , consumer1("consumer1")
      {
         producer1.out.bind(simple_perf1);
         consumer1.in.bind(simple_perf1);
      }
};

int sc_main(int argc, char* argv[])
{
   int size = (argc > 1) ? atoi(argv[1]) : 10;
   size = (size > 100000) ? 100000 : size;
   size = (size < 1) ? 1 : size;
   top top1("top1", size);
   sc_core::sc_start();
   sc_core::sc_stop();
   return 0;
}
