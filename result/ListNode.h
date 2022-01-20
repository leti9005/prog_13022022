#pragma once

template <typename T>
struct ListNode
{
    T Value;
    ListNode<T>* Next = nullptr;

    ListNode()
    {
    }
};
