/*
 * pastrynetwork.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Anil Jangam, Shilpa Kokre, Kimberly White
 */

#ifndef PASTRYNETWORK_H_
#define PASTRYNETWORK_H_

#include "common.h"

PastryNode *PastryNetwork[PS_NODES];

// Function decelerations.
int AddPastryNode(PastryNode *node, int nodeid);
int AddFirstNode(PastryNode *node);

int PopulateFirstNodeState(PastryNode *node);
int ExchangeNodeState(PastryNode*);
int UpdateNodeState(PastryNode*, unsigned int newNodeId);

int UpdateLeafSet(PastryNode *currNode, PastryNode *newNode);
int UpdateLeafSetNodeId(PastryNode *currNode, unsigned int newNodeId);

int UpdateRoutingTable(PastryNode *currNode, PastryNode *newNode);
int UpdateRoutingTableNodeId(PastryNode *currNode, unsigned int newNodeId);

int UpdateNeighborhoodSet(PastryNode *currNode, PastryNode *newNode);
int UpdateNeighborhoodSetNodeId(PastryNode *currNode, unsigned int newNodeId);

int PrefixMatch(int, int, int);

void PrintPastryNetwork();
void PrintPastryNetworkToFile();

#endif /* PASTRYNETWORK_H_ */
