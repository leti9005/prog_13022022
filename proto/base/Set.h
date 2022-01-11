#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename T>
using Func = std::function<T(T)>;

template<typename T>
struct Set
{
private:
    std::vector<T> _data;

public:
    Set(std::initializer_list<T> initial_list)
    {
        for (auto value: initial_list) this->push(value);
    }

    bool contains(T value)
    {
        return std::find(_data.begin(), _data.end(), value) != _data.end();
    }

    Set<T> filter(Func<bool> conditionExpr)
    {
        Set<T> result {};

        for (auto el: _data)
        {
            if (!conditionExpr(el)) continue;

            result.push(el);
        }

        return result;
    }

    Set<T> append(Set<T> appended_set)
    {
        Set<T> result {};

        for (auto el: _data) result.push(el);
        for (auto el: appended_set) result.push(el);

        return result;
    }

    void push(T value)
    {
        if (this->contains(value)) return;
        _data.push_back(value);
    }

    std::string to_string()
    {
        std::string result = "";
        for (auto el: _data) result += el;
        return result;
    }

    typedef typename std::vector<T>::iterator iterator;

    iterator begin()
    {
        return _data.begin();
    }

    iterator end()
    {
        return _data.end();
    }
};
