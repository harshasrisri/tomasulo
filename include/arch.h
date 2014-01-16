/* Default file to look for definition of instructions */
#define DEF_INSTR_DEFN_FILE "instr.def"

/* Default file to look for instruction trace */
#define DEF_TRACE_FILE "trace"

/* No of Integer registers */
#define NUM_INT_REGS 20

/* No of Floating point registers */
#define NUM_FLOAT_REGS 20

/* Reservation station count for each of */
/* RSs for LD */
#define NUM_LD_RS 2

/* RSs for SD */
#define NUM_SD_RS 2

/* RSs for Integer Adders */
#define NUM_INT_ADD_RS 4

/* RSs for Integer Multipliers */
#define NUM_INT_MUL_RS 2

/* RSs for FP Adders */
#define NUM_FLT_ADD_RS 4

/* RSs for FP Multipliers */
#define NUM_FLT_MUL_RS 2

/*Reservation station IDs */
#define FP_ADD 0

#define FP_MUL 1

#define INT_ADD 2

#define INT_MUL 3

#define LD 4

#define SD 5

/* MAX number of Reservation stations */
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAX_RS MAX( \
		MAX(NUM_LD_RS,NUM_SD_RS),MAX( \
			MAX(NUM_INT_ADD_RS,NUM_INT_MUL_RS),MAX(NUM_FLT_ADD_RS,NUM_FLT_MUL_RS)))

/*Macro to form the reservation station pointers*/
/*Operation -add or mul or ld or sd*/
/*Type - _fp or _int (note the _)*/
#define RES_STN(operation,type)  operation##type##_rs
