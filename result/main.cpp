// Множество, содержащее буквы, имеющиеся во множестве A,
// но не являющиеся общими для B и C, и все буквы из D

#include <iostream>
#include <string>
#include <functional>
#include <time.h>

#include "BitSet.h"
#include "LinkedList.h"
#include "ListNode.h"
#include "CalculatorService.h"

using namespace std;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    auto calc = CalculatorService();

    unsigned int eWord = 0;
    BitSet eBitSet = nullptr;
    LinkedList<int>* eList = nullptr;

    unsigned int bitWord[4];
    bitWord[0] = rand(); // Множество A
    bitWord[1] = rand(); // Множество B
    bitWord[2] = rand(); // Множество C
    bitWord[3] = rand(); // Множество D

    auto bitSets = new BitSet*[4];
    for (int i = 0; i < 4; i++) bitSets[i] = BitSet::From(bitWord[i]);

    auto lists = new LinkedList<int>*[4];
    for (int i = 0; i < 4; i++) lists[i] = LinkedList<int>::From(bitSets[i]->GetInternalArray());

    std::function<std::string(const int)> getChar = [](const int i)
    {
        return std::string(1, 'A' + i);
    };

    cout << "Initial sets:" << endl;
    cout << "A: " << lists[0]->ToString(&getChar) << endl;
    cout << "B: " << lists[1]->ToString(&getChar) << endl;
    cout << "C: " << lists[2]->ToString(&getChar) << endl;
    cout << "D: " << lists[3]->ToString(&getChar) << endl;

    {
        clock_t benchmark_total = 0;
        for (int i = 0; i < 500000; i++)
        {
            clock_t iter_start_at = clock();

            eWord = calc.Calculate(bitWord[0], bitWord[1], bitWord[2], bitWord[3]);

            benchmark_total += clock() - iter_start_at;
        }

        cout << "Bit word (500000 iterations): " << benchmark_total << " ticks." << endl;
    }

    {
        clock_t benchmark_total = 0;
        for (int i = 0; i < 500000; i++)
        {
            clock_t iter_start_at = clock();

            eBitSet = calc.Calculate(*bitSets[0], *bitSets[1], *bitSets[2], *bitSets[3]);

            benchmark_total += clock() - iter_start_at;
        }

        cout << "Bit array (500000 iterations): " << benchmark_total << " ticks." << endl;
    }

    {
        clock_t benchmark_total = 0;
        for (int i = 0; i < 500000; i++)
        {
            clock_t iter_start_at = clock();

            eList = calc.Calculate(*lists[0], *lists[1], *lists[2], *lists[3]);

            benchmark_total += clock() - iter_start_at;
        }

        cout << "Linked lists (500000 iterations): " << benchmark_total << " ticks." << endl;
    }

    cout << endl << "Result: " << endl;
    auto eBitSetFromWord = BitSet::From(eWord);
    eBitSetFromWord->Print();
    delete eBitSetFromWord;

    eBitSet.Print();
    cout << eList->ToString(&getChar) << endl;

    return 0;
}
