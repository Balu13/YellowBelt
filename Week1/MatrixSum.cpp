#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdexcept>

using namespace std;

class Matrix
{
public:
	Matrix();
	Matrix(const int num_rows, const int num_cols);

	void Reset(const int num_rows, const int num_cols);
	int At(const int rowNo, const int colNo) const;
	int& At(const int rowNo, const int colNo);
	int GetNumRows() const
	{
		return rowNum;
	}
	int GetNumColumns() const
	{
		return colNum;
	}
private:
	int rowNum;
	int colNum;
	vector<vector<int>> m;

	void reset();
};

Matrix::Matrix()
{
	rowNum = 0;
	colNum = 0;
	reset();
}

Matrix::Matrix(const int num_rows, const int num_cols)
{
	if (num_rows < 0 || num_cols < 0)
	{
		throw std::out_of_range("negative row or column number");
	}
	rowNum = num_rows;
	colNum = num_cols;
	reset();
}

void Matrix::Reset(const int num_rows, const int num_cols)
{
	if (num_rows < 0 || num_cols < 0)
	{
		throw std::out_of_range("negative row or column number");
	}

	rowNum = num_rows;
	colNum = num_cols;
	reset();
}

void Matrix::reset()
{
	m.clear();
	m.resize(rowNum);
	for_each(m.begin(), m.end(), [this](auto& row) {
		row.resize(colNum, 0);
	});
}

int Matrix::At(const int rowNo, const int colNo) const
{
	if (rowNo >= rowNum || rowNo < 0)
	{
		string err = "row number is invalid: " + to_string(rowNo);
		throw std::out_of_range(err + ": int Matrix...");
	}
	if (colNo >= colNum || colNo < 0)
	{
		string err = "column number is invalid: " + to_string(colNo);
		throw std::out_of_range(err + ": int Matrix...");
	}

	return m[rowNo][colNo];
}

int& Matrix::At(const int rowNo, const int colNo)
{
	if (rowNo >= rowNum || rowNo < 0)
	{
		string err = "row number is invalid: " + to_string(rowNo);
		throw std::out_of_range(err);
//		throw out_of_range("");
	}
	if (colNo >= colNum || colNo < 0)
	{
		string err = "column number is invalid: " + to_string(colNo);
		throw std::out_of_range(err);
//		throw out_of_range("");
	}

	return m[rowNo][colNo];
}

istream& operator >> (istream& input, Matrix& m)
{
	int rowNum, colNum;
	input >> rowNum >> colNum;
	m.Reset(rowNum, colNum);
	for (int rowNo = 0; rowNo < m.GetNumRows(); ++rowNo)
	{
		for (int colNo = 0; colNo < m.GetNumColumns(); ++colNo)
		{
			int el;
			input >> el;
			m.At(rowNo, colNo) = el;
		}
	}

	return input;
}

ostream& operator << (ostream& output, Matrix m)
{
	output << m.GetNumRows() << " " << m.GetNumColumns() << endl;
	for (int rowNo = 0; rowNo < m.GetNumRows(); ++rowNo)
	{
		for (int colNo = 0; colNo < m.GetNumColumns(); ++colNo)
		{
			if (colNo!=0)
			{
				output << " ";
			}
			try
			{
				output << m.At(rowNo, colNo);
			}
			catch (out_of_range e)
			{
				throw out_of_range(string(e.what()) + " from operator<<");
			}
		}
		output << endl;
	}

	return output;
}

bool operator == (const Matrix& left, const Matrix& right)
{
	bool areEqual = left.GetNumRows() == right.GetNumRows()
		&& left.GetNumColumns() == right.GetNumColumns();

	if (areEqual)
	{
		int row, col;
		try {
			for (int rowNo = 0; rowNo < left.GetNumRows(); ++rowNo)
			{
				row = rowNo;
				for (int colNo = 0; colNo < left.GetNumColumns(); ++colNo)
				{
					col = colNo;
					if (left.At(rowNo, colNo) != right.At(rowNo, colNo))
					{
						areEqual = false;
						break;
					}
				}
				if (!areEqual)
				{
					break;
				}
			}
		}
		catch (out_of_range e)
		{
			throw out_of_range(string(e.what()) + " from operator==" + " rowNo=" + to_string(row) + " colNo=" + to_string(col));
		}
	}

	return areEqual;
}

Matrix operator + (const Matrix& first, const Matrix& second)
{
	if (first.GetNumColumns() != second.GetNumColumns() || first.GetNumRows() != second.GetNumRows())
	{
		throw invalid_argument("");
	}

	Matrix res{ first.GetNumRows(), first.GetNumColumns() };
	try {
	for (int rowNo = 0; rowNo < first.GetNumRows(); ++rowNo)
	{
		for (int colNo = 0; colNo < first.GetNumColumns(); ++colNo)
		{
			res.At(rowNo, colNo) = first.At(rowNo, colNo) + second.At(rowNo, colNo);
		}
	}
	}
	catch (out_of_range e)
	{
		throw out_of_range(string(e.what()) + " from operator+");
	}

	return res;
}

/*int main()
{
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;

	cin.ignore(32768);
	cin.get();
	return 0;
}
*/