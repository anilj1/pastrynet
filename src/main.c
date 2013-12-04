/*
 * routingtable.c
 *
 *  Created on: Nov 21, 2013
 *      Author: Anil Jangam
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "pastrynode.h"
#include "pastrynetwork.h"
#include "nodeserver.h"
#include "nodeclient.h"

int main() {

	int index = 0;
	int socketHandle = 0;
	int option = 0;
	int nodeId;
	char cmdBuf[BUFSIZE];
	char command[CMDSIZE+1];
	PastryNode *nNode;
	PastryNode *tNode;

	InitNodeIds();

	while (option != 5) {

		option = GetOpt();

		switch (option) {
		case 1:
			// Add new node.
			nNode = malloc(sizeof(PastryNode));
			nNode->NodeId = GetNextNodeId();
			nNode->PortNumber = getNextPortNum();
			strcpy(nNode->HostName, LOCAL_HOST);

			// Update the Node state.
			//PopulateFirstNodeState(nNode);

			// Add node to the Network array.
			PastryNetwork[NodeIndex] = nNode;
			NodeIndex++;

			// child
			printf("CLIENT: Creating a new Node...\n");
			pid_t pID = fork();

			if (pID == 0) {
				// Code only executed by child process
				// Spwan a server process.
				printf("CLIENT: Spawning child process.\n");
				NodeServerFunction(*nNode);

			} else if (pID < 0) {
				// failed to fork
				printf("CLIENT: Failed to fork.\n");
				exit(0);
				// Throw exception
			} else {

				sleep(1);
				// Code only executed by parent process
				for (index = 0; index < NodeIndex; index++) {
					//printNodeArray();
					// Connect to each of the existing node to pass node Id.
					tNode = PastryNetwork[index];

					// Connect to the Pastry node. Node should not communicate with self.
					if (nNode->NodeId != tNode->NodeId) {
						printf("CLIENT: Controller communicating with node [%d] [%d].\n", tNode->NodeId, tNode->PortNumber);
						socketHandle = Connect(*tNode);

						// Build add node command and send it to existing node.
						buildAddNodeCommand(cmdBuf, nNode->NodeId);
						printf("CLIENT: Add Node command is: %s\n", cmdBuf);

						SendMessage(socketHandle, cmdBuf);
						close(socketHandle);

						// ########### EXCHANGING the Node State. #############
						printf("CLIENT: Controller communicating with node [%d] [%d].\n", nNode->NodeId, nNode->PortNumber);
						socketHandle = Connect(*nNode);

						// Build add node command and send it to existing node.
						buildAddNodeCommand(cmdBuf, tNode->NodeId);
						printf("CLIENT: Add Node command is: %s\n", cmdBuf);

						SendMessage(socketHandle, cmdBuf);
						close(socketHandle);
					}
				}
			}
			break;
		case 2:
			printf("Current nodes in the network are: %d\n\n", NodeIndex);
			printf("%-10s %-10s %-10s\n", "Node", "Node Id", "Port Number");
			for (index = 0; index < NodeIndex; index++) {
				// Connect to each of the existing node to pass node Id.
				tNode = PastryNetwork[index];
				printf("%-10d %-10d %-10d\n", index, tNode->NodeId, tNode->PortNumber);
			}
			printf("\n\n");
			break;
		case 3:
			printf("CLIENT: Enter the nodeId to be Displayed: ");
			scanf("%d", &nodeId);
			if (nodeId <= NodeIndex) {
				tNode = PastryNetwork[nodeId];

				// Build display command and send it to node.
				buildDisplayCommand(cmdBuf, tNode->NodeId);
				printf("CLIENT: Display command is: %s\n", cmdBuf);

				//PrintNodeState(tNode);
				// Connect to the node. Send the node Id to the new node, and existing nodes.
				socketHandle = Connect(*tNode);
				SendMessage(socketHandle, cmdBuf);
				close(socketHandle);

			} else {
				printf("CLIENT: Invalid node index provided, please try again.\n\n");
			}
			break;
		case 4:
			printf("CLIENT: Enter the nodeId to be deleted: ");
			scanf("%d", &nodeId);
			if (nodeId <= NodeIndex) {
				tNode = PastryNetwork[nodeId];

				// Build delete command and send it to node.
				buildDeleteCommand(cmdBuf, tNode->NodeId);
				printf("CLIENT: Delete command is: %s\n", cmdBuf);

				// Connect to the node. Send the node Id to the new node, and existing nodes.
				// This however makes the process defunct.
				socketHandle = Connect(*tNode);
				SendMessage(socketHandle, cmdBuf);
				close(socketHandle);

			} else {
				printf("CLIENT: Invalid node index provided, please try again.\n\n");
			}
			break;
		case 5:
			// Exit the program. Send terminate signal
			// to all nodes/processes.
			usleep(500000);
			printf("CLIENT: Total nodes in the network are: [%d]\n", NodeIndex);

			// Code only executed by parent process
			for (index = 0; index < NodeIndex; index++) {
				//printNodeArray();
				// Connect to each of the existing node to pass node Id.
				tNode = PastryNetwork[index];
				printf("CLIENT: Controller communicating with node [%d] [%d].\n", tNode->NodeId, tNode->PortNumber);

				// Build delete command and send it to node.
				buildDeleteCommand(cmdBuf, tNode->NodeId);
				printf("CLIENT: Delete command is: %s\n", cmdBuf);

				// Connect to the node.
				// Send the node Id to the new node, and existing nodes.
				socketHandle = Connect(*tNode);
				SendMessage(socketHandle, cmdBuf);
				close(socketHandle);
			}
			break;
		}
	}

	return 0;
}
