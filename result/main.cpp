// Множество, содержащее буквы, имеющиеся во множестве A,
// но не являющиеся общими для B и C, и все буквы из D

#include <iostream>
#include <time.h>

#include "bitSet.h"
#include "list.h"

using namespace std;

int main(int argc, char** argv)
{
    clock_t runtime = 0;
    clock_t runtime_total = 0;
    srand(time(NULL));

    unsigned int bitWord[5];
    bitWord[0] = rand(); // Множество A
    bitWord[1] = rand(); // Множество B
    bitWord[2] = rand(); // Множество C
    bitWord[3] = rand(); // Множество D

    bool** bitSet = new bool*[5];
    for (int i = 0; i < 4; i++) bitSet[i] = convertWordToSet(bitWord[i]);

    item** list = new item*[5];
    for (int i = 0; i < 4; i++) list[i] = convertSetToList(bitSet[i]);

    /* Выводим исходные множества */
    cout << "Initial sets:" << endl;
    cout << "A: ";
    listPrint(list[0]);

    cout << "B: ";
    listPrint(list[1]);

    cout << "C: ";
    listPrint(list[2]);

    cout << "D: ";
    listPrint(list[3]);

    /* Вычисляем множество E для машинного слова */
    for (int i = 0; i < 500000; i++)
    {
        runtime = clock();
        bitWord[4] = bitWordCalculate(bitWord[0], bitWord[1], bitWord[2], bitWord[3]);
        runtime = clock() - runtime;
        runtime_total += runtime;
    }

    cout << endl;
    cout << "Bit word (500000 iterations): " << runtime_total << " ticks." << endl;

    /* Вычисляем множество E для массива бит */
    for (int i = 0; i < 500000; i++)
    {
        runtime = clock();
        bitSet[4] = bitSetCalculate(bitSet[0], bitSet[1], bitSet[2], bitSet[3]);
        runtime = clock() - runtime;
        runtime_total += runtime;
    }
    cout << "Bit array (500000 iterations): " << runtime_total << " ticks." << endl;

    /* Вычисляем множество E для списка */
    for (int i = 0; i < 500000; i++)
    {
        runtime = clock();
        list[4] = listCalculate(list[0], list[1], list[2], list[3]);
        runtime = clock() - runtime;
        runtime_total += runtime;
    }

    cout << "Linked list (500000 iterations): " << runtime_total << " ticks." << endl;

    cout << endl << "Result: " << endl;
    bitSetPrint(convertWordToSet(bitWord[4]));
    bitSetPrint(bitSet[4]);
    listPrint(list[4]);

    return 0;
}
