/*
 * pastrynetwork.c
 *
 *  Created on: Nov 21, 2013
 *      Author: Anil Jangam, Shilpa Kokre, Kimberly White
 */

#include <stdio.h>
#include <stdlib.h>

#include "pastrynode.h"
#include "pastrynetwork.h"

static char* logFile = "pastryNet.log";

// Routing table row index.
const int RT_COL_1 = 0;
const int RT_COL_2 = 1;
const int RT_COL_3 = 2;
const int RT_COL_4 = 3;

int PopulateFirstNodeState(PastryNode *node) {

	int result = 0;

	// Set leaf set
	SetLowerLeaf1(node, 0);
	SetLowerLeaf2(node, 0);
	SetUpperLeaf1(node, 999999);
	SetUpperLeaf2(node, 999999);

	// Set routing table.
	Set0MatchRoutingTable0(node, 0);
	Set0MatchRoutingTable1(node, 0);
	Set0MatchRoutingTable2(node, 0);
	Set0MatchRoutingTable3(node, 0);

	Set1MatchRoutingTable0(node, 0);
	Set1MatchRoutingTable1(node, 0);
	Set1MatchRoutingTable2(node, 0);
	Set1MatchRoutingTable3(node, 0);

	Set2MatchRoutingTable0(node, 0);
	Set2MatchRoutingTable1(node, 0);
	Set2MatchRoutingTable2(node, 0);
	Set2MatchRoutingTable3(node, 0);

	Set3MatchRoutingTable0(node, 0);
	Set3MatchRoutingTable1(node, 0);
	Set3MatchRoutingTable2(node, 0);
	Set3MatchRoutingTable3(node, 0);

	// Set neighbors
	SetNeighbor1(node, node->NodeId);
	SetNeighbor2(node, node->NodeId);
	SetNeighbor3(node, node->NodeId);
	SetNeighbor4(node, node->NodeId);

	return result;
}

int PrefixMatch(int currNodeId, int newNodeId, int prefixSize) {

	int result = 0;
	char str1[6];
	char str2[6];

	convertToStr(str1, currNodeId);
	convertToStr(str2, newNodeId);

	if (strncmp(str1, str2, prefixSize) != 0) {
		result = 1;
	}

	return result;
}

int UpdateLeafSet(PastryNode *currNode, PastryNode *newNode) {

	int result = 0;

	// Check for the lower leaf set.
	if (newNode->NodeId < currNode->NodeId) {
		if (newNode->NodeId > GetLowerLeaf2(currNode)) {
			SetLowerLeaf2(currNode, newNode->NodeId);
		} else if (newNode->NodeId > GetLowerLeaf1(currNode)) {
			SetLowerLeaf1(currNode, newNode->NodeId);
		}
	} else if (newNode->NodeId > currNode->NodeId) {
		// Check for the upper leaf set.
		if (newNode->NodeId < GetUpperLeaf2(currNode)) {
			SetUpperLeaf2(currNode, newNode->NodeId);
		} else if (newNode->NodeId < GetUpperLeaf1(currNode)) {
			SetUpperLeaf1(currNode, newNode->NodeId);
		}
	}

	return result;
}

int UpdateLeafSetNodeId(PastryNode *currNode, unsigned int newNodeId) {

	int result = 0;

	// Check for the lower leaf set.
	if (newNodeId < currNode->NodeId) {
		if (newNodeId > GetLowerLeaf2(currNode)) {
			SetLowerLeaf2(currNode, newNodeId);
		} else if (newNodeId > GetLowerLeaf1(currNode)) {
			SetLowerLeaf1(currNode, newNodeId);
		}
	} else if (newNodeId > currNode->NodeId) {
		// Check for the upper leaf set.
		if (newNodeId < GetUpperLeaf2(currNode)) {
			SetUpperLeaf2(currNode, newNodeId);
		} else if (newNodeId < GetUpperLeaf1(currNode)) {
			SetUpperLeaf1(currNode, newNodeId);
		}
	}

	return result;
}

