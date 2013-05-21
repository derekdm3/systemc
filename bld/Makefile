CXX := g++
CXXFLAGS := -g -I../inc -I$(SYSTEMC)/include
LIBS := -lsystemc
LIBPATH := -L$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

full_adder_test_EXE := full_adder_test
ripple_adder_test_EXE := ripple_adder_test

full_adder_test_OBJS := full_adder_test.o full_adder_monitor.o full_adder_driver.o full_adder.o half_adder.o
ripple_adder_test_OBJS := ripple_adder_test.o ripple_adder_monitor.o ripple_adder_driver.o ripple_adder.o full_adder.o half_adder.o

all :

%.o : ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(full_adder_test_EXE) : $(full_adder_test_OBJS)
	$(CXX) -o $@ $(full_adder_test_OBJS) $(LIBPATH) $(LIBS)
$(ripple_adder_test_EXE) : $(ripple_adder_test_OBJS)
	$(CXX) -o $@ $(ripple_adder_test_OBJS) $(LIBPATH) $(LIBS)

clean :
	$(RM) -f \
	$(ripple_adder_test_OBJS) \
	$(full_adder_test_OBJS) \
	$(ripple_adder_test_EXE) \
	$(full_adder_test_EXE)

.PHONY : clean all
