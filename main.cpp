#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Перечисление операций
enum Operations {
    VV_SUM,
    VV_SUB,
    VV_SCALAR
};

// Структура для хранения параметров задачи
struct CalcProblemParams {
    vector<double> v1;
    vector<double> v2;
    Operations operation;
};

// Функция для чтения вектора из файла
vector<double> ReadVectorFromFile(const string& filename) {
    vector<double> vec;
    ifstream file(filename);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return vec;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        double num;
        while (ss >> num) {
            vec.push_back(num);
        }
    }
    file.close();
    return vec;
}

// Функция для инициализации данных
CalcProblemParams Init(const string& file1, const string& file2, Operations operation) {
    CalcProblemParams params;
    params.v1 = ReadVectorFromFile(file1);
    params.v2 = ReadVectorFromFile(file2);
    params.operation = operation;

    // Проверка: оба вектора должны быть одной длины
    if (params.v1.size() != params.v2.size()) {
        cerr << "Ошибка: Векторы имеют разную длину!" << endl;
    }

    return params;
}

// Функция для расчета
vector<double> Calc(const CalcProblemParams& params) {
    vector<double> result;

    if (params.v1.size() != params.v2.size()) {
        return result; // возвращаем пустой результат, если векторы разной длины
    }

    switch (params.operation) {
        case VV_SUM:
            for (size_t i = 0; i < params.v1.size(); ++i) {
                result.push_back(params.v1[i] + params.v2[i]);
            }
            break;
        case VV_SUB:
            for (size_t i = 0; i < params.v1.size(); ++i) {
                result.push_back(params.v1[i] - params.v2[i]);
            }
            break;
        case VV_SCALAR:
            double scalar_result = 0;
            for (size_t i = 0; i < params.v1.size(); ++i) {
                scalar_result += params.v1[i] * params.v2[i];
            }
            result.push_back(scalar_result);
            break;
    }

    return result;
}

// Функция для записи результата в файл
void Export(const vector<double>& result, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    for (double val : result) {
        outFile << val << " ";
    }

    outFile.close();
    cout << "Результат записан в файл: " << filename << endl;
}

int main()
{
    // Имена файлов
    string file1 = "vec1.txt";
    string file2 = "vec2.txt";
    string output_file = "result.txt"; // Файл для записи результата

    // Инициализация с выбором операции (например, сложение векторов)
    CalcProblemParams params = Init(file1, file2, VV_SUM);

    // Расчет
    vector<double> result = Calc(params);

    // Запись результата в файл
    Export(result, output_file);

    return 0;
}