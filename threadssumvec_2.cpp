#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
using namespace std;

mutex mtx;  // Мьютекс для защиты общей переменной

// Кусочное суммирование
void sum_part(int start, int end, double& sum, vector<double>& vec1) {
    double local_sum = 0.0;
    for (int i = start; i < end; ++i) {
        local_sum += vec1[i];
    }

    lock_guard<mutex> lock(mtx);
    sum += local_sum;
}

int main() {
    double sum = 0.0;
    int SIZE = 10000000;
    vector<double> vec1(SIZE, 0.1);

    int num_threads;
    cout << "Enter the number of threads: between 2 and 8: ";
    cin >> num_threads;

    if (num_threads <= 1 || num_threads > 8) {
        cerr << "Number of threads must be between 2 and 8" << endl;
        return 1;
    }

    vector<thread> threads;
    int part_size = vec1.size() / num_threads;  // Размер части для каждого потока

    // Создание потоков
    for (int i = 0; i < num_threads; ++i) {
        int start = i * part_size;
        int end = (i == num_threads - 1) ? vec1.size() : start + part_size; // Последний поток до конца вектора
        threads.emplace_back(sum_part, start, end, ref(sum), ref(vec1));  // Передача параметров в поток
    }

    // Ожидание завершения потоков
    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Sum of elements: " << sum << endl; // Вывод результата
    return 0;
}