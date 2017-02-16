# Unix Sockets

* A collection of different sockets written in C

## Socket Types
* [Simple TCP Sockets](https://github.com/sjfricke/Unix_Sockets/tree/master/simple_tcp)
  * Both a server and client program to send a TCP message
* [Simple UDP Sockets](https://github.com/sjfricke/Unix_Sockets/tree/master/simple_udp)
  * Both a server and client program to send a UDP message
  
## How To Run
* First clone the repo: `git clone https://github.com/sjfricke/Unix_Sockets.git`
* Run the make file `make`
* Each sample will now have a `client` and `server` program
  * Run the server by going `./server [port]`
	* port is optional, default to 5000 if not passed
  * Run the client application `./client <server_ip> <port>`
	* **NOTE:** I only tested this on a set of two different devices, internal device connection may vary
