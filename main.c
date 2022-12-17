#include "monty.h"

/**
 * main - Program entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success
 */

int main(int ac, __attribute__((unused)) char **av)
{
	_stack_t *stack = malloc(sizeof(_stack_t));

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	read_file(av[1], &stack);
	free_stack_t(stack);
	return (0);
}
