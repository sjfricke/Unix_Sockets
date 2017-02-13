/*
 * Simple TCP Socket client
 * Author: Spencer Fricke
 * 
 * To compile:
 *     gcc simple_tcp_socket_client.c -o client
 * 
 * To run pass <IP> <PORT> <MESSAGE>
 *     ./client 192.168.1.1 5000 a
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>

// wrapper for throwing error
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc , char *argv[]) {

  // first checks arguments
  if (argc < 4) {
    error("Need to pass IP, PORT, and message\n./client <IP_of_server> <PORT_on_server> <message>\n");
  }

  int socket_desc;
  struct sockaddr_in server;
  char* server_reply;
  char* hostIP = argv[1];
  int port = atoi(argv[2]);
  char* message = argv[3];
  int status;

  // allocate messages
  server_reply = (char*) malloc(sizeof(char) * 512);
  if (server_reply == NULL) { error("ERROR allocating message"); }
  
  // Create socket
  // AF_INET refers to the Internet Domain
  // SOCK_STREAM sets a stream to send data
  // 0 will have the OS pick TCP for SOCK_STREAM
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) { error ("Could not create socket"); }

  server.sin_addr.s_addr = inet_addr(hostIP); // sets IP of server
  server.sin_family = AF_INET; // uses internet address domain
  server.sin_port = htons(port); // sets PORT on server

  // Connect to remote server with socket
  status = connect(socket_desc, (struct sockaddr *)&server , sizeof(server));
  if (status < 0) { error("Connection error"); }

  puts("Connected\n");

  // sends message of only 1 byte
  status =  send(socket_desc , message , 1 , 0);
  if (status < 0) { error("Send failed"); }

  puts("Data Sent\n");

  //Receive a reply from the server
  status = recv(socket_desc, server_reply , 512, 0);
  if (status < 0) {
    puts("ERROR: Reply failed");
  } else {
    puts("Reply received:");
    puts(server_reply);
  }

  close(socket_desc);
  return EXIT_SUCCESS;
}
