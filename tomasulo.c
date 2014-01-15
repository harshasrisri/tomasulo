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
	add_fp_rs = malloc(NUM_FLT_ADD_RS*sizeof(RS));
	add_int_rs = malloc(NUM_INT_ADD_RS*sizeof(RS));
	mul_fp_rs = malloc(NUM_FLT_MUL_RS*sizeof(RS));
	mul_int_rs = malloc(NUM_INT_MUL_RS*sizeof(RS));
	ld_rs = malloc(NUM_LD_RS*sizeof(RS));
	sd_rs = malloc(NUM_SD_RS*sizeof(RS));
	
	if(!add_fp_rs || !add_int_rs || !mul_fp_rs || !mul_int_rs || !ld_rs || !sd_rs){
		fatal("Error creating the architecture");
	}
}

RS *is_op_used(char *src)
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
					timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				}
				else
					timer--;
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
					timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				}
				else
					timer--;
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
					timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					timer--;
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
					timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					timer--;
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
					timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					timer--;
			}

		rs_no++;
		}
	 

	/*STORE Reservation stations*/ 
	 while(rs_no<NUM_SD_RS){

		if(sd_rs[rs_no].status == BUSY){
		
			cur_instr = sd_rs[rs_no].instr_no;	
			
				/*if the timer has not been set ,set it to the instruction latency*/
				if(sd_rs[rs_no].timer==0){
					timer = iq[cur_instr].latency;   /*TO DO Move the latency to RS ?*/
					iq[cur_instr].exec_time = cycles;
				} 
				else 
					timer--;
			}
		rs_no++;
		
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
