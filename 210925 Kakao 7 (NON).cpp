#include <string>
#include <vector>
#include <iostream>
/*
문제 설명
플레이어 A와 플레이어 B가 서로 게임을 합니다.
당신은 이 게임이 끝날 때까지 양 플레이어가 캐릭터를 몇 번 움직이게 될지 예측하려고 합니다.

각 플레이어는 자신의 캐릭터 하나를 보드 위에 올려놓고 게임을 시작합니다.
게임 보드는 1x1 크기 정사각 격자로 이루어져 있으며,
보드 안에는 발판이 있는 부분과 없는 부분이 있습니다.
발판이 있는 곳에만 캐릭터가 서있을 수 있으며,
처음 캐릭터를 올려놓는 곳은 항상 발판이 있는 곳입니다.
캐릭터는 발판이 있는 곳으로만 이동할 수 있으며, 보드 밖으로 이동할 수 없습니다.
밟고 있던 발판은 그 위에 있던 캐릭터가 다른 곳으로 이동하여 다른 발판을 밞음과 동시에 사라집니다.
양 플레이어는 번갈아가며 자기 차례에 자신의 캐릭터를
상하좌우로 인접한 4개의 칸 중에서 발판이 있는 칸으로 옮겨야 합니다.

다음과 같은 2가지 상황에서 패자와 승자가 정해지며, 게임이 종료됩니다.

움직일 차례인데 캐릭터의 상하좌우 주변 4칸이 모두 발판이 없거나 보드 밖이라서 이동할 수
없는 경우, 해당 차례 플레이어는 패배합니다.
두 캐릭터가 같은 발판 위에 있을 때, 상대 플레이어의 캐릭터가 다른 발판으로 이동하여
자신의 캐릭터가 서있던 발판이 사라지게 되면 패배합니다.
게임은 항상 플레이어 A가 먼저 시작합니다. 양 플레이어는 최적의 플레이를 합니다.
즉, 이길 수 있는 플레이어는 최대한 빨리 승리하도록 플레이하고,
질 수밖에 없는 플레이어는 최대한 오래 버티도록 플레이합니다.
'이길 수 있는 플레이어'는 실수만 하지 않는다면 항상 이기는 플레이어를 의미하며,
'질 수밖에 없는 플레이어'는 최선을 다해도 상대가 실수하지 않으면 항상 질 수밖에 없는 플레이어를 의미합니다.
최대한 오래 버틴다는 것은 양 플레이어가 캐릭터를 움직이는 횟수를 최대화한다는 것을 의미합니다.

아래 그림은 초기 보드의 상태와 각 플레이어의 위치를 나타내는 예시입니다.
*/
using namespace std;

int N, M;
bool b[5][5];
pair<int, int> A, B;
int di[4] = { 1,-1,0,0 }, dj[4] = { 0,0,1,-1 };

int play(int time) {
    pair<int, int> cur, nxt;
    if (time & 1) cur = B, nxt = A;
    else  cur = A, nxt = B;
   
    cout << time << " " << cur.first << " " << cur.second << "\n";

    if (!b[nxt.first][nxt.second]) return time;
    int ret = time;

    bool move = false;
    pair<int, int> O = cur;
    b[O.first][O.second] = false;
    for (int d = 0; d < 4; ++d) {
        int ni = O.first + di[d];
        int nj = O.second + dj[d];
        if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        //if (!b[ni][nj] || (ni == nxt.first && nj == nxt.second)) continue;
        if (!b[ni][nj]) continue;

        cur = { ni,nj };
        int tmp = play(time + 1);
        if (tmp > ret) ret = tmp;
        move = true;
    }
    if (!move) return time;
    b[O.first][O.second] = true; cur = O;

    return ret;
}
int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    N = board.size();
    M = board[0].size();
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) b[i][j] = board[i][j];
    }
    A = { aloc[0],aloc[1] };
    B = { bloc[0],bloc[1] };
    int answer = play(0);
    
    return answer;
}
int main() {
    cout << solution({ {1,1,1,1,1} }, { 0,0 }, { 0,4 });
    return 0;
}