//
// Created by Benedikt Weis on 10.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY10_H
#define ADVENTOFCODE_2025_DAY10_H

#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <bitset>

class day10 {

	std:: vector<std::vector<uint16_t>> switches;
	std::vector<uint16_t> targets;
	std::vector<std::vector<uint16_t>> joltage_requirements;
public:
	day10() {
		std::ifstream input("../inputs/day10.txt");
		std::string line{};
		std::regex target{R"(\[[.#]+\])"};
		std::regex single_switches{R"(\(\d(,\d)*\))"};
		std::regex joltages{R"(\{\d(,\d)*\})"};

		std::regex re2{R"([*+])"};

		while (std::getline(input, line)) {
			for (std::sregex_iterator it(line.begin(), line.end(), target), end; it != end; ++it) {
				std::string s{it->str()};
				uint16_t current{};
				s = s.substr(1, s.size() - 2);
				for (int i = 0; i < s.size(); ++i) {
					if (s[i] == '#') {
						current |= 1 << i;
					}
				}
				targets.emplace_back(current);
			}
			std::vector<uint16_t> current_switches{};
			for (std::sregex_iterator it(line.begin(), line.end(), single_switches), end; it != end; ++it) {
				std::string temp = it->str();
				std::stringstream s{temp.substr(1, temp.size() - 2)};
				uint16_t current{};
				while (std::getline(s, temp, ',')) {
					current |= 1 << std::stoi(temp);
				}
				//std::bitset<8> bs(current);
				//std::cout << bs << "\n";
				current_switches.emplace_back(current);
			}
			switches.emplace_back(current_switches);

			for (std::sregex_iterator it(line.begin(), line.end(), single_switches), end; it != end; ++it) {
				std::string temp = it->str();
				std::stringstream s{temp.substr(1, temp.size() - 2)};
				uint16_t current{};
				std::vector<uint16_t> curr_joltages{};
				while (std::getline(s, temp, ',')) {
					current = std::stoi(temp);
					curr_joltages.emplace_back(current);
				}
				joltage_requirements.emplace_back(curr_joltages);
			}
			}
		}
	void part1() {
		const auto start_time = std::chrono::high_resolution_clock::now();
		uint64_t result{};
		for (int i = 0; i < targets.size(); i++) {
			uint16_t current_target = targets[i];
			std::vector<uint16_t> current_switches = switches[i];
			uint16_t starting_point{};
			uint16_t current_best = -1;
			std::set<uint16_t> best_seq{};
			for (int j = 0; j < current_switches.size(); j++) {
				if (current_switches[j] == current_target) {
					current_best = 1;
					break;
				}
				if (current_switches[j] & current_target) {
					starting_point = current_switches[j];
					std::vector<uint16_t> switches_left = current_switches;
					std::set start_seq{starting_point};
					switches_left.erase(std::ranges::find(switches_left, starting_point));
					for (int k = 3; k < current_switches.size() + 1 && k <= current_best; ++k) {
						auto current_seq = get_switch_sequence(start_seq, switches_left, k, current_target, starting_point);
						if (!current_seq.empty() && current_seq.size() < current_best) {
							current_best = current_seq.size();
							best_seq = current_seq;
							break;
						}
					}
				}
			}
			if (current_best == std::numeric_limits<uint16_t>::max()) {
				std::cout << "no solution found\n";
			}
			result += current_best;

		}
		const auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << result << "\n";
		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::milliseconds>((end_time - start_time))).
				count() << "ms \n";
	}
	std::set<uint16_t> get_switch_sequence(std::set<uint16_t> current_seq, std::vector<uint16_t> switches_left, uint16_t best_depth,
		uint16_t target, uint16_t current_state) {
		if (current_seq.size() + 1 == best_depth) {
			return std::set<uint16_t>{};
		}
		for (auto s: switches_left) {
			uint16_t next_state = current_state ^ s;
			if (next_state == target) {
				current_seq.insert(s);
				return current_seq;
			}
		}
		std::set<uint16_t> final_seq{};
		for (auto s: switches_left) {
			uint16_t next_state = current_state ^ s;
			auto next_seq = current_seq;
			next_seq.insert(s);
			auto new_switches_left = switches_left;
			new_switches_left.erase(std::ranges::find(new_switches_left, s));
			auto result = get_switch_sequence(next_seq, new_switches_left, best_depth, target, next_state);
			if (result.empty()) {
				continue;
			}
			if (final_seq.empty() || result.size() < final_seq.size()) {
				final_seq = result;
				best_depth = result.size();
			}
		}
		return final_seq;

	}

	struct cmp {
		bool operator()(const uint16_t& a,
		 const uint16_t& b) const {
			std::bitset<10> bs_a(a);
			std::bitset<10> bs_b(b);
			uint8_t one_count_a{};
			uint8_t one_count_b{};
			for (int i = 0; i < 10; ++i) {
				if (bs_a[i]) {
					one_count_a++;
				}
				if (bs_b[i]) {
					one_count_b++;
				}
			}
			return one_count_a > one_count_b;
		}
	};
	void part2() {
		// Still not finished
		uint64_t result{};
		for (int i = 0; i < switches.size(); ++i) {
			auto curr_switches = switches[i];
			auto ratings = joltage_requirements[i];
			std::ranges::sort(curr_switches, cmp());
			for (auto& s: curr_switches) {
				std::bitset<10> bs(s);
				std::vector<uint8_t> indices;
				for (int j = 0; j < 10; ++j) {
					if (bs[j]) {
						indices.emplace_back(j);
					}
				}
				uint16_t smallest_rating = -1;
				for (auto& idx: indices) {
					if (ratings[idx] < smallest_rating) {
						smallest_rating = ratings[idx];
					}
				}
				for (int j = 0; j < smallest_rating; ++j) {
					for (auto& idx: indices) {
						ratings[idx]--;
					}
				}
				result += smallest_rating;
			}
		}
		std::cout << result << "\n";
	}




};


#endif //ADVENTOFCODE_2025_DAY10_H