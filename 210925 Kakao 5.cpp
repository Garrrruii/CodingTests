#include <queue>
#include <vector>
#include <iostream>
using namespace std;

struct node {
    int s, w;
};
bool operator<(node A, node B) { //A<B
    if (A.s == B.s) return A.w > B.w;
    else return A.s < B.s;
}
node dp[17][1 << 17];

vector<int> edge[17][2];

int solution(vector<int> info, vector<vector<int>> edges) {
    int N = info.size(); //0:sheep 1:wolf root=0, always sheep
    int MAX = 1 << N;

    for (vector<int> e : edges) {
        edge[e[0]][0].push_back(e[1]);
        edge[e[1]][1].push_back(e[0]);
    } //input

    //solve
    priority_queue<pair<node, pair<int, int>>> pq;
    dp[0][1] = { 1,0 }, pq.push({ {1,0},{0,1} });
    while (!pq.empty()) {
        node cnt = pq.top().first;
        int cur = pq.top().second.first;
        int bit = pq.top().second.second; pq.pop();
        if (cnt < dp[cur][bit]) continue;

        //부모
        if (cur) {
            int par = edge[cur][1][0];
            if (dp[par][bit] < cnt) dp[par][bit] = cnt, pq.push({ cnt,{par,bit} });
        }
        //자식
        for (int nxt : edge[cur][0]) {
            if (bit & (1 << nxt)) {
                if (dp[nxt][bit] < cnt) dp[nxt][bit] = cnt, pq.push({ cnt,{nxt,bit} });
            }
            else {
                int nbit = bit | (1 << nxt);

                node ncnt = cnt;
                if (info[nxt]) ncnt.w++;
                else ncnt.s++;
                if (ncnt.s <= ncnt.w) continue;

                if (dp[nxt][nbit] < ncnt) dp[nxt][nbit] = ncnt, pq.push({ ncnt,{nxt,nbit} });
            }
        }
    }

    //ans
    int answer = 0;
    for (int i = 0; i < MAX; ++i) if (answer < dp[0][i].s) answer = dp[0][i].s;
    return answer;
}