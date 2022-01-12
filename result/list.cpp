#include <iostream>
#include "list.h"

using namespace std;

// Множество, содержащее все цифры множества A, за исключением цифр из B и C, а также все цифры из D
item* listCalculate(item* A, item* B, item* C, item* D)
{
    item* E = nullptr;

    while (A)
    {
        // за исключением цифр из B и C
        if (
            !listContains(B, A->value)
            && !listContains(C, A->value)
        ) {
            E = listPush(E, new item(A->value));
        }

        A = A->next;
    }

    // также все цифры из D
    while (D)
    {
        E = listPush(E, new item(D->value));
        D = D->next;
    }

    return E;
}

bool listContains(item* list, int value)
{
    while (list)
    {
        if (list->value == value) return true;

        list = list->next;
    }

    return false;
}

void listPrint(item* head)
{
    while (head)
    {
        cout << head->value << " ";
        head = head->next;
    }

    cout << endl;
}

item* listPush(item* head, item* element)
{
    if (head) element->next = head;
    return element;
}
