#include <string>
#include <vector>
#include <algorithm>
#include <queue>
//리프트는 일정한 시간 간격으로 들어옴
//들어오는 순서대로 이프트에 번호 부여, 0부터
//한대에는 한명 만
//한대 출발 후 다음 리프트 도착 전까지 도착한 승객 : 같은 시간에 도착한 거
//티켓 등급 높은 순 > 도착 순서 빠른 순 > 아이디 값 작은 순
// t: 손님i의 도착 시각을 저장한 배열
// r: 손님i의 등급
using namespace std;

struct node {
    int id, t, r;
};
bool sortbyt(node A, node B) {
        return A.t < B.t;
}
vector<node> v;

struct sortpq {
    bool operator()(node A, node B) {
        if (A.r == B.r) {
            if (A.t == B.t) return A.id > B.id;
            else return A.t > B.t;
        }
        return A.r > B.r;
    }
};
priority_queue<node, vector<node>, sortpq> pq;
vector<int> solution(vector<int> t, vector<int> r) {
    vector<int> answer;

    for (int i = 0; i < t.size(); ++i) v.push_back({ i,t[i],r[i] });
    sort(v.begin(), v.end(), sortbyt);

    int vidx = 0;
    int T = 0;
    while (vidx<v.size()) {
        while (vidx<v.size() && v[vidx].t == T) pq.push(v[vidx]), vidx++;
        T++;
        if(!pq.empty()) answer.push_back(pq.top().id), pq.pop();
    }
    while (!pq.empty()) answer.push_back(pq.top().id), pq.pop();

    return answer;
}
int main() {
    vector<int> t = { 7, 6, 8, 1 };// { 0, 1, 3, 0 };
    vector<int> r = { 0, 1, 2, 3 };
    vector<int> ans = solution(t, r);
    for (int a : ans) printf("%d ", a);
    return 0;
}