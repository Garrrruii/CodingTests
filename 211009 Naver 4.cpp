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
		
		//(y,x)���� �밢������ ������ �� �ִ� �� ǥ��
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

		//(y,x)�� �����ϸ� y+1Ž��
		if (available) {		
			y_for_x[x] = y, ret += select(y + 1), y_for_x[x] = -1;
		}

		//vis�ʱ�ȭ
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
0: �آ�
1: �֢�
2: empty

string���� �־����� N*N���忡 N+1���� ���� ���´�.
���� ������ ���� �����δ�.
1. ���� ���󼭸� ������
2. ���� ���󼭸� ������
3. �밢���� ���󼭸� ������

��� ���� �����̸鼭 ���� ������ �ʴ� ������ ����� ���� ���Ͻÿ�

=> �ϴ� ��, ������ �� ���� �־���ϹǷ� �ึ�� ���� ���� ��(8!)
=> ���⼭ �밢�� ���� �̵��ϸ鼭 ������ �ֵ��� ������ �� ��.
   �밢������ �̵��� �� �ִ� ������ ĭ�� e[i][j]�� �����ص� ��,
   y���� x�� �� �� ���� ������ �� �ִ� ���� ����.
   
   y=k�� ����,
   �߰��� 0~k-1���� ���� ������ �ƿ� ���� Ž�� X
   k=N+1�̸� +1
*/