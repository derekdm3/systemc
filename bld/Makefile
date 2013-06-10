CXX := g++
CXXFLAGS := -g -I../inc -I$(SYSTEMC)/include
LIBS := -lsystemc
LIBPATH := -L$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

all :

%.o : ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

full_adder_test_OBJS := full_adder_test.o full_adder_monitor.o full_adder_driver.o full_adder.o half_adder.o
full_adder_test.x : $(full_adder_test_OBJS)
	$(CXX) -o $@ $(full_adder_test_OBJS) $(LIBPATH) $(LIBS)
ripple_adder_test_OBJS := ripple_adder_test.o ripple_adder_monitor.o ripple_adder_driver.o ripple_adder.o full_adder.o half_adder.o
ripple_adder_test.x : $(ripple_adder_test_OBJS)
	$(CXX) -o $@ $(ripple_adder_test_OBJS) $(LIBPATH) $(LIBS)
basic_ff_test_OBJS := basic_ff_test.o basic_ff.o
basic_ff_test.x : $(basic_ff_test_OBJS)
	$(CXX) -o $@ $(basic_ff_test_OBJS) $(LIBPATH) $(LIBS)
seq_det_test_OBJS := seq_det_test.o seq_det.o
seq_det_test.x : $(seq_det_test_OBJS)
	$(CXX) -o $@ $(seq_det_test_OBJS) $(LIBPATH) $(LIBS)
tri_state_test_OBJS := tri_state_test.o tri_state.o
tri_state_test.x : $(tri_state_test_OBJS)
	$(CXX) -o $@ $(tri_state_test_OBJS) $(LIBPATH) $(LIBS)
simple_fifo_test_OBJS := simple_fifo_test.o simple_fifo.o
simple_fifo_test.x : $(simple_fifo_test_OBJS)
	$(CXX) -o $@ $(simple_fifo_test_OBJS) $(LIBPATH) $(LIBS)
simple_perf_test_OBJS := simple_perf_test.o simple_perf.o
simple_perf_test.x : $(simple_perf_test_OBJS)
	$(CXX) -o $@ $(simple_perf_test_OBJS) $(LIBPATH) $(LIBS)
simple_bus_test_OBJS := simple_bus_test.o simple_bus.o
simple_bus_test.x : $(simple_bus_test_OBJS)
	$(CXX) -o $@ $(simple_bus_test_OBJS) $(LIBPATH) $(LIBS)

clean :
	@$(RM) -f *.x; $(RM) -f *.o; $(RM) -f *.vcd; $(RM) -f *.log

distclean : clean
	@$(RM) -f ../inc/*~; $(RM) -f ../src/*~; $(RM) -f ../doc/*~; $(RM) -f *~

.PHONY : clean all distclean
