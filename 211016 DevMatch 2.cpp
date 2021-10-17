#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(int leave, string day, vector<int> holidays) {
    bool rest[32];          // �� ���� �޹����ΰ�? rest[1]~rest[30]
    vector<int> work;       // ���� ����� �� = �ٹ���

    int weekend = 1;
    if (day == "SUN") weekend += 6, rest[1] = true;
    else if (day == "MON") weekend += 5;
    else if (day == "TUE") weekend += 4;
    else if (day == "WED") weekend += 3;
    else if (day == "THU") weekend += 2;
    else if (day == "FRI") weekend++;
    
    // �޹���, �ٹ��� ���
    while (weekend < 31) { rest[weekend] = true; rest[weekend + 1] = true; weekend += 7; }
    for (int h : holidays) rest[h] = true;
    rest[31] = false;

    for (int i = 1; i <= 30; ++i) if (!rest[i]) work.push_back(i);
    
    // ���� �� �Ⱓ ã��
    // 1. ��밡�� ���� �� > ���ϴ� �� �� => 1�Ϻ��� 30�ϱ��� �� �� �� ����
    if (leave >= work.size()) return 30;
    
    // 2. else
    int answer = 2, wsize=work.size();
    
    //work[0]���� work[leave-1]���� ���� �޹�
    for (int i = 0; i < leave; ++i) rest[work[i]] = true;
    
    for (int i = leave - 1; i < wsize; ++i) {  // sliding (leave���� ���� ���� ���)
        rest[work[i]] = true;               /* ������ ���� ���� */

        int s = 0, e = 1, tmp = 0;          /* ���� �޹��� ��� */         
        for ( ; e <= 30; ++e) {
            if (rest[e] && !s) s = e;
            else if (s && !rest[e]) {   
                tmp = (e - s); s = 0; answer = (answer > tmp) ? answer : tmp;
            }
            //ó�� ���� ��, set s
            //s ����, e �ٹ� => s~e-1���� ���� �޹�
        }
        if (s) {
            tmp = (e - s); s = 0; answer = (answer > tmp) ? answer : tmp;
            //30���� �޹��� ���
        }

        rest[work[i - leave + 1]] = false;  /* ù ���� ���� */
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
/*
1�Ϻ��� 30�ϱ��� �ִ� ��
leave���� ���� ��� ����, 1���� ������ day, holidays�� ���� ���
�������� ���� ���� �� �� �ִ� �ϼ�?
*/