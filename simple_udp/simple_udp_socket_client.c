/*
 * Simple UDP Socket client
 * Author: Spencer Fricke
 *
 * To compile:
 *     gcc simple_udp_socket_client.c -o client
 *
 * To run pass <IP> <PORT>
 *     ./client 192.168.1.1 5000
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 512

// wrapper for throwing error
void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {

  // first checks arguments
  if (argc < 3) {
    error("Need to pass IP and PORT\n./client <IP_of_server> <PORT_on_server>\n");
  }

  int mySocket; // holds ID of the socket
  struct sockaddr_in serv; // object of server to connect to
  unsigned int sockaddr_length = sizeof(struct sockaddr_in);
  char* server_reply;
  char* hostIP = argv[1];
  int port = atoi(argv[2]);
  char message[MSG_SIZE]; // sets aside extra space to expand from single char
  int status;// used to get function return values

  // allocate space for messages
  server_reply = (char*) malloc(sizeof(char) * MSG_SIZE);
  if (server_reply == NULL) { error("ERROR allocating server_reply"); }

  // Create socket
  // AF_INET refers to the Internet Domain
  // SOCK_DGRAM sets to datagram packets
  // 0 will have the OS pick UDP for SOCK_DGRAM
  mySocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mySocket < 0) { error ("Could not create socket"); }

  serv.sin_addr.s_addr = inet_addr(hostIP); // sets IP of server
  serv.sin_family = AF_INET; // uses internet address domain
  serv.sin_port = htons(port); // sets PORT on server

  for (;;) { // runs forever

    printf("Enter letter to send: ");
    scanf("%s", message); // gets user input

    // sends UDP packet to server
    status = sendto(mySocket, message, MSG_SIZE,0 , (const struct sockaddr *)&serv, sockaddr_length);
    if (status < 0) { error("Send failed\n"); }

    printf("Sent Message\n");

    // gets reply from server
    status = recvfrom(mySocket, server_reply, MSG_SIZE, 0, (struct sockaddr *)&serv, &sockaddr_length);
    if (status < 0) {
      error("ERROR: Reply failed\n");
    } else {
      printf("Reply received: %s\n\n", server_reply);
    }

  } // end forever loop

  close(mySocket);
  return 0;
}
