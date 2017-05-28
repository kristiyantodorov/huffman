#include "frequency_table.hpp"
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;

Counter::Counter() {
	memset(cnt_table, 0, sizeof(cnt_table));
}

FrequencyTable::FrequencyTable() {
	memset(table, 0, sizeof(table));
}

void FrequencyTable::print() {
	for(int i = 33; i < 126; i++) {
		std::cout << (char)(i) << " " << table[i] << std::endl;
	}
}

void FrequencyTable::counter_thread(const long begin, const long size, const std::string& str, Counter& c_arr) {
#ifdef DEBUG
	printf("Begin: %ld, Size %ld, End: %ld\n", begin, size, begin+size-1);
#endif

	for(auto i = begin; i < begin+size; i++) {
		c_arr.cnt_table[(int)str[i]]++;
	}

	mtx.lock();
	for(auto i = 0; i < 256; i++) {
		table[i] += c_arr.cnt_table[i];
	}
	mtx.unlock();
}

void FrequencyTable::generate_table(const std::string& str, const int num_threads) {
	std::vector<std::thread> threads;
	Counter* counter_array = new Counter[num_threads];

	auto size = str.size();
#ifdef DEBUG
	std::cout << "String size: " << size << std::endl;
#endif

	auto piece = size/num_threads;
	auto last_piece = piece + size%num_threads;
#ifdef DEBUG
	std::cout << "Piece size: " << piece << std::endl;
#endif

	for(auto i = 0; i < num_threads; i++) {
#ifdef DEBUG
		std::cout << "Starting thread " << i << std::endl;
#endif
		if( i == num_threads-1 ) {
			threads.push_back(std::thread(&FrequencyTable::counter_thread, this, i*piece, last_piece, str, std::ref(counter_array[i])));
		} else {
			threads.push_back(std::thread(&FrequencyTable::counter_thread, this, i*piece, piece, str, std::ref(counter_array[i])));
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
