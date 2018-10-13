OBJS=	Buckets.o HashTable.o Node.o normal_distr.o general_functions.o NN_search.o Range_search.o Euclidean_distance.o main.o
SOURCE=	./src/Buckets.cpp ./src/HashTable.cpp ./src/Node.cpp ./src/normal_distr.cpp ./src/general_functions.cpp ./src/NN_search.cpp ./src/Range_search.cpp ./src/Euclidean_distance.cpp ./src/main.cpp
HEADER=	./include.Buckets.h ./include/HashTable.h ./include/Node.h ./include/normal_distr.h ./include/general_functions.h ./include/NN_search.h ./include/Range_search.h ./include/Euclidean_distance.h
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

NN_search.o:	./src/NN_search.cpp
	$(CC) $(FLAGS) ./src/NN_search.cpp

Range_search.o:	./src/Range_search.cpp
	$(CC) $(FLAGS) ./src/Range_search.cpp

Euclidean_distance.o:	./src/Euclidean_distance.cpp
	$(CC) $(FLAGS) ./src/Euclidean_distance.cpp

main.o:	./src/main.cpp
	$(CC) $(FLAGS) ./src/main.cpp	

clean:	
	rm -rf output *.o