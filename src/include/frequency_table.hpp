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

class FrequencyTable {
public:
	FrequencyTable();
	void print();
	void generate_table(const std::string& str);

private:
	int table[256];
};



#endif /* SRC_INCLUDE_FREQUENCY_TABLE_HPP_ */
