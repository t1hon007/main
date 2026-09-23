// Практика 3. Функции и рекурсия
#include <iostream>
#include <cmath>
#include <locale.h>
using namespace std;

// ================= Занятие 7. Функции =================

// 1. обмен без третьей переменной
void swap2(int* x, int* y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

// 2. вывод значения функции через указатель на функцию
void print(float x, float (*f)(float))
{
    cout << "f(" << x << ") = " << f(x) << endl;
}

float f1(float x)
{
    return x * x;
}

float f2(float x)
{
    return x * x * x - 1;
}

// 3. перегрузка max и min
float max(float a[], int n)
{
    float m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m) m = a[i];
    return m;
}

float min(float a[], int n)
{
    float m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < m) m = a[i];
    return m;
}

double max(double a[], int n)
{
    double m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m) m = a[i];
    return m;
}

double min(double a[], int n)
{
    double m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < m) m = a[i];
    return m;
}

// 4*. ряд e^x тремя способами
// по значению
double sum1(double x, double eps)
{
    double t = 1, s = 1;
    int n = 1;
    while (fabs(t) >= eps)
    {
        t = t * x / n;
        s = s + t;
        n++;
    }
    return s;
}

// через указатели
void sum2(double* x, double* eps, double* s)
{
    double t = 1;
    *s = 1;
    int n = 1;
    while (fabs(t) >= *eps)
    {
        t = t * *x / n;
        *s = *s + t;
        n++;
    }
}

// по ссылке, возвращает ссылку
double& sum3(double& x, double& eps, double& s)
{
    double t = 1;
    s = 1;
    int n = 1;
    while (fabs(t) >= eps)
    {
        t = t * x / n;
        s = s + t;
        n++;
    }
    return s;
}

// ================= Занятие 8. Рекурсия =================

// 1. корень методом Ньютона
double koren(double a, int n)
{
    if (n == 0)
        return (1 + a) / 2;
    double x = koren(a, n - 1);
    return 0.5 * (x + a / x);
}

// 2. произведение 2/1 * 2/3 * 4/3 * 4/5 * ...
double proizv(int n)
{
    if (n == 0)
        return 1;
    double m;
    if (n % 2 == 1)
        m = (double)(n + 1) / n;
    else
        m = (double)n / (n + 1);
    return m * proizv(n - 1);
}

// 3. массив в обратном порядке
void obratno(int a[], int i)
{
    if (i < 0)
        return;
    cout << a[i] << " ";
    obratno(a, i - 1);
}

// 4. степень двойки
bool stepen2(int n)
{
    if (n == 1)
        return true;
    if (n < 1 || n % 2 != 0)
        return false;
    return stepen2(n / 2);
}

// 5. функция Аккермана
int akkerman(int m, int n)
{
    if (m == 0)
        return n + 1;
    if (n == 0)
        return akkerman(m - 1, 1);
    return akkerman(m - 1, akkerman(m, n - 1));
}

// 6. x в степени a
double step(double x, int a)
{
    if (a == 0)
        return 1;
    if (a % 2 == 0)
    {
        double y = step(x, a / 2);
        return y * y;
    }
    return x * step(x, a - 1);
}

// 7. сумма цифр
int sumcifr(int n)
{
    if (n < 10)
        return n;
    return n % 10 + sumcifr(n / 10);
}

// 8*. сколько элементов равны максимуму
int mx = 0, kol = 0;

void maximum()
{
    int x;
    cin >> x;
    if (x == 0)
        return;
    if (x > mx)
    {
        mx = x;
        kol = 1;
    }
    else if (x == mx)
        kol++;
    maximum();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "--- Занятие 7 ---" << endl;

    int a = 5, b = 12;
    cout << "a=" << a << " b=" << b << endl;
    swap2(&a, &b);
    cout << "a=" << a << " b=" << b << endl;

    print(3, f1);
    print(2, f2);

    float m1[4] = { 3.5, -2.1, 8, 4.4 };
    float m2[5] = { 1, 2, -6, 9, 0.5 };
    float min1 = min(m1, 4), max1 = max(m1, 4);
    float min2 = min(m2, 5), max2 = max(m2, 5);
    cout << "Массив 1: min=" << min1 << " max=" << max1 << endl;
    cout << "Массив 2: min=" << min2 << " max=" << max2 << endl;
    cout << "Произведение минимумов: " << min1 * min2 << endl;
    cout << "Среднее геометрическое максимумов: " << sqrt(max1 * max2) << endl;

    double x = 0.2, eps = 0.00005, s;
    cout << "1) " << sum1(x, eps) << endl;
    sum2(&x, &eps, &s);
    cout << "2) " << s << endl;
    cout << "3) " << sum3(x, eps, s) << endl;
    cout << "exp(0.2) = " << exp(0.2) << endl;

    cout << "\n--- Занятие 8 ---" << endl;

    cout << "sqrt(2) = " << sqrt(2.0) << ", Ньютон: " << koren(2, 6) << endl;

    cout << "Произведение (n=20): " << proizv(20) << endl;

    int arr[5] = { 10, 20, 30, 40, 50 };
    cout << "Массив наоборот: ";
    obratno(arr, 4);
    cout << endl;

    int n;
    cout << "Введите N: ";
    cin >> n;
    if (stepen2(n))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    cout << "A(2,3) = " << akkerman(2, 3) << endl;

    cout << "2^10 = " << step(2, 10) << endl;
    cout << "3^7 = " << step(3, 7) << endl;

    cout << "Введите число: ";
    cin >> n;
    cout << "Сумма цифр: " << sumcifr(n) << endl;

    cout << "Введите числа (0 - конец): ";
    maximum();
    cout << "Максимум " << mx << " встречается " << kol << " раз" << endl;

    return 0;
}
