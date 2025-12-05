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
	std::vector<std::pair<int, int> > to_remove{};

public:
	day4() {
		std::ifstream input("../inputs/day4.txt");
		std::string line{};
		// Add also padding at the borders of the grid to make the convolution branchless
		while (input >> line) {
			grid.push_back("." + line + ".");
		}
		grid.insert(grid.begin(), std::string(grid[0].size(), '.'));
		grid.emplace_back(grid[0].size(), '.');
		input.close();
	}

	void part1(const bool print_result) {
		const int x_size = grid[0].size();
		const int y_size = grid.size();
		// We start at 1 to max_size - 1 as the borders are only padding
		for (int i = 1; i < x_size - 1; ++i) {
			for (int j = 1; j < y_size - 1; ++j) {
				if (grid[i][j] == '@' && check_surrounding(i, j)) {
					result++;
					to_remove.emplace_back(i, j);
				}
			}
		}
		if (print_result)
			std::cout << result << "\n";
	}

	/**
	 * part2 was luckily very simple today and not something with moving parts
	 */
	void part2() {
		const auto start_time = std::chrono::high_resolution_clock::now();
		// reset result in case part1() was called before
		result          = 0;
		do {
			to_remove.clear();
			part1(false);
			for (auto [i, j]: to_remove) {
				grid[i][j] = '.';
			}
		} while (!to_remove.empty());

		const auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << result << "\n";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::microseconds>((end_time - start_time))).
				count() << "us \n";
	}

	/**
	 * The challenge today was basically running a 3x3 kernel convolution where a "@" is and check if the sum is less than 4
	 * @param i x cord
	 * @param j y cord
	 * @return true if grid[i][j] has less than 4 rolls surrounding it
	 */
	[[nodiscard]] bool check_surrounding(const int i, const int j) const {
		int count_rolls{};
		count_rolls += grid[i - 1][j - 1] == '@' ? 1 : 0;
		count_rolls += grid[i - 1][j] == '@' ? 1 : 0;
		count_rolls += grid[i - 1][j + 1] == '@' ? 1 : 0;
		count_rolls += grid[i][j - 1] == '@' ? 1 : 0;
		count_rolls += grid[i][j + 1] == '@' ? 1 : 0;
		count_rolls += grid[i + 1][j - 1] == '@' ? 1 : 0;
		count_rolls += grid[i + 1][j] == '@' ? 1 : 0;
		count_rolls += grid[i + 1][j + 1] == '@' ? 1 : 0;

		return count_rolls < 4;
	}
};


#endif //ADVENTOFCODE_2025_DAY4_H
