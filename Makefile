CXXFLAGS = -std=c++17 -fPIC
CPPFLAGS = -DNDEBUG -I${mkBoostInc}
LDFLAGS = -L. -L${mkBoostLib}
LIBS = -lboost_system -lboost_filesystem -lboost_iostreams

all: main

main: main.o function.o 
	$(CXX) $(LDFLAGS) $(LIBS) main.o function.o -o main

main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I./ -c main.cpp

function.o: function.cpp function.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c function.cpp

clean:
	$(RM) *.o	result.dat

distclean: 
	$(RM) main
