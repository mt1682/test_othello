main: main.o func.o disk.o
	g++ -Wall -O2 -o main main.o func.o disk.o

main.o: main.cpp
	g++ -c main.cpp 

func.o: func.cpp
	g++ -c func.cpp

disk.o: disk.cpp
	g++ -c disk.cpp
	
clean:
	rm -f hello disk.o main.o func.o