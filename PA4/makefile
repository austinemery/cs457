all:	PA4

PA4:	PA4.cpp	classes.o	classes.h
		g++	-std=c++11	PA4.cpp	classes.o	-g	-o	PA4

classes.o:	classes.cpp
		g++	-std=c++11	-c	classes.cpp	-g

clean:
		rm	-rf	*.o	PA4