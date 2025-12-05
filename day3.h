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
	static void part1_2(const int digits_battery) {
		std::ifstream input("../inputs/day3.txt");
		std::string line{};
		uint64_t result{};
		auto start_time = std::chrono::high_resolution_clock::now();
		while (input >> line) {
			// -1 otherwise the first digit would be skipped
			int idx_last_digit = - 1;
			uint64_t battery_pack{};
			for (int i = digits_battery - 1; i >= 0; i--) {
				int highest_digit{};
				for (int j = idx_last_digit + 1; j < line.size() - i; ++j) {
					const int current_digit = line[j] - '0';
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
		auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << result << "\n";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::microseconds>((end_time - start_time))).count() << "us \n";
	}

};


#endif //ADVENTOFCODE_2025_DAY3_H