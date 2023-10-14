#include "main.h"

/**
 * malloc_check - checks for memory allocation failure
 *
 * @pointer: pointer to the allocated variable
 * Return: void
 */
void malloc_check(char *pointer)
{
	if (!pointer)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

/**
 * malloc_check_prev - checks for memory allocation failure
 *
 * @pointer: pointer to the allocated variable
 * @prev_alloc: free all the previous allocations
 * Return: void
 */

void malloc_check_prev(char *pointer, char *prev_alloc)
{

	if (!pointer)
	{
		perror("malloc failed");
		free(prev_alloc);
		exit(EXIT_FAILURE);
	}
}

/**
 * malloc_check_prev_double - checks for memory allocation failure
 *
 * @pointer: pointer to the allocated variable
 * @prev_alloc: free all the previous allocations
 * Return: void
 */

void malloc_check_prev_double(char **pointer, char *prev_alloc)
{

	if (!pointer)
	{
		perror("malloc failed");
		free(prev_alloc);
		exit(EXIT_FAILURE);
	}
}
/**
 * malloc_check_all - checks for memory allocation failure and free
 * all the memoryin the heap
 *
 * @pointer: pointer to the allocated variable
 * @prev_alloc: previously allocated variables in the heap
 * @pointers: freeing each element in the array of arrays
 * @i: number of elements in the array
 *
 * Return: void
 */
void malloc_check_all(char *pointer, char *prev_alloc, char **pointers, int i)
{
	if (!pointer)
	{
		perror("malloc failed free all");
		free(prev_alloc);
		while (i--)
		{
			free(pointers[i]);
		}
		free(pointers);
		exit(EXIT_FAILURE);
	}
}
