#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

double c = 0.01;
int N = 2;
int K = 1000;

double differential(double a);
double norm(double a, double b);

int main()
{
    double x[N];
    for (int n = 0; n < N; n++) {
        cin >> x[n]; // keybordから出力
    }

    char filepath[256];
    sprintf(filepath, "conjugate/%lf,%lf.txt", x[0], x[1]);
    ofstream fout; // file出力の為の定義
    fout.open(filepath); // ファイルを開く
    fout << "#k¥tx1¥tx2¥tλ" << endl; // 見出し出力

    double v[N];
    for (int n = 0; n < N; n++) {
        v[n] = 0;
    }
    double y[N];
    double λ = 0;
    double λ_x = 0;
    double λ_y = 1;
    double sum;
    double tmp;

    for (int k = 1; k <= K; k++) {
        fout << k << "\t";
        fout << x[0] << "\t";
        fout << x[1] << "\t";
        fout << λ << endl;

        λ_x = norm(x[0], x[1]);
        λ_y = norm(y[0], y[1]);
        λ = λ_x / λ_y;
        for (int n = 0; n < N; n++) {
            v[n] = λ * v[n] - differential(x[n]);
        }

        sum = 0;
        for (int n = 0; n < N; n++) {
            sum += pow(v[n], 2);
        }
        if (sqrt(sum) == 0) break;

        for (int n = 0; n < N; n++) {
            y[n] = x[n];
            x[n] = x[n] + c * v[n];
        }
    }
}

double differential(double a)
{
    double b;
    b = 4 * pow(a, 3) - 32 * a + 5;
    return b;
}
double norm(double a, double b)
{
    double c;
    a = differential(a);
    b = differential(b);
    c = a * a + b * b;
    return c;
}
