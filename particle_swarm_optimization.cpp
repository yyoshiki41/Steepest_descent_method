#include <iostream>
#include <fstream>
#include <math.h>

#define N 2
#define I 5
#define K 1000

using namespace std;

double λ = 0.01;
double objective_f(double x1, double x2);

int main()
{
    ofstream fout;
    fout.open("pso.txt");
    fout << "#k\tx1_1\tx1_2\tx2_1\tx2_2\tx3_1\tx3_2\tx4_1\tx4_2\tx5_1\tx5_2\tx_gbest1\tx_gbest2" << endl; // 見出し

    // 初期点郡
    double x[I][N] = {
        {1, 1},
        {3, 3},
        {1, 4},
        {-3, 2},
        {1, -4}
    };
    double v[I][N] = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };
    double x_pbest[I][N] = {
        {1, 1},
        {3, 3},
        {1, 4},
        {-3, 2},
        {1, -4}
    };
    double x_gbest[N];
    double r1, r2;

    /* 動的にメモリ確保
    double ** x = new double*[I];
    for(int i = 0; i < I; i++) {
        x[i] = new double[N];
    }
    */

    for(int k = 1; k < K; k++) {
        fout << k << "\t";
        r1 = ((double)rand() / ((double)RAND_MAX + 1)) * 1.5;
        r2 = ((double)rand() / ((double)RAND_MAX + 1)) * 1.5;
        for (int i = 0; i < I; i++) {
            for (int n = 0; n < N; n++) {
                v[i][n] = λ * v[i][n] + r1 * (x_pbest[i][n] - x[i][n]) + r2 * (x_gbest[n] - x[i][n]);
            }
            for (int n = 0; n < N; n++) {
                x[i][n] = x[i][n] + v[i][n];
            }
            for (int n = 0; n < N; n++) {
                fout << x[i][n] << "\t";
            }
            double tmp_pbest = objective_f(x_pbest[i][0], x_pbest[i][1]);
            double tmp_x = objective_f(x[i][0], x[i][1]);
            if (tmp_pbest > tmp_x) {
                for (int n = 0; n < N; n++) {
                    x_pbest[i][n] = x[i][n];
                }
                double tmp_gbest = objective_f(x_gbest[0], x_gbest[1]);
                if (tmp_gbest > tmp_x) {
                    for (int n = 0; n < N; n++) {
                        x_gbest[n] = x[i][n];
                    }
                }
            }
        }
        fout << x_gbest[0] << "\t";
        fout << x_gbest[1] << endl;
    }
}

double objective_f (double x1, double x2)
{
    double f;
    f = pow(x1, 4) -16 * pow(x1, 2) + 5 * x1 + pow(x2, 4) -16 * pow(x2, 2) + 5 * x2;
    return f;
}
