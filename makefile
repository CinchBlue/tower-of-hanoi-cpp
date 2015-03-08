
CCC = g++
CCFLAGS = -ansi

hanoi: hmain.o hanoi.o 
	$(CCC) -o hanoi hanoi.o hmain.o

hanoi_it: hmain.o hanoi_it.o 
	$(CCC) -o hanoi_it hanoi_it.o hmain.o

hmain.o: hanoi.h 

hanoi.o: hanoi.h

clean:
	rm -f *.o

real_clean: clean
	rm -f hanoi hanoi_it
