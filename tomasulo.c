#include "header.h"

Operation *ops = NULL;
Instruction *iq = NULL;

int op_count = 0;
int instr_count = 0;
int instr_proc = 0;

unsigned int cycles;

int main (int argc, char **argv) {

	parse_args (argc, argv);

	parse_file (inst_defn_file, 'd');

	parse_file (inst_trace_file, 't');

	while (instr_proc < instr_count) {

		instr_proc++;	

		cycles++;
	}

	return 0;
}
