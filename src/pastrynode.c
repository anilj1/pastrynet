/*
 * pastry.c
 *
 *  Created on: Nov 21, 2013
 *      Author: Anil Jangam
 */

#include <stdio.h>
#include <stdlib.h>

//#include "log.h"
#include "pastrynode.h"
#include "common.h"

static int Index = 0;

unsigned int GetRandomNumber(unsigned int min, unsigned int max) {

	unsigned int result = 0;
	int low_num = 0;
	int hi_num = 0;

	if (min < max) {
		// this is done to include max_num in output.
		low_num = min;
		hi_num = max + 1;
	} else {
		// this is done to include max_num in output.
		low_num = max + 1;
		hi_num = min;
	}

	//srand(time(NULL));
	result = (rand() % (hi_num - low_num)) + low_num;

	return result;
}

void InitNodeIds() {

	int i = 0;

	for (i = 0; i < PS_NODES; i++)
		NodeIds[i] = GetRandomNumber(65000, 70000);
}

void PrintNodeIds() {

	int i = 0;

	for (i = 0; i < PS_NODES; i++)
		printf("Node is: %d\n", NodeIds[i]);
}

unsigned int GetNextNodeId() {

	if (Index == PS_NODES)
		return NodeIds[PS_NODES];
	else
		return NodeIds[Index++];
}

// Set leaf-set nodes.
void SetLowerLeaf1(PastryNode *node, unsigned int nodeId) {
	node->State.LowerLeafSet[0] = nodeId;
}

void SetLowerLeaf2(PastryNode *node, unsigned int nodeId) {
	node->State.LowerLeafSet[1] = nodeId;
}

void SetUpperLeaf1(PastryNode *node, unsigned int nodeId) {
	node->State.UpperLeafSet[0] = nodeId;
}

void SetUpperLeaf2(PastryNode *node, unsigned int nodeId) {
	node->State.UpperLeafSet[1] = nodeId;
}

// Get leaf-set nodes.
int GetLowerLeaf1(PastryNode *node) {
	return node->State.LowerLeafSet[0];
}

int GetLowerLeaf2(PastryNode *node) {
	return node->State.LowerLeafSet[1];
}

int GetUpperLeaf1(PastryNode *node) {
	return node->State.UpperLeafSet[0];
}

int GetUpperLeaf2(PastryNode *node) {
	return node->State.UpperLeafSet[1];
}

// Set routing table - 0 match
void Set0MatchRoutingTable0(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[0][0] = nodeId;
}

void Set0MatchRoutingTable1(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[0][1] = nodeId;
}

void Set0MatchRoutingTable2(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[0][2] = nodeId;
}

void Set0MatchRoutingTable3(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[0][3] = nodeId;
}

int Get0MatchRoutingTable0(PastryNode *node) {
	return node->State.RoutingTable[0][0];
}

int Get0MatchRoutingTable1(PastryNode *node) {
	return node->State.RoutingTable[0][1];
}

int Get0MatchRoutingTable2(PastryNode *node) {
	return node->State.RoutingTable[0][2];
}

int Get0MatchRoutingTable3(PastryNode *node) {
	return node->State.RoutingTable[0][3];
}

// Set routing table - 1 match
void Set1MatchRoutingTable0(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[1][0] = nodeId;
}

void Set1MatchRoutingTable1(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[1][1] = nodeId;
}

void Set1MatchRoutingTable2(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[1][2] = nodeId;
}

void Set1MatchRoutingTable3(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[1][3] = nodeId;
}

int Get1MatchRoutingTable0(PastryNode *node) {
	return node->State.RoutingTable[1][0];
}

int Get1MatchRoutingTable1(PastryNode *node) {
	return node->State.RoutingTable[1][1];
}

int Get1MatchRoutingTable2(PastryNode *node) {
	return node->State.RoutingTable[1][2];
}

int Get1MatchRoutingTable3(PastryNode *node) {
	return node->State.RoutingTable[1][3];
}

// Set routing table - 2 match
void Set2MatchRoutingTable0(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[2][0] = nodeId;
}

void Set2MatchRoutingTable1(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[2][1] = nodeId;
}

void Set2MatchRoutingTable2(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[2][2] = nodeId;
}

