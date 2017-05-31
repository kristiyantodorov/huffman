#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include "frequency_table.hpp"

int main(int argc, char* argv[]) {
	static int num_threads;

	timeval start, end;

	if ( argc > 1 ) {
		num_threads = atoi(argv[1]);
	} else {
		num_threads = 1;
	}

	std::cout << "Executing with " << num_threads << " threads" << std::endl;

	std::ifstream file("input.txt");
	std::string str;

    FrequencyTable table;

	gettimeofday(&start, NULL);
	while (getline(file, str)) {
        std::cout << "Row" << std::endl;

        if( num_threads == 1 ) {
            table.generate_table(str);
        } else {
            table.generate_table(str, num_threads);
        }
    }

	gettimeofday(&end, NULL);
	table.print();

	auto time_diff = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) / 1000;

	std::cout << "Time elapsed: " << time_diff << " milliseconds" << std::endl;

	return 0;
}
