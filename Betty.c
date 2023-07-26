#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * add_numbers - function to add numbers.
 * @numx: The first number to be added.
 * @numy: The second number to be added.
 * Return: The sum of @numx and @numy.
 */
int add_numbers(int numx, int numy)
{
return (numx + numy);
}
int main(void)
{
int result = add_numbers(5, 12);
char result_str[30];
int length = snprintf(result_str,
	sizeof(result_str), "The result is: %d\n", result);
write(1, result_str, length);
return (0);
}

