/*****************TOMASULO SIMULATOR************/
/* 		Author : Sudarshan Sargur 			   */
/* 		Date   : 1/4/2014                      */
/* 		Tomasulo_structures.h                  */
/***********************************************/


typedef struct {
	char *op;
	char *src_one;
	char *src_two;
	char *dest;
	int no_op;
	int latency;
	bool sched_flag;
	int issue_time;
	int exec_time;
	int write_time;
	} INSTR;
	
typedef struct {
	 bool busy;
	 char *op;
	 RES_FUNC *qj;
	 RES_FUNC *qk;
	 RES_MEM  *qj;
	 RES_MEM  *qk;
	 bool vj;
	 bool vk;
	 int timer;
	} RES_FUNC; 
	
