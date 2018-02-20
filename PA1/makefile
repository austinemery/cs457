all:	PA1

PA1:	database.cpp	table.o	table.h
		g++	database.cpp	table.o	-g	-o	PA1

table.o:	table.cpp
		g++	-c	table.cpp	-g

clean:
		rm	-rf	*.o	PA1