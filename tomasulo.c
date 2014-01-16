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

static void update_rs_exec(int stn_type, int no_stn)
{
	RS *rsrv_stn;
	int rs_no = 0;

	/*Find the reservation station requested */
	switch(stn_type){
		case FP_ADD : rsrv_stn = RES_STN(add,_fp);
						  break;
		case FP_MUL : rsrv_stn = RES_STN(mul,_fp);
						  break;
		case INT_ADD: rsrv_stn = RES_STN(add,_int);
						  break;
		case INT_MUL: rsrv_stn = RES_STN(mul,_int);
						  break;
		case LD : rsrv_stn = RES_STN(ld,);
						  break;
		case SD : rsrv_stn = RES_STN(sd,);
						  break;

		default : fatal("Access to a non existed reservation station requested"); 
		
		}

	/*Cycle through_ Reservation Stations of the given type*/
	while(rs_no<no_stn){

		if(rsrv_stn[rs_no].status == BUSY){
			
			if((rsrv_stn[rs_no].qj == NULL)&&(rsrv_stn[rs_no].qk == NULL)){

				/*if the timer has not been set ,set it to the instruction latency*/
				if(rsrv_stn[rs_no].timer==0){
					rsrv_stn[rs_no].timer = rsrv_stn[rs_no].instr->latency; /*TO DO Move the latency to RS ?*/
					rsrv_stn[rs_no].instr->exec_time = cycles;
				}
				else
					rsrv_stn[rs_no].timer--;
			}
		}
	
		rs_no++;
	}
}

static void update_rs_write(int stn_type, int no_stn)
{
	RS *rsrv_stn;
	int rs_no = 0;

	/*Find the reservation station requested */
	switch(stn_type){
		case FP_ADD : rsrv_stn = RES_STN(add,_fp);
						  break;
		case FP_MUL : rsrv_stn = RES_STN(mul,_fp);
						  break;
		case INT_ADD: rsrv_stn = RES_STN(add,_int);
						  break;
		case INT_MUL: rsrv_stn = RES_STN(mul,_int);
						  break;
		case LD : rsrv_stn = RES_STN(ld,);
						  break;
		case SD : rsrv_stn = RES_STN(sd,);
						  break;
		default : fatal("Access to a non existed reservation station requested"); 
		
		}

	/*Cycle through the Reservation Stations of the given type*/
	while(rs_no<no_stn){
	 
	/*check if any RS is ready to move to write back stage*/
		if(rsrv_stn[rs_no].status == BUSY){
			
			if((rsrv_stn[rs_no].qj == NULL)&&(rsrv_stn[rs_no].qk == NULL)){

				/*if the functional unit has completed execution*/
				if(rsrv_stn[rs_no].timer == 0){
					rsrv_stn[rs_no].status = RESULT_READY;
				}
			}
		}
	
	 /*Also check if any RS will complete write back this cycle*/
		else if(rsrv_stn[rs_no].status == RESULT_READY){
			
			/*update the write back time */
			rsrv_stn[rs_no].instr->write_time = cycles;
			
			/*Flust the instruction and reset the reservation station */
			rsrv_stn[rs_no].status = AVAILABLE;
			rsrv_stn[rs_no].instr = NULL;		
			rsrv_stn[rs_no].qj = rsrv_stn[rs_no].qk = NULL;

		}
		
		rs_no++;
	}
}

void execute()
{
	/*Update the fields of all the reservations stations*/
 	update_rs_exec(FP_ADD,NUM_FLT_ADD_RS);
 	update_rs_exec(FP_MUL,NUM_FLT_MUL_RS);
	update_rs_exec(INT_ADD,NUM_INT_ADD_RS);
	update_rs_exec(INT_MUL,NUM_INT_MUL_RS);
	update_rs_exec(LD,NUM_LD_RS);
	update_rs_exec(SD,NUM_SD_RS);

}

void write_back()
{
 	update_rs_write(FP_ADD,NUM_FLT_ADD_RS);
 	update_rs_write(FP_MUL,NUM_FLT_MUL_RS);
	update_rs_write(INT_ADD,NUM_INT_ADD_RS);
	update_rs_write(INT_MUL,NUM_INT_MUL_RS);
	update_rs_write(LD,NUM_LD_RS);
	update_rs_write(SD,NUM_SD_RS);
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
	rs->instr = curr;

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

		issue ();

		execute ();
		
		write_back();

	}

	finish ();

	return 0;
}
