#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct Block
{
	int m_density;
	int m_w;
	int m_h;
	int m_d;

	Block() : m_density(0), m_w(0), m_d(0)
	{
	}

	Block(int density, int w, int h, int d) : m_density(density), m_w(w), m_h(h), m_d(d)
	{
	}

	uint64_t calcWeight() const
	{
		return static_cast<uint64_t>(m_density) * m_w * m_h * m_d;
	}
};

/*int main()
{
	int blockNum, density;
	cin >> blockNum >> density;

	vector<Block> blocks(blockNum);
	for (int blockNo = 0; blockNo < blockNum; ++blockNo)
	{
		int w, h, d;
		cin >> w >> h >> d;
		blocks.push_back({ density, w, h, d });
	}

	uint64_t weightSum{ 0 };
	for (auto& block : blocks)
	{
		weightSum += block.calcWeight();
	}

	cout << weightSum;

	cin.clear();
	cin.ignore(32768, '\n');
	cin.get();
	return 0;
}*/