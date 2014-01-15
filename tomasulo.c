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
RS *sd_rs;

void create_arch()
{
	int i;
	add_fp_rs = malloc (NUM_FLT_ADD_RS * sizeof (RS));
	add_int_rs = malloc (NUM_INT_ADD_RS * sizeof (RS));
	mul_fp_rs = malloc (NUM_FLT_MUL_RS * sizeof (RS));
	mul_int_rs = malloc (NUM_INT_MUL_RS * sizeof (RS));
	ld_rs = malloc (NUM_LD_RS * sizeof (RS));
	sd_rs = malloc (NUM_SD_RS * sizeof (RS));
	
	if(!add_fp_rs || !add_int_rs || !mul_fp_rs || !mul_int_rs || !ld_rs || !sd_rs){
		fatal("Error creating the architecture\n");
	}

	for (i = 0; i < MAX_RS; i++) {
		if (i < NUM_FLT_ADD_RS) {
			add_fp_rs[i].status = AVAILABLE;
			add_fp_rs[i].timer = 0;
			add_fp_rs[i].qj = add_fp_rs[i].qk = NULL;
		}

		if (i < NUM_INT_ADD_RS) {
			add_int_rs[i].status = AVAILABLE;
			add_int_rs[i].timer = 0;
			add_int_rs[i].qj = add_int_rs[i].qk = NULL;
		}

		if (i < NUM_FLT_MUL_RS) {
			mul_fp_rs[i].status = AVAILABLE;
			mul_fp_rs[i].timer = 0;
			mul_fp_rs[i].qj = mul_fp_rs[i].qk = NULL;
		}

		if (i < NUM_INT_MUL_RS) {
			mul_int_rs[i].status = AVAILABLE;
			mul_int_rs[i].timer = 0;
			mul_int_rs[i].qj = mul_int_rs[i].qk = NULL;
		}

		if (i < NUM_LD_RS) {
			ld_rs[i].status = AVAILABLE;
			ld_rs[i].timer = 0;
			ld_rs[i].qj = ld_rs[i].qk = NULL;
		}

		if (i < NUM_SD_RS) {
			sd_rs[i].status = AVAILABLE;
			sd_rs[i].timer = 0;
			sd_rs[i].qj = sd_rs[i].qk = NULL;
		}
	}
}

RS *dep_lookup(char *src)
{
	int instr = instr_proc-1;

	while(instr>0){
		if(!strcmp(iq[instr].dest,src)){
			return iq[instr].cur;
		}
		instr--;
	}

	return NULL;
}

