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
        if ('0' <= new_id[i] && new_id[i] <= '9') { n *= 10, n += (new_id[i] - '0'); }
        else slen++;
    }

    string ans = new_id;
    while (1) {
        if (S.find(ans) == S.end()) return ans;

        int N = ++n, TEN = 1;
        while (TEN <= N) TEN *= 10;
        TEN /= 10;

        ans = new_id.substr(0, slen);
        while (TEN) { ans += ((N / TEN) + '0'); N %= TEN; TEN /= 10; }
    }
}
int main() {
    //vector<string> reg = { "card", "ace13", "ace18", "banker", "ace17", "ace19" };
    //string newid = "ace13";
    vector<string> reg = { "cow", "cow1", "cow2", "cow3", "cow4", "cow9", "cow8", "cow7", "cow6", "cow5" };
    string newid="cow";
    cout << solution(reg, newid);
    return 0;
}
/*
newid=(문자열)+(숫자) 형식
newid가 기존 아이디 리스트에 존재하지 않을 때까지 숫자+1하여 해당하는 아이디를 리턴
숫자는 0으로 시작하지 않으며, 최대 6자리임. 추천하지 못하는 경우는 주어지지 않음
s=AAA n=0  => AAA
s=AAA n=1  => AAA1
s=AAA n=02 => AAA2
*/
