// КТ 4. Структуры и файлы. Вариант 3 - музыкальные альбомы
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <locale.h>
using namespace std;

const int N = 20;

enum Genre { ROCK, INDIE, POP, JAZZ, BLUES, ELECTRO, HIPHOP, CLASSIC, METAL, FUNK };

const char* genreNames[] = { "рок", "инди-рок", "поп", "джаз", "блюз",
                             "электроника", "хип-хоп", "классика", "метал", "фанк" };

struct Time
{
    int min;
    int sec;
};

// строки через char[], чтобы можно было записать в бинарный файл
struct Album
{
    char title[64];
    char artist[48];
    Genre genre;
    int year;
    Time time;
    double price;
    int rating;
    int tracks;
};

void printAlbum(Album a)
{
    cout << a.title << " - " << a.artist << " (" << a.year << "), "
         << genreNames[a.genre] << ", " << a.time.min << ":" << a.time.sec
         << ", цена " << a.price << ", рейтинг " << a.rating
         << ", треков " << a.tracks << endl;
}

void printAll(Album a[], int n)
{
    for (int i = 0; i < n; i++)
        printAlbum(a[i]);
}

int find(Album a[], int n, const char* title)
{
    for (int i = 0; i < n; i++)
        if (strcmp(a[i].title, title) == 0)
            return i;
    return -1;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Album albums[N] = {
        { "The Wall", "Pink Floyd", ROCK, 1979, {81, 10}, 15.99, 98, 5 },
        { "Turn on the Bright Lights", "Interpol", INDIE, 2002, {49, 0}, 12.50, 70, 8 },
        { "1989", "Taylor Swift", POP, 2014, {48, 41}, 13.99, 95, 3 },
        { "Kind of Blue", "Miles Davis", JAZZ, 1959, {45, 44}, 11.20, 90, 5 },
        { "Abbey Road", "The Beatles", ROCK, 1969, {47, 23}, 14.30, 99, 9 },
        { "Discovery", "Daft Punk", ELECTRO, 2001, {61, 21}, 12.00, 88, 4 },
        { "The Chronic", "Dr. Dre", HIPHOP, 1992, {60, 0}, 10.50, 80, 3 },
        { "The Four Seasons", "Antonio Vivaldi", CLASSIC, 1725, {42, 0}, 9.99, 60, 4 },
        { "Master of Puppets", "Metallica", METAL, 1986, {54, 46}, 13.00, 97, 8 },
        { "Uptown Funk", "Mark Ronson", FUNK, 2015, {35, 10}, 8.99, 75, 3 },
        { "Funeral", "Arcade Fire", INDIE, 2004, {46, 57}, 12.75, 92, 5 },
        { "The Sky Is Crying", "Stevie Ray Vaughan", BLUES, 1991, {49, 12}, 10.00, 55, 3 },
        { "Back in Black", "AC/DC", ROCK, 1980, {42, 11}, 13.50, 96, 4 },
        { "Thriller", "Michael Jackson", POP, 1982, {42, 19}, 14.99, 100, 5 },
        { "In Rainbows", "Radiohead", INDIE, 2007, {42, 39}, 11.99, 94, 10 },
        { "Random Access Memories", "Daft Punk", ELECTRO, 2013, {74, 15}, 13.20, 91, 4 },
        { "good kid, m.A.A.d city", "Kendrick Lamar", HIPHOP, 2012, {68, 26}, 12.30, 93, 4 },
        { "Nevermind", "Nirvana", ROCK, 1991, {49, 8}, 12.99, 97, 4 },
        { "Symphony No. 5", "Beethoven", CLASSIC, 1808, {30, 0}, 8.50, 85, 4 },
        { "AM", "Arctic Monkeys", INDIE, 2013, {42, 8}, 11.50, 89, 4 }
    };

    cout << "Все альбомы:" << endl;
    printAll(albums, N);

    // рок и инди-рок, сортировка по исполнителю
    Album rock[N];
    int k = 0;
    for (int i = 0; i < N; i++)
        if (albums[i].genre == ROCK || albums[i].genre == INDIE)
        {
            rock[k] = albums[i];
            k++;
        }

    for (int i = 0; i < k - 1; i++)
        for (int j = 0; j < k - 1 - i; j++)
            if (strcmp(rock[j].artist, rock[j + 1].artist) > 0)
            {
                Album t = rock[j];
                rock[j] = rock[j + 1];
                rock[j + 1] = t;
            }

    cout << "\nРок и инди-рок по исполнителю:" << endl;
    printAll(rock, k);

    // поиск по названию
    char name[64];
    cout << "\nВведите название альбома: ";
    cin.getline(name, 64);
    int idx = find(albums, N, name);
    if (idx == -1)
        cout << "Не найден" << endl;
    else
        printAlbum(albums[idx]);

    // топ-5 по рейтингу
    Album top[N];
    for (int i = 0; i < N; i++)
        top[i] = albums[i];
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - 1 - i; j++)
            if (top[j].rating < top[j + 1].rating)
            {
                Album t = top[j];
                top[j] = top[j + 1];
                top[j + 1] = t;
            }
    cout << "\nТоп-5:" << endl;
    for (int i = 0; i < 5; i++)
        cout << i + 1 << ". " << top[i].title << " - " << top[i].rating << endl;

    // изменение цены
    idx = find(albums, N, "1989");
    cout << "\nЦена 1989 была " << albums[idx].price;
    albums[idx].price = 9.99;
    cout << ", стала " << albums[idx].price << endl;

    // больше 7 треков
    Album big[N];
    int kb = 0;
    for (int i = 0; i < N; i++)
        if (albums[i].tracks > 7)
        {
            big[kb] = albums[i];
            kb++;
        }
    cout << "\nАльбомы, где больше 7 треков:" << endl;
    printAll(big, kb);

    // ---------- Занятие 10 ----------

    // запись в бинарный файл
    ofstream fout("albums.bin", ios::binary);
    fout.write((char*)albums, sizeof(albums));
    fout.close();

    // чтение из бинарного файла
    Album loaded[N];
    ifstream fin("albums.bin", ios::binary);
    fin.read((char*)loaded, sizeof(loaded));
    fin.close();
    cout << "\nПрочитали из файла, первый альбом: ";
    printAlbum(loaded[0]);

    // обновление рейтинга из текстового файла
    // формат строки: Название|рейтинг
    ofstream f("rating.txt");
    f << "The Wall|75" << endl;
    f << "Nevermind|100" << endl;
    f.close();

    ifstream ft("rating.txt");
    string title;
    int r;
    while (getline(ft, title, '|'))
    {
        ft >> r;
        ft.ignore();
        int i = find(loaded, N, title.c_str());
        if (i != -1)
            loaded[i].rating = r;
    }
    ft.close();

    cout << "\nПосле обновления из rating.txt:" << endl;
    printAlbum(loaded[find(loaded, N, "The Wall")]);
    printAlbum(loaded[find(loaded, N, "Nevermind")]);

    return 0;
}
