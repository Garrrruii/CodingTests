#include <iostream>
#include <queue>
using namespace std;
// N개의 프로그램
// D시간 내에 순서대로 수행하기 위해 필요한 컴퓨터 최소 개수
// 각 프로그램 실행 시간≤1만  T≤40  N≤10만  D≤1000만
// Binary Search  => logN
// Priority Queue => NlogN
// Total N(logN)(logN)
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	priority_queue<int, vector<int>, greater<int>> pq;
	int a[100000];

	int T; // 40
	int N; // 100'000
	int D; // 10'000'000
	
	cin >> T;
	for (int x = 1; x <= T; ++x) {
		cin >> N >> D;
	
		int L = 1, R = N, mid, tmp;
		while (L < R) {
			mid = (L + R) >> 1;
			for (int i = 0; i < mid; ++i) pq.push(a[i]);
			for (int i = mid; i < N; ++i) {
				tmp = pq.top(); tmp += a[i]; pq.push(tmp);
			}
			tmp = mid - 1;
			while (tmp--) pq.pop();

			if (pq.top() <= D) R = mid;
			else L = mid + 1;
			pq.pop();
		}
		cout << "#" << x << " " << L << "\n";
	}

	return 0;
}