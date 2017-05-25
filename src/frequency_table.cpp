#include "frequency_table.hpp"

FrequencyTable::FrequencyTable() {
	memset(table, 0, sizeof(table));
}

void FrequencyTable::print() {
	for(int i = 33; i < 126; i++) {
		std::cout << (char)(i) << " " << table[i] << std::endl;
	}
}

void FrequencyTable::generate_table(const std::string& str) {
	for(auto i = 0; i < str.length(); i++) {
		table[(int)str[i]]++;
	}
}
