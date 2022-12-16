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
				fprintf(stderr, "L%d: unknown instruction %s\n", line, cmds[0]);
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
				fprintf(stderr, "L%d: unknown instruction %s\n", line, cmds[0]);
				exit (EXIT_FAILURE);
			}
			instruction_t(&(*stack), line);
		}
		else
			if (instruction_t == NULL)
			{
				printf("L%d: unknown instruction %s\n", line, cmds[0]);
				exit (EXIT_FAILURE);
			}

		line++;
		cmds[0] = cmds[1] = NULL;
		instruction_t = NULL;

	}

	fclose(fp);
	if (cmd)
		free(cmd);
	exit(EXIT_SUCCESS);

}

void (*pall)(_stack_t **stack, __attribute__((unused)) size_t n) = _pall;
void (*push)(_stack_t **stack, size_t n) = _push;
void (*pint)(_stack_t **stack, __attribute__((unused)) size_t n) = _pint;

