
MAINFILE=sort-main.cpp
MAINOBJ=$(MAINFILE:.cpp=.o)
CXX=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=-Wall -Wextra

main: $(MAINFILE)
	echo nope
	$(CXX) $(CFLAGS) $(MAINFILE)

%sort: %sort.o $(MAINOBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $<

clean:
	rm -f *.o *.d *~ core.* $(EXECUTABLE)
