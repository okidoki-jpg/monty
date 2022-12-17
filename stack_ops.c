#include "monty.h"

/**
 * push - push int to stack ds
 * @stack: stack ds
 * @n: value to push
 *
 * Return: void
 */

void push(_stack_t **stack, size_t n)
{
	_stack_t *new = malloc(sizeof(_stack_t));

	if (new == NULL)
		exit(0);

	new->n = n;
	new->prev = NULL;
	new->next = *stack;

	if (*stack)
		(*stack)->prev = new;
	*stack = new;
}

/**
 * pall - print stack
 * @stack: stack ds
 * @n: potential line number
 *
 * Return: void
 */

void pall(_stack_t **stack, __attribute__((unused)) size_t n)
{
	_stack_t *tmp = *stack;

	while (tmp->next)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * pint - print top val in stack
 * @stack: stack ds
 * @n: potential line number
 *
 * Return: void
 */

void pint(_stack_t **stack, __attribute__((unused)) size_t n)
{
	_stack_t *tmp = *stack;

	if (tmp)
		printf("%d\n", tmp->n);
}
