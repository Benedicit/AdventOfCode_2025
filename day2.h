//
// Created by Benedikt Weis on 02.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY2_H
#define ADVENTOFCODE_2025_DAY2_H


#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <sstream>

class day2 {
public:
	void static part1() {
		std::ifstream input("../inputs/day2.txt");
		std::string line{};
		unsigned long long result = 0;
		while (input >> line) {
		std::stringstream s {line};
			std::string current_range{};
			while (std::getline(s, current_range, ',')) {
				char split{};
				unsigned long long lower_bound{};
				unsigned long long upper_bound{};
				std::stringstream range_s {current_range};
				range_s >> lower_bound >> split >> upper_bound;
				auto str_lower= std::to_string(lower_bound);
				unsigned long long half_lower{};
				if (str_lower.length() > 1) {
					half_lower = std::stoull(str_lower.substr(0, str_lower.size()/2));
				} else {
					half_lower = 1ull;
				}
				auto doubled = std::stoull(std::to_string(half_lower) + std::to_string(half_lower));
				while (doubled < lower_bound) {
					half_lower++;
					doubled = std::stoull(std::to_string(half_lower) + std::to_string(half_lower));
				}
				while (doubled <= upper_bound) {
					result += doubled;
					half_lower++;
					try {
						doubled = std::stoull(std::to_string(half_lower) + std::to_string(half_lower));
					}
					catch (std::exception& e) {
						std::cerr << e.what() << "\n";
						std::cerr << "lower_bound: " << lower_bound << "\n";
						return;
					}
				}

			}
		}
		std::cout << result << "\n";
	}
	void static part2() {
		std::ifstream input("../inputs/day2.txt");
		std::string line{};
		unsigned long long result = 0;
		auto start_time = std::chrono::high_resolution_clock::now();
		while (input >> line) {

			std::stringstream s {line};
			std::string current_range{};
			while (std::getline(s, current_range, ',')) {
				char split{};
				unsigned long long lower_bound{};
				unsigned long long upper_bound{};
				std::stringstream range_s {current_range};

				range_s >> lower_bound >> split >> upper_bound;
				auto str_lower= std::to_string(lower_bound);
				unsigned long long half_lower = 1;
				std::set<unsigned long long> seen{};

				auto doubled = std::stoull(std::to_string(half_lower) + std::to_string(half_lower));
				// The 1 time duplicated is still the lower boundary, but it will start counting from 1 to not miss any 2 >= repeated one
				while (doubled <= upper_bound) {
					if (doubled >= lower_bound && seen.contains(doubled) == false) {
						result += doubled;
						seen.insert(doubled);
					}
					// Check if the repeated sequence is in the interval, if it's too large stop appending
					for (int i = 3; i < 9; ++i) {
						try {
							std::string temp{};
							for (int j = 0; j < i; ++j) {
								temp += std::to_string(half_lower);
							}
							auto multipled = std::stoull(temp);
							if (multipled > upper_bound) {
								break;
							}
							if (multipled >= lower_bound && seen.contains(multipled) == false) {
								result += multipled;
								seen.insert(multipled);
							}
						}
						catch (std::out_of_range& e) {
							break;
						}
					}

					half_lower++;
					doubled = std::stoull(std::to_string(half_lower) + std::to_string(half_lower));
				}

			}
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << "Day 2 part 2: " << result << "; ";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::milliseconds>((end_time - start_time))).count() << "ms \n";


	}

};


#endif //ADVENTOFCODE_2025_DAY2_H