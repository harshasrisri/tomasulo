
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
	char *src1;
	char *src2;
	int num_ops;
	int latency;
	struct resrv_stn *cur;
	unsigned int issue_time;
	unsigned int exec_time;
	unsigned int write_time;
} Instruction;

typedef struct {
	enum rs_status status;
	enum instr_type rs_type;
	int instr_no;
	struct resrv_stn *qj;
	struct resrv_stn *qk;
	int timer;
} resrv_stn;

typedef struct resrv_stn RS;
