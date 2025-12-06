//
// Created by Benedikt Weis on 06.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY6_H
#define ADVENTOFCODE_2025_DAY6_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

class day6 {
	std::vector<std::vector<int64_t>> numbers{};
	std::vector<std::vector<std::string>> all_columns_numbers{};
	std::vector<std::string> operators{};

	public:
	day6() {
		std::ifstream input("../inputs/day6.txt");
		std::stringstream s;
		std::string line{};
		std::regex re{R"([0-9]+)"};

		std::regex re2{R"([*+])"};

		std::smatch match;
		std::vector<std::string> all_lines{};
		while (std::getline(input, line)) {
			std::vector<int64_t> current_numbers{};
			std::vector<std::string> current_columns{};
			for (std::sregex_iterator it(line.begin(), line.end(), re), end; it != end; ++it) {
				current_numbers.emplace_back(std::stoll(it->str()));
			}
			if (current_numbers.empty()) {

				for (std::sregex_iterator it(line.begin(), line.end(), re2), end; it != end; ++it) {
					operators.emplace_back(it->str());
				}
			} else {
				numbers.emplace_back(current_numbers);
				all_columns_numbers.emplace_back(current_columns);
			}
			all_lines.emplace_back(line);

		}
		// This for part 2. I build a "tensor" of Dimensions NxCxS
		// (N is the number of rows the input has, C the number of columns and S the string length
		std::string operator_line = all_lines[all_lines.size()-1];
		int start_idx = 0;
		for (int i = 1; i < operator_line.size(); ++i) {
			while (operator_line[i++] == ' ' && i < operator_line.size()) {
			}
			if (i == operator_line.size()) {
				break;
			}

			for (int j = 0; j < all_lines.size() - 1; ++j) {
				all_columns_numbers[j].emplace_back(all_lines[j].substr(start_idx, i - 2 - start_idx));
			}
			start_idx = i - 1;
		}
		for (int j = 0; j < all_lines.size() - 1; ++j) {
			all_columns_numbers[j].emplace_back(all_lines[j].substr(start_idx, operator_line.size() - start_idx));
		}

	}
	void part1() {
		uint64_t result{};
		for (int i = 0; i < numbers[0].size(); ++i) {
			uint64_t temp = numbers[0][i];

			#pragma GCC loop unroll(4)
			for (int j = 1; j < 4; ++j) {
				if (operators[i] == "+") {
					temp += numbers[j][i];
				} else {
					temp *= numbers[j][i];
				}
			}
			result += temp;
		}
		std::cout << result << "\n";

	}
	void part2() {
		uint64_t result{};
		for (int i = 0; i < operators.size(); ++i) {
			uint64_t temp = -1;
			for (int j = 0; j < all_columns_numbers[0][i].size(); ++j) {
				int k = 0;

				// k is the row, i the column and j where we are in the current column
				while (all_columns_numbers[k][i][j] == ' ') {
					k++;
				}
				uint64_t x = all_columns_numbers[k++][i][j] - '0';

				#pragma GCC loop unroll(4)
				for (; k < 4; ++k) {
					if (all_columns_numbers[k][i][j] != ' ') {
						x *= 10;
						x += all_columns_numbers[k][i][j] - '0';
					} else {
						break;
					}
				}
				if (temp == -1) {
					temp = x;
				} else {
					if (operators[i] == "+") {
						temp += x;
					} else {
						temp *= x;
					}
				}
			}
			result += temp;
		}
		std::cout << result << "\n";
	}
};


#endif //ADVENTOFCODE_2025_DAY6_H