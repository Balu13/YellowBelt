#include "stdafx.h"
#include <vector>
#include <iostream>
#include <map>
using namespace std;

template <typename T> T Sqr(T x);
template <typename T> vector<T> Sqr(const vector<T>& x);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& x);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& x);

template <typename T>
T Sqr(T x)
{
    return x * x;
}

template<typename T>
vector<T> Sqr(const vector<T>& x)
{
    vector<T> y;
    for (auto xVal : x)
    {
        y.push_back(xVal * xVal);
    }
    return y;
}

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& x)
{
    return make_pair(Sqr(x.first), Sqr(x.second));
}

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& x)
{
    map<Key, Value> y;
    for (auto xVal : x)
    {
        y[xVal.first] = Sqr(xVal.second);
    }
    return y;
}

int main()
{
    vector<int> v = { 1, 2, 3 };
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs =
    {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& [key, pairValue] : Sqr(map_of_pairs))
    {
        cout << key << ' ' << pairValue.first << ' ' << pairValue.second << endl;
    }

    return 0;
}