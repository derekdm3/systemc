//! \file tri_state_test.cpp

#include "tri_state.hpp"

SC_MODULE(tri_state_driver)
{
   SC_HAS_PROCESS(tri_state_driver);

   sc_out<bool> ready;
   sc_out<bool> dina;
   sc_out<bool> dinb;

   tri_state_driver(sc_module_name)
   {
      SC_THREAD(prc_driver);
   }

   void prc_driver()
   {
      for(unsigned char pattern = 0 ; pattern < 0xf ; pattern++)
      {
         ready.write(pattern >> 2 & 1);
         dina.write(pattern >> 1 & 1);
         dinb.write(pattern & 1);
         wait(5, SC_NS);
      }
      sc_stop();
   }
};

SC_MODULE(tri_state_trace)
{
   sc_trace_file* trace_file;

   sc_in<bool> ready;
   sc_in<bool> dina;
   sc_in<bool> dinb;
   sc_in<sc_logic> selectx;

   tri_state_trace(sc_module_name)
   {
      trace_file = sc_create_vcd_trace_file("tri_state");
      if(trace_file)
      {
         //trace_file->set_time_unit(1, SC_NS);
         sc_trace(trace_file, ready, "ready");
         sc_trace(trace_file, dina, "dina");
         sc_trace(trace_file, dinb, "dinb");
         sc_trace(trace_file, selectx, "selectx");
      }
   }

   ~tri_state_trace()
   {
      if(trace_file)
      {
         sc_close_vcd_trace_file(trace_file);
      }
   }
};

int sc_main(int argc, char* argv[])
{
   tri_state ts0("ts0");
   tri_state_driver tsd0("tsd0");
   tri_state_trace tst0("tst0");

   sc_signal<bool> ready;
   sc_signal<bool> dina;
   sc_signal<bool> dinb;
   sc_signal<sc_logic> selectx;

   ts0.ready(ready);
   ts0.dina(dina);
   ts0.dinb(dinb);
   ts0.selectx(selectx);

   tsd0.ready(ready);
   tsd0.dina(dina);
   tsd0.dinb(dinb);

   tst0.ready(ready);
   tst0.dina(dina);
   tst0.dinb(dinb);
   tst0.selectx(selectx);

   sc_start(100, SC_NS);
   return 0;
}
