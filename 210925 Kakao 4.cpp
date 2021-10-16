#include <string>
#include <vector>
#include <iostream>
using namespace std;

//info[i]: ����ġ�� 10-i���� ���� ȭ�� ����
int aa[11], A; //apeach[i] ����ġ�� i���� ���� ȭ�� ����
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

    //���̾��� �� ������ �������� ��� => ���̾��� �ּ� aa[score]+1���� �ʿ�
    if (remain > aa[score]) {
        rr[score] = aa[score] + 1; R += score;
        solve(score + 1, remain - rr[score]);
        rr[score] = 0; R -= score;
    }

    //���̾��� ������ �� �������� ���
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
    �� ��ȸ ����ڿ��� �Ҹ��ϰ� ��Ģ
    ����ġ ���� n�� �� �� ���̾��� n�� ��
    10 9 8 7 6   4 ... 1 ���� ���
    k��: ����ġ�� a��, ���̾��� b��= > �� ���� ȭ���� ���� ����� k�� ������
    ���� ������ ���� ��� ����ġ�� ���

    ����, ����ġ�� n���� �� ��� ���̾��� �� ����
    info
    ���̾��� ����ġ�� ū ���� ���� �̱�� ���� n���� � ���ῡ ����� �ϴ��� ���Ϸ��� ��
    ���̾��� ����� �� ���� ��� -1�� �������ּ���

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