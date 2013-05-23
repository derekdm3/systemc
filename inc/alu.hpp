// File: alu.hpp

#include <systemc.h>

struct alu : sc_core::sc_module
{
   typedef alu SC_CURRENT_USER_MODULE;

   const static int WORD = 2;

   enum op_type { add, subtract, multiply, divide };

   sc_in<sc_uint<WORD> > a;
   sc_in<sc_uint<WORD> > b;

   sc_in<op_type> op;

   sc_out<sc_uint<WORD> > z;

   alu(sc_core::sc_module_name);

   void prc_alu();
};
