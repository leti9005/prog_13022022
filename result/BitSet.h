#include <iostream>

using std::cout;
using std::endl;

class BitSet
{
private:
    bool* _bitSet;

public:
    BitSet(bool* bs = nullptr) : _bitSet(bs) {}

    void Print()
    {
        for (int i = 0; i < 26; ++i)
            cout << _bitSet[i];
        cout << endl;
    }

    bool* GetInternalArray() { return this->_bitSet; }

    static BitSet From(int bitWord)
    {
        bool* bitSet = new bool[26];

        for (int i = 0; i < 26; i++)
            bitSet[i] = (bitWord >> i) & 1;

        return BitSet(bitSet);
    }

    BitSet operator~() const
    {
        // TODO: копировать массив, а не передавать bool*.
        BitSet c(this->_bitSet);

        for (int i = 0; i < 26; i++)
        {
            c._bitSet[i] = !this->_bitSet[i];
        }

        return c;
    }

    BitSet operator|(const BitSet& b) const
    {
        BitSet c(this->_bitSet);

        for (int i = 0; i < 26; i++)
        {
            c._bitSet[i] = this->_bitSet[i] || b._bitSet[i];
        }

        return c;
    }

    BitSet operator&(const BitSet& b) const
    {
        BitSet c(this->_bitSet);

        for (int i = 0; i < 26; i++)
        {
            c._bitSet[i] = this->_bitSet[i] && b._bitSet[i];
        }

        return c;
    }
};
