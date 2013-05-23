// File: basic_ff_test.cpp

#include <iostream>
#include "basic_ff.hpp"

struct basic_ff_driver : sc_core::sc_module
{
   typedef basic_ff_driver SC_CURRENT_USER_MODULE;
   sc_out<bool> d;
   sc_out<bool> clk;

   basic_ff_driver(sc_core::sc_module_name)
   {
      SC_THREAD(prc_driver);
   }

   void prc_driver()
   {
      sc_uint<2> pattern;
      d.write(0);
      clk.write(0);
      pattern = 0;
      do
      {
         wait(5, SC_NS);
         pattern++;
         d.write(pattern[1]);
         clk.write(pattern[0]);
      }
      while(0x3 != pattern);
      wait(5, SC_NS);
      sc_stop();
   }
};

struct basic_ff_monitor : sc_core::sc_module
{
   typedef basic_ff_monitor SC_CURRENT_USER_MODULE;
   sc_in<bool> d;
   sc_in<bool> clk;
   sc_in<bool> q;

   basic_ff_monitor(sc_core::sc_module_name)
   {
      SC_METHOD(prc_monitor);
      sensitive << d << clk << q;
      std::cout
        << "   d"
        << " clk"
        << "   q"
        << std::endl;
   }

   void prc_monitor()
   {
      std::cout
         << "   " << d
         << "   " << clk
         << "   " << q
         << std::endl;
   }
};

int sc_main(int argc, char* argv[])
{
   sc_signal<bool> d;
   sc_signal<bool> clk;
   sc_signal<bool> q;

   basic_ff bff0("bff0");
   basic_ff_driver bffd0("bffd0");
   basic_ff_monitor bffm0("bffm0");

   bff0.d(d);
   bff0.clk(clk);
   bff0.q(q);

   bffd0.d(d);
   bffd0.clk(clk);

   bffm0.d(d);
   bffm0.clk(clk);
   bffm0.q(q);

   // simulate for max 100 ns
   sc_start(100, SC_NS);
   return 0;
}
