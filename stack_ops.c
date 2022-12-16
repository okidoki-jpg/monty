#include "monty.h"

void _push(_stack_t **stack, size_t n)
{
	_stack_t *new = malloc(sizeof(_stack_t));

	if (new == NULL)
		exit (0);

	new->n = n;
	new->prev = NULL;
	new->next = *stack;

	if (*stack)
		(*stack)->prev = new;
	*stack = new;
}

void _pall(_stack_t **stack, __attribute__((unused)) size_t n)
{
	_stack_t *tmp = *stack;

	while (tmp->next)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

void _pint(_stack_t **stack, __attribute__((unused)) size_t n)
{
	_stack_t *tmp = *stack;

	if (tmp)
		printf("%d\n", tmp->n);
}
