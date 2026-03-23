#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    unordered_map<string, int> times;
    for (int i = 0; i < n; i++) {
        string chess = "";
        string temp;
        for (int j = 0; j < 8; j++) {
            cin >> temp;
            chess += temp;
        }
        times[chess]++;
        cout << times[chess] << "\n";
    }

    return 0;
}