#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    int N = id_list.size();
    int R = report.size();

    //아이디 별 정수
    map<string, int> M;
    int idx = 0;
    for (string id : id_list) M[id] = idx++;

    set<int> S[1000];//V[i]: i가 신고한 사람 목록
    int cnt[1000] = { 0, };
    for (string r : report) {
        int blank = 0;
        while (r[blank] != ' ') blank++;
        int A = M[r.substr(0, blank)];
        int B = M[r.substr(blank + 1)];
        if (S[A].find(B) == S[A].end()) S[A].insert(B), cnt[B]++;
    }
    for (string id : id_list) {
        int A = M[id], sum=0;
        for (auto it = S[A].begin(); it != S[A].end(); it++) {
            if (cnt[*it] >= k) sum++;
        }
        answer.push_back(sum);
    }

    return answer;
}
int main() {
    vector<string> id_list = { "muzi","frodo","apeach","neo" };
    vector<string> report = { "muzi frodo","apeach frodo","frodo neo", "muzi neo", "apeach muzi" };
    int k = 2;

    vector<int> ans = solution(id_list, report, k);
    for (int a : ans) cout << a << " ";

    return 0;
}