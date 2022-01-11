// Множество, содержащее буквы, имеющиеся во множестве A, но не являющиеся общими для B и C, и все буквы из D
#include <iostream>
#include <ctime>
#include <vector>
#include "base/Set.h"

class SetArguments
{
public:
    Set<char>* a;
    Set<char>* b;
    Set<char>* c;
    Set<char>* d;

    SetArguments(
        Set<char>* initial_set,
        Set<char>* b_set,
        Set<char>* c_set,
        Set<char>* appended_set
    )
    {
        this->a = initial_set;
        this->b = b_set;
        this->c = c_set;
        this->d = appended_set;
    }

    ~SetArguments()
    {
        delete a;
        delete b;
        delete c;
        delete d;
    }
};

class LatinCharacterSetsGenerator
{
private:
    int _a_length;
    int _b_length;
    int _c_length;
    int _d_length;

    const int POWER = 26;

    char GetRandomChar()
    {
        return 'a' + rand() % POWER;
    }

public:
    LatinCharacterSetsGenerator(int a_length, int b_length, int c_length, int d_length)
    {
        _a_length = a_length;
        _b_length = b_length;
        _c_length = c_length;
        _d_length = d_length;

        srand(time(nullptr) / 2);
    }

    SetArguments GenerateSets()
    {
        auto a = new Set<char> {};
        auto b = new Set<char> {};
        auto c = new Set<char> {};
        auto d = new Set<char> {};

        for (int i = 0; i < _a_length; i++) a->push(GetRandomChar());
        for (int i = 0; i < _b_length; i++) b->push(GetRandomChar());
        for (int i = 0; i < _c_length; i++) c->push(GetRandomChar());
        for (int i = 0; i < _d_length; i++) d->push(GetRandomChar());

        SetArguments result(a, b, c, d);
        return result;
    }
};

int main()
{
    LatinCharacterSetsGenerator generator(10, 5, 5, 1);
    auto generated_sets = generator.GenerateSets();

    std::cout << "a: " << generated_sets.a->to_string() << "\n";
    std::cout << "b: " << generated_sets.b->to_string() << "\n";
    std::cout << "c: " << generated_sets.c->to_string() << "\n";
    std::cout << "d: " << generated_sets.d->to_string() << "\n";

    auto result = generated_sets.a
        ->filter([&](const int el) {
            return !(
                generated_sets.b->contains(el)
                && generated_sets.c->contains(el)
            );
        })
        .append(*generated_sets.d);

    std::cout << "r: " << result.to_string() << std::endl;
}
