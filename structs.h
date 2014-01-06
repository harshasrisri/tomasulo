
enum instr_type { UNDEFINED, INTEGER, FLOAT , COMMON };

enum rs_status { UNKNOWN, AVAILABLE, BUSY, RESULT_READY };

typedef struct {
	char *name;
	int num_ops;
	int latency;
	enum instr_type type;
} Operation;

typedef struct {
	char *opcd;
	char *dest;
	char *src_one;
	char *src_two;
	int no_op;
	int latency;
	unsigned int issue_time;
	unsigned int exec_time;
	unsigned int write_time;
} Instruction;

typedef struct {
	enum rs_status status;
	char *op;
	struct resrv_stn *qj;
	struct resrv_stn *qk;
	int timer;
} resrv_stn;

typedef struct resrv_stn RS;
