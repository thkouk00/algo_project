all:
	(cd ./LSH ; make)
	(cd ./Hypercube ; make)

clean:	
	(cd ./LSH ; make clean)
	(cd ./Hypercube ; make clean)