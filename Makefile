CC = gcc
CFLAGS = -Wall -Werror

main: simpleTCP simpleUDP webSocket

simpleTCP:
	$(CC) simple_tcp/simple_tcp_socket_server.c $(CFLAGS) -o simple_tcp/server
	$(CC) simple_tcp/simple_tcp_socket_client.c $(CFLAGS) -o simple_tcp/client

simpleUDP:
	$(CC) simple_udp/simple_udp_socket_server.c $(CFLAGS) -o simple_udp/server
	$(CC) simple_udp/simple_udp_socket_client.c $(CFLAGS) -o simple_udp/client

webSocket:
	$(CC) web_socket/web_socket_server.c $(CFLAGS) -lpthread -o web_socket/server

clean:
	rm simple_tcp/server
	rm simple_tcp/client
	rm simple_udp/server
	rm simple_udp/client
	rm web_socket/server

