/*
 * Simple TCP Socket client
 * Author: Spencer Fricke
 * 
 * To compile:
 *     gcc simple_tcp_socket_client.c -o client
 * 
 * To run pass <IP> <PORT>
 *     ./client 192.168.1.1 5000
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

#define MSG_SIZE 512

// wrapper for throwing error
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc , char *argv[]) {

  // first checks arguments
  if (argc < 3) {
    error("Need to pass IP and PORT\n./client <IP_of_server> <PORT_on_server>\n");
  }

  int socket_desc;
  struct sockaddr_in server;
  char* server_reply;
  char* hostIP = argv[1];
  int port = atoi(argv[2]);
  char message[MSG_SIZE]; // sets aside extra space to expand from single char
  int status;

  // allocate space for messages
  server_reply = (char*) malloc(sizeof(char) * 512);
  if (server_reply == NULL) { error("ERROR allocating server_reply"); }
  
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

  for (;;) { //runs forever  

    printf("Enter letter to send: ");
    scanf("%s", message); // gets user input
   
    // sends all data of MSG_SIZE bytes
    status =  send(socket_desc, message , MSG_SIZE, 0);
    if (status < 0) { error("Send failed\n"); }

    printf("Sent Message\n");

    //Receive a reply from the server
    status = recv(socket_desc, server_reply, MSG_SIZE, 0);
    if (status < 0) {
      error("ERROR: Reply failed\n");
    } else {
      printf("Reply received: %s\n\n", server_reply);
    }

  }
  
  close(socket_desc);    
  return 0;
}
