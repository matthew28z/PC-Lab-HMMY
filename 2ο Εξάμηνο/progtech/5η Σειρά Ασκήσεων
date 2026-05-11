#include <iostream>

int main() {
    int N, M;
    std::cin >> N >> M;

    int* points = new int[N];

    for (int i = 0; i < M; i++) {
        int u, v;
        std::cin >> u >> v;

        points[u]++;
        points[v]++;
    }

    int u = -1, v = -1;

    for (int i = 0; i < N; i++) {
        if (points[i] % 2 == 1) {
            if (v != -1) {
                delete[] points;

                std::cout << "IMPOSSIBLE" << std::endl;

                return 0;
            }

            if (u == -1) {
                u = i;

                continue;
            }

            v = i;
        }
    }

    delete[] points;

    if (u == -1) {
        std::cout << "CYCLE" << std::endl;

        return 0;
    }

    std::cout << "PATH " << u << ' ' << v << std::endl;
}
