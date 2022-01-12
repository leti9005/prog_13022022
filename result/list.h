typedef struct item
{
    int value;
    item* next = nullptr;

    item(int value = 0)
    {
        this->value = value;
    }

} item;

item* convertSetToList(bool* bitSet);

item* listPush(item* head, item* element);
void listPrint(item* head);

bool listContains(item* list, int value);

item* listCalculate(item* A, item* B, item* C, item* D);
