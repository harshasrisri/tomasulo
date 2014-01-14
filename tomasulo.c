#include "header.h"

Operation *ops = NULL;
Instruction *iq = NULL;

int op_count = 0;
int instr_count = 0;
int instr_proc = 0;
unsigned int cycles = 0;

RS *add_fp_rs;
RS *add_int_rs;
RS *mul_fp_rs;
RS *mul_int_rs;
RS *ld_rs;
RS *st_rs;

void create_arch()
{
	int i;
	add_fp_rs = malloc(NUM_FLT_ADD_RS*sizeof(RS));
	add_int_rs = malloc(NUM_INT_ADD_RS*sizeof(RS));
	mul_fp_rs = malloc(NUM_FLT_MUL_RS*sizeof(RS));
	mul_int_rs = malloc(NUM_INT_MUL_RS*sizeof(RS));
	ld_rs = malloc(NUM_LD_RS*sizeof(RS));
	sd_rs = malloc(NUM_SD_RS*sizeof(RS));
	
	if(!add_fp_rs || !add_int_rs || !mul_fp_rs || !mul_int_rs || !ld_rs || !sd_rs){
		fatal("Error creating the architecture\n");
	}

	for (i = 0; i < MAX_RS; i++) {
		if (i < NUM_FLT_ADD_RS) {
			add_fp_rs[i].status = AVAILABLE;
			add_fp_rs[i].timer = 0;
			add_fp_rs[i].qj = add_fp_rs[i].qj = NULL;
		}

		if (i < NUM_INT_ADD_RS) {
			add_int_rs[i].status = AVAILABLE;
			add_int_rs[i].timer = 0;
			add_int_rs[i].qj = add_int_rs[i].qj = NULL;
		}

		if (i < NUM_FLT_MUL_RS) {
			mul_fp_rs[i].status = AVAILABLE;
			mul_fp_rs[i].timer = 0;
			mul_fp_rs[i].qj = mul_fp_rs[i].qj = NULL;
		}

		if (i < NUM_INT_MUL_RS) {
			mul_int_rs[i].status = AVAILABLE;
			mul_int_rs[i].timer = 0;
			mul_int_rs[i].qj = mul_int_rs[i].qj = NULL;
		}

		if (i < NUM_LD_RS) {
			ld_rs[i].status = AVAILABLE;
			ld_rs[i].timer = 0;
			ld_rs[i].qj = ld_rs[i].qj = NULL;
		}

		if (i < NUM_SD_RS) {
			sd_rs[i].status = AVAILABLE;
			sd_rs[i].timer = 0;
			sd_rs[i].qj = sd_rs[i].qj = NULL;
		}
	}
}

void issue () {
	Instruction *curr = iq[instr_proc];

	if (!(strcmp ("ADD", curr->opc)) || !(strcmp ("SUB", curr->opc))) {
		for (i = 0; i < NUM_INT_ADD_RS; i++)
			if (add_int_rs[i].status == AVAILABLE)
				break;

	}
}

int main (int argc, char **argv) {

	parse_args (argc, argv);

	parse_file (inst_defn_file, 'd');

	parse_file (inst_trace_file, 't');

	create_arch();

	while (instr_proc < instr_count) {

		instr_proc++;	

		cycles++;
	}

	finish ();

	return 0;
}
