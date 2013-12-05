/*
 * nodeclient.h
 *
 *  Created on: Dec 3, 2013
 *      Author: Anil Jangam, Shilpa Kokre, Kimberly White
 */

#ifndef NODECLIENT_H_
#define NODECLIENT_H_

#include "pastrynode.h"

int Connect(PastryNode node);
int SendMessage(int socketHandle, char* msg);

#endif /* NODECLIENT_H_ */
