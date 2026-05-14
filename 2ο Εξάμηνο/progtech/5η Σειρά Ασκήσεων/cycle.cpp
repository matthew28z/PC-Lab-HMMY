#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
    public: 
        Graph(int V) {
            pointToPoints.reserve(V);
        }

        ~Graph() { }

        void addEdge(int u, int v) {
            pointToPoints[v].insert(u);
        }

        bool cycle(std::vector<int>& path) const {
            for (const auto& pair : pointToPoints) {
                std::vector<int> p = { pair.first };

                const std::pair<bool, std::vector<int>>& t = check(pair.first, p, pointToPoints.size() + 1);

                if (t.first) {
                    path.insert(path.end(), t.second.rbegin(), t.second.rend()); //epeidh ta briskw anapoda

                    return true;
                }
            }

            return false;
        }

    private:
        std::unordered_map<int, std::unordered_set<int>> pointToPoints; //krataei poia nodes deixnoyn sto kleidi node

        std::pair<bool, std::vector<int>> check(int target, std::vector<int>& path, int smallestLength) const {
            if (smallestLength <= path.size() + 1) {
                return { false, { } };
            }

            auto it = pointToPoints.find(path.back());

            if (it == pointToPoints.end()) {
                return { false, { } };
            }

            if (it -> second.count(target) == 1) {
                return { true, path };
            }

            std::vector<int> goodRes;
            
            for (int n : it -> second) {
                if (std::find(path.begin(), path.end(), n) != path.end()) {
                    continue;
                }

                std::vector<int> tPath = path;
                tPath.push_back(n);

                std::pair<bool, std::vector<int>> res = check(target, tPath, goodRes.size() == 0 ? smallestLength : goodRes.size());

                if (res.first && (goodRes.empty() || goodRes.size() > res.second.size())) {
                    goodRes = res.second;
                }
            }

            if (goodRes.empty()) {
                return { false, { } };
            }

            return { true, goodRes };
        }
};
