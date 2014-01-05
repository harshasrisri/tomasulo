#include "header.h"

Operation *ops = NULL;
int op_count = 0;

static void create_operation (char *line) {
	char name[20], typ[20];
	int num_ops, latency; 
	char type;

	if (!(op_count % 10))
		ops = (Operation *) realloc (ops, sizeof(Operation) * 10);

	if (NUM_FIELDS != sscanf (line, "%s %d %d %c", name, &num_ops, &latency, &type))
		fatal ("Invalid number of fields in instruction definition : %s\n", line);

	if (!name[0])
		fatal ("OP name not proper : %s\n", line);
	ops[op_count].name = strdup (name);

	if (0 == num_ops)
		fatal ("Operand count not proper : %s\n", line);
	ops[op_count].num_ops = num_ops;

	if (0 == latency)
		fatal ("Latency not proper : %s\n", line);
	ops[op_count].latency = latency;

	if (type == 'I') {
		ops[op_count].type = INTEGER;
		strcpy (typ, "Integer");
	}
	if (type == 'F') {
		ops[op_count].type = FLOAT;
		strcpy (typ, "Floating Point");
	}
	if (type == 'C') {
		ops[op_count].type = COMMON;
		strcpy (typ, "Common");
	}
	else
		fatal ("Unknown instruction type : %s\n", line);

	pinfo ("%s operation %s defined taking %d operands with latency %d\n", 
			typ,
			ops[op_count].name, 
			ops[op_count].num_ops, 
			ops[op_count].latency);

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
}
