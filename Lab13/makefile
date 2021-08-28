EXEC = Lab12
OBJECTS = Graph.o Lab12.o
		  #(listing all of your object files here, separated by space)
HEADERS = Graph.h WordLadder.h
		  #(listing all header files here, separated by spaces)
TEST = testWordLadder
TESTOBJS = testWordLadder.o WordLadder.o Graph.o
		  #(listing all of your object files here, separated by space)
$(EXEC) : $(OBJECTS)
	g++ $^ -o $@i
$(TEST): $(TESTOBJS)
	g++ $^ -o $@
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
clean:
	rm -i *.o
	rm -i `find ./ -type f -executable`
