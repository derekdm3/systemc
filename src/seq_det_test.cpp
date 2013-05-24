// File: seq_det_test.cpp

#include <iostream>
#include "seq_det.hpp"

SC_MODULE(seq_det_driver)
{
   SC_HAS_PROCESS(seq_det_driver);

   sc_out<bool> clk;
   sc_out<bool> data;

   seq_det_driver(sc_core::sc_module_name)
   {
      SC_THREAD(prc_driver);
   }

   void prc_driver()
   {
      sc_uint<3> pattern;
      data.write(0);
      clk.write(0);
      pattern = 0;
      do
      {
         wait(5, SC_NS);
         pattern++;
         data.write(pattern[1]);
         clk.write(pattern[0]);
      }
      while(0x7 != pattern);
      wait(5, SC_NS);
      sc_stop();
   }
};

SC_MODULE(seq_det_monitor)
{
   SC_HAS_PROCESS(seq_det_monitor);

   sc_in<bool> data;
   sc_in<bool> clk;
   sc_in<bool> seq_found;

   seq_det_monitor(sc_core::sc_module_name)
   {
      SC_METHOD(prc_monitor);
      sensitive << data << clk << seq_found;
      std::cout
         << "  data"
         << "   clk"
         << " found"
         << std::endl;
   }

   void prc_monitor()
   {
      std::cout
         << "     " << data
         << "     " << clk
         << "     " << seq_found
         << std::endl;
   }
};

SC_MODULE(seq_det_trace)
{
   sc_trace_file* tracefile;

   sc_in<bool> data;
   sc_in<bool> clk;
   sc_in<bool> seq_found;

   seq_det_trace(sc_module_name)
   {
      if(tracefile = sc_create_vcd_trace_file("seq_det"))
      {
         tracefile->set_time_unit(1, SC_NS);
         sc_trace(tracefile, data, "data");
         sc_trace(tracefile, clk, "clk");
         sc_trace(tracefile, seq_found, "seq_found");
      }
   }

   ~seq_det_trace()
   {
      if(tracefile)
      {
         sc_close_vcd_trace_file(tracefile);
      }
   }
};

int sc_main(int argc, char* argv[])
{
   sc_signal<bool> data;
   sc_signal<bool> clk;
   sc_signal<bool> seq_found;

   seq_det sd0("sd0");
   seq_det_driver sdd0("sdd0");
   seq_det_trace sdt0("sdt0");
   seq_det_monitor sdm0("sdm0");

   sd0.data(data);
   sd0.clk(clk);
   sd0.seq_found(seq_found);

   sdd0.data(data);
   sdd0.clk(clk);

   sdm0.data(data);
   sdm0.clk(clk);
   sdm0.seq_found(seq_found);

   sdt0.data(data);
   sdt0.clk(clk);
   sdt0.seq_found(seq_found);

   // simulate for max 100 ns
   sc_start(100, SC_NS);
   return 0;
}
