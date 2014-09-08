
MAINFILE=sort-main.cpp
MAINOBJ=$(MAINFILE:.cpp=.o)
CXX=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=-Wall -Wextra

main: $(MAINFILE)
	$(CXX) $(CFLAGS) $(MAINFILE)

num-list: make-num-list.cpp
	$(CXX) $(LDFLAGS) make-num-list.cpp -o make-num-list

%sort: %sort.o $(MAINOBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $<

clean:
	rm -f *.o *.d *~ core.*
