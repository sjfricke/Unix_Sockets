CC = gcc
CFLAGS = -Wall -Werror

main: simpleTCP simpleUDP

simpleTCP:
	$(CC) simple_tcp/simple_tcp_socket_server.c $(CFLAGS) -o simple_tcp/server
	$(CC) simple_tcp/simple_tcp_socket_client.c $(CFLAGS) -o simple_tcp/client

simpleUDP:
	$(CC) simple_udp/simple_udp_socket_server.c $(CFLAGS) -o simple_udp/server
	$(CC) simple_udp/simple_udp_socket_client.c $(CFLAGS) -o simple_udp/client

clean:
	rm simple_tcp/server
	rm simple_tcp/client
	rm simple_udp/server
	rm simple_udp/client
