//! File: simple_fifo_tb.cpp

#include <systemc.h>
#include "simple_fifo.hpp"

class producer
   : public sc_module
{
   public:
      SC_HAS_PROCESS(producer);
      sc_port<write_if> out;

      producer(sc_module_name name)
         : sc_module(name)
      {
         SC_THREAD(main);
      }

      void main()
      {
         for(char i = 'A' ; i <= 'Z' ; i++)
         {
            out->write(i);
         }
      }
};

class consumer
   : public sc_module
{
   public:
      SC_HAS_PROCESS(consumer);
      sc_port<read_if> in;

      consumer(sc_module_name name)
         : sc_module(name)
      {
         SC_THREAD(main);
      }

      void main()
      {
         char c;
         std::cout << std::endl << std::endl;
         while(true)
         {
            in->read(c);
            std::cout << c << std::endl << std::flush;
            if(1 == in->num_available() ||
               9 == in->num_available())
            {
               std::cout << "<" << in->num_available() << ">\n" << std::flush;
            }
         }
      }
};

int sc_main(int argc, char* argv[])
{
   simple_fifo f("f");
   producer p("p");
   consumer c("c");

   p.out(f);
   c.in(f);

   sc_start();
   return 0;
}
