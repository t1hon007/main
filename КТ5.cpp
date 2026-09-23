// КТ 5. Классы. Вариант 3
#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

// ================= a) множество для int =================
class IntSet
{
    int data[50];
    int n;

public:
    IntSet()
    {
        n = 0;
    }

    IntSet(int a[], int size)
    {
        n = 0;
        for (int i = 0; i < size; i++)
            add(a[i]);
    }

    bool has(int x) const
    {
        for (int i = 0; i < n; i++)
            if (data[i] == x)
                return true;
        return false;
    }

    void add(int x)
    {
        if (!has(x))
        {
            data[n] = x;
            n++;
        }
    }

    // удаление элемента
    IntSet operator-(int x)
    {
        IntSet res;
        for (int i = 0; i < n; i++)
            if (data[i] != x)
                res.add(data[i]);
        return res;
    }

    // B подмножество A
    bool operator>(IntSet b)
    {
        for (int i = 0; i < b.n; i++)
            if (!has(b.data[i]))
                return false;
        return true;
    }

    bool operator!=(IntSet b)
    {
        if (n != b.n)
            return true;
        for (int i = 0; i < n; i++)
            if (!b.has(data[i]))
                return true;
        return false;
    }

    void print()
    {
        cout << "{ ";
        for (int i = 0; i < n; i++)
            cout << data[i] << " ";
        cout << "}" << endl;
    }
};

// ================= b) иерархия "Файлы" =================
class File
{
protected:
    string name;
    int size;
    static int count;
    static int totalSize;

public:
    File(string nm, int sz)
    {
        name = nm;
        size = sz;
        count++;
        totalSize += sz;
    }

    virtual ~File()
    {
        count--;
        totalSize -= size;
    }

    virtual void info()
    {
        cout << "Файл " << name << ", " << size << " байт" << endl;
    }

    static void stats()
    {
        cout << "Файлов: " << count << ", общий размер: " << totalSize << " байт" << endl;
    }
};

int File::count = 0;
int File::totalSize = 0;

class TextFile : public File
{
    int lines;

public:
    TextFile(string nm, int sz, int l) : File(nm, sz)
    {
        lines = l;
    }

    void info()
    {
        cout << "Текстовый файл " << name << ", " << size << " байт, строк: " << lines << endl;
    }
};

class ImageFile : public File
{
    int w, h;

public:
    ImageFile(string nm, int sz, int width, int height) : File(nm, sz)
    {
        w = width;
        h = height;
    }

    void info()
    {
        cout << "Картинка " << name << ", " << size << " байт, " << w << "x" << h << endl;
    }
};

// ================= c) шаблонное множество =================
template <class T>
class Set
{
    T data[50];
    int n;

public:
    Set()
    {
        n = 0;
    }

    Set(T a[], int size)
    {
        n = 0;
        for (int i = 0; i < size; i++)
            add(a[i]);
    }

    bool has(T x) const
    {
        for (int i = 0; i < n; i++)
            if (data[i] == x)
                return true;
        return false;
    }

    void add(T x)
    {
        if (!has(x))
        {
            data[n] = x;
            n++;
        }
    }

    Set operator-(T x)
    {
        Set res;
        for (int i = 0; i < n; i++)
            if (!(data[i] == x))
                res.add(data[i]);
        return res;
    }

    bool operator>(Set b)
    {
        for (int i = 0; i < b.n; i++)
            if (!has(b.data[i]))
                return false;
        return true;
    }

    bool operator!=(Set b)
    {
        if (n != b.n)
            return true;
        for (int i = 0; i < n; i++)
            if (!b.has(data[i]))
                return true;
        return false;
    }

    void print()
    {
        cout << "{ ";
        for (int i = 0; i < n; i++)
            cout << data[i] << " ";
        cout << "}" << endl;
    }
};

// файл для шаблонного множества
struct FileRec
{
    string name;
    string type;
};

bool operator==(FileRec a, FileRec b)
{
    return a.name == b.name;
}

ostream& operator<<(ostream& out, FileRec f)
{
    out << f.name << "(" << f.type << ")";
    return out;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "--- a) ---" << endl;
    int a1[7] = { 1, 2, 3, 4, 5, 3, 2 };
    int a2[2] = { 2, 3 };
    int a3[2] = { 10, 20 };
    IntSet A(a1, 7), B(a2, 2), C(a3, 2);

    cout << "A = "; A.print();
    cout << "B = "; B.print();
    cout << "C = "; C.print();
    cout << "A - 3 = "; (A - 3).print();
    cout << "A > B: " << (A > B) << endl;
    cout << "A > C: " << (A > C) << endl;
    cout << "A != B: " << (A != B) << endl;
    cout << "B != B: " << (B != B) << endl;

    cout << "\n--- b) ---" << endl;
    File* files[4];
    files[0] = new TextFile("notes.txt", 2048, 57);
    files[1] = new ImageFile("photo.png", 5242880, 1920, 1080);
    files[2] = new TextFile("readme.md", 1024, 30);
    files[3] = new ImageFile("icon.png", 4096, 64, 64);

    for (int i = 0; i < 4; i++)
        files[i]->info();
    File::stats();

    for (int i = 0; i < 4; i++)
        delete files[i];
    File::stats();

    cout << "\n--- c) ---" << endl;
    double d1[4] = { 1.5, 2.25, 3.0, 2.25 };
    double d2[2] = { 2.25, 3.0 };
    Set<double> D1(d1, 4), D2(d2, 2);
    cout << "D1 = "; D1.print();
    cout << "D2 = "; D2.print();
    cout << "D1 - 2.25 = "; (D1 - 2.25).print();
    cout << "D1 > D2: " << (D1 > D2) << endl;
    cout << "D1 != D2: " << (D1 != D2) << endl;

    FileRec f1[3] = { {"a.txt", "текст"}, {"b.png", "картинка"}, {"c.txt", "текст"} };
    FileRec f2[1] = { {"b.png", "картинка"} };
    Set<FileRec> F1(f1, 3), F2(f2, 1);
    cout << "F1 = "; F1.print();
    cout << "F2 = "; F2.print();
    cout << "F1 - b.png = "; (F1 - f2[0]).print();
    cout << "F1 > F2: " << (F1 > F2) << endl;
    cout << "F1 != F2: " << (F1 != F2) << endl;

    return 0;
}
