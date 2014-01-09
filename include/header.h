#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arch.h>
#include <structs.h>

#define fatal(fmt, ...) do {fprintf(stderr, "[FATAL] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); exit(-1); } while (0)
#define perr(fmt, ...)  do {fprintf(stderr, "[ERROR] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define pwarn(fmt, ...) do {fprintf(stderr,  "[WARN] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define pinfo(fmt, ...) do {fprintf(stderr,  "[INFO] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)

#define DELIMITERS " \t,"

extern char *inst_defn_file;
extern char *inst_trace_file;

extern void parse_args (int argc, char **argv);
extern void parse_file (char *file_name, char file_type);
extern void finish (void);

extern Operation *ops;
extern Instruction *iq;
extern int instr_count, instr_proc, op_count;
