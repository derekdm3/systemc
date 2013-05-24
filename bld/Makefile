CXX := g++
CXXFLAGS := -g -I../inc -I$(SYSTEMC)/include
LIBS := -lsystemc
LIBPATH := -L$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

full_adder_test_EXE := full_adder_test.x
ripple_adder_test_EXE := ripple_adder_test.x
basic_ff_test_EXE := basic_ff_test.x
seq_det_test_EXE := seq_det_test.x

full_adder_test_OBJS := full_adder_test.o full_adder_monitor.o full_adder_driver.o full_adder.o half_adder.o
ripple_adder_test_OBJS := ripple_adder_test.o ripple_adder_monitor.o ripple_adder_driver.o ripple_adder.o full_adder.o half_adder.o
basic_ff_test_OBJS := basic_ff_test.o basic_ff.o
seq_det_test_OBJS := seq_det_test.o seq_det.o

all :

%.o : ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(full_adder_test_EXE) : $(full_adder_test_OBJS)
	$(CXX) -o $@ $(full_adder_test_OBJS) $(LIBPATH) $(LIBS)
$(ripple_adder_test_EXE) : $(ripple_adder_test_OBJS)
	$(CXX) -o $@ $(ripple_adder_test_OBJS) $(LIBPATH) $(LIBS)
$(basic_ff_test_EXE) : $(basic_ff_test_OBJS)
	$(CXX) -o $@ $(basic_ff_test_OBJS) $(LIBPATH) $(LIBS)
$(seq_det_test_EXE) : $(seq_det_test_OBJS)
	$(CXX) -o $@ $(seq_det_test_OBJS) $(LIBPATH) $(LIBS)

clean :
	$(RM) -f *.x; $(RM) -f *.o

.PHONY : clean all
