//
// Created by Benedikt Weis on 04.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY4_H
#define ADVENTOFCODE_2025_DAY4_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

class day4 {

private:
	std::vector<std::string> grid{};
	int result = {};
	std::vector<std::pair<int, int>> to_remove{};

public:

	day4() {
		std::ifstream input("../inputs/day4.txt");
		std::string line{};
		while (input >> line) {
			grid.push_back(line);
		}
	}
	void part1(const bool print_result) {

		const int x_size = grid[0].size();
		const int y_size = grid.size();
		for (int i = 0; i < x_size; ++i) {
			for (int j = 0; j < y_size; ++j) {
				if (grid[i][j] == '@') {
					if (check_surrounding(i, j, x_size, y_size)) {
						result++;
						to_remove.emplace_back(i, j);
					}
				}
			}
		}
		if (print_result)
			std::cout << result << "\n";

	}
	void part2() {

		auto start_time = std::chrono::high_resolution_clock::now();
		result = 0;
		do {
			to_remove.clear();
			part1(false);
			for (auto [i, j] : to_remove) {
				grid[i][j] = '.';
			}
		} while (!to_remove.empty());

		auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << result << "\n";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::microseconds>((end_time - start_time))).count() << "us \n";
	}

	[[nodiscard]] bool check_surrounding(const int i, const int j, const int x_size, const int y_size) const {
		int count_rolls{};
		if (i > 0 && i < x_size - 1 && j > 0 && j < y_size - 1) {
			count_rolls += grid[i - 1][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i - 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i - 1][j + 1] == '@' ? 1 : 0;
			count_rolls += grid[i][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i][j + 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j + 1] == '@' ? 1 : 0;
		} else if (i == 0 && j > 0 && j < y_size - 1) {
			count_rolls += grid[i][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i][j + 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j + 1] == '@' ? 1 : 0;
		} else if (i == x_size - 1 && j > 0 && j < y_size - 1) {
			count_rolls += grid[i - 1][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i - 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i - 1][j + 1] == '@' ? 1 : 0;
			count_rolls += grid[i][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i][j + 1] == '@' ? 1 : 0;
		} else if (i > 0 && i < x_size - 1 && j == 0) {
			count_rolls += grid[i - 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i - 1][j + 1] == '@' ? 1 : 0;
			count_rolls += grid[i][j + 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j + 1] == '@' ? 1 : 0;
		} else if (i > 0 && i < x_size - 1 && j == y_size - 1) {
			count_rolls += grid[i - 1][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i - 1][j] == '@' ? 1 : 0;
			count_rolls += grid[i][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j - 1] == '@' ? 1 : 0;
			count_rolls += grid[i + 1][j] == '@' ? 1 : 0;
		}

		return count_rolls < 4;
	}
};


#endif //ADVENTOFCODE_2025_DAY4_H