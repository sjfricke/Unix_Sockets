CC = gcc
CFLAGS = -Wall -Werror

main: TCP UDP MultiCast

TCP:
	$(CC) tcp/simple_tcp_socket_server.c $(CFLAGS) -o tcp/server
	$(CC) tcp/threaded_tcp_server.c $(CFLAGS) -lpthread -o tcp/server_threaded
	$(CC) tcp/simple_tcp_socket_client.c $(CFLAGS) -o tcp/client

UDP:
	$(CC) udp/simple_udp_socket_server.c $(CFLAGS) -o udp/server
	$(CC) udp/simple_udp_socket_client.c $(CFLAGS) -o udp/client

MultiCast:

clean:
	rm tcp/server
	rm tcp/server_threaded
	rm tcp/client
	rm udp/server
	rm udp/client

