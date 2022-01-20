#include <iostream>

using std::cout;
using std::endl;

class BitSet
{
private:
    bool* _bitSet;

public:
    BitSet(bool* bs) : _bitSet(bs) {}

    void Print()
    {
        for (int i = 0; i < 26; ++i)
            cout << _bitSet[i];
        cout << endl;
    }

    bool* GetInternalArray() { return this->_bitSet; }

    static BitSet* From(int bitWord)
    {
        bool* bitSet = new bool[26];

        for (int i = 0; i < 26; i++)
            bitSet[i] = (bitWord >> i) & 1;

        return new BitSet(bitSet);
    }

    // BitSet operator~() const
    // {
    //     BitSet C;
    //     for (char c = 'A'; c <= 'Z'; ++c)
    //     { // Цикл по универсуму
    //         bool f = true;
    //         for (int j = 0; j < n; ++j)
    //             if (c == A[j])
    //             {
    //                 f = false;
    //                 break;
    //             }
    //         if (f)
    //             C.A[C.n++] = c;
    //     }
    //     C.A[C->n] = 0;
    //     return std::move(C);
    // }

    // BitSet& operator|=(const BitSet& B)
    // {
    //     for (int i = 0; i < B.n; ++i)
    //     {
    //         bool f = true;
    //         for (int j = 0; j < n; ++j)
    //             if (B.A[i] == A[j])
    //                 f = false;
    //         if (f)
    //             A[n++] = B.A[i];
    //     }
    //     A[n] = 0;
    //     return *this;
    // }

    // BitSet operator|(const BitSet& B) const
    // {
    //     BitSet C(*this);
    //     return std::move(C |= B);
    // }

    ~BitSet() { delete[] this->_bitSet; }
};
