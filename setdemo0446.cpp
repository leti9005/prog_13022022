#include <clocale>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;
struct EL
{
    char d;
    EL* next;
    explicit EL(char d, EL* next = nullptr) : d(d), next(next) {}
    ~EL() { delete next; }
};
const int U = 26; //Мощность универсума
bool array_contains(const char arr[], int arr_len, char c)
{
    for (int i = 0; i < arr_len; i++)
    {
        if (arr[i] == c) return true;
    }
    return false;
}
bool list_contains(EL* list, char c)
{
    for (auto u = list; u; u = u->next)
    {
        if (u->d == c) return true;
    }
    return false;
}
int main()
{
    unsigned int nA, nB, nC, nD, nE, //Мощности множеств
        wA, wB, wC, wD, wE, //Память для машинных слов
        bA[U] = {0},        //Пустые массивы битов
        bB[U] = {0}, bC[U] = {0}, bD[U] = {0},
        bE[U]; //Память для результата
    EL *La = nullptr, *Lb = nullptr, *Lc = nullptr, *Ld = nullptr,
       *Le = nullptr; //Указатели на списки
    char A[2 * U], B[2 * U], C[2 * U],
        D[2 * U], //Исходные множества (память с запасом на ввод)
        E[U + 1]; //Память под результат - массив (1 байт - запасной)
    srand(time(nullptr));
    wA = rand();
    wB = rand();
    wC = rand();
    wD = rand();

    //Преобразование в массивы (строки символов)...
    nA = 0;
    for (int i = 0; i < U; ++i)
        if (wA & (1 << i))
            A[nA++] = i + 'A';
    A[nA] = '\0';
    nB = 0;
    for (int i = 0; i < U; ++i)
        if (wB & (1 << i))
            B[nB++] = i + 'A';
    B[nB] = '\0';
    nC = 0;
    for (int i = 0; i < U; ++i)
        if (wC & (1 << i))
            C[nC++] = i + 'A';
    C[nC] = '\0';
    nD = 0;
    for (int i = 0; i < U; ++i)
        if (wD & (1 << i))
            D[nD++] = i + 'A';
    D[nD] = '\0';

    //Преобразование строки символов в список
    La = nullptr;
    for (int i = 0; A[i]; ++i)
        La = new EL(A[i], La);
    Lb = nullptr;
    for (int i = 0; B[i]; ++i)
        Lb = new EL(B[i], Lb);
    Lc = nullptr;
    for (int i = 0; C[i]; ++i)
        Lc = new EL(C[i], Lc);
    Ld = nullptr;
    for (int i = 0; D[i]; ++i)
        Ld = new EL(D[i], Ld);
    //Преобразование строк символов в массивы битов и машинные слова
    wA = 0;
    for (int i = 0; A[i]; ++i)
    {
        bA[A[i] - 'A'] = 1;
        wA |= (1 << (A[i] - 'A'));
    }
    wB = 0;
    for (int i = 0; B[i]; ++i)
    {
        bB[B[i] - 'A'] = 1;
        wB |= (1 << (B[i] - 'A'));
    }
    wC = 0;
    for (int i = 0; C[i]; ++i)
    {
        bC[C[i] - 'A'] = 1;
        wC |= (1 << (C[i] - 'A'));
    }
    wD = 0;
    for (int i = 0; D[i]; ++i)
    {
        bD[D[i] - 'A'] = 1;
        wD |= (1 << (D[i] - 'A'));
    }

    //Операция над массивами: пересечение
    const long RepeatA = 1000000;
    clock_t ta_start = clock();
    for (int cnt = 0; cnt < RepeatA; ++cnt)
    {
        nE = 0;
        for (int x = 0; x < nA; x++)
        {
            if (!(array_contains(B, nB, A[x]) && array_contains(C, nC, A[x])))
            {
                E[nE] = A[x];
                nE++;
            }
        }
        for (int x = 0; x < nD; x++)
        {
            E[nE] = D[x];
            nE++;
        }
        E[nE] = 0;
    }
    clock_t ta_end = clock();

    //Операция над списками: пересечение
    const long RepeatB = 1000000;
    clock_t tb_start = clock();
    for (int cnt = 0; cnt < RepeatB; ++cnt)
    {
        delete Le;
        Le = nullptr;
        for (EL* u = La; u; u = u->next)
        {
            if (!(list_contains(Lb, u->d) && list_contains(Lc, u->d)))
            {
                Le = new EL(u->d, Le);
            }
        }
        for (auto u = Ld; u; u = u->next)
        {
            Le = new EL(u->d, Le);
        }
    }
    clock_t tb_end = clock();

    //Операция над массивами битов: пересечение
    const long RepeatC = 100000000;
    clock_t tc_start = clock();
    for (int cnt = 0; cnt < RepeatC; ++cnt)
    {
        for (int i = 0; i < U; ++i)
            bE[i] = (bA[i] && !(bB[i] && bC[i])) || bD[i];
    }
    clock_t tc_end = clock();

    //Операция над машинными словами: пересечение
    const long RepeatD = 100000000;
    clock_t td_start = clock();
    for (long cnt = 0; cnt < RepeatD; ++cnt)
    {
        wE = wA & ~(wB & wC) | wD;
    }
    clock_t td_end = clock();

    //===== ВЫВОД РЕЗУЛЬТАТОВ =====
    cout << "\n A=" << A << "\n B=" << B << "\n C=" << C
         << "\n D=" << D;
    cout << "\nПересечение массивов: E=" << E
         << " (t=" << ((double)(ta_end - ta_start) / CLOCKS_PER_SEC) / RepeatA
         << ")";
    cout << "\n La=";
    for (auto v = La; v; v = v->next) cout << v->d;
    cout << "\n Lb=";
    for (auto v = Lb; v; v = v->next) cout << v->d;
    cout << "\n Lc=";
    for (auto v = Lc; v; v = v->next) cout << v->d;
    cout << "\n Ld=";
    for (auto v = Ld; v; v = v->next) cout << v->d;
    cout << "\nПересечение списков: Le=";
    for (auto v = Le; v; v = v->next) cout << v->d;
    cout << " (t=" << ((double)(tb_end - tb_start) / CLOCKS_PER_SEC) / RepeatB << ")";
    cout << "\n bA=";
    for (int i = U - 1; i >= 0; --i) cout << bA[i] ? char(i + 'A') : '-';
    cout << "\n bB=";
    for (int i = U - 1; i >= 0; --i) cout << bB[i] ? char(i + 'A') : '-';
    cout << "\n bC=";
    for (int i = U - 1; i >= 0; --i) cout << bC[i] ? char(i + 'A') : '-';
    cout << "\n bD=";
    for (int i = U - 1; i >= 0; --i) cout << bD[i] ? char(i + 'A') : '-';
    cout << "\nПересечение биты: bE=";
    for (int i = U - 1; i >= 0; --i) cout << bE[i] ? char(i + 'A') : '-';
    cout << " (t=" << ((double)(tc_end - tc_start) / CLOCKS_PER_SEC) / RepeatC << ")";
    cout << "\nПересечения слова: wE=";
    for (int i = U - 1; i >= 0; --i) cout << (wE & (1 << i)) ? char(i + 'A') : '-';
    cout << " (t=" << ((double)(td_end - td_start) / CLOCKS_PER_SEC) / RepeatD << ")";
    delete La;
    delete Lb;
    delete Lc;
    delete Ld;
    delete Le;
    return 0;
}
