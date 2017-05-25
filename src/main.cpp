#include <iostream>
#include <string>
#include <cstring>
#include "frequency_table.hpp"

int main() {
	std::string str = "ABRACADABRA";
	FrequencyTable table;
	table.generate_table(str);
	table.print();
	return 0;
}
