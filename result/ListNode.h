#pragma once

template <typename T>
struct ListNode
{
    T Value;
    ListNode<T>* Next;

    ListNode(T value, ListNode<T>* next = nullptr)
        : Value(value),
          Next(next)
    {
    }

    ~ListNode()
    {
        delete this->Next;
    }
};
