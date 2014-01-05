#include <stdio.h>
#include <unistd.h>

#define perr(fmt, ...) fprintf(stderr, "[ERROR] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define pwarn(fmt, ...) fprintf(stderr, "[WARN] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define pinfo(fmt, ...) fprintf(stderr, "[INFO] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

typedef struct {
	char *name;
	int num_ops;
	int latency;
} Instruction;

extern char *inst_defn_file;
extern char *inst_trace_file;

extern void parse_args (int argc, char **argv);
extern int line_2_words (char ***words, char *line, char *temp_delim);
