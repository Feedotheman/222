#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

const int mf = 500;

int main() {
    int i, j, N;
    vector<double> T(mf), alfa(mf), beta(mf);
    double ai, bi, ci, fi;
    double lamda, ro, c, h, tau;
    double Tl, T0, Tr, L, t_end, time;
    
    // Ввод параметров
    cout << "Enter a number of area nods, N: ";
    cin >> N;
    cout << "Enter a time of end, t_end: ";
    cin >> t_end;
    cout << "Enter a width of plate, L: ";
    cin >> L;
    cout << "Enter a coefficient of termal conductivity of plate's material, lamda: ";
    cin >> lamda;
    cout << "Enter density of plate's material, ro: ";
    cin >> ro;
    cout << "Enter heat capacity of plate's material, c: ";
    cin >> c;
    cout << "Enter start temperature, T0: ";
    cin >> T0;
    cout << "Enter temperature on border x=0, Tl: ";
    cin >> Tl;
    cout << "Enter temperature on border x=L, Tr: ";
    cin >> Tr;

    // Расчетный шаг по пространственной координате
    h = L / (N - 1);
    // Расчетный шаг по времени
    tau = t_end / 100.0;

    // Начальные значения температуры
    for (i = 1; i <= N; i++) {
        T[i] = T0;
    }

    // Интегрирование нестационарного уравнения теплопроводности
    time = 0;
    
    while (time < t_end) {
        time += tau;

        // Начальные прогоночные коэффициенты
        alfa[1] = 0.0;
        beta[1] = Tl;

        // Вычисление прогоночных коэффициентов
        for (i = 2; i < N; i++) {
            ai = lamda / (h * h);
            bi = 2.0 * lamda / (h * h) + ro * c / tau;
            ci = lamda / (h * h);
            fi = -ro * c * T[i] / tau;

            alfa[i] = ai / (bi - ci * alfa[i - 1]);
            beta[i] = (ci * beta[i - 1] - fi) / (bi - ci * alfa[i - 1]);
        }

        // Температура на правой границе
        T[N] = Tr;

        // Определение температуры
        for (i = N - 1; i >= 1; i--) {
            T[i] = alfa[i] * T[i + 1] + beta[i];
        }
    }

    // Запись результатов в файл
    ofstream f("res.txt");
    f << fixed << setprecision(4);
    f << "Толщина пластины L = " << L << endl;
    f << "Число узлов по координате N = " << N << endl;
    f << "Коэффициент теплопроводности материала пластины lamda = " << lamda << endl;
    f << "Плотность материала пластины ro = " << ro << endl;
    f << "Теплоемкость материала пластины c = " << c << endl;
    f << "Начальная температура T0 = " << T0 << endl;
    f << "Температура на границе x = 0, Tl = " << Tl << endl;
    f << "Температура на границе x = L, Tr = " << Tr << endl;
    f << "Результат получен с шагом по координате h = " << h << endl;
    f << "Результат получен с шагом по времени tau = " << tau << endl;
    f << "Температурное поле в момент времени t = " << t_end << endl;
    f.close();

    ofstream g("tempr.txt");
    g << fixed << setprecision(3);
    for (i = 1; i <= N; i++) {
        g << " " << h * (i - 1) << " " << setw(8) << setprecision(5) << T[i] << endl;
    }
    g.close();

    return 0;
}
