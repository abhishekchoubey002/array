#include <stdio.h>
#include "array.h"

int main(void)
{
	c_array* arr;

	arr = new_array(5, INTEGER);
	if(!arr)
		fprintf(stderr, "%s", array_errbuf);
	else
		fprintf(stderr, "got array\n");
	return 0;
}