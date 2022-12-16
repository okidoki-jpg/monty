#include "monty.h"

void read_file(char *file, _stack_t **stack)
{
	FILE *fp = fopen(file, "r");
	char *cmd = NULL, *cmds[3], *token;
	size_t len = 0, i = 0, line = 1, n;
	ssize_t read;
	void (*instruction_t)(_stack_t **, size_t);

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

		if (!strcmp(strip(&cmds[0]), "push") &&
			(atoi(cmds[1]) > 0 || !strcmp(cmds[1], "0")))
		{
			instruction_t = NULL;
			n = atoi(cmds[1]);
			instruction_t = get_op(cmds[0]);
			if (!instruction_t)
			{
				printf("L%d: unknown instruction %s\n", line, cmds[0]);
				exit (EXIT_FAILURE);
			}
			instruction_t(&(*stack), n);
		}
		else if (cmds[0])
		{
			instruction_t = NULL;
			instruction_t = get_op(strip(&cmds[0]));
			if (instruction_t == NULL)
			{
				printf("L%d: unknown instruction %s\n", line, cmds[0]);
				exit (EXIT_FAILURE);
			}
			instruction_t(&(*stack), line);
			//_pall(stack, line);
			//printf("--%p @ %s\n", instruction_t, cmds[0]);
		}
		/*else if (!strcmp(strip(&cmds[0]), "pall"))
		  {
		  pall(*stack);
		  }
		  else if (!strcmp(strip(&cmds[0]), "pint"))
		  {
		  pint(*stack);
		  }
		  else
		  {
		  printf("L%d: unknown instruction %s\n", line, cmds[0]);
		  exit (EXIT_FAILURE);
		  }

		if (instruction_t == NULL)
		{
			printf("L%d: unknown instruction %s\n", line, cmds[0]);
			exit (EXIT_FAILURE);
		}*/
		//printf("%s @ --%p\n", cmds[0], instruction_t);
		//instruction_t(&(*stack), line);

		line++;
		cmds[0] = cmds[1] = NULL;
		instruction_t = NULL;

	}

	fclose(fp);
	if (cmd)
		free(cmd);
	exit(EXIT_SUCCESS);

}

void _push(_stack_t **stack, size_t n)
{
	_stack_t *new = malloc(sizeof(_stack_t));

	if (new == NULL)
		//return 1;
		exit (0);

	new->n = n;
	new->prev = NULL;
	new->next = *stack;

	if (*stack)
		(*stack)->prev = new;
	*stack = new;
	//return (0);
}

void (*push)(_stack_t **stack, size_t n) = _push;

void _pall(_stack_t **stack, __attribute__((unused)) size_t n)
{
	_stack_t *tmp = *stack;

	while (tmp->next)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
void (*pall)(_stack_t **stack, __attribute__((unused)) size_t n) = _pall;

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

void _pint(_stack_t **stack, __attribute__((unused)) size_t n)
{
	_stack_t *tmp = *stack;

	if (tmp)
		printf("%d\n", tmp->n);
}
void (*pint)(_stack_t **stack, __attribute__((unused)) size_t n) = _pint;

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
