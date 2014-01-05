# include "header.h"

extern char *optarg;
extern int optind, opterr, optopt;

void parse_args (int argc, char **argv) {

	while ((c = getopt (argc, argv, "dth:")) != 1) {
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
				perr ("Invalid command line option :%s\n", optarg);
				exit (-1);
		}
	}
}

static char *delim;
static inline int is_delim (char c) {
	char *temp = delim;
	do {
		if (c == *temp)
			return 1;
	} while (*++temp);
	return 0;
}

int line_2_words (char ***words, char *line, char *temp_delim) {
	char **sentence = NULL, *temp, *save, c;
	int word_count = 0, white = 1;

	if ((!line) || (!*line) || !temp_delim) {
		return 0;
	}

	delim = temp_delim;

	temp = (char *) malloc (50);
	save = temp;
	while (1) {
		c = *line++;
		if (is_delim(c) || (c == '\0')) {
			white = 1;
			if (is_delim(c)) continue;
		} 
		if (white) {
			white = 0;
			if (!(word_count % 10)) {
				sentence = (char **) realloc (sentence, (word_count + 10) * sizeof (char *));
			}
			*temp = '\0';
			if (*save) {
				temp = save;
				sentence[word_count++] = strdup(temp);
			}
			if ((c == '\0')) break;
		}
		*temp++ = c;
	}
	if (sentence) {
		sentence[word_count + 1] = '\0';
	}

	*words = sentence;

	delim = NULL;

	return word_count;
}
