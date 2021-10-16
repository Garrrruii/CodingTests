//몬스터를 최대한 많이 없애자
//목표점(row,col) r번째 가로선 c번째 세로선 만나는 지점. 각각 1부터 시작
//대각선의 길이가 r인 정사각형을 45도 기울인 모양으로 마법 사용
//즉 (row,col)에서 좌우상하 길이 r/2만큼
// 노란색: 모든 몬스터들 공격력 -p, 공격력 0되면 사라짐
// 파란색: 모든 몬스처들 공격력 -p/2, "

//p, r이 주어질 때 마법을 한 번 사용하여 없앨 수 있는 몬스터의 최대 수?
#include <string>
#include <vector>

using namespace std;

int dp[51][51];
int ava[50][50][2];
int solution(vector<vector<int>> maps, int p, int r) {
    int answer = 0;

    int N = maps.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ava[i][j][0] = (maps[i][j] > p) ? 0 : 1;
            ava[i][j][1] = (maps[i][j] > (p >> 1)) ? 0 : 1;
        }
    }
    r >>= 1;

    for (int R = 0; R <= N; ++R) {
        for (int C = 0; C <= N; ++C) {
            int tmp = 0;
            
            int i = R - r;
            for ( ; i < R; ++i) {
                if (i < 0) continue;

                int j = (R + C - r - 1) - i;
                tmp += (j < 0) ? 0 : ava[i][j][1];
                j++;
                for (; j < (C - R + r) + i; ++j) {
                    if (j < 0 || j >= N) continue;
                    tmp += ava[i][j][0];
                }
                tmp += (j >= N) ? 0 : ava[i][j][1];
            }
            for ( ; i < R + r; ++i) {
                if (i >= N) continue;

                int j = (C - R - r) + i;
                tmp += (j < 0) ? 0 : ava[i][j][1];
                j++;
                for (; j < (R + C + r - 1) - i; ++j) {
                    if (j < 0 || j >= N) continue;
                    tmp += ava[i][j][0];
                }
                tmp += (j >= N) ? 0 : ava[i][j][1];
            }
            dp[R][C] = tmp;
            answer = (answer > tmp) ? answer : tmp;
        }
    }
 /*   for (int i = 0; i < r; ++i) {
        if (i >= N) continue;
        for (int j = 0; j < r - i - 1; ++j) {
            if (j < N) dp[0][0] += ava[i][j][0];
        }
        dp[0][0] += ava[i][r-i][1];
    }
    */
    return answer;
}
int main() {
    vector<vector<int>> maps = {{1, 28, 41, 22, 25, 79, 4},
    {39, 20, 10, 17, 19, 18, 8},
    {21, 4, 13, 12, 9, 29, 19},
    {58, 1, 20, 5, 8, 16, 9},
    {5, 6, 15, 2, 39, 8, 29},
    {39, 7, 17, 5, 4, 49, 5},
    {74, 46, 8, 11, 25, 2, 11 }};//정방형 50*50 이하
    int p=19; //1이상 99이하
    int r=6;//2이상 maps의 행의 길이 이하
    printf("%d ", solution(maps, p, r)); return 0;
}