#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    int K;
    std::cin >> K;

    std::unordered_map<std::string, std::pair<int, int>> data;
    data.reserve(K);

    std::string movieName;

    while (std::cin >> movieName) {
        int r;
        std::cin >> r;

        if (r < 0 || r > 100) {
            continue;
        }

        std::pair<int, int>& p = data[movieName];

        p.first++;
        p.second += r;
    }

    std::vector<std::pair<std::string, int>> v;
    v.reserve(data.size());

    for (const std::pair<std::string, std::pair<int, int>>& p : data) {
        v.push_back({ p.first, p.second.second / p.second.first });
    }

    std::sort(v.begin(), v.end(), [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }

        return a.second > b.second;
    });

    int tracker = 0;

    for (const std::pair<std::string, int>& p : v) {
        std::cout << p.first << ' ' << p.second << std::endl;

        tracker++;

        if (tracker == K) {
            break;
        }
    }
}
