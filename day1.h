//
// Created by Benedikt Weis on 30.11.25.
//

#ifndef ADVENTOFCODE_2025_DAY1_H
#define ADVENTOFCODE_2025_DAY1_H

#include <fstream>
#include <string>
#include <iostream>

class day1 {
public:
	static int part1() {
		std::ifstream input{"../inputs/day1.txt"};
		if (!input.is_open()) {
			std::cerr << "errno: " << errno << " => " << std::strerror(errno) << "\n";
			return -1;
		}
		char direction       = {};
		int hop              = {};
		int current_position = 50;
		int result           = 0;
		while (input >> direction >> hop) {
			if (direction == 'L') {
				current_position -= hop;
				// Cpp has no "real" modulo
				while (current_position < 0) {
					current_position += 100;
				}
			} else {
				current_position = (current_position + hop) % 100;
			}
			if (current_position == 0) {
				result += 1;
			}
		}
		std::cout << result << "\n";
		return result;
	}

	static int part2() {
		std::ifstream input{"../inputs/day1.txt"};
		if (!input.is_open()) {
			std::cerr << "errno: " << errno << " => " << std::strerror(errno) << "\n";
			return -1;
		}
		char direction       = {};
		int hop              = {};
		int current_position = 50;
		int result           = 0;
		while (input >> direction >> hop) {
			if (direction == 'L') {
				for (int i = 0; i < hop; i++) {
					current_position--;
					if (current_position < 0) {
						current_position = 99;
					}
					if (current_position == 0) {
						result += 1;
					}
				}
			} else {
				current_position += hop;
				while (current_position >= 100) {
					current_position -= 100;
					result += 1;
				}
			}
		}
		std::cout << result << "\n";
		return result;
	}
};


#endif //ADVENTOFCODE_2025_DAY1_H
