
MAINFILE=sort-main.cpp
MAINOBJ=$(MAINFILE:.cpp=.o)
CXX=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=-Wall -Wextra

main: $(MAINFILE)
	$(CXX) $(CFLAGS) $(MAINFILE)

num-list: make-num-list.cpp
	$(CXX) $(LDFLAGS) make-num-list.cpp -o make-num-list

timing-stats: get-timing-stats.o program-output.o timing-data.o
	$(CXX) $(LDFLAGS) -lboost_program_options -lboost_filesystem -lboost_system get-timing-stats.o program-output.o timing-data.o -o get-timing-stats

%sort: %sort.o $(MAINOBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $<

clean:
	rm -f *.o *.d *~ core.*
