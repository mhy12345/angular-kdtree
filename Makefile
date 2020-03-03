target : shared_lib examples 

CFLAGS = -g

shared_lib : kdt_toolbox.so

kdt_toolbox.so : kdt_toolbox.o kdtree.o
	g++ -o kdt_toolbox.so -shared -fPIC kdt_toolbox.o kdtree.o

kdt_toolbox.o : kdt_toolbox.cpp
	g++ $(CFLAGS) kdt_toolbox.cpp -o kdt_toolbox.o -c -fPIC

kdtree.o : kdtree.cpp kdtree.h
	g++ $(CFLAGS) kdtree.cpp -o kdtree.o -c -fPIC

examples : examples.o kdtree.o kdt_toolbox.o
	g++ $(CFLAGS) examples.o kdtree.o kdt_toolbox.o -o examples

examples.o : examples.cpp
	g++ $(CFLAGS) examples.cpp -o examples.o -c

clean :
	rm *.o
	rm examples
	rm *.so
