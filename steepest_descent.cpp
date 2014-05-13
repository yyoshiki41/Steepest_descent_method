#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

double c = 0.01;
int N = 2;
int K = 1000;

int main()
{
    double x[N];
    for (int n = 0; n < N; n++) {
        cin >> x[n]; // keybordから出力
    }

    char filepath[256];
    sprintf(filepath, "steepest/%lf,%lf.txt", x[0], x[1]);
    ofstream fout; // file出力の為の定義
    fout.open(filepath); // ファイルを開く
    fout << "#k¥tx1¥tx2" << endl; // 見出し出力

    double v[2];
    double t;
    for (int k = 1; k <= K; k++) {
        fout << k << "\t";
        fout << x[0] << "\t";
        fout << x[1] << endl;

        for (int n = 0; n < N; n++) {
            v[n] = 4 * pow(x[n], 3) - 32 * x[n] + 5;
        }

        double sum = 0;
        for (int n = 0; n < N; n++) {
            sum += pow(v[n], 2);
        }
        if (sqrt(sum) == 0) break;

        for (int n = 0; n < N; n++) {
            x[n] = x[n] - c * v[n];
        }
    }
}
