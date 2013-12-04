/*
 * common.c
 *
 *  Created on: Nov 27, 2013
 *      Author: Anil Jangam
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "common.h"

int compareInt (const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

void convertToStr(char* str, int nodeId) {
	memset(str, '\0', 6);
	sprintf(str, "%d", nodeId);
}

// Check if file already exists.
int fileExist(char *filename) {
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

// Get port number for the node.
int getNextPortNum() {
	return portNumber++;
}

// Get user options.
int GetOpt() {
	int option = 0;

	printf("%-15s", "1. Add New Node\n");
	printf("%-15s", "2. Display Nodes\n");
	printf("%-15s", "3. Dump Node data\n");
	printf("%-15s", "4. Delete Node\n");
	printf("%-15s", "5. Exit\n");

	scanf("%d", &option);
	return option;
}

// Build display command string to be sent to Node.
void buildAddNodeCommand(char *str, int nodeId) {
	memset(str, '\0', BUFSIZE);
	sprintf(str, "%s", ADDNODE);
	sprintf(str + 4, "%d", nodeId);
}

// Build display command string to be sent to Node.
void buildDisplayCommand(char *str, int nodeId) {
	memset(str, '\0', BUFSIZE);
	sprintf(str, "%s", DISNODE);
	sprintf(str + 4, "%d", nodeId);
}

// Build delete command string to be sent to Node.
void buildDeleteCommand(char *str, int nodeId) {
	memset(str, '\0', BUFSIZE);
	sprintf(str, "%s", DELNODE);
	sprintf(str + 4, "%d", nodeId);
}

// Parse the command to be executed.
void parseCommand(char* str, char *command, int *nodeId) {
	char nodeIdBuf[NODEIDLEN];
	memset(command, '\0', CMDSIZE+1);
	memset(nodeIdBuf, '\0', NODEIDLEN);

	strncpy(command, str, CMDSIZE);
	strncpy(nodeIdBuf, str+CMDSIZE, NODEIDLEN);

	*nodeId = atoi(nodeIdBuf);
}
