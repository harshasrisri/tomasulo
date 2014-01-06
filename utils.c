# include "header.h"

/* extern char *optarg; */
/* extern int optind, opterr, optopt; */

char *inst_defn_file;
char *inst_trace_file;

void parse_args (int argc, char **argv) {
	int c;

	while ((c = getopt (argc, argv, "a:d:t:h")) != -1)
		switch (c) {
			case 'd' :
				inst_defn_file = strdup (optarg);
				pinfo ("Instruction Definition File set to : %s\n", inst_defn_file);
				break;
			case 't' :
				inst_trace_file = strdup (optarg);
				pinfo ("Instruction trace File set to : %s\n", inst_trace_file);
				break;
			case 'h' :
				pwarn ("Help file to come here\n");
				/* print_help(); */
				break;
			default :
				fatal ("Invalid command line option : -%c\n", c);
		}

	if (!inst_defn_file)
		pinfo ("Using default instruction definition file : %s\n", inst_defn_file = strdup (DEF_INSTR_DEFN_FILE));

	if (!inst_trace_file)
		pinfo ("Using default instruction trace file : %s\n", inst_trace_file = strdup (DEF_TRACE_FILE));
}
