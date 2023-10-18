#include "monty.h"

/**
 * execute_script - reads instructions from bytecod file and executes them
 */
void execute_script(void)
{
	char *line = NULL;
	size_t len = 0;
	int i;
	unsigned int line_number = 0;
	instruction_t ops[] = {
		{"push", _push}, {"pall", _pall}, {"pint", _pint},
		{"pop", _pop}, {"swap", _swap}, {"add", _add},
		{"nop", _nop}, {NULL, NULL}
	};
	stack_t *stack = NULL;

	while (getline(&line, &len, mem.pScript) != -1)
	{
		line_number++;
		/* Finds opcode in ops[] */
		mem.token = strtok(line, " \n");
		if (mem.token == NULL || mem.token[0] == '#')
			continue;
		for (i = 0; ops[i].opcode != NULL; i++)
		{
			if (strcmp(ops[i].opcode, mem.token) == 0)
			{
				mem.n = strtok(NULL, " \n");
				ops[i].f(&stack, line_number);
				break;
			}
		}
		if (ops[i].opcode == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, mem.token);
			free_all(stack);
			exit(EXIT_FAILURE);
		}
	}
	free_all(stack);
}
