#ifndef C_ARRAY
#define C_ARRAY

#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define ERRBUF_SIZE 256

typedef struct array_t {
	void* base;		/* base pointer to the array */
	int size;		/* total number of elements in array */
	int type;		/* type of array i.e. integer, char ... */
}c_array;

enum array_types { 
	TYPE_FIRST,
	INTEGER,
	CHAR,
	POINTER,
	TYPE_LAST
};

char array_errbuf[ERRBUF_SIZE];

static int sanity_check(int size, int type)
{
	int ret1, ret2;
	ret1 = ((size<=0) || (size>=INT_MAX));
	ret2 = ((type<=TYPE_FIRST) || (type>=TYPE_LAST));
	return ret1 || ret2;
}

static int c_array_new(const int ne, const int type, c_array** arr)
{
	int es; /* size of each element */
	int def_value; /* default value */
	switch(type)
	{
		case INTEGER:
			es = sizeof(int);
			def_value = -1;
			break;
		case CHAR:
			es = sizeof(char);
			def_value = '\0';
			break;
		case POINTER:
			es = sizeof(int*);
			def_value = '\0';
			break;
	}
	*arr = (c_array*)malloc(sizeof(c_array));
	(*arr)->base = calloc(ne, es);
	if(!((*arr)->base))
		return 1;
	(*arr)->size = ne;
	(*arr)->type = type;
	memset((*arr)->base, def_value, es*ne);
	return 0;
}

#if 0
static void  c_array_print(c_array* arr)
{
	int i;
	char* cast;
	char* fmt = NULL; /* format specifier */
	switch(arr->type)
	{
		case INTEGER:
			fmt = "d";
			cast="int*";
			break;
		case CHAR:
			fmt = "c";
			 break;
		case POINTER:
			fmt = "p";
			break;
	}
	for(i=0; i<arr->size; i++)
		fprintf(stdout, "%s", fmt, ()arr->base[i])
}
#endif

/* ne : number of elements, type = type of each element */
static void* new_array(int ne, int type)
{
	c_array* arr;

	if(sanity_check(ne, type)) {
		snprintf(array_errbuf, ERRBUF_SIZE, "Invalid size or type."
			"Size = %u, type = %u", ne, type);
		return NULL;
	}
	
	if(c_array_new(ne, type, &arr)) {
		snprintf(array_errbuf, ERRBUF_SIZE, 
			"%s", strerror(errno));
		return NULL;
	}
	return arr;
}

#endif