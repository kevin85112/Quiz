#include "../TestEngine.hpp"
#include <algorithm>
#include <set>
#include <deque>

// source url: https://leetcode.com/problems/merge-intervals/
class MergeIntervals : public ITestable
{
private:
	// bad performance
	static std::vector<std::vector<int>> merge_0(std::vector<std::vector<int>>& intervals)
	{
		auto isIntersect = [](const std::vector<int>& input1, const std::vector<int>& input2) -> bool
		{
			if (input2[1] < input1[0] || input2[0] > input1[1])
			{
				return false;
			}
			return true;
		};

		std::vector<std::vector<int>> groupList;
		for (int i = 0; i < static_cast<int>(intervals.size()); i++)
		{
			std::vector<int> newGroup;
			const std::vector<int>& interval = intervals[i];
			for (int groupIndex = static_cast<int>(groupList.size()) - 1; groupIndex >= 0; groupIndex--)
			{
				std::vector<int>& group = groupList[groupIndex];
				for (int groupMemberIndex : group)
				{
					const std::vector<int>& groupMember = intervals[groupMemberIndex];
					if (isIntersect(groupMember, interval))
					{
						// insert.
						newGroup.insert(newGroup.end(), group.begin(), group.end());
						// erase.
						group = groupList.back();
						groupList.pop_back();
						break;
					}
				}
			}
			newGroup.push_back(i);
			groupList.push_back(newGroup);
		}

		std::vector<std::vector<int>> result;
		for (const std::vector<int>& group : groupList)
		{
			int start = INT_MAX;
			int end = INT_MIN;
			for (int groupMemberIndex : group)
			{
				std::vector<int>& groupMember = intervals[groupMemberIndex];
				start = std::min(start, groupMember[0]);
				end = std::max(end, groupMember[1]);
			}
			result.push_back({ start, end });
		}
		return result;
	}

	// use stl algorithm, less memory but just as slow.
	static std::vector<std::vector<int>> merge_1(std::vector<std::vector<int>>& intervals)
	{
		auto isIntersect = [](int start1, int end1, int start2, int end2) -> bool
		{
			if (end2 < start1 || start2 > end1)
			{
				return false;
			}
			return true;
		};

		std::deque<std::vector<int>> merged;
		auto append = [&](const std::vector<int>& interval)
		{
			if (merged.empty())
			{
				merged.push_back(interval);
			}
			else
			{
				int start = merged.front()[0];
				int end = merged.back()[1];
				if (isIntersect(interval[0], interval[1], start, end))
				{
					std::deque<std::vector<int>>::iterator startIt = std::find_if(merged.begin(), merged.end(), [&](const std::vector<int>& value)
						{
							return interval[0] <= value[1];
						});

					std::deque<std::vector<int>>::iterator endIt = std::find_if(startIt, merged.end(), [&](const std::vector<int>& value)
						{
							return interval[1] < value[0];
						});
					--endIt;

					if (isIntersect(interval[0], interval[1], (*startIt)[0], (*endIt)[1]))
					{
						int min = std::min((*startIt)[0], interval[0]);
						int max = std::max((*endIt)[1], interval[1]);
						*startIt = { min, max };
						merged.erase(startIt + 1, endIt + 1);
					}
					else
					{
						merged.insert(startIt, interval);
					}
				}
				else
				{
					if (interval[1] < start)
					{
						merged.push_front(interval);
					}
					else
					{
						merged.push_back(interval);
					}
				}
			}
		};

		for (const std::vector<int>& interval : intervals)
		{
			append(interval);
		}

		std::vector<std::vector<int>> result(merged.begin(), merged.end());
		return result;
	}

	// just sort.
	static std::vector<std::vector<int>> merge_2(std::vector<std::vector<int>>& intervals)
	{
		std::sort(intervals.begin(), intervals.end());
		std::vector<std::vector<int>> result;
		int start = -1;
		int end = -1;
		for (const std::vector<int>& interval : intervals)
		{
			if (start == -1)
			{
				start = interval[0];
				end = interval[1];
			}
			else
			{
				if (interval[0] > end)
				{
					result.push_back({ start, end });
					start = interval[0];
					end = interval[1];
				}
				else
				{
					end = std::max(end, interval[1]);
				}
			}
		}
		if (start >= 0)
		{
			result.push_back({ start,end });
		}
		return result;
	}

public:
	std::string GetName() const
	{
		return "MergeIntervals";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::vector<std::vector<int>>, std::vector<std::vector<int>>&> checker(
			[](std::vector<std::vector<int>>& intervals)
			{
				return StringTools::GetMatrixString(intervals);
			},
			[](std::vector<std::vector<int>> output)
			{
				return StringTools::GetMatrixString(output);
			},
				[](std::vector<std::vector<int>> output, std::vector<std::vector<int>> answer)
			{
				if (output.size() != answer.size())
				{
					return false;
				}
				for (size_t i = 0; i < output.size(); i++)
				{
					bool isMatch = false;
					for (size_t j = 0; j < answer.size(); j++)
					{
						if (std::equal(output[i].begin(), output[i].end(), answer[j].begin(), answer[j].end()))
						{
							isMatch = true;
							answer.erase(answer.begin() + j);
							break;
						}
					}
					if (!isMatch)
					{
						return false;
					}
				}
				return true;
			});

		checker.AddFunction(merge_0);
		checker.AddFunction(merge_1);
		checker.AddFunction(merge_2);

		std::vector<std::vector<int>> intervals;
		std::vector<std::vector<int>> answer;

		intervals = { { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 } };
		answer = { { 1, 6 }, { 8, 10 }, { 15, 18 } };
		checker.CheckAnswer(intervals, answer);

		intervals = { {2, 3}, { 5,5 }, { 2,2 }, { 3,4 }, { 3,4 } };
		answer = { { 2, 4 }, { 5, 5 } };
		checker.CheckAnswer(intervals, answer);

		intervals = { {2, 3}, { 4,5 }, { 6,7 }, { 8,9 }, { 1,10 } };
		answer = { { 1, 10 } };
		checker.CheckAnswer(intervals, answer);

		intervals = { { 1, 4 }, { 4, 5 } };
		answer = { { 1, 5 } };
		checker.CheckAnswer(intervals, answer);

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
