CPP = c++
INCLUDE = -I/usr/local/include/cc++2
LIBDIR = 
LIBS = -lccgnu2 -lpthread -ldl
CFLAGS = -O

OBJECTS = \
  Clock.o \
  ClockClient.o \
  ClockPacket.o \
  ClockServer.o \
  ConfigReader.o \
  Exceptions.o \
  PhaseLockedClock.o \
  SystemClock.o \
  Timestamp.o \
  VariableFrequencyClock.o \
  clockkit.o

all: $(OBJECTS) ckserver ckphaselock tcl ruby python

# To test, run "./ckserver 4444" in one window, and in other windows run
# ckphaselock ckphaselock.py ckphaselock.rb and/or ckphaselock.tcl.

tcl: clockkit_tcl.so
python: _clockkit.so
ruby: clockkit.so

ckserver: ClockServerMain.o $(OBJECTS)
	$(CPP) $(CFLAGS) $(LIBS) $^ -o ckserver

ckphaselock: PhaseLockMain.o $(OBJECTS)
	$(CPP) $(CFLAGS) $(LIBS) $^ -o ckphaselock

clockkit_tcl_wrap.c:
	swig -tcl -o $@ clockkit.h
clockkit_tcl.so: clockkit_tcl_wrap.o $(OBJECTS)
	$(CPP) $(CFLAGS) $(LIBS) -shared -o $@ $?


clockkit_ruby_wrap.c:
	swig -ruby -o /tmp/clockkit.tmp clockkit.h
	sed -e "s/ _wrap_ck/ (VALUE (*)(...))_wrap_ck/" /tmp/clockkit.tmp > $@
# prepend the cast (VALUE (*)(...)) to _wrap* in lines starting with rb_define_module_function
# ruby needs foo.so to be the same name as the module Foo,
# hence clockkit.so not clockkit_ruby.so
clockkit_ruby_wrap.o: clockkit_ruby_wrap.c
	$(CPP) -c $(CFLAGS) $(INCLUDE) -I/usr/local/src/ruby-1.8.1/ $?
clockkit.so: clockkit_ruby_wrap.o $(OBJECTS)
	$(CPP) $(CFLAGS) $(LIBS) -shared -o $@ \
               $(OBJECTS) clockkit_ruby_wrap.o

clockkit_python_wrap.c:
	swig -python -o $@ clockkit.h
clockkit_python_wrap.o: clockkit_python_wrap.c
	$(CPP) -c $(CFLAGS) $(INCLUDE) -I/usr/include/python2.3 $?
_clockkit.so: clockkit_python_wrap.o $(OBJECTS)
	$(CPP) $(CFLAGS) $(LIBS) -shared -o $@ $?
# bug: if ruby's clockkit.so exists, ckphaselock.py uses it instead of _clockkit.so.

docs:
	doxygen doxygen.conf

clean:
	rm -rf *.o ckserver ckphaselock docs doxygen.warn *.pyc clockkit_*_wrap.c *clockkit*.so clockkit.py

# Compilation rule:
.cpp.o:
	$(CPP) -c $(CFLAGS) $(INCLUDE) $< 

.c.o:
	$(CPP) -c $(CFLAGS) $(INCLUDE) $<
