#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string s;
    map<char, int> m;
    while (cin >> s) {
        for (auto c : s) {
            ++m[c];
        }
    }
    //for (auto el : m) {
    //   cout << el.first << " " << el.second;
    //}
    return 0;
}