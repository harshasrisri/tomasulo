#include "header.h"

Operation *ops = NULL;
int op_count = 0;

static void create_operation (char *line) {
	char **definition;
	int fields, temp;

	if (!(op_count % 10))
		ops = (Operation *) realloc (ops, sizeof(Operation) * 10);

	fields = line_2_words (&definition, line, ":");

	if (fields != 3)
		fatal ("Invalid instruction definition : %s\n", line);

	if (!definition)
		fatal ("Something's wrong in the code parsing definitions\n");

	if (!definition[0])
		fatal ("definition[0] not proper\n");
	ops[op_count].name = strdup (definition[0]);

	if (!definition[1] || 0 == (temp = atoi(definition[1])))
		fatal ("definition[1] not proper\n");
	ops[op_count].num_ops = temp;

	if (!definition[2] || 0 == (temp = atoi(definition[2])))
		fatal ("definition[2] not proper\n");
	ops[op_count].latency = temp;

	op_count++;
}

void define_operations (void) {
	char line[200];
	int i;
	FILE *defn_file = fopen (inst_defn_file, "r");

	if (!defn_file)
		fatal ("Can't open definition file\n");

	while (fgets (line, 200, defn_file)) {

		for (i = 0; isspace (line[i]); i++)
			;

		if (!line[i]) continue;

		if (line[i] == '#') continue;

		create_operation (&line[i]);
	}

	for (i = 0; i < op_count; i++)
		printf ("%s %d %d\n", ops[i].name, ops[i].num_ops, ops[i].latency);
}
