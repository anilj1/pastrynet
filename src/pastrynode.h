/*
 * pastry.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Anil Jangam, Shilpa Kokre, Kimberly White
 */

#ifndef PASTRYNODE_H_
#define PASTRYNODE_H_

#include "common.h"

#define ROUTE_TABLE_ROWS 4
#define ROUTE_TABLE_COLS 4

#define LEAF_SET_ROWS 1
#define LEAF_SET_COLS 4

#define NEIGHBOR_SET_ROWS 1
#define NEIGHBOR_SET_COLS 4

#define LOWER_LEAF_SET_COLS 2
#define UPPER_LEAF_SET_COLS 2

#define THR_MATCH 3
#define TWO_MATCH 2
#define ONE_MATCH 1

typedef struct NodeState {

	unsigned int LowerLeafSet[LOWER_LEAF_SET_COLS];
	unsigned int UpperLeafSet[UPPER_LEAF_SET_COLS];
	unsigned int RoutingTable[ROUTE_TABLE_ROWS][ROUTE_TABLE_COLS];
	unsigned int NeighborSet[NEIGHBOR_SET_COLS];

} NodeState;

typedef struct PastryNode {

	unsigned int NodeId;
	unsigned int PortNumber;
	char HostName[MAXHOSTNAME+1];
	NodeState State;

} PastryNode;

typedef struct NetworkOp {

	int opCode;
	PastryNode Node;

} NetworkOp;

// Node Id array
unsigned int NodeIds[PS_NODES];

// Function decelerations.
unsigned int  GetRandomNumber(unsigned int min, unsigned int max);
void InitNodeIds();
void PrintNodeIds();
unsigned int  GetNextNodeId();

// Set leaf-set nodes.
void SetLowerLeaf1(PastryNode *node, unsigned int nodeId);
void SetLowerLeaf2(PastryNode *node, unsigned int nodeId);
void SetUpperLeaf1(PastryNode *node, unsigned int nodeId);
void SetUpperLeaf2(PastryNode *node, unsigned int nodeId);

// Get leaf-set nodes.
int GetLowerLeaf1(PastryNode *node);
int GetLowerLeaf2(PastryNode *node);
int GetUpperLeaf1(PastryNode *node);
int GetUpperLeaf2(PastryNode *node);

// Set routing table.
void Set0MatchRoutingTable0(PastryNode *node, unsigned int nodeId);
void Set0MatchRoutingTable1(PastryNode *node, unsigned int nodeId);
void Set0MatchRoutingTable2(PastryNode *node, unsigned int nodeId);
void Set0MatchRoutingTable3(PastryNode *node, unsigned int nodeId);

int Get0MatchRoutingTable0(PastryNode *node);
int Get0MatchRoutingTable1(PastryNode *node);
int Get0MatchRoutingTable2(PastryNode *node);
int Get0MatchRoutingTable3(PastryNode *node);

// Set routing table - 1 match
void Set1MatchRoutingTable0(PastryNode *node, unsigned int nodeId);
void Set1MatchRoutingTable1(PastryNode *node, unsigned int nodeId);
void Set1MatchRoutingTable2(PastryNode *node, unsigned int nodeId);
void Set1MatchRoutingTable3(PastryNode *node, unsigned int nodeId);

int Get1MatchRoutingTable0(PastryNode *node);
int Get1MatchRoutingTable1(PastryNode *node);
int Get1MatchRoutingTable2(PastryNode *node);
int Get1MatchRoutingTable3(PastryNode *node);

// Set routing table - 2 match
void Set2MatchRoutingTable0(PastryNode *node, unsigned int nodeId);
void Set2MatchRoutingTable1(PastryNode *node, unsigned int nodeId);
void Set2MatchRoutingTable2(PastryNode *node, unsigned int nodeId);
void Set2MatchRoutingTable3(PastryNode *node, unsigned int nodeId);

int Get2MatchRoutingTable0(PastryNode *node);
int Get2MatchRoutingTable1(PastryNode *node);
int Get2MatchRoutingTable2(PastryNode *node);
int Get2MatchRoutingTable3(PastryNode *node);

// Set routing table - 3 match
void Set3MatchRoutingTable0(PastryNode *node, unsigned int nodeId);
void Set3MatchRoutingTable1(PastryNode *node, unsigned int nodeId);
void Set3MatchRoutingTable2(PastryNode *node, unsigned int nodeId);
void Set3MatchRoutingTable3(PastryNode *node, unsigned int nodeId);

int Get3MatchRoutingTable0(PastryNode *node);
int Get3MatchRoutingTable1(PastryNode *node);
int Get3MatchRoutingTable2(PastryNode *node);
int Get3MatchRoutingTable3(PastryNode *node);

// Set neighbor-set nodes.
void SetNeighbor1(PastryNode *node, unsigned int nodeId);
void SetNeighbor2(PastryNode *node, unsigned int nodeId);
void SetNeighbor3(PastryNode *node, unsigned int nodeId);
void SetNeighbor4(PastryNode *node, unsigned int nodeId);

// Get neighbor-set nodes.
int GetNeighbor1(PastryNode *node);
int GetNeighbor2(PastryNode *node);
int GetNeighbor3(PastryNode *node);
int GetNeighbor4(PastryNode *node);

// Print the node
void ResetNodeState(PastryNode *node);
void PrintNodeState(PastryNode *node);
void PrintNodeStateToFile(char *file, PastryNode *node, int insertionCount);
int GetHopDistance(unsigned int node1, unsigned int node2);

#endif /* PASTRYNODE_H_ */
