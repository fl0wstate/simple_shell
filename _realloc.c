#include "main.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: size in bytes of the allocated space for `ptr`
 * @new_size: new size, in bytes of the new memory block
 *
 * Return: pointer to the newly allocated memory,
 * or `NULL`
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (0);
	}
	if (new_size == old_size)
		return (ptr);
	if (!ptr)
		return (malloc(new_size * sizeof(ptr)));

	return (adjust_book(ptr, old_size, new_size));
}
/**
 * adjust_book - adjust the book-keeping
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: size in bytes of the allocated space for `ptr`
 * @new_size: new size, in bytes of the new memory block
 *
 * Return: pointer
 */
void *adjust_book(char *ptr, unsigned int old_size, unsigned int new_size)
{
	size_t i, min = old_size;
	char *new_ptr;

	if (new_size < old_size)
		min = new_size;
	new_ptr = malloc(new_size);

	if (!new_ptr)
		return (0);

	for (i = 0; i < min; i++)
		new_ptr[i] = ptr[i];

	free(ptr);

	return (new_ptr);
}
