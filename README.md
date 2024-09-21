# TCP Echo Server and Client

This repository contains a simple TCP echo server and client application implemented in C. The server is capable of handling multiple clients using the forking concept.

## Requirements

- A C compiler (e.g., GCC)
- Git (to clone the repository)
- Access to a terminal

## Getting Started

### Cloning the Repository

To get started, clone the repository to your local machine:

```bash
git clone https://github.com/aabdurrohim/tcp-echo-server.git
cd tcp-echo-server
```

## Building the Application
### Navigate to the project directory and compile the server and client:
```bash
gcc server_fork.c -o server_fork
gcc client_fork.c -o client_fork
```

## Running the Server
Open a terminal window and navigate to the directory where the server binary is located.
Run the server by specifying a port number (e.g., 8080):
```bash
./server_fork <PORT>
```
The server will start listening for incoming client connections.

## Running the Client
1. Open another terminal window.
2. Navigate to the directory where the client binary is located.
3. Run the client by specifying the server's IP address and the port number. Replace server_ip with the actual server IP address:
```bash
./client_fork <SERVER_IP> <PORT>
```

## Display Server and Client Processes with **netstat** or **ps**
Use the **netstat** command to view active connections. On the server, run:
```bash
netstat -anp | grep <PORT>
```
This will display all active connections on port <PORT> (server port).

**ps:**
To see the server and client processes, run on each terminal:
```bash
ps aux | grep server
ps aux | grep client
```

