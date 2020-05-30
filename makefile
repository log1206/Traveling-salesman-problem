all:TSP.cpp
	g++ TSP.cpp -o TSP.out -std=c++11
clean:
	rm -f TSP.out
.PHONY:clean