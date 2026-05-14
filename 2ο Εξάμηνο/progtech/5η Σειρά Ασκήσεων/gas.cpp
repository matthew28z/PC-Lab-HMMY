#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

struct Compare {
    bool operator () (const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        if (a.first != b.first) {
            if (a.second != b.second) {
                return a.second < b.second;
            }

            return a.first < b.first;
        }

        return false;
    }
};

std::pair<std::vector<int>, int> findPath(int start, int end, int size, std::unordered_map<int, std::set<std::pair<int, int>, Compare>>& connections, int fills, int gas, std::vector<int>& path) {
    const auto& connectsTo = connections[start]; 

    for (const auto& pair : connectsTo) { // an initial check to find the shortest path
        if (pair.second > size) {
            break;
        }

        if (pair.first == end) {
            if (gas >= pair.second) {
                return { path, fills };
            }
            return { path, fills + 1 };
        }
    }

    for (const auto& pair : connectsTo) {
        if (std::find(path.begin(), path.end(), pair.first) != path.end()) { //glitwnei to na kanei kyklous
            continue;
        }        

        if (pair.second > size) { //epeidh ola ta epomena tha exoun megalytero keno
            return { { }, -1 };
        }

        int tGas = gas;
        int tFills = fills;

        if (pair.second > gas) {
            tGas = size;
            tFills++;
        }

        path.push_back(pair.first);

        const std::pair<std::vector<int>, int>& res = findPath(pair.first, end, size, connections, tFills, tGas - pair.second, path);

        if (res.second != -1) {
            return res;
        }

        path.pop_back();
    }

    return { { }, -1 }; //means no suitable path found
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::unordered_map<int, std::set<std::pair<int, int>, Compare>> connections;

    for (int i = 0; i < M; i++) {
        int U, V, L;
        std::cin >> U >> V >> L;

        connections[U].insert({ { V, L } });
        connections[V].insert({ { U, L } });
    }

    int Q;
    std::cin >> Q;

    for (int i = 0; i < Q; i++) {
        int A, B, C;
        std::cin >> A >> B >> C;

        std::vector<int> p = { A };

        const std::pair<std::vector<int>, int>& res = findPath(A, B, C, connections, 1, C, p);

        if (res.second == -1) {
            std::cout << "IMPOSSIBLE" << std::endl;
        } else {
            std::cout << "POSSIBLE: " << res.second << " fill(s), ";

            for (int n : res.first) {
                std::cout << n << ' ';
            }

            std::cout << B << std::endl;
        }
    }
}
