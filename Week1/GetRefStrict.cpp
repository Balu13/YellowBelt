//#include "stdafx.h"
#include <map>
#include <iostream>
#include <string>

using namespace std;

template<typename T1, typename T2> T2& GetRefStrict(map<T1, T2> &m, T1 key);

template<typename T1, typename T2>
T2& GetRefStrict(map<T1, T2> &m, T1 key)
{
    if (m.count(key) == 0)
    {
        throw runtime_error("");
    }
    
    return m[key];
}

//int main()
//{
//    map<int, string> m = { {0, "value"} };
//    string& item = GetRefStrict(m, 1);
//    item = "newvalue";
//    cout << m[0] << endl; // выведет newvalue
//    return 0;
//}