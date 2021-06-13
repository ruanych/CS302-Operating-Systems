#include <iostream>
#include<algorithm>

int main() {
    using namespace std;
    int S, M, N;
    cin >> S >> M >> N;
    int *req = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> req[i];
    }
    sort(req, req + N);
    int start_idx = N - 1;
    while (start_idx >= 0 && req[start_idx] > S) {
        --start_idx;
    }

    cout << S;
    for (int i = start_idx; i >= 0; --i) {
        cout << " " << req[i];
    }
    for (int i = N - 1; i > start_idx; --i) {
        cout << " " << req[i];
    }

    int cnt = 0;
    if (start_idx > -1) {
        cnt += S - req[0];
    }

    if (start_idx < N - 1) {
        if (start_idx > -1) {
            cnt += req[N - 1] - req[0] + req[N - 1] - req[start_idx + 1];
        } else {
            cnt += req[N - 1] - S + req[N - 1] - req[start_idx + 1];
        }
    }
    cout << "\n" << cnt << "\n";
    delete[] req;
}