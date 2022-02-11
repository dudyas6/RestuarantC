#ifndef  _HEADER
#define _HEADER 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Manot {
	char* productname;
	int price;
	int quantity;
	struct Manot* next;
}Manot, * PManot;

typedef struct list
{
	struct Manot* head;
	struct Manot* tail;
	int count;
}List, * PList;

void RemoveTable(PManot*, int);
void RemoveItem(PManot*, int, char*);
void OrderItem(PManot*, PList, int, char*, int);
void AddItems(char*, int, PList);
void CreateProducts(PList);
int CheckVals(int, int);
void endMsg(char*, PList);
void freeTables(PManot*);

#endif
