//
// Created by Benedikt Weis on 08.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY8_H
#define ADVENTOFCODE_2025_DAY8_H


#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>
#include <ranges>

#include "day5.h"

typedef std::tuple<int64_t, int64_t, int64_t> cord;

class day8 {
	struct cmp {
		bool operator()(const std::pair<std::pair<cord, cord>, double> &a,
		const std::pair<std::pair<cord, cord>, double> &b) const {
			return a.second < b.second;
		}
	};
	std::vector<std::set<cord>> junctions{};
	std::vector<std::pair<cord, cord>> pairs{};

	double euclidian_distance(cord a, cord b) {
		auto [x1, y1, z1] = a;
		auto [x2, y2, z2] = b;
		return sqrt((x1-x2)*(x1 - x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));

	}
public:
	day8() {
		std::vector<std::pair<std::pair<cord, cord>, double>> temp{};
		std::ifstream input("../inputs/day8.txt");
		int x{};
		int y{};
		int z{};
		char c1, c2;
		std::vector<cord> cords{};
		while (input >> x >> c1 >> y >> c2 >> z) {
			cords.emplace_back(x, y, z);
		}
		input.close();
		std::set<std::pair<cord, cord>> inserted{};
		for (auto a: cords) {
			for (auto const b: cords) {
				if (b == a) {
					continue;
				}
				if (inserted.contains({b, a})) {
					continue;
				}
				double distance = euclidian_distance(a, b);
				auto pair = std::make_pair(a, b);
				inserted.insert(pair);
				temp.emplace_back(pair, distance);
			}
			junctions.emplace_back(std::set{a});
		}
		std::ranges::sort(temp, cmp());
		for (auto &key: temp | std::views::keys) {
			pairs.emplace_back(key);
		}
	}


	void part1() {
		int i{};
		std::pair<cord,cord> last{};

		while (junctions.size() > 1) {
			if (i==1000) {
				// Part 1
				std::ranges::sort(junctions, [](const auto& a, const auto& b) {return a.size() > b.size();});
				const uint64_t result = junctions[0].size() * junctions[1].size() * junctions[2].size();
				std::cout << result << "\n";
			}
			last = pairs[i];
			auto a = pairs[i].first;
			auto b = pairs[i].second;
			std::set<cord>* set_with_a;
			for (auto& g: junctions) {
				if (g.contains(a)) {
					set_with_a = &g;
					break;
				}
			}

			if (set_with_a->contains(b)) {
				i++;
				continue;
			}
			std::set<cord> merged{};
			for (auto& group: junctions) {
				if (group.contains(b)) {
					set_with_a->merge(group);
					merged = group;
					break;
				}
			}
			junctions.erase(std::ranges::find(junctions, merged));
			i++;
		}
		// Part 2
		std::cout << std::get<0>(last.first) * std::get<0>(last.second) << "\n";

	}
	void part2() {
		// Included in part 1
	}


};


#endif //ADVENTOFCODE_2025_DAY8_H