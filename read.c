#include "monty.h"

void read_file(char *file, _stack_t **stack)
{
	FILE *fp = fopen(file, "r");
	char *cmd = NULL, *cmds[3], *token;
	size_t len = 0, i = 0, line = 1;
	ssize_t read;

	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file);
		exit (EXIT_FAILURE);
	}

	while ((read = getline(&cmd, &len, fp)) != -1) 
	{
		token = strtok(cmd, " ");
		while (token)
		{
			cmds[i] = &*token;
			i++;
			if (i == 2)
				break;
			token = strtok(NULL, " ");
		}
		i = 0;

		if (!strcmp(strip(&cmds[0]), "push") && cmds[1])
		{
			if (!atoi(cmds[1]) && strcmp(strip(&cmds[1]), "0"))
			{
			}
			else if (!atoi(cmds[1]) || atoi(cmds[1]))
			{
				*stack = push(atoi(cmds[1]), &(*stack));
			}
		}
		else if (!strcmp(strip(&cmds[0]), "pall"))
		{
			pall(*stack);
		}
		else if (!strcmp(strip(&cmds[0]), "pint"))
		{
			pint(*stack);
		}
		else
			printf("L%d: unknown instruction %s\n", line, cmds[0]);

		line++;
		cmds[0] = cmds[1] = NULL;

	}

	fclose(fp);
	if (cmd)
		free(cmd);
	exit(EXIT_SUCCESS);

}

_stack_t *push(size_t n, _stack_t **stack)
{
	_stack_t *new = malloc(sizeof(_stack_t));
	
	if (new == NULL)
		return NULL;

	new->n = n;
	new->prev = NULL;
	new->next = *stack;

	if (*stack)
		(*stack)->prev = new;
	*stack = new;
	return (new);
}


void pall(_stack_t *stack)
{
	_stack_t *tmp = stack;

	while (tmp->next)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
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

void pint(_stack_t *stack)
{
	_stack_t *tmp = stack;

	if (tmp)
		printf("%d\n", tmp->n);
}
