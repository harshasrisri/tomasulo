# include "header.h"

/* extern char *optarg; */
/* extern int optind, opterr, optopt; */

char *inst_defn_file = DEFAULT_DEFINITION_FILE;
char *inst_trace_file = DEFAULT_TRACE_FILE;;

void parse_args (int argc, char **argv) {
	int c;

	while ((c = getopt (argc, argv, "d:t:h")) != -1)
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
				pinfo ("Help file to come here\n");
				/* print_help(); */
				break;
			default :
				fatal ("Invalid command line option : -%c\n", c);
		}
}
