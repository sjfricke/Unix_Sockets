CC = gcc
CFLAGS = -Wall -Werror

main: simpleTCP

simpleTCP:
	$(CC) simple_tcp/simple_tcp_socket_server.c $(CFLAGS) -o simple_tcp/server
	$(CC) simple_tcp/simple_tcp_socket_client.c $(CFLAGS) -o simple_tcp/client

clean:
	rm simple_tcp/server
	rm simple_tcp/client
