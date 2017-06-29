#include "frequency_table.hpp"
#include <thread>
#include <fstream>
#include <mutex>
#include <vector>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>

std::mutex mtx;
int num_of_working_threads;

Counter::Counter() {
	memset(cnt_table, 0, sizeof(cnt_table));
}

FrequencyTable::FrequencyTable(bool q_mode) : quiet_mode(q_mode) {
	memset(table, 0, sizeof(table));
}

void FrequencyTable::print() {
	for(int i = 33; i < 126; i++) {
		std::cout << (char)(i) << " " << table[i] << std::endl;
	}
}

void FrequencyTable::counter_thread(const long begin, const long size, const std::string& file_name, Counter& c_arr, int number) {
	timeval start, end;
	if(!quiet_mode) {
		//printf("Begin: %ld, Size %ld, End: %ld\n", begin, size, begin+size-1);
		printf("Thread %d started\n", number);
		gettimeofday(&start, NULL);

	}

	num_of_working_threads++;
	char symbol;

    std::ifstream fin;
    fin.open(file_name.c_str(), std::ios::in);
    fin.seekg(begin, std::ios::beg);

	for(auto i = begin; i < begin+size; i++) {
		fin.get(symbol);
		c_arr.cnt_table[(int)symbol]++;
	}

	mtx.lock();
	for(auto i = 0; i < 256; i++) {
		table[i] += c_arr.cnt_table[i];
	}
	mtx.unlock();

	if(!quiet_mode) {
		gettimeofday(&end, NULL);
		auto time_diff = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) / 1000;
		printf("Thread %d stopped\n", number);
		printf("Thread %d execution time was (millis): %ld\n", number, time_diff);
	}

	num_of_working_threads--;
}

void FrequencyTable::generate_table(const std::string& file_name, const int num_threads) {
	std::vector<std::thread> threads;
	Counter* counter_array = new Counter[num_threads];

	std::ifstream file;
	file.open(file_name.c_str());
	file.seekg(0, file.end);
    long long int fileLength = file.tellg();
    if(!quiet_mode)
    	printf("File size: %lld\n", fileLength);
    file.close();

	auto piece = fileLength/num_threads;
	auto last_piece = piece + fileLength%num_threads;

	for(auto i = 0; i < num_threads; i++) {
		if( i == num_threads-1 ) {
			threads.push_back(std::thread(&FrequencyTable::counter_thread, this, i*piece, last_piece, file_name, std::ref(counter_array[i]), i));
		} else {
			threads.push_back(std::thread(&FrequencyTable::counter_thread, this, i*piece, piece, file_name, std::ref(counter_array[i]), i));
		}
	}

	for(size_t i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}

void FrequencyTable::generate_table(const std::string& str) {
	for(auto i = str.begin(); i != str.end(); i++) {
		table[(int)(*i)]++;
	}
	std::cout << std::endl;
}
