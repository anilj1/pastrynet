/*
 * client.c
 *
 *  Created on: Dec 2, 2013
 *      Author: Anil Jangam
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "nodeclient.h"
#include "pastrynode.h"

int Connect(PastryNode node) {

	struct sockaddr_in remoteSocketInfo;
	struct hostent *hPtr;
	int socketHandle;

	printf("CLIENT: Connecting with Node: %s %d %d\n", node.HostName, node.NodeId, node.PortNumber);
	memset(&remoteSocketInfo, 0x0, sizeof(remoteSocketInfo));

	// Get system information
	if ((hPtr = gethostbyname(node.HostName)) == NULL) {
		printf("CLIENT: System DNS name resolution not configured properly.\n");
		printf("Error number: [%d]\n", ECONNREFUSED);
		exit(EXIT_FAILURE);
	}

	// create socket
	if ((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("CLIENT: Failed to create socket to node.\n");
		close(socketHandle);
		exit(EXIT_FAILURE);
	} else {
		printf("CLIENT: Successfully created socket to node.\n");
	}

	// Load system information into socket data structures
	//memcpy((char *) &remoteSocketInfo.sin_addr, hPtr->h_name, hPtr->h_length);
	remoteSocketInfo.sin_addr.s_addr = htonl(INADDR_ANY);
	remoteSocketInfo.sin_family = AF_INET;
	remoteSocketInfo.sin_port = htons((u_short) node.PortNumber); // Set port number

	if (connect(socketHandle, (struct sockaddr *) &remoteSocketInfo, sizeof(remoteSocketInfo)) < 0) {
		printf("CLIENT: Connection failed with remote node server.\n");
		close(socketHandle);
		exit(EXIT_FAILURE);
	} else {
		printf("CLIENT: Connection succeeded with remote node server.\n\n");
	}

	return socketHandle;
}

int SendMessage(int socketHandle, char* msg) {

	// Actual number of bytes read by function read()
	printf("CLIENT: Sending message to remote node.\n");
	send(socketHandle, msg, strlen(msg) + 1, 0);

	return 0;
}
