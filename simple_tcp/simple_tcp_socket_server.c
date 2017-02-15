/*
 * Simple TCP Socket server
 * Author: Spencer Fricke
 * 
 * To compile:
 *     gcc simple_tcp_socket_server.c -o server
 * 
 * To run
 *     ./server <optional_port_number>
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

#define DEFAULT_PORT 5000
#define MSG_SIZE 512

// wrapper for throwing error
void error(char *msg) {
    perror(msg);
    exit(1);
}

// holds counter data of mesages
struct message_counter {
  int a_count;
  int b_count;
  int c_count;
  char a;
  char b;
  char c;
} message_counter; 

int main(int argc, char *argv[]) {

  char* receiveMsg;
  char returnMsg[] = "message received";
  int msgSize; // used to store incoming message size
  int status; // used to check status of c functions
  int port;

  // see if passed port in argument
  if (argc == 2) {
    port = atoi(argv[1]);
  } else {
    port = DEFAULT_PORT;
  }

  struct message_counter counter = {0,0,0,'a','b','c'}; // used to keep track of messages
    
  struct sockaddr_in dest; // socket info about the machine connecting to us
  struct sockaddr_in serv; // socket info about our server
  int mySocket;            // socket used to listen for incoming connections
  int consocket;           // used to hold status of connect to socket 
  socklen_t socksize = sizeof(struct sockaddr_in);
  
  // allocates size for receive message
  receiveMsg = malloc(sizeof(char) * MSG_SIZE); // max chars for sending data 
  if (receiveMsg == NULL) { error("ERROR: receiveMsg allocation"); }

  memset(&serv, 0, sizeof(serv)); // zero the struct before filling the fields
  serv.sin_family = AF_INET; // set to use Internet address family
  serv.sin_addr.s_addr = htonl(INADDR_ANY); // set our local IP address
  serv.sin_port = htons(port); // set the server port number

  // creates the socket
  // AF_INET refers to the Internet Domain
  // SOCK_STREAM sets a stream to send data
  // 0 will have the OS pick TCP for SOCK_STREAM
  mySocket = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket Created! \n");

  // bind serv information to mySocket
  status = bind(mySocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

  // checks for TIME_WAIT socket
  // when daemon is closed there is a delay to make sure all TCP data is propagated 
  if (status < 0) {
    printf("ERROR opening socket: %d , possible TIME_WAIT\n", status);
    printf("USE: netstat -ant|grep %d to find out\n", port);
    exit(1);
  } else {
    printf("Socket Binded!\n");
  }
  
  // start listening, allowing a queue of up to 1 pending connection
  listen(mySocket, 1);
  printf("Socket Listening on port %d!\n", port);

  // prevents daemon from closing on a closed client
  signal(SIGPIPE, SIG_IGN);
  
  for (;;) { // keeps daemon running forever

    // blocks until a TCP handshake is made
    consocket = accept(mySocket, (struct sockaddr *)&dest, &socksize);

    // a connection has been been received can see the client IP
    printf("Incoming connection from %s \n", inet_ntoa(dest.sin_addr));
    msgSize = 1;
    
    // main loop to wait for a request
    while(consocket && msgSize > 0) {

      printf("recv %d\tstatus %d\tconsocket %d\n", msgSize, status, consocket);
      
      // used to get the message of length MSG_SIZE
      msgSize = recv(consocket, receiveMsg, MSG_SIZE , 0);
      if (msgSize < 0) { error("ERROR on recv"); }
      
      printf("Client sent the character: %s\n", receiveMsg);

      // adds to message counter if one of the accepted letters
      if (receiveMsg[0] == counter.a) { 
	counter.a_count++;
      } else if (receiveMsg[0] == counter.b) {
	counter.b_count++;
      } else if (receiveMsg[0] == counter.c) {
	counter.c_count++;
      }
	
      printf("Current Count\n\tA: %d\n\tB: %d\n\tC: %d\n", counter.a_count, counter.b_count, counter.c_count);

      //clears receive message
      bzero(receiveMsg, MSG_SIZE);

      //sends back response message
      status = send(consocket, returnMsg, strlen(returnMsg), 0);
      if (status < 0) {
	consocket = 0; // ends for loop
	close(consocket); // ends current TCP connection
	puts("client dropped connection");
      }
      
    } //connection while loop

  } // forever for loop

  // clean up on close
  printf("\nClosing Socket\n");
  free(receiveMsg);
  close(mySocket);
  return EXIT_SUCCESS;
}
