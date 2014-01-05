#include "header.h"

Operation *ops = NULL;
int op_count = 0;

static void create_operation (char *line) {
	char name[20];
	int num_ops, latency;;

	if (!(op_count % 10))
		ops = (Operation *) realloc (ops, sizeof(Operation) * 10);

	sscanf (line, "%s %d %d", name, &num_ops, &latency);

	if (!name[0])
		fatal ("OP name not proper in %s\n", line);
	ops[op_count].name = strdup (name);

	if (0 == num_ops)
		fatal ("Operand count not proper in %s\n", line);
	ops[op_count].num_ops = num_ops;

	if (0 == latency)
		fatal ("Latency not proper in %s\n", line);
	ops[op_count].latency = latency;

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
