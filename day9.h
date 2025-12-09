//
// Created by Benedikt Weis on 09.12.25.
//

#ifndef ADVENTOFCODE_2025_DAY9_H
#define ADVENTOFCODE_2025_DAY9_H
#include <cstdint>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <numeric>


typedef std::pair<int64_t, int64_t> cord_2D;

class day9 {
	std::vector<cord_2D> points;
	std::vector<cord_2D> points_sorted;
	std::vector<cord_2D> points_sorted_rev;
	struct cmp {
		bool operator()(const cord_2D& a,
		 const cord_2D& b) const {

			if (a.first == b.first)
				return a.second < b.second;
			return a.first < b.first;
		}
	};
public:
	day9() {
		int64_t x{};
		int64_t y{};
		char comma{};
		std::ifstream input("../inputs/day9.txt");
		while (input >> x >> comma >> y) {
			points.emplace_back(x, y);
		}
		// Luckily the points are already sorted in clockwise manner
		points_sorted = points;
		std::ranges::sort(points_sorted, cmp());
		points_sorted_rev = points_sorted;
		std::ranges::reverse(points_sorted_rev);
	}
	static int64_t cross(const cord_2D &A, const cord_2D& B, const cord_2D& C) {
		return (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
	}
	static bool on_segment(const cord_2D &A, const cord_2D &B, const cord_2D &Pnt) {
		if (cross(A, B, Pnt) != 0) return false; // not collinear
		// bounding-box test
		if (std::min(A.first, B.first) <= Pnt.first && Pnt.first <= std::max(A.first, B.first)
		 && std::min(A.second, B.second) <= Pnt.second && Pnt.second <= std::max(A.second, B.second))
			return true;
		return false;
	}

	// Using ray-cast algorithm
	bool check_if_point_in_hull(const cord_2D &pt) {
		const std::int64_t px = pt.first;
		const std::int64_t py = pt.second;
		const int n = static_cast<int>(points.size());

		bool inside = false;
		// iterate edges (i = current, j = previous)
		for (int i = 0, j = n - 1; i < n; j = i++) {
			const auto &[xi, yi] = points[i];
			const auto &[xj, yj] = points[j];

			// Check if on edge of polygon
			if (on_segment(points[i], points[j], pt)) return true;

			if ((yi > py) != (yj > py)) {
				int64_t lhs = (px - xi) * (yj - yi);
				int64_t rhs = (xj - xi) * (py - yi);

				if ( (yj > yi && lhs < rhs) || (yj < yi && lhs > rhs) ) {
					inside = !inside;
				}
			}
		}
		return inside;
	}


	void part1() {
		int64_t max_distance = std::numeric_limits<int64_t>::min();
		std::pair<int64_t, int64_t> edges{};
		for (const auto& point: points) {
			for (const auto& other_point: points) {
				if (point == other_point) {
					continue;
				}
				int64_t dist_x = std::abs(point.first - other_point.first) + 1;
				int64_t dist_y =  std::abs(point.second - other_point.second) + 1;
				int64_t current_distance = dist_x + dist_y;
				if (current_distance > max_distance) {
					max_distance = current_distance;
					edges = {dist_x, dist_y};
				}
			}
		}
		uint64_t result = edges.first * edges.second;
		std::cout << result << "\n";
	}
	bool check_edge_x_in_polygon(const int64_t start_x, const int64_t end_x, int64_t y) {
		for (int64_t i = start_x + 1; i < end_x; ++i) {
			if (!check_if_point_in_hull({i, y})) {
				return false;
			}
		}
		return true;
	}
	bool check_edge_y_in_polygon(const int64_t start_y, const int64_t end_y, int64_t x) {
		for (int64_t i = start_y + 1; i < end_y; ++i) {
			if (!check_if_point_in_hull({x, i})) {
				return false;
			}
		}
		return true;
	}
	void part2() {
		const auto start_time = std::chrono::high_resolution_clock::now();
		int64_t max_distance = std::numeric_limits<int64_t>::min();
		std::pair<int64_t, int64_t> edges{};
		for (const auto& point: points_sorted) {
			for (const auto& other_point: points_sorted_rev) {
				if (point == other_point) {
					continue;
				}
				int64_t dist_x = std::abs(point.first - other_point.first) + 1;
				int64_t dist_y =  std::abs(point.second - other_point.second) + 1;
				const int64_t current_distance = dist_x + dist_y;
				const int64_t smaller_x = std::min(point.first, other_point.first);
				const int64_t smaller_y = std::min(point.second, other_point.second);
				const int64_t bigger_x = std::max(point.first, other_point.first);
				const int64_t bigger_y = std::max(point.second, other_point.second);
				// For now just check if the edge points are inside the polygon and only then check the edges to speed up significantly (but is still slow)
				if (current_distance > max_distance && check_if_point_in_hull({point.first, other_point.second}) && check_if_point_in_hull({other_point.first, point.second})) {

					bool rect_in_polygon = check_edge_y_in_polygon(smaller_y, bigger_y, smaller_x);
					rect_in_polygon &= check_edge_y_in_polygon(smaller_y, bigger_y, bigger_x);
					if (rect_in_polygon) {
						max_distance = current_distance;
						edges = {dist_x, dist_y};
					}
				}
			}
		}
		const uint64_t result = edges.first * edges.second;
		const auto end_time = std::chrono::high_resolution_clock::now();
		std::cout << result << "\n";

		std::cout << "Runtime: " << (std::chrono::duration_cast<std::chrono::milliseconds>((end_time - start_time))).
				count() << "ms \n";
	}

};


#endif //ADVENTOFCODE_2025_DAY9_H