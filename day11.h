//
// Created by Benedikt Weis on 11.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY11_H
#define ADVENTOFCODE_2025_DAY11_H

#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <iostream>
#include <stack>
#include <unordered_map>

class day11 {
	std::unordered_map<std::string, std::vector<std::string>> edges{};
	std::unordered_map<std::string, int> paths{};
public:
	day11() {
		std::ifstream input("../inputs/day11.txt");
		std::string line{};
		while (std::getline(input, line)) {
			std::stringstream s{line};
			std::string temp{};
			std::string key{};
			std::vector<std::string> values{};
			while (std::getline(s, temp, ' ')) {
				if (std::ranges::find(temp, ':') != temp.end()) {
					key = temp.substr(0, temp.size() - 1);
				} else {
					values.emplace_back(temp);
				}
			}
			edges.emplace(key, values);
		}
	}
	void part1() {
		uint64_t result{};
		std::string current = "you";
		std::stack<std::string> visited{};
		visited.emplace(current);
		while (!visited.empty()) {
			current = visited.top();
			visited.pop();
			for (const auto& next: edges[current]) {
				visited.emplace(next);
			}
			if (current == "out") {
				result++;
			}
		}
		std::cout << result << "\n";
	}
	void part2() {

		uint64_t result{};
		uint64_t svr_fft = dfs("fft", "svr");
		uint64_t svr_dac = dfs("dac", "svr");
		uint64_t dac_fft = dfs("fft", "dac");
		uint64_t dac_out = dfs("out", "dac");
		uint64_t fft_out = dfs("out", "fft");
		uint64_t fft_dac = dfs("dac", "fft");
		result = svr_dac * dac_fft * fft_out + svr_fft * fft_dac * dac_out;
		std::cout << result << "\n";

	}
	int dfs(std::string target, std::string current) {

		if (current == "out") {
			if (current == target) {
				return 1;
			}
			return 0;
		}
		if (current == target) {
			return 1;
		}
		int count_path = 0;
		for (const auto& next: edges[current]) {
			count_path += dfs(target, next);
		}
		return count_path;
	}
};


#endif //ADVENTOFCODE_2025_DAY11_H