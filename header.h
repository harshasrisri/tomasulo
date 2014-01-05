#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define fatal(fmt, ...) do {fprintf(stderr, "[FATAL] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); exit(--err_count); } while (0)
#define perr(fmt, ...)  do {fprintf(stderr, "[ERROR] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define pwarn(fmt, ...) do {fprintf(stderr,  "[WARN] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#define pinfo(fmt, ...) do {fprintf(stderr,  "[INFO] (%s:%d) " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)

#define DEFAULT_DEFINITION_FILE "instr.def"
#define DEFAULT_TRACE_FILE "trace"

typedef struct {
	char *name;
	int num_ops;
	int latency;
} Operation;

extern int err_count;
extern char *inst_defn_file;
extern char *inst_trace_file;

extern void parse_args (int argc, char **argv);
extern int line_2_words (char ***words, char *line, char *temp_delim);
extern void define_operations (void);
