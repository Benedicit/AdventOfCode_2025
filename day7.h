//
// Created by Benedikt Weis on 07.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY7_H
#define ADVENTOFCODE_2025_DAY7_H

#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>

class day7 {
	std::vector<std::string> grid_part1{};
	std::vector<std::string> grid_part2{};
	long start{};

public:
	day7() {
		std::vector<std::string> grid{};
		std::ifstream input("../inputs/day7.txt");
		std::string line{};
		while (input >> line) {
			grid.push_back(line);
		}
		input.close();
		start = std::ranges::find(grid[0], 'S') - grid[0].begin();
		grid_part1 = grid;
		grid_part2 = grid;
	}

	void part1() {
		long current_x = start;
		long current_y = 1;
		long result    = 0;
		std::stack<std::pair<long, long>> rays{};
		rays.emplace(current_x, current_y);
		while (!rays.empty()) {
			current_x = rays.top().first;
			current_y = rays.top().second;
			rays.pop();

			if (grid_part1[current_y][current_x] == '|') {
				continue;
			}

			while (current_y < grid_part1.size()) {
				if (grid_part1[current_y][current_x] == '^') {
					rays.emplace(current_x + 1, current_y);
					rays.emplace(current_x - 1, current_y);
					result++;
					break;
				}
				if (grid_part1[current_y][current_x] == '|') {
					break;
				}
				grid_part1[current_y++][current_x] = '|';
			}
		}

		std::cout << result << "\n";
	}
	void part2() {

		const auto start_time = std::chrono::high_resolution_clock::now();
		const auto current_x        = static_cast<int32_t>(start);
		constexpr int32_t current_y = 1;
		long result                 = 0;
		std::unordered_map<uint64_t, long> cache;
		result = part2_cached(cache, current_x, current_y);

		const auto end_time = std::chrono::high_resolution_clock::now();

		std::cout << result << "\n";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::microseconds>((end_time - start_time))).
				count() << "us \n";

	}

	long part2_cached(auto& cache, const int32_t current_x, int32_t current_y) {
		long result_left{};
		long result_right{};
		while (current_y < grid_part2.size()) {
			if (grid_part2[current_y][current_x] == '^') {
				uint64_t key = current_x << 16 | current_y;
				if (cache.contains(key)) {
					return cache[key];
				}

				result_left = part2_cached(cache, current_x - 1, current_y);
				result_right = part2_cached(cache, current_x + 1, current_y);
				long complete_result = result_left + result_right;
				cache[key] = complete_result;
				return complete_result;
			}
			current_y++;
		}
		return 1;

	}
};


#endif //ADVENTOFCODE_2025_DAY7_H
