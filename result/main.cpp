// Множество, содержащее буквы, имеющиеся во множестве A,
// но не являющиеся общими для B и C, и все буквы из D

#include <iostream>
#include <string>
#include <functional>
#include <time.h>

#include "bitSet.h"
#include "LinkedList.h"
#include "ListNode.h"
#include "CalculatorService.h"

using namespace std;

int main(int argc, char** argv)
{
    srand(time(nullptr));

    unsigned int bitWord[5];
    bitWord[0] = rand(); // Множество A
    bitWord[1] = rand(); // Множество B
    bitWord[2] = rand(); // Множество C
    bitWord[3] = rand(); // Множество D

    auto bitSet = new bool*[5];
    for (int i = 0; i < 4; i++) bitSet[i] = convertWordToSet(bitWord[i]);

    auto lists = new LinkedList<int>*[5];
    for (int i = 0; i < 4; i++) lists[i] = LinkedList<int>::From(bitSet[i]);

    std::function<std::string(const int)> getChar = [](const int i)
    {
        return std::string(1, 'A' + i);
    };

    cout << "Initial sets:" << endl;
    cout << "A: " << lists[0]->ToString(&getChar) << endl;
    cout << "B: " << lists[1]->ToString(&getChar) << endl;
    cout << "C: " << lists[2]->ToString(&getChar) << endl;
    cout << "D: " << lists[3]->ToString(&getChar) << endl;

    auto calc = CalculatorService();
    auto eList = calc.Calculate(*lists[0], *lists[1], *lists[2], *lists[3]);
    cout << "E: " << eList->ToString(&getChar) << endl;


    // cout << endl;

    // {
    //     clock_t benchmark_total = 0;
    //     for (int i = 0; i < 500000; i++)
    //     {
    //         clock_t iter_start_at = clock();

    //         bitWord[4] = bitWordCalculate(bitWord[0], bitWord[1], bitWord[2], bitWord[3]);

    //         benchmark_total += clock() - iter_start_at;
    //     }

    //     cout << "Bit word (500000 iterations): " << benchmark_total << " ticks." << endl;
    // }

    // {
    //     clock_t benchmark_total = 0;
    //     for (int i = 0; i < 500000; i++)
    //     {
    //         clock_t iter_start_at = clock();

    //         bitSet[4] = bitSetCalculate(bitSet[0], bitSet[1], bitSet[2], bitSet[3]);

    //         benchmark_total += clock() - iter_start_at;
    //     }

    //     cout << "Bit array (500000 iterations): " << benchmark_total << " ticks." << endl;
    // }

    // {
    //     clock_t benchmark_total = 0;
    //     for (int i = 0; i < 500000; i++)
    //     {
    //         clock_t iter_start_at = clock();

    //         lists[4] = listCalculate(lists[0], lists[1], lists[2], lists[3]);

    //         benchmark_total += clock() - iter_start_at;
    //     }

    //     cout << "Linked lists (500000 iterations): " << benchmark_total << " ticks." << endl;
    // }

    // cout << endl << "Result: " << endl;
    // bitSetPrint(convertWordToSet(bitWord[4]));
    // bitSetPrint(bitSet[4]);
    // listPrint(lists[4]);

    return 0;
}
