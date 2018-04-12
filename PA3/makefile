all:	PA3

PA3:	PA3.cpp	classes.o	classes.h
		g++	-std=c++11	PA3.cpp	classes.o	-g	-o	PA3

classes.o:	classes.cpp
		g++	-std=c++11	-c	classes.cpp	-g

clean:
		rm	-rf	*.o	PA3
