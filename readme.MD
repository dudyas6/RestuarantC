# Semester 2 HW 
This project represents a restaurant in C language.

Me and my friend, David Asulin worked on this together as a project



## Structure
- Array of pointers for ALL tables
- LinkedLists for the dishes and the for each table.
- 3 files: Header file, Implementation file and main file

## Files
- "Manot.txt" contains the dishes info: Name, price and quantity
- "Instructions.txt" contains the instructions to make like: Order/Cancel a dish, Closing a table, add new dish to stock etc.
- Header.h: all the defines and signatures of the functions
- Header.c: implementions of the functions
- main.c: sticks all together

## Functions
### CreateProducts: Gets the dishes info from "Manot.txt" and add to Stock (by linkedlist)
- Example (ProductName, Quantity, Price):
```bash
Falafel 40 10

Pasta 22 30

Steak 31 25
```

### AddItems: Add stock for an exist dish
- Example (ProductName, Quantity):
```bash
2 Pasta 4 
```

(That means: activate function #2, with params: "Pasta 4")



### OrderItem: Makes an order for an item and quantity (by linkedlist)
- Example (TableNumber, ProductName, Quantity):
```bash
3 5 Steak 2
```

(That means: activate function #3 with params: "5 Steak 2". For table #5, order 2 Steak)



### RemoveItem: Cancel the LAST dish from the table
- Example (TableNumber):
```bash
4 1
```

(That means: activate function #4 with params: "1". Cancel the last dish from table #1)



### RemoveTable: Close the table and give the check.
- Example (TableNumber):
```bash
5 7
```

(That means: activate function #5 with params: "7". Close Table #7)







