#include "monty.h"

/**
 * add - add the top 2 vals in stack
 * @stack: stack ds
 * @n: potential line number
 *
 * Return: void
 */

void add(_stack_t **stack, __attribute__((unused)) unsigned int n)
{
	_stack_t *tmp = malloc(sizeof(_stack_t));

	if (*stack && (*stack)->n && (*stack)->next->n)
	{
		tmp = (*stack)->next;
		tmp->n = tmp->n + (*stack)->n;
		*stack = tmp;
		(*stack)->prev = NULL;
	}
	else
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", n);
		exit(EXIT_FAILURE);
	}
}

/**
 * nop - does nothing
 * @stack: stack ds
 * @n: potential line number
 *
 * Return: void
 */

void nop(_stack_t **stack, __attribute__((unused)) unsigned int n)
{
	(void)stack;
	(void)n;
}
