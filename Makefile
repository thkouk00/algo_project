OBJS=	Buckets.o HashTable.o Node.o normal_distr.o general_functions.o main.o
SOURCE=	./src/Buckets.cpp ./src/HashTable.cpp ./src/Node.cpp ./src/normal_distr.cpp ./src/general_functions.cpp ./src/main.cpp
HEADER=	./include.Buckets.h ./include/HashTable.h ./include/Node.h ./include/normal_distr.h ./include/general_functions.h 
CC=	g++
FLAGS=	-c

all: $(OBJS)
	$(CC) -g3 -o lsh $(OBJS) 

Buckets.o:	./src/Buckets.cpp
	$(CC) $(FLAGS) ./src/Buckets.cpp

HashTable.o:	./src/HashTable.cpp
	$(CC) $(FLAGS) ./src/HashTable.cpp

Node.o:	./src/Node.cpp
	$(CC) $(FLAGS) ./src/Node.cpp

normal_distr.o:	./src/normal_distr.cpp
	$(CC) $(FLAGS) ./src/normal_distr.cpp

general_functions.o:	./src/general_functions.cpp
	$(CC) $(FLAGS) ./src/general_functions.cpp

main.o:	./src/main.cpp
	$(CC) $(FLAGS) ./src/main.cpp	

clean:	
	rm -rf output *.o