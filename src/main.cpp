#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include "frequency_table.hpp"

static int total_time_elapsed;

struct options {
	bool quiet;
	bool print_table = false;
	int num_threads;
	std::string file_name;
};

int main(int argc, char* argv[]) {
	int c;
	options opt;
	char* opt_value;
	timeval start, end;

	while ((c = getopt (argc, argv, "qt:f:p")) != -1)
		switch (c)
		{
		case 'q':
			opt.quiet = true;
			printf("Quiet mode set\n");
			break;
		case 't':
			opt_value = optarg;
			opt.num_threads = atoi(opt_value);
			printf("Threads: %d\n", opt.num_threads);
			break;
		case 'f':
			opt_value = optarg;
			opt.file_name = std::string(opt_value);
			printf("File name: %s\n", opt.file_name.c_str());
			break;
		case 'p':
			opt.print_table = true;
			break;
		default:
			abort ();
		}

    FrequencyTable table(opt.quiet);

    gettimeofday(&start, NULL);

    table.generate_table(opt.file_name, opt.num_threads);

	gettimeofday(&end, NULL);
	auto time_diff = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) / 1000;
	total_time_elapsed += time_diff;


	if(!table.quiet_mode) {
		std::cout << "Total time elapsed: " << total_time_elapsed << " milliseconds" << std::endl;
	}

	if(opt.print_table)
		table.print();

	return 0;
}
