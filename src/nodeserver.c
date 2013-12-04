/*
 * node.c
 *
 *  Created on: Dec 1, 2013
 *      Author: Anil Jangam
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "pastrynode.h"
#include "nodeserver.h"
#include "common.h"
#include "pastrynetwork.h"

void NodeServerFunction(PastryNode pNode) {

	PastryNode node;
	struct sockaddr_in socketInfo;
	struct hostent *hPtr;
	unsigned int nodeId = 0;
	int socketHandle = 0;
	int bytesRecv = 0;
	char buffer[10241];
	char command[CMDSIZE+1];
	char fileName[CMDSIZE+1];

	strcpy(node.HostName, pNode.HostName);
	node.NodeId = pNode.NodeId;
	node.PortNumber = pNode.PortNumber;

	// Initialize the node state.
	PopulateFirstNodeState(&node);

	// Dump the state info to log file.
	buildLogFileName(fileName, node.NodeId);
	printf("SERVER: Display log file is: [%s]\n", fileName);
	removeExistingLogFile(fileName);
	PrintNodeStateToFile(fileName, &node);

	//signal(SIGCHLD, handleSig);
	printf("SERVER: Hello World! It's me, Node Id # %d Port Number %d!\n", node.NodeId, node.PortNumber);

	// Clear structure memory
	memset(&socketInfo, 0x0, sizeof(socketInfo));

	// Get the name of this computer we are running on
	gethostname(node.HostName, MAXHOSTNAME);
	if ((hPtr = gethostbyname(node.HostName)) == NULL) {
		printf("SERVER: System host name misconfigured.\n");
		exit(EXIT_FAILURE);
	}

	// create socket
	if ((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		close(socketHandle);
		exit(EXIT_FAILURE);
	} else {
		printf("SERVER: Success: Server socket creation.\n");
	}

	// Load system information into socket data structures
	// Use any address available to the system
	// Set port number
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_addr.s_addr = htonl(INADDR_ANY);
	socketInfo.sin_port = htons(node.PortNumber);

	// Bind the socket to a local socket address
	if (bind(socketHandle,
			(struct sockaddr *) &socketInfo,
			sizeof(struct sockaddr_in)) < 0) {
		close(socketHandle);
		perror("bind");
		exit(EXIT_FAILURE);
	} else {
		printf("SERVER: Success: Server socket bind.\n");
	}

	listen(socketHandle, 1);

	// infinite loop to handle remote connections. This should be limited.
	printf("SERVER: Now waiting for new connections from controller!!\n\n");
	int socketConnection;
	for (;;) {
		if ((socketConnection = accept(socketHandle, NULL, NULL)) < 0) {
			close(socketHandle);
			if (errno == EINTR)
				continue;
			perror("accept");
			exit(EXIT_FAILURE);
		} else {
			printf("SERVER [%d]: New connection accepted from %d!!\n", node.NodeId, socketConnection);
		}

		// Receive from client
		if ((bytesRecv = recv(socketConnection, buffer, 10240, 0)) == -1) {
			printf("SERVER: Error in receiving message!!\n");
			perror("recv");
			exit(1);
		} else if (bytesRecv == 0) {
			continue;
		}

		buffer[bytesRecv+1] = '\0';
		parseCommand(buffer, command, &nodeId);
		printf("SERVER: Node to be [%s] is: %d\n", command, nodeId);

		if (strcmp(command, ADDNODE) == 0) {
			printf("#### SERVER: Message received: %s at: %d %s %d\n\n", buffer, node.NodeId, node.HostName, node.PortNumber);
			// Update the Node's state with new Node added to network.
			UpdateNodeState(&node, nodeId);
			PrintNodeStateToFile(fileName, &node);
		} else if (strcmp(command, DISNODE) == 0) {
			// Displat the node state.
			printf("#### SERVER: Display Message received; displaying the node [%d] [%d]\n", node.NodeId, node.PortNumber);
			PrintNodeState(&node);
		} else if (strcmp(command, DELNODE) == 0) {
			// Close socket and shutdown the process.
			printf("#### SERVER: Exit Message received; Shutting down the node [%d] [%d]\n", node.NodeId, node.PortNumber);
			close(socketHandle);
			exit(0);
		}
	}
}
