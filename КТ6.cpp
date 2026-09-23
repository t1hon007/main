// Практика 6. STL, Eigen, OpenCV
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <chrono>
#include <cmath>
#include <locale.h>
#include <Eigen/Dense>
using namespace std;

// ================= Задание 1. STL =================

vector<int> sortVector(vector<int> v)
{
    sort(v.begin(), v.end());
    return v;
}

vector<int> reverseVector(vector<int> v)
{
    reverse(v.begin(), v.end());
    return v;
}

int sumVector(vector<int> arr, int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += arr[i];
    return s;
}

int findFrequency(vector<int> arr, int x)
{
    int k = 0;
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == x)
            k++;
    return k;
}

void printVector(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

// перевод в римские числа
string toRoman(int n)
{
    int nums[13] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    string rim[13] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    string res = "";
    for (int i = 0; i < 13; i++)
    {
        while (n >= nums[i])
        {
            res += rim[i];
            n -= nums[i];
        }
    }
    return res;
}

// проверка ISBN-10 (код из задания)
bool validate_isbn_10(string_view isbn)
{
    auto valid = false;
    if (isbn.size() == 10 && count_if(begin(isbn), end(isbn), ::isdigit) == 10) {
        auto w = 10;
        auto sum = accumulate(
            begin(isbn),
            end(isbn), 0,
            [&w](int const total, char const c) {
                return total + w-- * (c - '0');
            });
        valid = !(sum % 11);
    }
    return valid;
}

// улучшение: убираем дефисы
bool validate_isbn_dash(string s)
{
    string t = "";
    for (int i = 0; i < s.length(); i++)
        if (s[i] != '-')
            t += s[i];
    return validate_isbn_10(t);
}

// ================= Задание 2. Eigen =================

void task1()
{
    cout << "\n--- Умножение матриц 500x500 ---" << endl;
    int n = 500;

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> B(n, vector<double>(n));
    vector<vector<double>> C(n, vector<double>(n));
    Eigen::MatrixXd Ae(n, n), Be(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            A[i][j] = (double)(i + j) / n;
            B[i][j] = (double)(i - j) / (n + 1);
            Ae(i, j) = A[i][j];
            Be(i, j) = B[i][j];
        }

    // обычное умножение
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    auto t2 = chrono::high_resolution_clock::now();

    // через Eigen
    Eigen::MatrixXd Ce = Ae * Be;
    auto t3 = chrono::high_resolution_clock::now();

    double time1 = chrono::duration<double>(t2 - t1).count();
    double time2 = chrono::duration<double>(t3 - t2).count();

    cout << "Обычное: " << time1 << " с" << endl;
    cout << "Eigen: " << time2 << " с" << endl;
    cout << "Eigen быстрее в " << time1 / time2 << " раз" << endl;
    cout << "Проверка: " << C[10][10] << " и " << Ce(10, 10) << endl;
    cout << "Память на 3 матрицы: " << 3 * n * n * sizeof(double) / 1024 << " КБ" << endl;
}

void task3()
{
    cout << "\n--- Скалярное произведение и норма ---" << endl;
    int n = 1000;
    vector<double> x(n), y(n);
    Eigen::VectorXd xe(n), ye(n);
    for (int i = 0; i < n; i++)
    {
        x[i] = sin(0.001 * i);
        y[i] = cos(0.001 * i);
        xe(i) = x[i];
        ye(i) = y[i];
    }

    double dot = 0, norm = 0;
    for (int i = 0; i < n; i++)
    {
        dot += x[i] * y[i];
        norm += x[i] * x[i];
    }
    norm = sqrt(norm);

    cout << "Скалярное произведение: " << dot << ", Eigen: " << xe.dot(ye) << endl;
    cout << "Норма: " << norm << ", Eigen: " << xe.norm() << endl;
}

// ================= Задание 3. OpenCV =================
// без установленного OpenCV не собирается, поэтому через #ifdef
#ifdef WITH_OPENCV
#include <opencv2/opencv.hpp>

void opencvTask()
{
    cv::Mat img = cv::imread("test.jpg");
    if (img.empty())
    {
        cout << "Не удалось открыть test.jpg" << endl;
        return;
    }

    cv::Mat gray, blur;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blur, cv::Size(5, 5), 0);
    cv::imwrite("result.jpg", blur);

    cv::imshow("Исходное", img);
    cv::imshow("Результат", blur);
    cv::waitKey(0);
}
#endif

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "--- STL ---" << endl;
    vector<int> v = { 5, 2, 9, 1, 5, 6, 5, 3 };
    cout << "Вектор: ";
    printVector(v);
    cout << "Сортировка: ";
    printVector(sortVector(v));
    cout << "Наоборот: ";
    printVector(reverseVector(v));
    cout << "Сумма: " << sumVector(v, v.size()) << endl;
    cout << "Сколько раз 5: " << findFrequency(v, 5) << endl;

    cout << "42 = " << toRoman(42) << endl;
    cout << "1994 = " << toRoman(1994) << endl;
    cout << "3999 = " << toRoman(3999) << endl;

    cout << "0306406152: " << validate_isbn_10("0306406152") << endl;
    cout << "0306406153: " << validate_isbn_10("0306406153") << endl;
    cout << "0-306-40615-2: " << validate_isbn_dash("0-306-40615-2") << endl;

    task1();
    task3();

#ifdef WITH_OPENCV
    opencvTask();
#endif

    return 0;
}
