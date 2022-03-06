#include "../TestEngine.hpp"
#include <algorithm>

// source url: https://leetcode.com/problems/interval-list-intersections/submissions/
class L0986_IntervalListIntersections : public ITestable
{
private:
	static std::vector<std::vector<int>> intervalIntersection
	(
		std::vector<std::vector<int>>& firstList,
		std::vector<std::vector<int>>& secondList
	)
	{
		std::vector<std::vector<int>> result;
		size_t secondPos = 0;
		for (const std::vector<int>& firstItem : firstList)
		{
			int start = firstItem[0];
			int end = firstItem[1];
			for (; secondPos < secondList.size(); secondPos++)
			{
				int value = secondList[secondPos][1];
				if (value < start)
				{
					// too small, skip.
				}
				else if (value <= end)
				{
					// in range.
					result.push_back({ std::max(secondList[secondPos][0], start), value });
				}
				else
				{
					// too big.
					if (secondList[secondPos][0] <= end)
					{
						result.push_back({ std::max(secondList[secondPos][0], start), end });
					}
					break;
				}
			}
		}
		return result;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::vector<std::vector<int>>,
			std::vector<std::vector<int>>&,
			std::vector<std::vector<int>>&> checker(
				[](std::vector<std::vector<int>>& firstList, std::vector<std::vector<int>>& secondList)
				{
					std::string firstListString = StringTools::GetMatrixString(firstList);
					std::string secondListString = StringTools::GetMatrixString(secondList);
					return "firstList: \n" + firstListString + "\nsecondListString:\n" + secondListString;
				},
				[](std::vector<std::vector<int>> output)
				{
					return StringTools::GetMatrixString(output);
				},
					[](std::vector<std::vector<int>> output, std::vector<std::vector<int>> answer)
				{
					return std::equal(output.begin(), output.end(), answer.begin(), answer.end(),
						[](const std::vector<int>& a, const std::vector<int>& b)
						{
							return std::equal(a.begin(), a.end(), b.begin(), b.end());
						});
				});

		checker.AddFunction(intervalIntersection);

		std::vector<std::vector<int>> firstList;
		std::vector<std::vector<int>> secondList;
		std::vector<std::vector<int>> answer;

		firstList = { {0,2},{5,10},{13,23},{24,25} };
		secondList = { {1,5},{8,12},{15,24},{25,26} };
		answer = { {1,2},{5,5},{8,10},{15,23},{24,24},{25,25} };
		checker.CheckAnswer(firstList, secondList, answer);

		firstList = { {1,3},{5,9} };
		secondList = {};
		answer = {};
		checker.CheckAnswer(firstList, secondList, answer);

		firstList = { {8,15} };
		secondList = { {2,6},{8,10},{12,20} };
		answer = { {8,10},{12,15} };
		checker.CheckAnswer(firstList, secondList, answer);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
