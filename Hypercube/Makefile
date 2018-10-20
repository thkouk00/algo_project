OBJS=	Buckets.o HashTable.o Node.o normal_distr.o general_functions.o NN_search.o Range_search.o Distance.o cube_main.o
SOURCE=	./LSH/src/Buckets.cpp ./LSH/src/HashTable.cpp ./LSH/src/Node.cpp ./LSH/src/normal_distr.cpp ./LSH/src/general_functions.cpp ./LSH/src/NN_search.cpp ./LSH/src/Range_search.cpp ./LSH/src/Distance.cpp ./LSH/src/cube_main.cpp
HEADER=	./LSH/include.Buckets.h ./LSH/include/HashTable.h ./LSH/include/Node.h ./LSH/include/normal_distr.h ./LSH/include/general_functions.h ./LSH/include/NN_search.h ./LSH/include/Range_search.h ./LSH/include/Distance.h
CC=	g++
FLAGS=	-c

all: $(OBJS)
	$(CC) -g3 -o cube $(OBJS)

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

Distance.o:	./src/Distance.cpp
	$(CC) $(FLAGS) ./src/Distance.cpp

cube_main.o:	./src/cube_main.cpp
	$(CC) $(FLAGS) ./src/cube_main.cpp


clean:	
	rm -rf lsh output* *.o