void Set2MatchRoutingTable3(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[2][3] = nodeId;
}

int Get2MatchRoutingTable0(PastryNode *node) {
	return node->State.RoutingTable[2][0];
}

int Get2MatchRoutingTable1(PastryNode *node) {
	return node->State.RoutingTable[2][1];
}

int Get2MatchRoutingTable2(PastryNode *node) {
	return node->State.RoutingTable[2][2];
}

int Get2MatchRoutingTable3(PastryNode *node) {
	return node->State.RoutingTable[2][3];
}

// Set routing table - 3 match
void Set3MatchRoutingTable0(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[3][0] = nodeId;
}

void Set3MatchRoutingTable1(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[3][1] = nodeId;
}

void Set3MatchRoutingTable2(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[3][2] = nodeId;
}

void Set3MatchRoutingTable3(PastryNode *node, unsigned int nodeId) {
	node->State.RoutingTable[3][3] = nodeId;
}

int Get3MatchRoutingTable0(PastryNode *node) {
	return node->State.RoutingTable[3][0];
}

int Get3MatchRoutingTable1(PastryNode *node) {
	return node->State.RoutingTable[3][1];
}

int Get3MatchRoutingTable2(PastryNode *node) {
	return node->State.RoutingTable[3][2];
}

int Get3MatchRoutingTable3(PastryNode *node) {
	return node->State.RoutingTable[3][3];
}

// Set neighbor-set nodes.
void SetNeighbor1(PastryNode *node, unsigned int nodeId) {
	node->State.NeighborSet[0] = nodeId;
}

void SetNeighbor2(PastryNode *node, unsigned int nodeId) {
	node->State.NeighborSet[1] = nodeId;
}

void SetNeighbor3(PastryNode *node, unsigned int nodeId) {
	node->State.NeighborSet[2] = nodeId;
}

void SetNeighbor4(PastryNode *node, unsigned int nodeId) {
	node->State.NeighborSet[3] = nodeId;
}

// Get neighbor-set nodes.
int GetNeighbor1(PastryNode *node) {
	return node->State.NeighborSet[0];
}

int GetNeighbor2(PastryNode *node) {
	return node->State.NeighborSet[1];
}

int GetNeighbor3(PastryNode *node) {
	return node->State.NeighborSet[2];
}

int GetNeighbor4(PastryNode *node) {
	return node->State.NeighborSet[3];
}

void ResetNodeState(PastryNode *node) {

	node->State.LowerLeafSet[0] = 0;
	node->State.LowerLeafSet[1] = 0;
	node->State.UpperLeafSet[0] = 999999;
	node->State.UpperLeafSet[1] = 999999;

	node->State.RoutingTable[0][0] = 0;
	node->State.RoutingTable[0][1] = 0;
	node->State.RoutingTable[0][2] = 0;
	node->State.RoutingTable[0][3] = 0;

	node->State.RoutingTable[1][0] = 0;
	node->State.RoutingTable[1][1] = 0;
	node->State.RoutingTable[1][2] = 0;
	node->State.RoutingTable[1][3] = 0;

	node->State.RoutingTable[2][0] = 0;
	node->State.RoutingTable[2][1] = 0;
	node->State.RoutingTable[2][2] = 0;
	node->State.RoutingTable[2][3] = 0;

	node->State.RoutingTable[3][0] = 0;
	node->State.RoutingTable[3][1] = 0;
	node->State.RoutingTable[3][2] = 0;
	node->State.RoutingTable[3][3] = 0;

	node->State.NeighborSet[0] = node->NodeId;
	node->State.NeighborSet[1] = node->NodeId;
	node->State.NeighborSet[2] = node->NodeId;
	node->State.NeighborSet[3] = node->NodeId;
}

