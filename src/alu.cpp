// File: alu.cpp

#include "alu.hpp"

alu::alu(sc_core::sc_module_name)
{
   SC_METHOD(prc_alu);
   sensitive
      << a
      << b
      << op;
}

void alu::prc_alu()
{
   switch(op.read())
   {
      case add:
         z = a.read() + b.read();
         break;
      case subtract:
         z = a.read() - b.read();
         break;
      case multiply:
         z = a.read() * b.read();
         break;
      case divide:
         z = a.read() / b.read();
         break;
      default:
         break;
   }
}
