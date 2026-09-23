// Практика 1. Лабы 2, 3, 4. Вариант 3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <limits.h>
#include <cmath>
#include <locale.h>
using namespace std;

// ---------- Лаба 2 ----------

void zad1()
{
    char c;
    printf("Input char (getchar) = ");
    c = getchar();
    c = toupper(c);
    putchar(c);
    printf("\n");
    while (getchar() != '\n');

    printf("Input char (_getch) = ");
    c = _getch();
    c = toupper(c);
    putchar(c);
    printf("\n");

    printf("Input char (_getche) = ");
    c = _getche();
    c = toupper(c);
    printf("\n");
    putchar(c);
    printf("\n");
}

void zad2()
{
    int x, y, z, u;
    printf("Введите 3 числа: ");
    scanf_s("%i%i%i", &x, &y, &z);
    printf("%5i %5i %5i\n", x, y, z);
    while (getchar() != '\n');

    printf("Введите 12 3456 7: ");
    scanf_s("%i%2i%i", &x, &y, &z);
    printf("x=%i y=%i z=%i\n", x, y, z);
    while (getchar() != '\n');

    printf("Введите 4 числа: ");
    scanf_s("%i%i%i%i", &x, &y, &z, &u);
    printf("%5i %5i %5i %5i\n", x, y, z, u);
    while (getchar() != '\n');
}

void zad3()
{
    int x = 12, y = 28, z = 86, u = 165;
    printf("%i %i %i %i\n", x, y, z, u);
    printf("%o %o %o %o\n", x, y, z, u);
    printf("%x %x %x %x\n", x, y, z, u);

    int i, j;
    printf("Введите 8-ричное и 16-ричное число: ");
    scanf_s("%o%x", &i, &j);
    printf("%5i %5i\n", i, j);
    while (getchar() != '\n');
}

void zad4()
{
    float a, b;
    printf("Введите a и b: ");
    scanf_s("%e%f", &a, &b);
    printf("%f %e\n", a, b);
    while (getchar() != '\n');

    double da, db;
    // без l будет неправильно
    printf("Введите 5.345 и 2.2e3: ");
    scanf_s("%e%f", (float*)&da, (float*)&db);
    printf("%f %e\n", da, db);
    while (getchar() != '\n');

    // с l правильно
    printf("Введите 5.345 и 2.2e3: ");
    scanf_s("%le%lf", &da, &db);
    printf("%f %e\n", da, db);
    while (getchar() != '\n');
}

void zad5()
{
    char c = 'A';
    int is = -125, iu = 125, ix = 428;
    float f = 1.234e34f;
    double d = 5.67e124;
    printf("Character %c\n", c);
    printf("Integer signed %d, unsigned %u\n", is, iu);
    printf("Octal %o, Hex %x\n", ix, ix);
    printf("Float %f %e\n", f, f);
    printf("Double %f %e\n", d, d);
    printf("%s\n", "Who early to rise, that God gives.");
    int m = 100;
    printf("m = %10d | %-10d |\n", m, m);
    printf("y = %+12.5f\n", 3.65e-3);
}

void zad6()
{
    char a = (char)135;
    int i = (int)3000000000LL;
    short s2 = SHRT_MIN, s3 = SHRT_MAX;
    unsigned int v = (unsigned int)(-45000);
    float pi = 3.141593f;
    float f = (float)3.4e39;
    double d = 1e-5;
    printf("a = %i\n", a);
    printf("i = %i\n", i);
    printf("s2 = %hi, s3 = %hi\n", s2, s3);
    printf("v = %u\n", v);
    printf("pi = %.7f\n", pi);
    printf("f = %f\n", f);
    printf("d = %.10f\n", d);
}

void zad7()
{
    const int ci = -5;
    const char cc = 'A';
    const float cf = 1.234567f;
    const double cd = -1.2321e-17;
    const double e = 2.71828182845905;
    printf("ci = %i\n", ci);
    printf("cc = %c\n", cc);
    printf("cf = %f\n", cf);
    printf("cd = %e\n", cd);
    printf("e = %.14f\n", e);
}

void lab2()
{
    int n;
    do
    {
        printf("\nЛаба 2. Номер задания (1-7), 0 - назад: ");
        scanf_s("%i", &n);
        while (getchar() != '\n');
        if (n == 1) zad1();
        else if (n == 2) zad2();
        else if (n == 3) zad3();
        else if (n == 4) zad4();
        else if (n == 5) zad5();
        else if (n == 6) zad6();
        else if (n == 7) zad7();
        else if (n != 0) printf("Нет такого задания\n");
    } while (n != 0);
}

// ---------- Лаба 3 ----------

void lab3()
{
    // задание 1: снизу парабола y=2x^2, сверху окружность (x-1)^2+y^2=4
    double x, y;
    cout << "Введите x и y: ";
    cin >> x >> y;
    if (y >= 2 * x * x && (x - 1) * (x - 1) + y * y <= 4)
        cout << "Точка попадает в область" << endl;
    else
        cout << "Точка не попадает в область" << endl;

    // задание 2: победитель конкурса
    double m1, n1, p1, m2, n2, p2, m3, n3, p3;
    cout << "Баллы Иванова: ";
    cin >> m1 >> n1 >> p1;
    cout << "Баллы Петрова: ";
    cin >> m2 >> n2 >> p2;
    cout << "Баллы Сидорова: ";
    cin >> m3 >> n3 >> p3;

    double s1 = m1 + n1 + p1;
    double s2 = m2 + n2 + p2;
    double s3 = m3 + n3 + p3;

    if (s1 >= s2 && s1 >= s3)
        cout << "Победил Иванов" << endl;
    else if (s2 >= s1 && s2 >= s3)
        cout << "Победил Петров" << endl;
    else
        cout << "Победил Сидоров" << endl;
}

// ---------- Лаба 4 ----------

void lab4()
{
    // а) сумма ряда
    double s = 0;
    for (int n = 1; n <= 15; n++)
        s = s + 1 - 1 / pow(-2, n);
    cout << "a) S = " << s << endl;

    // б) максимум u
    double max = 0;
    int imax = 0;
    for (int i = 1; i <= 25; i++)
    {
        double u = i * i * exp(-0.2 * i);
        if (u > max)
        {
            max = u;
            imax = i;
        }
    }
    cout << "b) max = " << max << ", i = " << imax << endl;

    // в) сумма ряда с точностью 0.000001
    double x = 2, sum = 0, fact = 1, t = x;
    int k = 0;
    while (fabs(t) >= 0.000001)
    {
        sum = sum + t;
        k++;
        fact = fact * k;
        t = pow(-1, k) * pow(x, 2 * k + 1) / (fact * (2 * k + 1));
    }
    cout << "c) S = " << sum << endl;

    // г) последовательность A
    double a0 = 1, a1 = 0.3, a2;
    int n = 1;
    do
    {
        a2 = cos(a1) / n + a0;
        a0 = a1;
        a1 = a2;
        n++;
    } while (a1 > -0.5);
    cout << "d) n = " << n << ", A = " << a1 << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");

    int k;
    do
    {
        printf("\n1 - Лаба 2, 2 - Лаба 3, 3 - Лаба 4, 0 - выход: ");
        scanf_s("%i", &k);
        while (getchar() != '\n');
        if (k == 1) lab2();
        else if (k == 2) lab3();
        else if (k == 3) lab4();
        else if (k != 0) printf("Нет такого пункта\n");
    } while (k != 0);

    return 0;
}