void PrintNodeState(PastryNode *node) {

	printf("%s\n", "-------------------------------------------");
	printf("%-20s\n", "Pastry Node");
	printf("%8d\n", node->NodeId);

	printf("\n");
	printf("%-20s\n", "Leaf Set");
	printf("%8d%8d%8d%8d\n", node->State.LowerLeafSet[0],
							 node->State.LowerLeafSet[1],
							 node->State.UpperLeafSet[0],
							 node->State.UpperLeafSet[1]);

	printf("\n");
	printf("%-20s\n", "Routing Table");
	printf("%8d%8d%8d%8d\n", node->State.RoutingTable[0][0],
							 node->State.RoutingTable[0][1],
							 node->State.RoutingTable[0][2],
							 node->State.RoutingTable[0][3]);

	printf("%8d%8d%8d%8d\n", node->State.RoutingTable[1][0],
							 node->State.RoutingTable[1][1],
							 node->State.RoutingTable[1][2],
							 node->State.RoutingTable[1][3]);

	printf("%8d%8d%8d%8d\n", node->State.RoutingTable[2][0],
							 node->State.RoutingTable[2][1],
							 node->State.RoutingTable[2][2],
							 node->State.RoutingTable[2][3]);

	printf("%8d%8d%8d%8d\n", node->State.RoutingTable[3][0],
							 node->State.RoutingTable[3][1],
							 node->State.RoutingTable[3][2],
							 node->State.RoutingTable[3][3]);

	printf("\n");
	printf("%-20s\n", "Neighborhood Set");
	printf("%8d%8d%8d%8d\n", node->State.NeighborSet[0],
							 node->State.NeighborSet[1],
							 node->State.NeighborSet[2],
							 node->State.NeighborSet[3]);
	printf("%s\n", "-------------------------------------------");
	printf("\n");
}

void PrintNodeStateToFile(char *file, PastryNode *node, int insertionCount) {

	FILE *logFile = fopen(file, "a");
	if (logFile == NULL) {
		printf("Error! Could not open file: %s\n", file);
		return;
	}

	if (insertionCount == 0) {
		fprintf(logFile, "%s\n", "Initial Node Insertion");
	} else {
		fprintf(logFile, "After [%d] Insertion\n", insertionCount);
	}

	fprintf(logFile, "%s\n", "-------------------------------------------");
	fprintf(logFile, "%-20s\n", "Pastry Node");
	fprintf(logFile, "%8d\n", node->NodeId);

	fprintf(logFile, "\n");
	fprintf(logFile, "%-20s\n", "Leaf Set");
	fprintf(logFile, "%8d%8d%8d%8d\n",
			node->State.LowerLeafSet[0],
			node->State.LowerLeafSet[1],
			node->State.UpperLeafSet[0],
			node->State.UpperLeafSet[1]);

	fprintf(logFile, "\n");
	fprintf(logFile, "%-20s\n", "Routing Table");
	fprintf(logFile, "%8d%8d%8d%8d\n",
			node->State.RoutingTable[0][0],
			node->State.RoutingTable[0][1],
			node->State.RoutingTable[0][2],
			node->State.RoutingTable[0][3]);

	fprintf(logFile, "%8d%8d%8d%8d\n",
			node->State.RoutingTable[1][0],
			node->State.RoutingTable[1][1],
			node->State.RoutingTable[1][2],
			node->State.RoutingTable[1][3]);

	fprintf(logFile, "%8d%8d%8d%8d\n",
			node->State.RoutingTable[2][0],
			node->State.RoutingTable[2][1],
			node->State.RoutingTable[2][2],
			node->State.RoutingTable[2][3]);

	fprintf(logFile, "%8d%8d%8d%8d\n",
			node->State.RoutingTable[3][0],
			node->State.RoutingTable[3][1],
			node->State.RoutingTable[3][2],
			node->State.RoutingTable[3][3]);

	fprintf(logFile, "\n");
	fprintf(logFile, "%-20s\n", "Neighborhood Set");
	fprintf(logFile, "%8d%8d%8d%8d\n",
			node->State.NeighborSet[0],
			node->State.NeighborSet[1],
			node->State.NeighborSet[2],
			node->State.NeighborSet[3]);

	fprintf(logFile, "%s\n", "-------------------------------------------");
	fprintf(logFile, "\n");

	// Close the file handler.
	fclose(logFile);
}

// Get hop distance.
int GetHopDistance(unsigned int nodeId1, unsigned int nodeId2) {

	int hopCount = 0;

	if (nodeId1 == nodeId2) {
		return SAME_NODE_ID;
	} else {
		hopCount = (nodeId1 * nodeId2) % MAX_HOPS;
	}

	return hopCount;
}
