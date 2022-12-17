#include "monty.h"

void read_file(char *file, _stack_t **stack)
{
	FILE *fp = fopen(file, "r");
	char *cmd = NULL, **cmds;
	size_t len = 0, read, line = 1;
	void (*instruction_t)(_stack_t **, size_t);

	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&cmd, &len, fp)) != -1)
	{
		cmds = tokens(cmd);
		instruction_t = get_op(strip(&cmds[0]));

		if (!strcmp(strip(&cmds[0]), "push") && (atoi(cmds[1]) > 0 || !strcmp(cmds[1], "0")))
			instruction_t(&(*stack), atoi(cmds[1]));
		else if (cmds[0] && instruction_t)
			instruction_t(&(*stack), line);

		if (!instruction_t)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line, cmds[0]);
			exit(EXIT_FAILURE);
		}

		line++;
		free(cmds);
	}

	fclose(fp);
	if (cmd)
		free(cmd);
	exit(EXIT_SUCCESS);
}

char **tokens(char *cmd)
{
	char *token, **cmds = malloc(2);
	int i = 0;

	token = strtok(cmd, " ");
	while (token)
	{
		cmds[i] = &*token;
		i++;
		if (i == 2)
			break;
		token = strtok(NULL, " ");
	}
	return (cmds);
}
