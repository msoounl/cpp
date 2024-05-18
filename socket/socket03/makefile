all: test_server.cpp server.cpp test_client.cpp client.cpp
	g++ -o test_client test_client.cpp client.cpp -lpthread -std=c++11
	g++ -o test_server test_server.cpp server.cpp -lpthread -std=c++11
test_server: test_server.cpp server.cpp
	g++ -o test_server test_server.cpp server.cpp -lpthread -std=c++11
test_client: test_client.cpp client.cpp
	g++ -o test_client test_client.cpp client.cpp -lpthread -std=c++11

clean:
	rm test_server
	rm test_client
