// File: multiphase.cpp

#include "multiphase.hpp"

multiphase::multiphase(sc_core::sc_module_name)
{
   SC_METHOD(prc_rising);
   sensitive << zclk.pos();
   SC_METHOD(prc_falling);
   sensitive << zclk.neg();
}

void multiphase::prc_rising()
{
   e.write(d.read() & c.read());
}

void multiphase::prc_falling()
{
   d.write(a.read() & b.read());
}
