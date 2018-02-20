all:	PA1

PA1:	PA1.cpp	table.o	table.h	database.o	database.h
		g++	PA1.cpp	table.o	database.o	-g	-o	PA1

table.o:	table.cpp
		g++	-c	table.cpp	-g

database.o:	database.cpp
		g++	-c	database.cpp	-g

clean:
		rm	-rf	*.o	PA1