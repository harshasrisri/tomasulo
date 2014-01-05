#include "header.h"

int err_count = 0;

int main (int argc, char **argv) {

	parse_args (argc, argv);

	define_operations ();

}
