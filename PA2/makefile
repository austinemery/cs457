all:	PA2

PA2:	PA2.cpp	classes.o	classes.h
		g++ -std=c++11	PA2.cpp	classes.o	-g	-o	PA2

classes.o:	classes.cpp
		g++	-std=c++11 -c	classes.cpp	-g

clean:
		rm	-rf	*.o	PA2
