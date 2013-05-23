// File: xor_gates.cpp

#include "xor_gates.hpp"

xor_gates::xor_gates(sc_core::sc_module_name)
{
   SC_METHOD(prc_xor_gates);
   sensitive << bre << sty;
}

void xor_gates::prc_xor_gates()
{
   tap = bre.read() ^ sty.read();
}
