
CXX= g++ -std=c++17 -Wall 


SRC3 = launch_server.cpp server_engine.cpp
CFLAGS= -pthread



OBJ3= $(SRC3:.cpp=.o)

all  :	broadcast client
broadcast:   	$(HEAD) $(OBJ3)
		$(CXX) -o $@ $(OBJ3)



server_engine.o: server_engine.cpp server.h create_poll.hpp

launch_server.o: launch_server.cpp server.h create_poll.hpp

*.o	:	
	$(CXX) -c $< $(CFLAGS)


clean	:
		rm -rf *.o *.out client server

