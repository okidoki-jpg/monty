#include "monty.h"

int main(int ac, char **av)
{
	_stack_t *stack = malloc(sizeof(_stack_t));

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit (EXIT_FAILURE);
	}
	read_file(av[1], &stack);
	free_stack_t(stack);
	return (0);
}
