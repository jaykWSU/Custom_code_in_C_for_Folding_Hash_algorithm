#include "header.h"

int hash(char *key, int table_size) // this isn't mine, I found this on cpts 223 notes at WSU
{
	int hash_val = 0;

	while (*key != '\0')
	{
		hash_val += *key++;
	}

	return hash_val % table_size;
}

// hashing made using the video that only talks about the folding concept (no actual code was provided at this point, this is all my own work)
// at http://pluralsight.com/training/Player?author=robert-horvick&name=ads-hashtable&mode=live&clip=1&course=ads-part1
// later on C# code is shown but this code is all different and I can do any of this if asked to do it again

//did it first here without using bitwise operators, this one isn't as efficient-- but works (without bitwise operations)
int HashJay1(char *string, int table_size)
{
	int num = 0, sum = 0, i = 0, j = 0, k = 0, l = 0, r = 0, new_num = 0, total = 0;
	int *ar = (int *)calloc(8, sizeof(int));
	int *value = (int *)calloc(8, sizeof(int));
	int *newar = (int *)calloc(32, sizeof(int)), index_newar = 24;
	int *endvalue = (int *)calloc(32, sizeof(int)), endex = 0;
	char *temp;

	for (i = 0; i < 8; i++)
	{
		value[i] = (int)pow(2, i); // gets the values for 8 bits for use later
	}


	while (string[k] != '\0')
	{
		i = 0;
		temp = (char *)calloc(5, sizeof(char));
		while (i < 4 && string[k] != '\0')
		{
			temp[i] = string[k];
			i++;
			k++;
		}

		while (temp[l] != '\0')
		{
			num = temp[l];

			for (i = 7; i > -1; i--)
			{
				if (value[i] + sum <= num)
				{
					ar[i] = 1;
					sum += value[i];
				}
				else
					ar[i] = 0;
			}

			for (i = 7; i > -1; i--)
			{
				newar[index_newar] = ar[i];
				endvalue[endex] = pow(2, endex);
				index_newar++;
				endex++;
			}
			index_newar -= 16;
			sum = 0;
			l++;
		}

		for (i = 0, j = 31; i < 32, j > -1; i++, j--)
		{
			if (newar[i] == 1)
			{
				new_num += endvalue[j];
			}
		}
		total += new_num;
		for (i = 0; i < 32; i++)
		{
			newar[i] = 0;
		}
		new_num = 0;
		index_newar = 24;
		endex = 0;
		free(temp);
		l = 0;
	}
	free(ar);
	free(value);
	free(newar);
	free(endvalue);

	// n = dq + r, with algebra r = n-dq... not using modulo
	r = total - table_size * floor((double)total / table_size);
	return r;
}

// I decided to try adding bitwise operators, still made this
// from scratch, just remembered bitwise operations since I haven't used them in a while.
int HashJay2(char *string, int table_size)
{
	int num = 0, sum = 0, i = 0, j = 0, k = 0, l = 0, total = 0, r = 0, q = 0;
	div_t diver;
	int pusher[4] = { 24, 16, 8, 0 };

	char *temp;
	int size = 0;

	while (string[k] != '\0')
	{
		i = 0;
		temp = (char *)calloc(5, sizeof(char));
		while (i < 4 && string[k] != '\0')
		{
			temp[i] = string[k];
			i++;
			k++;
		}
		size = sizeof(temp) / sizeof(temp[0]);

		l = size - 1;
		while (l >= 0)
		{
			sum += temp[l] << pusher[j];
			j++;
			l--;
		}

		j = 0;
		total += sum;
		sum = 0;
		free(temp);
	}

	// n = dq + r, with algebra r = n-dq... not using modulo
	r = total - table_size * floor((double)total / table_size);
	return r;
}

Hashtable hashTableInit(int table_size)
{
	Hashtable some_table;
	int i = 0;
	some_table.tablesize = table_size;
	some_table.table = (Node **)calloc(table_size, sizeof(Node));

	for (i = 0; i < table_size; i++)
	{
		some_table.table[i] = (Node*)malloc(sizeof(Node));
		some_table.table[i]->next = NULL;
		some_table.table[i]->value = 0;
	}

	return some_table;
}

void putInside(Hashtable *some_table, Person human)
{
	int index = HashJay2(human.Name, some_table->tablesize);
	
	if (some_table->table[index]->value == 0)
	{
		some_table->table[index]->value = human.weight;
	}
	else
	{
		if (some_table->table[index]->next == NULL)
		{
			some_table->table[index]->next = (Node*)malloc(sizeof(Node));
			some_table->table[index]->next->next = NULL;
			some_table->table[index]->next->value = human.weight;
		}
		else
		{
			while (some_table->table[index]->next != NULL)
			{
				some_table->table[index] = some_table->table[index]->next;
			}
			some_table->table[index]->next = (Node*)malloc(sizeof(Node));
			some_table->table[index]->next->next = NULL;
			some_table->table[index]->next->value = human.weight;
		}
	}
}