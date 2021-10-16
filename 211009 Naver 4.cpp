#include <string>
#include <queue>
#include <iostream>
using namespace std;

int y_for_x[8], N;
int vis[8][8];
vector<pair<int, int>> e[8][8];
queue<pair<int, int>> Q;
int select(int y) {
	if (y > N) return 1;
	
	vector<pair<int, int>> visited;
	int ret = 0;

	for (int x = 0; x <= N; ++x) {
		if (y_for_x[x] >= 0 || vis[y][x]>=0) continue;
		
		//(y,x)에서 대각선으로 도달할 수 있는 곳 표시
		bool available = true;
		vis[y][x] = y, Q.push({ y,x }), visited.push_back({ y,x });
		while (!Q.empty() && available) {
			int i = Q.front().first;
			int j = Q.front().second; Q.pop();

			for (pair<int, int> nxt : e[i][j]) {
				int ni = nxt.first, nj = nxt.second;
				
				if (vis[ni][nj] == y) continue;
				else if (vis[ni][nj] >= 0) { available = false; break; }
				else vis[ni][nj] = y, Q.push({ ni,nj }), visited.push_back({ ni,nj });
			}
		}
		while (!Q.empty()) Q.pop();

		//(y,x)가 가능하면 y+1탐색
		if (available) {		
			y_for_x[x] = y, ret += select(y + 1), y_for_x[x] = -1;
		}

		//vis초기화
		for (pair<int, int> v : visited) vis[v.first][v.second] = -1;
		visited.clear();
	}
	return ret;
}
int solution(vector<string> b) {
	N = b.size();

	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= N; ++j) {
			if (i > 0 && j > 0 && b[i - 1][j - 1] == '0') e[i][j].push_back({ i - 1,j - 1 });
			if (i < N && j < N && b[i][j] == '0') e[i][j].push_back({ i + 1,j + 1 });
			if (i < N && j>0 && b[i][j - 1]=='1') e[i][j].push_back({ i + 1,j - 1 });
			if (i > 0 && j < N && b[i - 1][j] == '1') e[i][j].push_back({ i - 1,j + 1 });
		}
	}

/*	for (int i = 0; i <= N; ++i)
		for (int j = 0; j <= N; ++j) {
			for (pair<int, int> n: e[i][j]) cout << n.first << ',' << n.second << " ";
			cout << "\n";
		}
	cout << "\n";*/

	for (int i = 0; i <= N; ++i) y_for_x[i] = -1;
	for (int i = 0; i <= N; ++i) for (int j = 0; j <= N; ++j) vis[i][j] = -1;

	return select(0);
}
int main() {
	vector<string> board = { "0010","0121","1101","2000" }; //answer=27
	cout << solution(board);
	return 0;
}

/*
0: ↖↘
1: ↗↙
2: empty

string으로 주어지는 N*N보드에 N+1개의 말을 놓는다.
말은 다음과 같이 움직인다.
1. 열을 따라서만 움직임
2. 행을 따라서만 움직임
3. 대각선을 따라서만 움직임

모든 말이 움직이면서 서로 만나지 않는 가능한 경우의 수를 구하시오

=> 일단 행, 열마다 한 개씩 있어야하므로 행마다 열을 고르면 됨(8!)
=> 여기서 대각선 따라 이동하면서 만나는 애들이 있으면 안 됨.
   대각선따라 이동할 수 있는 인접한 칸을 e[i][j]에 저장해둔 뒤,
   y별로 x를 고를 때 마다 도달할 수 있는 곳을 구함.
   
   y=k에 대해,
   중간에 0~k-1행의 말과 만나면 아예 다음 탐색 X
   k=N+1이면 +1
*/