void execute()
{
	int rs_no=0;
	int cur_instr=0;
	
	/*For each RS, cycle through and check which is ready for execution*/
	
	/*FP ADDER Reservation stations*/
	while(rs_no<NUM_FLT_ADD_RS){

		if(add_fp_rs[rs_no].status == BUSY){
			cur_instr = add_fp_rs[rs_no].instr_no;	
			
			if((add_fp_rs[rs_no].qj == NULL)&&(add_fp_rs[rs_no].qk == NULL)){

				/*if the timer has not been set ,set it to the instruction latency*/
				if(add_fp_rs[rs_no].timer==0){
					add_fp_rs[rs_no].timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				}
				else
					add_fp_rs[rs_no].timer--;
			}
		}
	
		rs_no++;
	}

    rs_no=0;

	/*INT ADDER Reservation stations*/ 
	while(rs_no<NUM_INT_ADD_RS){

		if(add_int_rs[rs_no].status == BUSY){
		
			cur_instr = add_int_rs[rs_no].instr_no;	
			
			if((add_int_rs[rs_no].qj == NULL)&&(add_int_rs[rs_no].qk == NULL)){

				/*if the timer has not been set ,set it to the instruction latency*/
				if(add_int_rs[rs_no].timer==0){
					add_int_rs[rs_no].timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				}
				else
					add_int_rs[rs_no].timer--;
			}
		}
	
		rs_no++;
	}

	  rs_no=0;
	 
	/*FP MULTIPLIER Reservation stations*/ 
	while(rs_no<NUM_FLT_MUL_RS){

		if(mul_fp_rs[rs_no].status == BUSY){
		
			cur_instr = mul_fp_rs[rs_no].instr_no;	
			
			if((mul_fp_rs[rs_no].qj == NULL)&&(mul_fp_rs[rs_no].qk == NULL)){

				/*if the timer has not been set ,set it to the instruction latency*/
				if(mul_fp_rs[rs_no].timer==0){
					mul_fp_rs[rs_no].timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					mul_fp_rs[rs_no].timer--;
			}
		}
	
		rs_no++;
	}


	/*INT MULTIPLIER Reservation stations*/ 
  	 while(rs_no<NUM_INT_MUL_RS){

		if(mul_int_rs[rs_no].status == BUSY){
		
			cur_instr = mul_int_rs[rs_no].instr_no;	
			
			if((mul_int_rs[rs_no].qj == NULL)&&(mul_int_rs[rs_no].qk == NULL)){

				/*if the timer has not been set ,set it to the instruction latency*/
				if(mul_int_rs[rs_no].timer==0){
					mul_int_rs[rs_no].timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					mul_int_rs[rs_no].timer--;
			}
		}
	
		rs_no++;
	}


	/*LOAD Reservation stations*/ 
	 while(rs_no<NUM_LD_RS){

		if(ld_rs[rs_no].status == BUSY){
		
			cur_instr = ld_rs[rs_no].instr_no;	
			
				/*if the timer has not been set ,set it to the instruction latency*/
				if(ld_rs[rs_no].timer==0){
					ld_rs[rs_no].timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					ld_rs[rs_no].timer--;
			}

		rs_no++;
		}
	 

	/*STORE Reservation stations*/ 
	 while(rs_no<NUM_SD_RS){

		if(sd_rs[rs_no].status == BUSY){
		
			cur_instr = sd_rs[rs_no].instr_no;	
			
				/*if the timer has not been set ,set it to the instruction latency*/
				if(sd_rs[rs_no].timer==0){
					sd_rs[rs_no].timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					sd_rs[rs_no].timer--;
			}
		rs_no++;
		
	 	}

}

void issue () {
	int i, rs_count;
	Instruction *curr;
	RS *rs_type, *rs;
	curr = &iq[instr_proc];

	/* Based on the opcode type, assign a common looping pointer and a counter {{{ */ 
	if (!(strcmp ("ADD", curr->opcd)) || !(strcmp ("SUB", curr->opcd))) {
		rs_count = NUM_INT_ADD_RS; rs_type = add_int_rs;
	}
	else if (!(strcmp ("ADDD", curr->opcd)) || !(strcmp ("SUBD", curr->opcd))) {
		rs_count = NUM_FLT_ADD_RS; rs_type = mul_int_rs;
	}
	else if (!(strcmp ("MUL", curr->opcd)) || !(strcmp ("DIV", curr->opcd))) {
		rs_count = NUM_INT_MUL_RS; rs_type = add_fp_rs;
	}
	else if (!(strcmp ("MULD", curr->opcd)) || !(strcmp ("DIVD", curr->opcd))) {
		rs_count = NUM_FLT_MUL_RS; rs_type = mul_fp_rs;
	}
	else if (!(strcmp ("LD", curr->opcd))) {
		rs_count = NUM_LD_RS; rs_type = ld_rs;
	}
	else if (!(strcmp ("SD", curr->opcd))) {
		rs_count = NUM_SD_RS; rs_type = sd_rs;
	}
	/* }}} */

	/* Grab the first available RS of the type selected in the previous step {{{ */
	for (i = 0; i < rs_count; i++)
		if (rs_type[i].status == AVAILABLE)
			break;

	/* If all the RS are occupied, simply return back without incrementing */ 
	/* the number of instructions executed. this causes the subsequent issue */
	/* call to process the same instruction for issuing */ 

	if (i >= rs_count) return;

	/* }}} */

	/* now, the instruction is ready to be issued. we can get started */
	rs = &rs_type[i];
	rs->status = BUSY;

	if (curr->src1)
		rs->qj = dep_lookup (curr->src1);

	if (curr->src2)
		rs->qk = dep_lookup (curr->src2);

	curr->issue_time = cycles;
	instr_proc++;	
}

int main (int argc, char **argv) {

	parse_args (argc, argv);

	parse_file (inst_defn_file, 'd');

	parse_file (inst_trace_file, 't');

	create_arch();

	while (instr_proc < instr_count) {

		cycles++;
	}

	finish ();

	return 0;
}
