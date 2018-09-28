#include "stdafx.h"
#include <iostream>

#include <stdexcept>

using namespace std;

class Matrix
{
public:
	Matrix();
	Matrix(const int num_rows, const int num_cols);
	~Matrix();

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
};

Matrix::Matrix()
{
	rowNum = 0;
	colNum = 0;
}

Matrix::Matrix(const int num_rows, const int num_cols)
{
	if (num_rows < 0 || num_cols < 0)
	{
		throw std::out_of_range("negative row or column number");
	}
	rowNum = num_rows;
	colNum = num_cols;
}

Matrix::~Matrix()
{
}

void Matrix::Reset(const int num_rows, const int num_cols)
{
	if (num_rows < 0 || num_cols < 0)
	{
		throw std::out_of_range("negative row or column number");
	}
}

int Matrix::At(const int rowNo, const int colNo) const
{
	if (rowNo > rowNum || rowNo < 0)
	{
		throw std::out_of_range("row number is ivalid");
	}
	if (colNo > colNum || colNo < 0)
	{
		throw std::out_of_range("column number is ivalid");
	}
	return 0;
}

int& Matrix::At(const int rowNo, const int colNo)
{
	if (rowNo > rowNum || rowNo < 0)
	{
		throw std::out_of_range("row number is ivalid");
	}
	if (colNo > colNum || colNo < 0)
	{
		throw std::out_of_range("column number is ivalid");
	}

	int a{ 0 };

	return a;
}

istream& operator >> (istream& input, Matrix& matrix)
{
	return input;
}

ostream& operator << (ostream& output, const Matrix& matrix)
{
	return output;
}

bool operator == (const Matrix& left, const Matrix& right)
{
	return true;
}

Matrix operator + (const Matrix& first, const Matrix& second)
{
	Matrix res;

	return res;
}

int main()
{
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;
	return 0;
}
