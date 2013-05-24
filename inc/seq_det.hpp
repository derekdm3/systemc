// File: seq_det.hpp

#include <systemc.h>

SC_MODULE(seq_det)
{
   // just does typedef seq_det SC_CURRENT_USER_MODULE
   SC_HAS_PROCESS(seq_det);

   sc_in<bool> clk;
   sc_in<bool> data;

   sc_out<bool> seq_found;

   // synchronous logic
   void prc_seq_det();
   // combinatorial logic
   void prc_output();

   // interprocess communication
   sc_signal<bool> first;
   sc_signal<bool> second;
   sc_signal<bool> third;

   seq_det(sc_core::sc_module_name);
};
