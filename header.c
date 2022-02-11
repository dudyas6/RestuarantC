/* header.c - implementation file */
#define _CRT_SECURE_NO_WARNINGS
#include "header.h" 

int CheckVals(int v, int q) {
	// this function checks if postive numberes were given
	if (v < 0 || q < 0)
		return 0;
	return 1;
}

void endMsg(char* msg, PList kitchen) {
	// the function prints msg, free kitchen allocation and exit the program
	Manot* temp;
	while (kitchen->head != NULL)
	{
		temp = kitchen->head;
		kitchen->head = kitchen->head->next;
		free(temp->productname);
		free(temp);
	}
	printf("%s", msg);
	exit(1);
}

void CreateProducts(PList kitchen) {
	// this function creates linked-lists of Manot from given file
	FILE* in;
	Manot* temp;
	char name[50];  // temp name before allocation new
	kitchen->count = 0; // reset
	if ((in = fopen("Manot.txt", "rt")) == NULL) // error loading file
		endMsg("Cannot open Manot.txt file.", kitchen);

	while (!feof(in))  // while not the end of file
	{
		if ((temp = (Manot*)malloc(sizeof(Manot))) == NULL)
			endMsg("Not enought memory for the allocation", kitchen);

		fscanf(in, "%s %d %d", &name, &(temp->price), &(temp->quantity));  // reads info from file
		temp->productname = (char*)malloc(strlen(name) + 1);
		if (temp->productname == NULL) {  // allocation failed
			free(temp); // free current 
			endMsg("Not enough memory", kitchen);
		}

		strcpy(temp->productname, name);
		if (!CheckVals(temp->price, temp->quantity)) {
			free(temp->productname); // free name allocation
			free(temp); // free current
			endMsg("Not a valid number, negative number.", kitchen);
		}
		kitchen->count++;
		// linked-list promote BLOCK
		temp->next = NULL;
		if (kitchen->head == NULL)
			kitchen->head = temp;
		else
			kitchen->tail->next = temp;
		kitchen->tail = temp;
		// end of BLOCK
	}
	printf("The kitchen was created.\n");  // everything was good 
	fclose(in); // close file
}

void AddItems(char* productname, int quantity, PList kitchen)
{
	// this function adds item quantity by name

	Manot* temp = kitchen->head;
	if (quantity < 0)
		endMsg("Not a valid amount, negative number.\n", kitchen);

	while (strcmp(temp->productname, productname) != 0) {  // while we not found the item yet
		temp = temp->next;
		if (temp->next == NULL)
			endMsg("Product not found\n", kitchen);  // if there is not 
	}
	// here it means item were found
	temp->quantity += quantity;  // update quantity
	printf("%d %s were added to the kitchen\n", quantity, productname);
}

void OrderItem(PManot* table, PList kitchen, int i, char* productname, int quantity) {
	// this function gets orders per table and adding it to linked-list.
	Manot* temp, * tabletemp;
	tabletemp = (Manot*)malloc(sizeof(Manot));
	if (tabletemp == NULL || i > 50 || quantity < 0) {
		freeTables(table);
		if (i > 50)
			endMsg("Table does not exist!\n", kitchen);
		else if (quantity < 0)
			endMsg("Quantity is not a valid number!\n", kitchen);
		else
			endMsg("Error allocating memory.", kitchen);

	}
	temp = kitchen->head; // update temp
	while (strcmp(temp->productname, productname) != 0)
	{
		if (temp->next == NULL)
		{
			printf("We don't have %s, Sorry!\n", productname);
			return; // dont need to exit the whole program
		}
		temp = temp->next;
	}
	tabletemp->productname = (char*)malloc(strlen(productname) + 1);  // allocation for product name
	if (tabletemp->productname == NULL) {
		free(tabletemp->productname);
		free(tabletemp);
		freeTables(table);
		endMsg("Error allocating memory.", kitchen);
	}
	strcpy(tabletemp->productname, productname);
	tabletemp->quantity = quantity; // update quantity per table
	tabletemp->price = temp->price; // copy the price
	temp->quantity -= quantity;  // update total quantity

	if (table[i] == NULL) {  // no order yet
		table[i] = tabletemp;
		table[i]->next = NULL; // update next
	}
	else {  // table is already order something
		tabletemp->next = table[i];
		table[i] = tabletemp;
	}
	printf("%d %s were added to table number %d.\n", tabletemp->quantity, tabletemp->productname, i);

}

void RemoveItem(PManot* table, int i, char* check_arr) {
	// this function removes the latest ordered item from table. each table can cancel just once.
	// we use the check_arr as array of flags which checks if order were already canceled
	Manot* temp = NULL;
	if (check_arr[i] == 1)  // flag = 1 means one order was already canceled
		printf("Cannot cancel another order for table %d\n", i);
	else if (table[i] == NULL)   // there is no orders to cancel
		printf("The table number %d is empty!\n", i);
	else {  // cancel order
		check_arr[i] = 1;
		temp = table[i];
		table[i] = table[i]->next;

		printf("%d %s was returned to the kitchen from table number %d.\n", temp->quantity, temp->productname, i);
		free(temp->productname); // free = food to garbage \ cancel order
		free(temp);
	}
}

void RemoveTable(PManot* table, int i) {
	// this function calculates the bill for a table and free memory
	float sum = 0;
	Manot* temp, * remove;
	if (table[i] == NULL)
		printf("Table %d has not ordered yet.\n", i);
	else {
		while (table[i] != NULL) { // cancel all orders
			temp = table[i];
			printf("%d %s, ", table[i]->quantity, table[i]->productname);
			sum += (table[i]->price * table[i]->quantity);  // calculates the bill
			table[i] = table[i]->next; // update table
			free(temp->productname);
			free(temp);
		}
		printf("%g nis + %g nis for tips, please!\n", sum, (0.15 * sum));
	}
}

void freeTables(PManot* tables) {
	// this function release all memory per table.
	Manot* temp;
	int i;
	for (i = 0; i < 50; i++)
	{
		while (tables[i] != NULL)
		{
			temp = tables[i];
			tables[i] = tables[i]->next;
			free(temp->productname);
			free(temp);
		}
	}
}
