#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

int main1()
{
	size_t dayNum;
	cin >> dayNum;

	vector<int32_t> temp(dayNum);

	for (size_t dayNo = 0; dayNo < dayNum; ++dayNo)
	{
		cin >> temp.at(dayNo);
	}

	int64_t tempSum{ 0 };
	for (int32_t& dayTemp : temp)
	{
		tempSum += dayTemp;
	}
	int64_t avgTemp = tempSum / static_cast<int64_t>(temp.size());

	vector<size_t> hotDays;
	for (size_t dayNo = 0; dayNo < dayNum; ++dayNo)
	{
		if (temp[dayNo] > avgTemp)
		{
			hotDays.push_back(dayNo);
		}
	}

	cout << hotDays.size() << endl;
	for (size_t hotDayNo = 0; hotDayNo < hotDays.size(); ++hotDayNo)
	{
		if (hotDayNo != 0)
		{
			cout << " ";
		}
		cout << hotDays[hotDayNo];
	}

	cin.clear();
	cin.ignore(32768, '\n');
	cin.get();
	return 0;
}