#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
//3^13>1000000 => r(10^13) => 3333333

bool notp[3333334];
vector<long long> prime;
int solution(int n, int k) {
    int answer = 0;
    long long MAX = 3333333;
    notp[0] = notp[1] = true;
    for (long long i = 2; i < MAX; ++i) {
        if (!notp[i]) {
            prime.push_back(i);
            for (long long j = i * i; j <= MAX; j += i) notp[j] = true;
        }
    }
    
    int K = 1;
    while (K < n) K *= k;
    K /= k;

    long long num = 0;
    while (K > 1) {
        long long q = n / K; n %= K; K /= k;
        if (!q) {
            //몫 없음 => 소수인지 판정해야 함
            cout << num << " ";
            if (num <= MAX) {
                if (!notp[num]) answer++;
            }
            else {
                bool notprime = false;
                long long r = sqrt(num) + 1;
                for (int p : prime) {
                    if (p > r) break;
                    if (!(num % p)) { notprime = true; break; }
                }
                if (!notprime) answer++;
            }

            num = 0;
        }
        else num *= 10, num += q;
    }
    if (num) {
        //num이 소수인가?
        cout << num << " ";
        if (num <= MAX) if (!notp[num]) answer++;
        else {
            bool notprime = false;
            long long r = sqrt(num) + 1;
            for (int p : prime) {
                if (p > r) break;
                if (!(num % p)) { notprime = true; break; }
            }
            if (!notprime) answer++;
        }
    }
    return answer;
}
int main() {
    cout << solution(437674, 3)<<"\n";
    cout << solution(110011, 10) << "\n";

    cout << solution(1679615, 3) << "\n";

}