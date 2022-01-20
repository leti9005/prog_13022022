#include "LinkedList.h"

// Класс, содержащий в себе бизнес-логику вычисления множества E разными способами по правилу:
// Множество, содержащее буквы, имеющиеся во множестве A,
// но не являющиеся общими для B и C, и все буквы из D.
class CalculatorService
{
private:
    template <typename T>
    LinkedList<T>* intersectLists(
        LinkedList<T> a,
        LinkedList<T> b
    )
    {
        auto r = new LinkedList<T>;

        for (auto n = a.GetHead(); n; n = n->Next)
        {
            if (!b.Contains(n->Value)) continue;

            r->AddIfNotContains(n->Value);
        }

        return r;
    }

public:
    CalculatorService() {}

    template <typename T>
    LinkedList<T>* Calculate(
        LinkedList<T> a,
        LinkedList<T> b,
        LinkedList<T> c,
        LinkedList<T> d
    )
    {
        auto e = new LinkedList<T>();

        auto bcIntersection = this->intersectLists(b, c);
        for (auto n = a.GetHead(); n; n = n->Next)
        {
            if (bcIntersection->Contains(n->Value)) continue;

            e->AddIfNotContains(n->Value);
        }

        for (auto n = d.GetHead(); n; n = n->Next)
        {
            e->AddIfNotContains(n->Value);
        }

        delete bcIntersection;
        return e;
    }
};
