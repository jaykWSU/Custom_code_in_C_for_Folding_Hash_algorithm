#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct node
{
	int value;
	struct node *next;
} Node; 

typedef struct person
{
	char *Name; 
	int weight; // in lbs
}Person;

typedef struct hashtable
{
	Node **table;
	int tablesize;
} Hashtable;

int hash(char *key, int table_size);
int HashJay1(char *string, int table_size);
int HashJay2(char *string, int table_size);
Hashtable hashTableInit(int table_size);
void putInside(Hashtable *some_table, Person human);


#endif