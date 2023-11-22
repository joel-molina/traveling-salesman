salesman: driver.o
	g++ -o salesman driver.o

driver.o: driver.cpp
	g++ -c driver.cpp

clean:
	rm *.o salesman
