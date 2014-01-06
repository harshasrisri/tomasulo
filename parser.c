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
	else if (type == 'F') {
		ops[op_count].type = FLOAT;
		strcpy (typ, "Floating Point");
	}
	else if (type == 'C') {
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

void parse_file (char *file_name, char file_type) {
	char line[200];
	int i;
	FILE *fp = fopen (file_name, "r");

	if (!fp)
		fatal ("Can't open definition file\n");

	while (fgets (line, 200, fp)) {

		for (i = 0; isspace (line[i]); i++)
			;

		if (!line[i]) continue;

		if (line[i] == '#') continue;

		if (file_type == 'd')
			create_operation (&line[i]);
		else if (file_type == 't')
			;
			/* queue_instuction (&line[i]); */
		else
			fatal ("unknown file type to function : %c\n", file_type);
	}
}
