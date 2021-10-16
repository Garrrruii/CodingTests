#include <string>
#include <vector>
#include <iostream>
using namespace std;

//info[i]: 어피치가 10-i점을 맞힌 화살 개수
int aa[11], A; //apeach[i] 어피치가 i점을 맞힌 화살 개수
int rr[11], R;
int ans[11], MAXDIFF = 0;
void solve(int score, int remain) {
    if (score > 10) {
        int diff = R - A;

        if (MAXDIFF < diff) {
            rr[0] = remain;

            MAXDIFF = diff;
            for (int i = 0; i < 11; ++i) ans[i] = rr[i];

            //cout << "\n" << diff << "\t";
            //for (int i = 0; i < 11; ++i) cout << ans[i] << " ";
        }
        return;
    }

    //라이언이 이 점수를 가져가는 경우 => 라이언은 최소 aa[score]+1발이 필요
    if (remain > aa[score]) {
        rr[score] = aa[score] + 1; R += score;
        solve(score + 1, remain - rr[score]);
        rr[score] = 0; R -= score;
    }

    //라이언이 점수를 안 가져가는 경우
    rr[score] = 0;
    if (aa[score]) A += score, solve(score + 1, remain), A -= score;
    else solve(score + 1, remain);

}
vector<int> solution(int n, vector<int> info) {
    for (int i = 0; i < 11; ++i) aa[i] = info[10 - i];
    for (int i = 0; i < 11; ++i) ans[i] = 0;
    A = 0, R = 0, MAXDIFF = 0;
    
    solve(1, n);
    vector<int> answer;
    if(MAXDIFF) for (int i = 0; i < 11; ++i) answer.push_back(ans[10 - i]);
    else answer.push_back(-1);

    return answer;
}
/* 
    전 대회 우승자에게 불리하게 규칙
    어피치 먼저 n발 쏜 후 라이언이 n발 쏨
    10 9 8 7 6   4 ... 1 점수 계산
    k점: 어피치가 a발, 라이언이 b발= > 더 많은 화살을 맞춘 사람이 k점 가져감
    최종 점수가 같은 경우 어피치가 우승

    현재, 어피치가 n발을 다 쏘고 라이언이 쏠 차례
    info
    라이언은 어피치를 큰 점수 차로 이기기 위해 n발을 어떤 과녁에 맞춰야 하는지 구하려고 함
    라이언이 우승할 수 없는 경우 -1을 리턴해주세요

*/
int main() {
    vector<int> answer;
    answer = solution(5, { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 });
    for (int a : answer) cout << a << " ";
    cout << "\n";

    answer = solution(1, { 1,0,0,0,0,0,0,0,0,0,0 });
    for (int a : answer) cout << a << " ";
    cout << "\n";

    answer = solution(9, { 0,0,1,2,0,1,1,1,1,1,1 });
    for (int a : answer) cout << a << " ";
    cout << "\n";

    answer = solution(10, { 0,0,0,0,0,0,0,0,3,4,3 });
    for (int a : answer) cout << a << " ";
    cout << "\n";
    
    return 0;
}