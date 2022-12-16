#include "monty.h"

void free_stack_t(_stack_t *head)
{
	_stack_t *node, *next_node;

	if (head)
	{
		node = head;
		next_node = head->next;
		while (next_node)
		{
			free(node);
			node = next_node;
			next_node = next_node->next;
		}
		free(node);
	}
}

char *strip(char **str)
{
	char *bc = malloc(sizeof(strlen(*str)));

	bc = strtok(*str, "\n");
	if (bc)
		*str = bc;
	return (*str);
}

void (*get_op(char *opcode))(_stack_t **, size_t line)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{NULL, NULL}};
	int i = 0;

	while (ops[i].opcode)
	{
		if (!strcmp(opcode, ops[i].opcode))
			return (ops[i].f);
		i++;
	}
	return (NULL);
}
