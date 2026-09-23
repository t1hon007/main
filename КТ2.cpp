// Практика 2. Массивы и строки. Вариант 3
#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // ---------- Задача на массивы ----------
    int n;
    int r[100];
    cout << "Количество студентов: ";
    cin >> n;
    cout << "Введите рейтинги (0-100): ";
    for (int i = 0; i < n; i++)
        cin >> r[i];

    int seg[10] = { 0 };
    for (int i = 0; i < n; i++)
    {
        int k = r[i] / 10;
        if (k == 10) // 100 баллов в последний сегмент
            k = 9;
        seg[k]++;
    }

    cout << "\nСегменты:\n";
    for (int i = 0; i < 10; i++)
    {
        int end = i * 10 + 9;
        if (i == 9)
            end = 100;
        cout << i * 10 << "-" << end << ": " << seg[i] << " чел. ("
             << seg[i] * 100.0 / n << "%)\n";
    }

    int otl = 0, hor = 0, ud = 0, neud = 0;
    for (int i = 0; i < n; i++)
    {
        if (r[i] >= 85) otl++;
        else if (r[i] >= 75) hor++;
        else if (r[i] >= 60) ud++;
        else neud++;
    }
    cout << "\nОтлично: " << otl << endl;
    cout << "Хорошо: " << hor << endl;
    cout << "Удовлетворительно: " << ud << endl;
    cout << "Неудовлетворительно: " << neud << endl;

    // ---------- Задача на строки ----------
    // поменять местами самое длинное и самое короткое слово
    cin.ignore();
    string s;
    cout << "\nВведите строку: ";
    getline(cin, s);

    string words[100];
    int cnt = 0;
    string w = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
            w += s[i];
        else if (w != "")
        {
            words[cnt] = w;
            cnt++;
            w = "";
        }
    }
    if (w != "")
    {
        words[cnt] = w;
        cnt++;
    }

    int imax = 0, imin = 0;
    for (int i = 1; i < cnt; i++)
    {
        if (words[i].length() > words[imax].length()) imax = i;
        if (words[i].length() < words[imin].length()) imin = i;
    }

    cout << "Самое длинное: " << words[imax] << endl;
    cout << "Самое короткое: " << words[imin] << endl;

    string t = words[imax];
    words[imax] = words[imin];
    words[imin] = t;

    string res = "";
    for (int i = 0; i < cnt; i++)
    {
        res += words[i];
        if (i < cnt - 1)
            res += " ";
    }
    cout << "Результат: " << res << endl;

    return 0;
}
