#include <iostream>
#include "list.h"

using namespace std;

// Множество, содержащее буквы, имеющиеся во множестве A,
// но не являющиеся общими для B и C, и все буквы из D
item* listCalculate(item* A, item* B, item* C, item* D)
{
    item* E = nullptr;

    while (A)
    {
        // Все из A, не являющиеся общими для B и C
        if (!(listContains(B, A->value) && listContains(C, A->value)))
        {
            E = listPushIfNotContains(E, new item(A->value));
        }

        A = A->next;
    }

    // все буквы из D
    while (D)
    {
        E = listPushIfNotContains(E, new item(D->value));
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
    element->next = head;
    return element;
}

item* listPushIfNotContains(item* head, item* element)
{
    if (head && listContains(head, element->value)) {
        return head;
    }

    return listPush(head, element);
}
