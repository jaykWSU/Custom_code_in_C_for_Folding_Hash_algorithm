#include "header.h"


int main(void)
{
	char *string = "lorem ipsum dolor";
	int ar[5] = { 1, 2, 3, 4, 5 };
	Hashtable some_table = hashTableInit(1);
	Person Lisa, Riff;
	Lisa.Name = "Lisa";
	Lisa.weight = 110;
	Riff.Name = "Riff";
	Riff.weight = 180;
	printf("%d is the size of your hashtable\n\n", some_table.tablesize);

	putInside(&some_table, Lisa);
	putInside(&some_table, Riff);
	
	return 0;
}