int UpdateRoutingTable(PastryNode *currNode, PastryNode *newNode) {

	int result = 0;
	int idx = 0;
	int currNodeId = 0;

	// Check for 3 digit match criteria.
	// I think I am sorting the array to ensure comparisons are minimum.
	// and we can break the loop. Same is done in the NS update.
	qsort(&(currNode->State.RoutingTable[THR_MATCH]), 4, sizeof(int), compareInt);
	for (idx = 0; idx < ROUTE_TABLE_COLS; idx++) {
		currNodeId = currNode->State.RoutingTable[THR_MATCH][idx];

		if (PrefixMatch(currNode->NodeId, newNode->NodeId, THR_MATCH) == 0) {
			if (newNode->NodeId > currNodeId) {
				currNode->State.RoutingTable[THR_MATCH][idx] = newNode->NodeId;
				break;
			}
		}
	}

	// Check for 2 digit match criteria.
	qsort(&(currNode->State.RoutingTable[TWO_MATCH]), 4, sizeof(int), compareInt);
	for (idx = 0; idx < ROUTE_TABLE_COLS; idx++) {
		currNodeId = currNode->State.RoutingTable[TWO_MATCH][idx];

		if (PrefixMatch(currNode->NodeId, newNode->NodeId, TWO_MATCH) == 0) {
			if (newNode->NodeId > currNodeId) {
				currNode->State.RoutingTable[TWO_MATCH][idx] = newNode->NodeId;
				break;
			}
		}
	}

	// Check for 1 digit match criteria.
	qsort(&(currNode->State.RoutingTable[ONE_MATCH]), 4, sizeof(int), compareInt);
	for (idx = 0; idx < ROUTE_TABLE_COLS; idx++) {
		currNodeId = currNode->State.RoutingTable[ONE_MATCH][idx];

		if (PrefixMatch(currNode->NodeId, newNode->NodeId, ONE_MATCH) == 0) {
			if (newNode->NodeId > currNodeId) {
				currNode->State.RoutingTable[ONE_MATCH][idx] = newNode->NodeId;
				break;
			}
		}
	}

	// Check for 0 digit match criteria.

	return result;
}

int UpdateRoutingTableNodeId(PastryNode *currNode, unsigned int newNodeId) {

	int result = 0;
	int idx = 0;
	int currNodeId = 0;

	// Check for 3 digit match criteria.
	// I think I am sorting the array to ensure comparisons are minimum.
	// and we can break the loop. Same is done in the NS update.
	qsort(&(currNode->State.RoutingTable[THR_MATCH]), 4, sizeof(int), compareInt);
	for (idx = 0; idx < ROUTE_TABLE_COLS; idx++) {
		currNodeId = currNode->State.RoutingTable[THR_MATCH][idx];

		if (PrefixMatch(currNode->NodeId, newNodeId, THR_MATCH) == 0) {
			if (newNodeId > currNodeId) {
				currNode->State.RoutingTable[THR_MATCH][idx] = newNodeId;
				break;
			}
		}
	}

	// Check for 2 digit match criteria.
	qsort(&(currNode->State.RoutingTable[TWO_MATCH]), 4, sizeof(int), compareInt);
	for (idx = 0; idx < ROUTE_TABLE_COLS; idx++) {
		currNodeId = currNode->State.RoutingTable[TWO_MATCH][idx];

		if (PrefixMatch(currNode->NodeId, newNodeId, TWO_MATCH) == 0) {
			if (newNodeId > currNodeId) {
				currNode->State.RoutingTable[TWO_MATCH][idx] = newNodeId;
				break;
			}
		}
	}

	// Check for 1 digit match criteria.
	qsort(&(currNode->State.RoutingTable[ONE_MATCH]), 4, sizeof(int), compareInt);
	for (idx = 0; idx < ROUTE_TABLE_COLS; idx++) {
		currNodeId = currNode->State.RoutingTable[ONE_MATCH][idx];

		if (PrefixMatch(currNode->NodeId, newNodeId, ONE_MATCH) == 0) {
			if (newNodeId > currNodeId) {
				currNode->State.RoutingTable[ONE_MATCH][idx] = newNodeId;
				break;
			}
		}
	}

	// Check for 0 digit match criteria.

	return result;
}

int UpdateNeighborhoodSet(PastryNode *currNode, PastryNode *newNode) {

	int result = 0;
	int newHopCnt = 0;
	int curHop = 0;
	int idx = 0;

	newHopCnt = GetHopDistance(currNode->NodeId, newNode->NodeId);

	// Sort the NS array.
	//qsort(currNode->State.NeighborSet, 4, sizeof(int), compareInt);

	// Iterate through and update the neighborhood set for
	// the current nodes.
	for (idx = 0; idx < NEIGHBOR_SET_COLS; idx++) {

		curHop = GetHopDistance(currNode->NodeId, currNode->State.NeighborSet[idx]);
		// @@ Check if the current hop is less than the first.
		// If its smaller, then update the location, and break.
		if (newHopCnt < curHop) {
			currNode->State.NeighborSet[idx] = newNode->NodeId;
			break;
		} else if (newHopCnt == curHop) {
			// Hop count of both the nodes is same, hence
			// chose the numerically closest node.
			if (newNode->NodeId < currNode->State.NeighborSet[idx]) {
				currNode->State.NeighborSet[idx] = newNode->NodeId;
				break;
			}
		}
	}

	return result;
}

