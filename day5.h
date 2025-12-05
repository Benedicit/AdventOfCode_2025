//
// Created by Benedikt Weis on 05.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY5_H
#define ADVENTOFCODE_2025_DAY5_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
typedef __uint128_t uint128_t;
class day5 {
	public:
	void part1() {
		std::vector<std::pair<uint64_t, uint64_t>> ranges{};
		uint64_t result{};
		std::ifstream input("../inputs/day5.txt");
		std::string line{};
		while (input >> line) {
			auto pos = line.find('-');
			if (pos != std::string::npos) {
				std::stringstream s {line};
				uint64_t lower{};
				uint64_t upper{};
				char temp{};
				s >> lower >> temp >> upper;
				ranges.emplace_back(lower, upper);
			} else {
				uint64_t id{};
				std::stringstream s {line};
				s >> id;
				for (auto [lower, upper] : ranges) {
					if (id >= lower && id <= upper) {
						result++;
						break;
					}
				}

			}

		}
		std::cout << result << "\n";

	}
	void part2() {
		std::vector<std::pair<uint64_t, uint64_t>> ranges{};
		uint64_t result{};
		std::ifstream input("../inputs/day5.txt");
		std::string line{};
		const auto start_time = std::chrono::high_resolution_clock::now();
		while (input >> line) {
			if (auto pos = line.find('-'); pos != std::string::npos) {
				std::stringstream s {line};
				uint64_t lower{};
				uint64_t upper{};
				char temp{};
				s >> lower >> temp >> upper;
				bool already_in = false;
				std::vector<std::pair<uint64_t, uint64_t>> old_pairs;
				for (auto [lower_bound, upper_bound]: ranges) {
					if (lower >= lower_bound && lower <= upper_bound && upper >= lower_bound && upper <= upper_bound) {
						already_in = true;
						break;
					}

					if (lower < lower_bound && upper > upper_bound) {
						old_pairs.emplace_back(lower_bound, upper_bound);
					}
					if (lower < lower_bound && upper >= lower_bound && upper <= upper_bound) {
						upper = upper_bound;
						old_pairs.emplace_back(lower_bound, upper_bound);
					}
					if (upper > upper_bound && lower >= lower_bound && lower <= upper_bound) {
						lower = lower_bound;
						old_pairs.emplace_back(lower_bound, upper_bound);
					}

				}
				if (already_in) {
					continue;
				}

				for (auto old_pair: old_pairs) {
					ranges.erase(std::ranges::find(ranges, old_pair));
				}
				ranges.emplace_back(lower, upper);
			} else {
				break;
			}

		}
		for (auto [lower, upper]: ranges) {
			result += upper - lower + 1;
		}

		const auto end_time = std::chrono::high_resolution_clock::now();

		std::cout << result << "\n";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::microseconds>((end_time - start_time))).
				count() << "us \n";
	}
};


#endif //ADVENTOFCODE_2025_DAY5_H