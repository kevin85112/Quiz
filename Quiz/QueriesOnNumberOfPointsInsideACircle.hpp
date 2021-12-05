#include "TestEngine.hpp"

// source url: https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/
class QueriesOnNumberOfPointsInsideACircle : public ITestable
{
private:
	static std::vector<int> countPoints_0(std::vector<std::vector<int>> points, std::vector<std::vector<int>> queries)
	{
		std::vector<int> results;
		for (const std::vector<int>& circle : queries)
		{
			int inCount = 0;

			int circleX = circle[0];
			int circleY = circle[1];
			int radius = circle[2];
			int radiusSquare = radius * radius;

			for (const std::vector<int>& point : points)
			{
				int x = point[0];
				int y = point[1];
				int xOffset = x - circleX;
				int yOffset = y - circleY;
				int distanceSquare = xOffset * xOffset + yOffset * yOffset;
				if (distanceSquare <= radiusSquare)
				{
					++inCount;
				}
			}
			results.push_back(inCount);
		}
		return results;
	}

public:
	std::string GetName() const
	{
		return "Queries on Number of Points Inside a Circle";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::vector<int>, std::vector<std::vector<int>>, std::vector<std::vector<int>>> checker(
			[](std::vector<std::vector<int>> points, std::vector<std::vector<int>> queries)
			{
				std::stringstream text;
				text << "points:\n" << StringTools::GetMatrixString(points)
					<< "\nqueries:\n" << StringTools::GetMatrixString(queries);
				return text.str();
			},
			[](std::vector<int> output)
			{
				return StringTools::GetVectorString(output);
			},
				[](std::vector<int> output, std::vector<int> answer)
			{
				return output == answer;
			});

		checker.AddFunction(countPoints_0);

		checker.CheckAnswer({
				{ 1, 3 },
				{ 3, 3 },
				{ 5, 3 },
				{ 2, 2 }
			}, {
				{ 2, 3, 1},
				{ 4, 3, 1},
				{ 1, 1, 2}
			}, { 3, 2, 2 });

		checker.CheckAnswer({
				{ 1, 1 },
				{ 2, 2 },
				{ 3, 3 },
				{ 4, 4 },
				{ 5, 5 }
			}, {
				{ 1, 2, 2},
				{ 2, 2, 2},
				{ 4, 3, 2},
				{ 4, 3, 3}
			}, { 2, 3, 2, 4 });

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
