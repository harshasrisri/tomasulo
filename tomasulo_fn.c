#include"header.h"

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


