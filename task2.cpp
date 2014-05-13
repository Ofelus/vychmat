#include<iostream>
#include<cmath>

using namespace std;

//аналитическое решение
long double analit(double x, double t)
{
    return exp(x - 8 * t) + 0.5 * t * t;
}
//начальное условие
long double Uol(double x)
{
    return exp(x);
}

//граничное условие
long double Uno(double t)
{
    return exp(- 8 * t) + 0.5 * t * t;
}

int main()
{
    int L = 160, N = 20000;
    int step = (int)L / 10, i = 0;
    double U[10241] = {0}, U1[10241] = {0};
    double h = (double)1 / L, tau = (double)1 / N;
    int it, ix;
    double razn;

    cout<<"x"<<"         "<<"Analit"<<"          "<<"chisl"<<"           "<<"razn"<<endl;

    for(ix = 0; ix <= L; ix++)
    {
        U[ix] = Uol(ix * h);
    }

    for(it = 0; it <= N; it++)
    {
        U1[0] = Uno(it * tau);
        U1[1] = Uno(it * tau) + h * exp(-8 * it * tau) + 0.5 * h * h * exp(-8 * it * tau) + exp(-8 * it * tau) * h * h * h / 6;
        U1[2] = Uno(it * tau) + 2* h * exp(-8 * it * tau) + 2 * h * h * exp(-8 * it * tau) + exp(-8 * it * tau) * h * h * h * 4 / 3;

        for(ix = 3; ix <= L; ix++)
        {
            double x = ix * h;
            double t = it * tau;
            double t1 = (it - 1) * tau;

            U1[ix] = U[ix] + 4 * tau * (2 * U[ix - 3] - 9 * U[ix - 2] + 18 * U[ix - 1] - 11 * U[ix]) / (3 * h)
                    + 32 * tau * tau * (-U[ix - 3] + 4 * U[ix - 2] - 5 * U[ix - 1] + 2 * U[ix])/ (h * h)
                    - 256 * tau * tau * tau * (-U[ix-3] + 3 * U[ix - 2] - 3 * U[ix - 1] + U[ix])/ (3 * h * h * h)
                    + tau * t1 + 0.5 * tau * tau;

        }

        for(ix = 0; ix <= L; ix++)
            U[ix] = U1[ix];

    }

    for (ix = 0; ix <= L; ix++)
    {
        if(ix == step * i)
        {
            razn = abs(analit(ix * h, 1) - U[ix]);
            cout<<ix * h<<"         "<<analit(ix * h, 1)<<"          "<<U[ix]<<"           "<<razn<<endl;
            i++;
        }
    }


    return 0;
}
