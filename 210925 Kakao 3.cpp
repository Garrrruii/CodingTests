#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {
    int MAXTIM = 23 * 60 + 59;
    int t0 = fees[0], c0 = fees[1];
    int t1 = fees[2], c1 = fees[3];

    int in[10000];
    for (int i = 0; i < 10000; ++i) in[i] = -1;
    int tim[10000] = { 0, };
    for (string r : records) {
        int h = 10 * (r[0] - '0') + r[1] - '0';
        int m = 10 * (r[3] - '0') + r[4] - '0';
        int time = h * 60 + m;

        int carnum = 0;
        for (int c = 6; c < 10; c++) carnum*=10, carnum += (r[c] - '0');
        
        if (r[11] == 'I') {
            in[carnum] = time;
            //    cout << carnum << "  " << time << "\tin\n";
        }
        else{
            tim[carnum] += (time - in[carnum]); in[carnum] = -1;
            //   cout << carnum << "  " << time << "\tout=> " << tim[carnum] << "\n"; 
        }
    }
    vector<int> answer;
    for (int c = 0; c < 10000; ++c) {
        if (!tim[c] && in[c]<0) continue;
        else if (in[c]>=0) tim[c] += (MAXTIM - in[c]);

        int cost = c0;
        tim[c] -= t0;
        if (tim[c] > 0) cost += ((tim[c] + t1 - 1) / t1) * c1;
        
        answer.push_back(cost);
    }

    return answer;
}
int main() {
    vector<int> fees = { 180, 5000, 10, 600 };
    vector<string> records
        = { "05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT"
        , "07:59 5961 OUT", "07:59 0148 IN", "18:59 0000 IN"
        , "19:09 0148 OUT", "22:59 5961 IN", "23:00 5961 OUT" };

    vector<int> ans = solution(fees, records);
    for (int a:ans) cout << a << " ";
    return 0;
}