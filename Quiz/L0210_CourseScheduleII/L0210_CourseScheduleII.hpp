#include "../TestEngine.hpp"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

// source url: https://leetcode.com/problems/course-schedule-ii/
class L0210_CourseScheduleII : public ITestable
{
private:
	// Basic.
	static std::vector<int> findOrder_0(int numCourses, std::vector<std::vector<int>>& prerequisites)
	{
		struct Node
		{
			std::unordered_set<int> parents;
			std::unordered_set<int> children;
		};
		std::vector<Node> nodes(numCourses);
		for (const std::vector<int>& requisites : prerequisites)
		{
			int childIndex = requisites[0];
			int parentIndex = requisites[1];
			nodes[parentIndex].children.emplace(childIndex);
			nodes[childIndex].parents.emplace(parentIndex);
		}
		std::vector<int> noParentStack;
		for (int i = 0; i < numCourses; i++)
		{
			if (nodes[i].parents.empty())
			{
				noParentStack.push_back(i);
			}
		}
		std::vector<int> result;
		while (!noParentStack.empty())
		{
			int nodeIndex = noParentStack.back();
			noParentStack.pop_back();

			result.push_back(nodeIndex);
			const Node& node = nodes[nodeIndex];
			for (int childIndex : node.children)
			{
				Node& child = nodes[childIndex];
				child.parents.erase(nodeIndex);
				if (child.parents.empty())
				{
					noParentStack.push_back(childIndex);
				}
			}
		}
		if (result.size() != numCourses)
		{
			return std::vector<int>();
		}
		return result;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::vector<int>, int, std::vector<std::vector<int>>&> checker(
			[](int numCourses, std::vector<std::vector<int>>& prerequisites)
			{
				return "numCourses: " + std::to_string(numCourses) + "\nprerequisites:\n" + StringTools::GetMatrixString(prerequisites);
			},
			[](std::vector<int> output)
			{
				return StringTools::GetVectorString(output);
			},
				[](std::vector<int> output, std::vector<int> answer)
			{
				return std::equal(output.begin(), output.end(), answer.begin(), answer.end());
			});

		checker.AddFunction(findOrder_0);

		int numCourses;
		std::vector<std::vector<int>> prerequisites;
		std::vector<std::vector<int>> answerList;

		numCourses = 2;
		prerequisites = { { 1, 0 } };
		answerList = { { 0, 1 } };
		checker.CheckAnswer(numCourses, prerequisites, answerList);

		numCourses = 4;
		prerequisites = { { 1, 0 }, { 2, 0 }, { 3, 1 }, { 3, 2 } };
		answerList = { { 0, 2, 1, 3 }, { 0, 1, 2, 3 } };
		checker.CheckAnswer(numCourses, prerequisites, answerList);

		numCourses = 1;
		prerequisites = {};
		answerList = { { 0 } };
		checker.CheckAnswer(numCourses, prerequisites, answerList);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
