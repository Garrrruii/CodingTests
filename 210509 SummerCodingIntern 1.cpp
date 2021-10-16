#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int val[24];
vector<int> solution(string code, string day, vector<string> data) {
    vector<int> answer;
    
    for (string str : data) {
        int l = str.size();

        cout << str.substr(l-22,6) << "\n";
        cout << str.substr(l-10,8) << "\n";
        if (code != str.substr(l-22,6)) 
            continue;
        if (day != str.substr(l-10, 8)) 
            continue;

        //price °è»ê
        int p = 0;
        for (int i = 6; i < l-28; ++i) {
            p *= 10, p += (str[i] - '0');
        }
        int t = (str[l-2] - '0') * 10 + (str[l-1] - '0');
        val[t] = p;
    }
    for (int i = 0; i < 24; ++i) if (val[i] > 0) answer.push_back(val[i]);

    return answer;
}
int main() {
    string code="012345";
    string day="20190620";
    vector<string> data = { "price=80 code=987654 time=2019062113",
        "price=90 code=012345 time=2019062014",
        "price=120 code=987654 time=2019062010",
        "price=110 code=012345 time=2019062009",
        "price=95 code=012345 time=2019062111" };
    vector<int> ans = solution(code, day, data);
    for (int a : ans) printf("%d ", a);
    return 0;
}