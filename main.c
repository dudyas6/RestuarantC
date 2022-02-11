#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

void main()
{
	FILE* open;
	List plist;
	int instruction, quantity, tablenum;
	char productname[50];
	PManot Table[50] = { NULL };
	char check_arr[50] = { 0 };
	plist.head = plist.tail = NULL;
	open = fopen("Instructions.txt", "rt");
	if (open == NULL)
		endMsg("error open instructions file", &plist);
	

	while (!feof(open)) {
		rewind(stdin); // clear pointer
		fscanf(open, "%d", &instruction); // 
		switch (instruction) // switch between cases as function of given int 
		{
		case 1:
			CreateProducts(&plist);
			break;
		case 2:
			fscanf(open, "%s %d", &productname, &quantity);
			AddItems(productname, quantity, &plist);
			break;
		case 3:
			fscanf(open, "%d %s %d", &tablenum, &productname, &quantity);
			OrderItem(Table, &plist, tablenum, productname, quantity);
			break;
		case 4:
			fscanf(open, "%d", &tablenum);
			RemoveItem(&Table, tablenum, check_arr);
			break;
		case 5:
			fscanf(open, "%d", &tablenum);
			RemoveTable(&Table, tablenum);
			break;
		default:
			break;
		}
	}
	fclose(open);
	endMsg("", &plist);
	freeTables(&Table);
}

