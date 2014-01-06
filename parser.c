#include "header.h"

Operation *ops = NULL;
Instruction *iq = NULL;

int op_count = 0;
int instr_count = 0;

static void create_operation (char *line) {
	char name[20], typ[20];
	int num_ops, latency; 
	char type;

	if (!(op_count % 10))
		ops = (Operation *) realloc (ops, sizeof(Operation) * 10);

	if (NUM_OP_DEFN_FIELDS != sscanf (line, "%s %d %d %c", name, &num_ops, &latency, &type))
		fatal ("Invalid number of fields in instruction definition : %s\n", line);

	if (!name[0])
		fatal ("OP name not proper : %s\n", line);
	ops[op_count].name = strdup (name);

	if (0 > num_ops)
		fatal ("Operand count not proper : %s\n", line);
	ops[op_count].num_ops = num_ops;

	if (0 >= latency)
		fatal ("Latency not proper : %s\n", line);
	ops[op_count].latency = latency;

	if ('I' == type) {
		ops[op_count].type = INTEGER;
		strcpy (typ, "Integer");
	}
	else if ('F' == type) {
		ops[op_count].type = FLOAT;
		strcpy (typ, "Floating Point");
	}
	else if ('C' == type) {
		ops[op_count].type = COMMON;
		strcpy (typ, "Common");
	}
	else
		fatal ("Unknown instruction type : %s\n", line);

	pinfo ("Definition %d : %s operation %s defined taking %d operands with latency %d\n",
			op_count, typ, ops[op_count].name, ops[op_count].num_ops, 
			ops[op_count].latency);

	op_count++;
}

static int lookup_definition (char *opcode, Operation *instr_defn) {
	int i;
	for (i = 0; i < op_count; i++)
		if (!strcmp (opcode, ops[i].name)) {
			*instr_defn = ops[i];
			return 1;
		}
	return 0;
}

static void queue_instuction (char *line) {
	char opcode[20];
	Operation instr_defn;
	
	if (!(instr_count % 10))
		iq = (Instruction *) realloc (iq, sizeof(Instruction) * 10);

	iq[instr_count].dest = iq[instr_count].src1 = iq[instr_count].src2 = 0;
	iq[instr_count].issue_time = iq[instr_count].exec_time = iq[instr_count].write_time = 0;

	sscanf (line, "%s", opcode);

	if (!lookup_definition (opcode, &instr_defn)) 
		fatal ("Undefined instruction : %s\n", line);

	iq[instr_count].opcd = strdup (strtok (line, DELIMITERS));

	if (instr_defn.num_ops > 0) iq[instr_count].dest = strdup (strtok (NULL, DELIMITERS));

	if (instr_defn.num_ops > 1) iq[instr_count].src1 = strdup (strtok (NULL, DELIMITERS));

	if (instr_defn.num_ops > 2) iq[instr_count].src2 = strdup (strtok (NULL, DELIMITERS));

	iq[instr_count].num_ops = instr_defn.num_ops;

	iq[instr_count].latency = instr_defn.latency;

	pinfo ("Instruction %d : %s %s, %s, %s \n", instr_count, 
			iq[instr_count].opcd, iq[instr_count].dest,
			iq[instr_count].src1, iq[instr_count].src2);

	instr_count++;
}

void parse_file (char *file_name, char file_type) {
	char line[200];
	int i;
	FILE *fp = fopen (file_name, "r");

	if (!fp)
		fatal ("Can't open definition file : %s\n", file_name);

	while (fgets (line, 200, fp)) {

		for (i = 0; isspace (line[i]); i++)
			;

		if (!line[i]) continue;

		if (line[i] == '#') continue;

		* (strchr (line, '\n')) = '\0';

		switch (file_type) {
			case 'd' :
				create_operation (&line[i]);
				break;
			case 't' :
				queue_instuction (&line[i]);
				break;
			default :
				fatal ("unknown file type to function : %c\n", file_type);
		}
	}
}
