 EXEC = CS216PA3
 OBJECTS = Graph.o WordLadder.o main.o
 HEADERS = Graph.h WordLadder.h
$(EXEC) : $(OBJECTS)
	g++ $^ -o $@
%,o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm -i *.o $(EXEC)
