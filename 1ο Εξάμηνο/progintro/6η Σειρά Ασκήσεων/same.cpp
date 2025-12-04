#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void readLine(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());
}

int min(int a, int b) {
    if (a > b) {
        return b;
    }

    return a;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

int main() {
    int N;

    cin >> N;

    vector<int> a(N);
    vector<int> b(N);

    readLine(a);
    readLine(b);

    bool same = true;
    int m;

    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            if (same) {
                cout << "no " << min(a[i], b[i]) << " ";
                m = max(a[i], b[i]);
                same = false;
            } else {
                const int temp = max(a[i], b[i]);

                if (temp > m) {
                    m = temp;
                }
            }

        }
    }

    if (same) {
        cout << "yes" << endl;
    } else {
        cout << m << endl;
    }
        
    return 0;
}
