#include "TestEngine.hpp"
#include <algorithm>

// source url: https://www.hackerrank.com/challenges/flipping-the-matrix/problem
class FlippingTheMatrix : public ITestable
{
private:
	enum class Director
	{
		RowLeft,
		RowRight,
		ColumnDown,
		ColumnUp
	};

	static int flippingMatrix(std::vector<std::vector<int>> matrix)
	{
		int columnCount = static_cast<int>(matrix.size());
		int rowCount = 0;
		if (!matrix.empty())
		{
			rowCount = static_cast<int>(matrix[0].size());
		}

		int halfColumnCount = std::lroundf(static_cast<float>(columnCount) / 2.0f);
		int halfRowCount = std::lroundf(static_cast<float>(rowCount) / 2.0f);

		int result = 0;
		std::vector<int> values(4);
		for (int column = 0; column < halfColumnCount; column++)
		{
			for (int row = 0; row < halfRowCount; row++)
			{
				int relativelyRow = rowCount - 1 - row;
				int relativelyColumn = columnCount - 1 - column;
				values[0] = (matrix[column][row]);
				values[1] = (matrix[column][relativelyRow]);
				values[2] = (matrix[relativelyColumn][row]);
				values[3] = (matrix[relativelyColumn][relativelyRow]);
				int maxValue = *std::max_element(values.begin(), values.end());
				result += maxValue;
			}
		}
		return result;
	}

public:
	std::string GetName() const
	{
		return "FlippingTheMatrix";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<int, std::vector<std::vector<int>>> checker(
			[](std::vector<std::vector<int>> matrix)
			{
				return StringTools::GetMatrixString(matrix);
			},
			[](int output)
			{
				return std::to_string(output);
			},
				[](int output, int answer)
			{
				return output == answer;
			});

		checker.AddFunction(flippingMatrix);

		checker.CheckAnswer({
				{ 1, 2 },
				{ 3, 4 }
			}, 4);

		checker.CheckAnswer({
				{ 112, 42, 83, 119 },
				{ 56, 125, 56, 49 },
				{ 15, 78, 101, 43 },
				{ 62, 98, 114, 108 }
			}, 414);

		checker.CheckAnswer({
				{ 107, 54, 128, 15 },
				{ 12, 75, 110, 138 },
				{ 100, 96, 34, 85 },
				{ 75, 15, 28, 112 }
			}, 488);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		if (isSuccess)
		{
			std::string message = checker.GetSuccessMessage();
			std::cout << message;
		}
		return isSuccess;
	}
};
