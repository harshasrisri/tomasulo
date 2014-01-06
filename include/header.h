#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arch.h"
#include "structs.h"

#define fatal(fmt, ...) do {fprintf(stderr, "[FATAL] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); exit(--err_count); } while (0)
#define perr(fmt, ...)  do {fprintf(stderr, "[ERROR] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define pwarn(fmt, ...) do {fprintf(stderr,  "[WARN] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define pinfo(fmt, ...) do {fprintf(stderr,  "[INFO] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)

#define DEF_INSTR_DEFN_FILE "instr.def"
#define DEF_TRACE_FILE "trace"

extern int err_count;
extern char *inst_defn_file;
extern char *inst_trace_file;

extern void parse_args (int argc, char **argv);
extern void parse_file (char *file_name, char file_type);
