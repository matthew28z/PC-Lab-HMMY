#include <iostream>
#include <vector>

int getCity(int village, int*& villageToCity) {
    if (villageToCity[village] == village) {
        return village;
    }

    return villageToCity[village] = getCity(villageToCity[village], villageToCity);
}

bool chooseCenter(int villageA, int villageB, int*& villageToCity) {
    int cityA = getCity(villageA, villageToCity);
    int cityB = getCity(villageB, villageToCity);

    if (cityA == cityB) {
        return false; 
    }

    if (villageA != cityA) { //means the first village already belongs to another city
        villageToCity[cityB] = cityA;

        return true;
    }

    villageToCity[cityA] = cityB;

    return true; //otherwise if no village or just the second one belong to a city go with the second city
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M, K;
    std::cin >> N >> M >> K;

    int* villageToCenter = new int[N + 1]; //gia na glitwsw to -1 kathe fora

    for (int i = 0; i < N + 1; i++) { //jekina ola ta xwria ws autonomes poleis
        villageToCenter[i] = i;
    }

    int centers = N;

    for (int i = 0; i < M; i++) {
        int A, B;
        std::cin >> A >> B;

        if (chooseCenter(A, B, villageToCenter)) {
            centers--;
        }
    }

    if (centers > K) {
        std::cout << centers - K << std::endl;
    } else {
        std::cout << 1 << std::endl;
    }

    delete[] villageToCenter;
}
