// Множество, содержащее буквы, имеющиеся во множестве A,
// но не являющиеся общими для B и C, и все буквы из D

#include <iostream>
#include "list.h"

using namespace std;

void bitSetPrint(bool* bitSet)
{
    for (int i = 0; i < 10; ++i) cout << bitSet[i];
    cout << endl;
}

bool* bitSetCalculate(bool* A, bool* B, bool* C, bool* D)
{
    bool* E = new bool[10];

    for (int i = 0; i < 10; ++i)
        E[i] = (A[i] && !(B[i] && C[i])) || D[i];

    return E;
}

unsigned int bitWordCalculate(int A, int B, int C, int D)
{
    return A & ~(B & C) | D;
}

item* convertSetToList(bool* bitSet)
{
    item* list = nullptr;

    for (int i = 0; i < 10; ++i)
        if (bitSet[i])
            list = listPushIfNotContains(list, new item(i));

    return list;
}

bool* convertWordToSet(int bitWord)
{
    bool* bitSet = new bool[10];

    for (int i = 0; i < 10; i++)
        bitSet[i] = (bitWord >> i) & 1;

    return bitSet;
}