int UpdateNeighborhoodSetNodeId(PastryNode *currNode, unsigned int newNodeId) {

	int result = 0;
	int newHopCnt = 0;
	int curHop = 0;
	int idx = 0;

	newHopCnt = GetHopDistance(currNode->NodeId, newNodeId);

	// Sort the NS array.
	//qsort(currNode->State.NeighborSet, 4, sizeof(int), compareInt);

	// Iterate through and update the neighborhood set for
	// the current nodes.
	for (idx = 0; idx < NEIGHBOR_SET_COLS; idx++) {

		curHop = GetHopDistance(currNode->NodeId, currNode->State.NeighborSet[idx]);
		// @@ Check if the current hop is less than the first.
		// If its smaller, then update the location, and break.
		if (newHopCnt < curHop) {
			currNode->State.NeighborSet[idx] = newNodeId;
			break;
		} else if (newHopCnt == curHop) {
			// Hop count of both the nodes is same, hence
			// chose the numerically closest node.
			if (newNodeId < currNode->State.NeighborSet[idx]) {
				currNode->State.NeighborSet[idx] = newNodeId;
				break;
			}
		}
	}

	return result;
}

int UpdateNodeState(PastryNode *currNode, unsigned int newNodeId) {

	int idx = 0;

	// Update the leaf set for the current node
	UpdateLeafSetNodeId(currNode, newNodeId);

	// Update the routing table for the current node
	UpdateRoutingTableNodeId(currNode, newNodeId);

	// Update the neighborhood set for the current node
	UpdateNeighborhoodSetNodeId(currNode, newNodeId);

	return 0;
}

int ExchangeNodeState(PastryNode *newNode) {

	int result = 0;
	int idx = 0;
	PastryNode* currNode;

	// Update all existing nodes w.r.t to new node.
	for (idx = 0; idx < NodeIndex; idx++) {
		currNode = PastryNetwork[idx];

		// Update the leaf set for the current node
		UpdateLeafSet(currNode, newNode);

		// Update the routing table for the current node
		UpdateRoutingTable(currNode, newNode);

		// Update the neighborhood set for the current node
		UpdateNeighborhoodSet(currNode, newNode);
	}

	// Update new node w.r.t to all existing nodes.
	for (idx = 0; idx < NodeIndex; idx++) {
		currNode = PastryNetwork[idx];

		// Update the leaf set for the current node
		UpdateLeafSet(newNode, currNode);

		// Update the routing table for the current node
		UpdateRoutingTable(newNode, currNode);

		// Update the neighborhood set for the current node
		UpdateNeighborhoodSet(newNode, currNode);
	}

	return result;
}

int AddPastryNode(PastryNode *node, int nodeId) {

	int result = 0;

	node->NodeId = nodeId;
	ResetNodeState(node);

	if (NodeIndex == 0) {
		// No node exist in the network.
		// Populate node routing state.
		PopulateFirstNodeState(node);

	} else {
		// Network already contains other nodes.
		// Update node routing state.
		ExchangeNodeState(node);
	}

	PastryNetwork[NodeIndex] = node;
	NodeIndex++;

	return result;
}

void PrintPastryNetwork() {

	int i = 0;
	PastryNode *node;

	// Check if file exist, and remove it.
	// It is being opened in "append" mode, each time,
	// logs will be appended over the old log, which is
	// not expected.
	removeExistingLogFile(logFile);

	// Print logs to file.
	PrintPastryNetworkToFile();

	// Console print network details.
	printf("%s\n", "*******************************************");
	printf("%-20s: %2d\n\n", "Total nodes in the network", NodeIndex);
	printf("%s %d %s\n", "(after", NodeIndex, "node insertions)");

	for (i = 0; i < NodeIndex; i++) {
		node = PastryNetwork[i];
		PrintNodeState(node);
		PrintNodeStateToFile(logFile, node, 0);
	}
}

void PrintPastryNetworkToFile() {

	FILE *file = fopen(logFile, "a");
	if (file == NULL) {
		printf("Error! Could not open file: %s\n", logFile);
		return;
	}

	// File print network details.
	fprintf(file, "%s\n", "*******************************************");
	fprintf(file, "%-20s: %2d\n\n", "Total nodes in the network", NodeIndex);
	fprintf(file, "%s %d %s\n", "(after", NodeIndex, "node insertions)");

	// Close the file handler.
	fclose(file);
}
