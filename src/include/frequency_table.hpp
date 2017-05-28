/*
 * frequency_table.hpp
 *
 *  Created on: May 22, 2017
 *      Author: kristiyan
 */

#ifndef SRC_INCLUDE_FREQUENCY_TABLE_HPP_
#define SRC_INCLUDE_FREQUENCY_TABLE_HPP_
#include <cstring>
#include <string>
#include <iostream>


struct Counter {
	Counter();
	long cnt_table[256];
};


class FrequencyTable {
public:
	FrequencyTable();
	void print();
	void generate_table(const std::string& str);
	void generate_table(const std::string& str, const int num_threads);

private:
	unsigned long long table[256];
	void counter_thread(const long begin, const long size, const std::string& str, Counter& c_arr);
};

#endif /* SRC_INCLUDE_FREQUENCY_TABLE_HPP_ */
