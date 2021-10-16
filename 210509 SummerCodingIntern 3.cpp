//���͸� �ִ��� ���� ������
//��ǥ��(row,col) r��° ���μ� c��° ���μ� ������ ����. ���� 1���� ����
//�밢���� ���̰� r�� ���簢���� 45�� ����� ������� ���� ���
//�� (row,col)���� �¿���� ���� r/2��ŭ
// �����: ��� ���͵� ���ݷ� -p, ���ݷ� 0�Ǹ� �����
// �Ķ���: ��� ��ó�� ���ݷ� -p/2, "

//p, r�� �־��� �� ������ �� �� ����Ͽ� ���� �� �ִ� ������ �ִ� ��?
#include <string>
#include <vector>

using namespace std;

int dp[51][51];
int ava[50][50][2];
int solution(vector<vector<int>> maps, int p, int r) {
    int answer = 0;

    int N = maps.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ava[i][j][0] = (maps[i][j] > p) ? 0 : 1;
            ava[i][j][1] = (maps[i][j] > (p >> 1)) ? 0 : 1;
        }
    }
    r >>= 1;

    for (int R = 0; R <= N; ++R) {
        for (int C = 0; C <= N; ++C) {
            int tmp = 0;
            
            int i = R - r;
            for ( ; i < R; ++i) {
                if (i < 0) continue;

                int j = (R + C - r - 1) - i;
                tmp += (j < 0) ? 0 : ava[i][j][1];
                j++;
                for (; j < (C - R + r) + i; ++j) {
                    if (j < 0 || j >= N) continue;
                    tmp += ava[i][j][0];
                }
                tmp += (j >= N) ? 0 : ava[i][j][1];
            }
            for ( ; i < R + r; ++i) {
                if (i >= N) continue;

                int j = (C - R - r) + i;
                tmp += (j < 0) ? 0 : ava[i][j][1];
                j++;
                for (; j < (R + C + r - 1) - i; ++j) {
                    if (j < 0 || j >= N) continue;
                    tmp += ava[i][j][0];
                }
                tmp += (j >= N) ? 0 : ava[i][j][1];
            }
            dp[R][C] = tmp;
            answer = (answer > tmp) ? answer : tmp;
        }
    }
 /*   for (int i = 0; i < r; ++i) {
        if (i >= N) continue;
        for (int j = 0; j < r - i - 1; ++j) {
            if (j < N) dp[0][0] += ava[i][j][0];
        }
        dp[0][0] += ava[i][r-i][1];
    }
    */
    return answer;
}
int main() {
    vector<vector<int>> maps = {{1, 28, 41, 22, 25, 79, 4},
    {39, 20, 10, 17, 19, 18, 8},
    {21, 4, 13, 12, 9, 29, 19},
    {58, 1, 20, 5, 8, 16, 9},
    {5, 6, 15, 2, 39, 8, 29},
    {39, 7, 17, 5, 4, 49, 5},
    {74, 46, 8, 11, 25, 2, 11 }};//������ 50*50 ����
    int p=19; //1�̻� 99����
    int r=6;//2�̻� maps�� ���� ���� ����
    printf("%d ", solution(maps, p, r)); return 0;
}