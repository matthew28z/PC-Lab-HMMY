#include "pzhelp"

bool goodInput(int N, int Q) {
    if (N >= 1 && N <= 200000 && Q >= 1 && Q <= 50000) {
        return true;
    }

    return false;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

long long sumPoints(int start, int end, int* stationPoints) {
    long long routePoints = 0LL;

    for (int i = start; i <= end; i++) {
        routePoints += stationPoints[i];
    }

    return routePoints;
}

PROGRAM {
    const int N = READ_INT();
    const int Q = READ_INT();

    if (goodInput(N, Q)) {
        int* stationPoints = new int[N];
        int** routes = new int*[Q];

        for (int i = 0; i < N; i++) {
            stationPoints[i] = READ_INT();
        }

        for (int j = 0; j < Q; j++) {
            routes[j] = new int[3];

            for (int k = 0; k < 3; k++) {
                //Ths morfhs [tj, aj, bj]
                routes[j][k] = READ_INT();
            }
        }

        for (int j = 0; j < Q; j++) {
            const int end = routes[j][0] - 1; //convert to 0-based

            const int minStart = max(end - routes[j][2] + 1, 0);
            int maxStart = end - routes[j][1] + 1;

            if (maxStart < 0) {
                maxStart = max(routes[j][1] - 1, 0);
            }
            /*
            WRITELN("Route:", j);
            WRITELN("Destination:", end);
            WRITELN("Minimum Start:", minStart);
            WRITELN("Maximum Start:", maxStart);*/
            long long routePoints = sumPoints(maxStart, end, stationPoints);

            for (int i = minStart; i < maxStart; i++) {
                
                if (stationPoints[i] <= 0) {
                    //WRITELN("Subroute", "Start:", i, "Skipped");
                    continue;
                }           

                long long temp = sumPoints(i, end, stationPoints);

                //WRITELN("Subroute", "Start:", i, "Points:", temp);
                if (temp > routePoints) {
                    routePoints = temp;
                }
            }

            WRITELN(routePoints);
        }
    }
}
