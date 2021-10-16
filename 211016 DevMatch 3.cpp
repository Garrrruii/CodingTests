#include <string>
#include <queue>
#include <iostream>
using namespace std;

vector<string> solution(vector<vector<int>> mac) {
    int map[6][6] = { 0, };
    bool vis[6][6] = { false, };
    int dy[4] = { 1,-1,0,0 }, dx[4] = { 0,0,1,-1 };
    queue<pair<int, int>> Q;
    vector<pair<int, int>> V;

    for (vector<int> m : mac) {

        //m[0] 열에 m[1] 색을 떨어트림
        int r = 5, c = m[0] - 1;
        while (r >= 0 && !map[r][c]) r--;
        map[r + 1][c] = m[1];

        //터트릴 거 없을 때 까지 터트리기
        bool nonstop = true;
        while (nonstop) {
            //초기화
            for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) if (map[i][j]) vis[i][j] = false;
            nonstop = false;

            //터트리기
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 6; ++j) {
                    if (vis[i][j]) continue;

                    int color = map[i][j];
                    Q.push({ i,j }); V.push_back({ i,j }); vis[i][j] = true;
                    while (!Q.empty()) {
                        int y = Q.front().first, x = Q.front().second; Q.pop();

                        for (int d = 0; d < 4; ++d) {
                            int ny = y + dy[d], nx = x + dx[d];
                            if (ny < 0 || ny>5 || nx < 0 || nx>5) continue;
                            if (vis[ny][nx] || map[ny][nx] != color) continue;

                            Q.push({ ny,nx }); V.push_back({ ny,nx }); vis[ny][nx] = true;
                        }
                    }
                    if (V.size() > 2) {
                        nonstop = true;
                        for (pair<int, int> v : V) map[v.first][v.second] = 0;
                    }
                    V.clear();
                }
            }

            //아래로 떨어트리기
            for (int c = 0; c < 6; ++c) {
                int low = 0;
                while (map[low][c]) low++;

                for (int r = low + 1; r < 6; ++r) {
                    if (map[r][c]) map[low][c] = map[r][c], map[r][c] = 0, low++;
                }
            }
        }
    }

    vector<string> answer;
    for (int i = 5; i >= 0; --i) {
        string row = "";
        for (int j = 0; j < 6; ++j) row += (map[i][j] + '0');
        answer.push_back(row);
    }
    return answer;
}
int main() {
    vector<vector<int>> macaron = { {1,1},{2,1},{1,2},{3,3},{6,4},{3,1},{3,3} ,{3,3},{3,4},{2,1} };
    vector<string> ans = solution(macaron);
    for (int i = 0; i < 6; ++i) cout << ans[i] << "\n";

    return 0;
}
