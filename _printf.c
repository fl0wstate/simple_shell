#include "main.h"

/**
 * _printf - prints only unsigned int and
 *  string datatype pass since that the most
 *  commonly use of this function on the shell
 *  project
 * @format: string pointer
 * Return: len of the string
 */

int _printf(const char *format, ...)
{
	va_list ap;
	int index_arr_no, i = 0;
	size_t count = 0;
	specifiers_x formats[] = {
		{'u', _ui_arg},
		{'s', _string_arg},
		{0, NULL}
	};
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			index_arr_no = 0;
			while (formats[index_arr_no].form_t)
			{
				if (format[i] == formats[index_arr_no].form_t)
				{
					count += formats[index_arr_no].call(&ap);
					break;
				}
				index_arr_no++;
			}
			if (formats[index_arr_no].form_t == 0)
				count += write(STDOUT_FILENO, &format[i], 1);
		}
		else
			count += write(STDOUT_FILENO, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

/**
 * _string_arg - prints a string format type
 * @ap: list of indefinite arguments number
 * Return: 0 (success)
 */
int _string_arg(va_list *ap)
{
	char *s;

	s = va_arg(*ap, char *);
	if (!s)
	{
		s = "(null)";
	}
	return ((unsigned int)(write(STDOUT_FILENO, s, _strlen(s))));
}
/**
 * _ui_arg - returns an unsigned int value
 *
 * @ap: list of indefinite arguments
 * Return: value to be printed
 */
int _ui_arg(va_list *ap)
{
	int retrive = 0;
	int mask = 0, mask_cpy = 0;
	ui result = 0;
	char *buf = NULL;

	retrive = va_arg(*ap, int);
	/* absolute functions */
	mask = retrive >> (sizeof(int) * 8 - 1);
	result = (retrive ^ mask) - mask;
	buf = malloc(sizeof(char) * (digit_counter(result) + 1));
	mask = 0;
	while (result > 0)
	{
		buf[mask++] = (result % 10) + '0';
		result /= 10;
	}
	mask_cpy = mask;
	/* check me out here **^^ */
	while (--mask_cpy >= 0)
	{
		write(STDOUT_FILENO, &buf[mask_cpy], 1);
	}
	free(buf);
	return (mask);
}
/**
 * digit_counter - counts the number of digits present
 * @num: digits passed
 * Return: number of digits present
 */
ui digit_counter(int num)
{
	unsigned int temp = 0, count = 0;

	temp = num;
	count = (temp == 0) ? 1 : 0;
	while (temp != 0)
	{
		temp /= 10;
		count++;
	}
	return (count);
}
