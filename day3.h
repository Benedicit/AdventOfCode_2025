//
// Created by Benedikt Weis on 03.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY3_H
#define ADVENTOFCODE_2025_DAY3_H

#include <fstream>
#include <string>
#include <iostream>
#include <cstdint>

class day3 {

	public:
	static void part1_2(int digits_battery) {
		std::ifstream input("../inputs/day3.txt");
		std::string line{};
		uint64_t result{};
		while (input >> line) {
			int idx_last_digit = - 1;
			uint64_t battery_pack{};
			for (int i = digits_battery - 1; i >= 0; i--) {
				int highest_digit{};
				for (int j = idx_last_digit + 1; j < line.size() - i; ++j) {
					int current_digit = line[j] - '0';
					if (current_digit > highest_digit) {
						highest_digit = current_digit;
						idx_last_digit = j;
					}
				}
				battery_pack *= 10;
				battery_pack += highest_digit;
			}

			result += battery_pack;
		}
		std::cout << result << "\n";
	}
	static int part2() {

	}
};


#endif //ADVENTOFCODE_2025_DAY3_H