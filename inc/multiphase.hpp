// File: multiphase.hpp
// use the systemc library
#include <systemc.h>
// declare a systemc module
SC_MODULE(multiphase)
{
   // declare this module has a process
   SC_HAS_PROCESS(multiphase);
   // declare module inputs
   sc_in<bool> zclk;
   sc_in<bool> a;
   sc_in<bool> b;
   sc_in<bool> c;
   // declare module outputs
   sc_out<bool> e;
   // declare module internal states
   sc_signal<bool> d;
   // declare module initialization
   multiphase(sc_core::sc_module_name);
   // declare module processes
   void prc_rising();
   void prc_falling();
};
