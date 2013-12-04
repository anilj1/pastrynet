/*
 * common.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Anil Jangam
 */

#ifndef COMMON_H_
#define COMMON_H_

static int NodeIndex = 0;
static int portNumber = 52000;

#define LOCAL_HOST "localhost"
#define ADDNODE "ADDN"
#define DISNODE "DISP"
#define DELNODE "DELT"

#define PS_NODES 100
#define MAX_HOPS 10
#define SAME_NODE_ID 1000000
#define MAXHOSTNAME 256
#define BUFSIZE 256
#define CMDSIZE 4
#define NODEIDLEN 6

int compareInt (const void *a, const void *b);
void convertToStr(char*, int nodeId);
int fileExist (char *filename);
int getNextPortNum();
int GetOpt();
void buildAddNodeCommand(char *str, int nodeId);
void buildDisplayCommand(char* str, int nodeId);
void buildDeleteCommand(char *str, int nodeId);
void parseCommand(char* str, char *command, int *nodeId);

#endif /* COMMON_H_ */
