#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(int leave, string day, vector<int> holidays) {
    bool rest[32];          // 이 날이 휴무일인가? rest[1]~rest[30]
    vector<int> work;       // 연차 사용할 날 = 근무일

    int weekend = 1;
    if (day == "SUN") weekend += 6, rest[1] = true;
    else if (day == "MON") weekend += 5;
    else if (day == "TUE") weekend += 4;
    else if (day == "WED") weekend += 3;
    else if (day == "THU") weekend += 2;
    else if (day == "FRI") weekend++;
    
    // 휴무일, 근무일 계산
    while (weekend < 31) { rest[weekend] = true; rest[weekend + 1] = true; weekend += 7; }
    for (int h : holidays) rest[h] = true;
    rest[31] = false;

    for (int i = 1; i <= 30; ++i) if (!rest[i]) work.push_back(i);
    
    // 가장 긴 기간 찾기
    // 1. 사용가능 연차 수 > 일하는 날 수 => 1일부터 30일까지 다 쉴 수 있음
    if (leave >= work.size()) return 30;
    
    // 2. else
    int answer = 2, wsize=work.size();
    
    //work[0]부터 work[leave-1]까지 연속 휴무
    for (int i = 0; i < leave; ++i) rest[work[i]] = true;
    
    for (int i = leave - 1; i < wsize; ++i) {  // sliding (leave개의 연차 연속 사용)
        rest[work[i]] = true;               /* 마지막 연차 포함 */

        int s = 0, e = 1, tmp = 0;          /* 연속 휴무일 계산 */         
        for ( ; e <= 30; ++e) {
            if (rest[e] && !s) s = e;
            else if (s && !rest[e]) {   
                tmp = (e - s); s = 0; answer = (answer > tmp) ? answer : tmp;
            }
            //처음 쉬는 날, set s
            //s 존재, e 근무 => s~e-1까지 연속 휴무
        }
        if (s) {
            tmp = (e - s); s = 0; answer = (answer > tmp) ? answer : tmp;
            //30일이 휴무인 경우
        }

        rest[work[i - leave + 1]] = false;  /* 첫 연차 제외 */
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
1일부터 30일까지 있는 달
leave개의 연차 사용 가능, 1일의 요일은 day, holidays는 휴일 목록
연속으로 가장 오래 쉴 수 있는 일수?
*/