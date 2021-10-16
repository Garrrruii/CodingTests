#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct stone {
	int x, y, k;
};
set<int> S;
int Y[400];

bool sorts(stone A, stone B) {
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
} //sort by 1)x 2)y

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T, N, K;
	stone s[400];

	cin >> T;
	while (T--) {
		cin >> N >> K;
		for (int i = 0; i < N; ++i) cin >> s[i].x >> s[i].y >> s[i].k;

		int yn = 0; S.clear();
		for (int i = 0; i < N; ++i) S.insert(s[i].y);
		for (auto it = S.begin(); it != S.end(); it++) Y[yn++] = *it;

		sort(s, s + N, sorts);

		int ANS = 987654321;
		for (int y1 = 0; y1 < yn && ANS; ++y1) {		//y1부터
			for (int y2 = 0; y2 < yn && ANS; ++y2) {	//y2까지
				int height = Y[y2] - Y[y1];

				queue<int> Q;
				int num[10] = { 0, }, cnt = 0;
				for (int l = 0, r = 0; r < N; ++r) {	// 이 높이에 해당하는 경우만 탐색
					if (s[r].y < Y[y1] || s[r].y > Y[y2]) continue;
					Q.push(r);

					if (!num[s[r].k]) cnt++;			// 새로 추가한 돌 마킹
					num[s[r].k]++;

					while (cnt == K) {					// 돌 K개 모았을 때
						int width = s[r].x - s[l].x;	// 넓이 계산
						ANS = min(ANS, height * width);

						num[s[Q.front()].k]--;			// l번째 돌 제거
						if (!num[s[Q.front()].k]) cnt--;
						Q.pop(); l = Q.front();
					}
				}
			}
		}
		cout << ANS << "\n";
	}
	return 0;
}
/*
3
6 4
2 1 1 2 2 2 2 3 3 2 4 4 1 2 1 1 3 4
7 3
10 10 1 10 60 1 20 20 2 30 40 3 40 20 1 40 50 3 50 30 2
2 2
1 2 1 100 92 2

0 300 8910
*/