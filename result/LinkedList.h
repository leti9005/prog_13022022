#pragma once

#include <iostream>
#include <string>
#include "ListNode.h"
#include <functional>



template <typename T>
class LinkedList
{
    ListNode<T>* _head = nullptr;

    void Add(T value)
    {
        auto newNode = new ListNode<T>(value);

        if (_head == nullptr)
        {
            _head = newNode;
            return;
        }

        auto last = GetLast();
        last->Next = newNode;
    }

public:
    LinkedList()
    {
    }

    void AddIfNotContains(T value)
    {
        if (this->Contains(value)) return;

        this->Add(value);
    }

    bool Contains(T value)
    {
        for (auto n = this->_head; n; n = n->Next)
        {
            if (n->Value == value) return true;
        }

        return false;
    }

    ListNode<T>* GetHead()
    {
        return _head;
    }

    ListNode<T>* GetLast()
    {
        auto h = _head;

        while (h->Next != nullptr)
        {
            h = h->Next;
        }

        return h;
    }

    ListNode<T>* ElementAt(int pos)
    {
        auto h = _head;
        if (pos == 0) return h;

        int i = 0;
        while (i != pos && h->Next != nullptr)
        {
            h = h->Next;
            i++;
        }

        return h;
    }

    bool IsEmpty()
    {
        return _head == nullptr;
    }

    void RemoveLastNode()
    {
        auto last = GetLast();

        if (_head == last)
        {
            _head = nullptr;
            delete last;
            return;
        }

        auto preLastNode = _head;
        while (preLastNode->Next != last)
        {
            preLastNode = preLastNode->Next;
        }

        delete last;

        preLastNode->Next = nullptr;
    }

    std::string ToString(std::function<std::string(T)>* valueConvertExpr = nullptr)
    {
        std::string str;

        for (auto n = this->_head; n; n = n->Next)
        {
            if (n != this->_head) str += " ";

            if (valueConvertExpr)
            {
                str += (*valueConvertExpr)(n->Value);
            }
            else
            {
                str += std::to_string(n->Value);
            }
        }

        return str;
    }

    static LinkedList<int>* From(bool* arr)
    {
        auto list = new LinkedList<int>();

        for (int i = 0; i < 10; ++i) {
            if (!arr[i]) continue;

            list->AddIfNotContains(i);
        }

        return list;
    }
};
