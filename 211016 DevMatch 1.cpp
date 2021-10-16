#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

set<string> S;
string solution(vector<string> registered_list, string new_id) {
    for (string r : registered_list) S.insert(r);
    
    int length = new_id.size(), n=0, slen=0;
    for (int i = 0; i < length; ++i) {
        if ('0' <= new_id[i] && new_id[i] <= '9') {
            n *= 10, n += (new_id[i] - '0');
        }
        else slen++;
    }

    string ans = new_id;
    while (1) {
        auto it = S.find(ans);
        if (it == S.end()) return ans;

        int N = ++n, TEN = 1;
        while (TEN <= N) TEN *= 10;
        TEN /= 10;

        ans = new_id.substr(0, slen);
        while (TEN) { ans += ((N / TEN) + '0'); N %= TEN; TEN /= 10; }
    }
}
int main() {
    //vector<string> reg = { "card", "ace13", "ace18", "banker", "ace17", "ace19" };
    vector<string> reg = { "cow", "cow1", "cow2", "cow3", "cow4", "cow9", "cow8", "cow7", "cow6", "cow5" };
    string newid="cow";
    cout << solution(reg, newid);
    return 0;
}