# Simple TCP Echo Server and Client with Timestamp

- [Simple TCP Echo Server and Client with Timestamp](#simple-tcp-echo-server-and-client-with-timestamp)
  - [Project Description](#project-description)
  - [Server](#server)
    - [Description](#description)
  - [Client](#client)
    - [Description](#description-1)
  - [Compilation and Usage](#compilation-and-usage)
  - [Order to run the two server-client commands](#order-to-run-the-two-server-client-commands)
  - [Note](#note)

## Project Description
This project was made for assignment purposes for CSCD58 @ University Of Toronto

This project consists of a simple TCP server and a TCP client. The server listens for incoming connections and echoes back any received message appended with the current timestamp. The client can connect to the server, send messages, and receive the echoed messages with timestamps.

## Server

### Description

The server listens on a predefined port (configurable within the client and server source files) and waits for incoming client connections. Upon establishing a connection, it enters into a communication loop where the server receives messages from the connected client, adds the current timestamp to each received message, and sends it back to the client. The communication continues until the client sends the message "Ciao-Ciao", letting the server known to close the connection.

## Client

### Description

The client takes the server IP address as a command-line argument and attempts to connect to the server on the predefined port. Upon establishing a connection, it enters into a communication loop where it sends messages to the server and receives the echoed messages with timestamps. The server will keep the connection “alive” until the word ``Ciao-Ciao`` is entered by the client

## Compilation and Usage


To compile the server code, navigate to the directory containing the server source file and run:

```sh
gcc server.c -o server
```

To execute the compiled server binary, run:

```sh
./server
```

The server will start listening for incoming connections on port 9999.

To compile the client code, navigate to the directory containing the client source file and run:

```sh
gcc client.c -o client
```

To execute the compiled client binary, run:

```sh
./client <Server IP Address>
```

Where `<Server IP Address>` with the actual IP address of the server (ex: ``127.0.0.1`` if the server is run on the same IP as the client).

## Order to run the two server-client commands

1. Start the server by running the compiled server binary.
2. Start the client by running the compiled client binary with the server's IP address.
3. The client will prompt the user to enter a message. Type a message and press Enter to send it to the server. See [Note](#note) for information about input.
4. The server will respond with the sent message with the current timestamp that the message was read by the server.
5. Repeat steps 3, 4 to continue the communication between the server and the client
6. To end the communication, type "Ciao-Ciao" at the client prompt and press Enter. The server will close the connection, and both the client and server will terminate.

## Note

- Make sure that the server is running and reachable from the client machine and that there are no firewall rules blocking the communication on the used port (9999 by default). 
- If one chooses to change the port of the server, you must ensure that the port (`SERVER_PORT` variable) in the client and server match. 
- If one chooses to change the max line length for the buffer, you must ensure that the buffer length (`MAX_LINE` variable) in the client and server match.