OBJS=	general_functions.o cube_main.o
SOURCE=	./src/general_functions.cpp ./src/cube_main.cpp
HEADER=	./include/general_functions.h
CC=	g++
FLAGS=	-c

all: $(OBJS) 
	$(CC) -g3 -o cube $(OBJS) 

general_functions.o:	./src/general_functions.cpp
	$(CC) $(FLAGS) ./src/general_functions.cpp

cube_main.o:	./src/cube_main.cpp
	$(CC) $(FLAGS) ./src/cube_main.cpp	

clean:	
	rm -rf cube output* *.o
