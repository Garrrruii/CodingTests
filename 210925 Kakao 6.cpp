#include <vector>
#include <iostream>
using namespace std;

int fen[1002][1002], N, M;
void upd(int r1, int c1, int r2, int c2, int x) {
    //1,1~i,j까지 +=x
    int c, r = r1;
    while (r <= N) {
        c = c1;
        while (c <= M) fen[r][c] += x, c += (c & -c);
        c = c2;
        while (c <= M) fen[r][c] -= x, c += (c & -c);
        r += (r & -r);
    }
    r = r2;
    while (r <= N) {
        c = c1;
        while (c <= M) fen[r][c] -= x, c += (c & -c);
        c = c2;
        while (c <= M) fen[r][c] += x, c += (c & -c);
        r += (r & -r);
    }
}
int sum(int r0, int c0) {
    int ret = 0, r, c;
    r = r0;
    while (r) {
        c = c0;
        while (c) ret += fen[r][c], c -= (c & -c);
        r -= (r & -r);
    }
    return ret;
}
int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    N = board.size() + 1;
    M = board[0].size() + 1;
   
    // typ r1 c1 r2 c2 deg
    for (vector<int> s : skill) {
        int r1 = s[1] + 1, c1 = s[2] + 1;
        int r2 = s[3] + 2, c2 = s[4] + 2;
        int deg = s[5];

        if (s[0] & 1) {//공격
            upd(s[1] + 1, s[2] + 1, s[3] + 2, s[4] + 2, -s[5]);
        }
        else {
            upd(s[1] + 1, s[2] + 1, s[3] + 2, s[4] + 2, +s[5]);
        }

        //for (int i = 1; i < N; ++i) {
        //    for (int j = 1; j < M; ++j) cout<<sum(i,j)<<' ';
        //    cout << "\n";
        //}
        //cout << "\n";
    }

    int answer = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < M; ++j) if (board[i-1][j-1]+sum(i, j) > 0) answer++;
    }
    return answer;
}
int main() {
    cout << solution(
        { {5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5} },
        { {1,0,0,3,4,4},{1,2,0,2,3,2},{2,1,0,3,1,2},{1,0,1,3,3,1} });

}