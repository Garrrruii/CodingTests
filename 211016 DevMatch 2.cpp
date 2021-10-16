#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool rest[32];
int solution(int leave, string day, vector<int> holidays) {
    int weekend = 1;
    if (day == "MON") weekend += 5;
    else if (day == "TUE") weekend += 4;
    else if (day == "WED") weekend += 3;
    else if (day == "THU") weekend += 2;
    else if (day == "FRI") weekend++;
    else if (day == "SUN") rest[1] = true, weekend += 6;

    while (weekend < 31) { rest[weekend] = true; rest[weekend + 1] = true; weekend += 7; }
    for (int h : holidays) rest[h] = true;
    rest[31] = false;

    vector<int> work;
    for (int i = 1; i <= 30; ++i) if (!rest[i]) work.push_back(i);
    
    if (leave >= work.size()) return 30;

    int answer = 2, wsize=work.size();
    //work[0]���� work[leave-1]���� ���� �������� ��
    for (int i = 0; i < leave; ++i) rest[work[i]] = true;
    //sliding
    for (int i = leave - 1; i < wsize; ++i) {
        //cout << "\n"<< i - leave + 1 << ": ";
        //���� ���� ����
        rest[work[i]] = true;

        //Ȯ��,
        int s = 0, e = 1, tmp = 0;
        for ( ; e <= 30; ++e) {
            //ó�� ���� ��, set s
            if (rest[e] && !s) s = e;
            //s ����, e�� ���� �ʴ� �� => s���� e-1���� �������� ��
            else if (s && !rest[e]) {
                tmp = (e - s); s = 0;
                answer = (answer > tmp) ? answer : tmp;
                //cout << tmp << " ";
            }
        }
        if (s) {
            tmp = (e - s); s = 0;
            answer = (answer > tmp) ? answer : tmp;
            //cout << tmp << " ";
        }

        //�̹� ���� ù�� ����
        rest[work[i - leave + 1]] = false;
    }

    return answer;
}
int main() {
    int l = 4;
    string day = "FRI";
    vector<int> hol = { 6, 21, 23, 27, 28 };
    cout << solution(l, day, hol);
    return 0;
}