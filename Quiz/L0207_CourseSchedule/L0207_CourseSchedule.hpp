#include "../TestEngine.hpp"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

// source url: https://leetcode.com/problems/course-schedule/
class L0207_CourseSchedule : public ITestable
{
private:
	// Intuitive but not performing well.
	static bool canFinish_0(int numCourses, std::vector<std::vector<int>>& prerequisites)
	{
		struct Node
		{
			std::unordered_set<int> parents;
			std::unordered_set<int> children;
			int passTimes = 0;
		};

		std::vector<Node> nodes(numCourses);
		std::vector<bool> isRoots(numCourses, true);
		for (const std::vector<int>& requisites : prerequisites)
		{
			int childIndex = requisites[0];
			int parentIndex = requisites[1];
			nodes[parentIndex].children.emplace(childIndex);
			nodes[childIndex].parents.emplace(parentIndex);
			isRoots[childIndex] = false;
		}

		for (int rootIndex = 0; rootIndex < static_cast<int>(isRoots.size()); rootIndex++)
		{
			if (!isRoots[rootIndex])
			{
				continue;
			}

			std::vector<int> nodeStack;
			nodeStack.push_back(rootIndex);
			while (!nodeStack.empty())
			{
				int nodeIndex = nodeStack.back();
				nodeStack.pop_back();

				Node& node = nodes[nodeIndex];

				bool isSkip = false;
				for (int parentIndex : node.parents)
				{
					if (nodes[parentIndex].passTimes == 0)
					{
						isSkip = true;
						break;
					}
				}
				if (isSkip)
				{
					continue;
				}

				if (node.passTimes > node.parents.size())
				{
					continue;
				}
				node.passTimes++;

				nodeStack.insert
				(
					nodeStack.end(),
					node.children.begin(),
					node.children.end()
				);
			}
		}

		for (Node& node : nodes)
		{
			if (node.passTimes == 0)
			{
				return false;
			}
		}
		return true;
	}

	// Just DFS.
	static bool canFinish_1(int numCourses, std::vector<std::vector<int>>& prerequisites)
	{
		struct Node
		{
			std::unordered_set<int> children;
			int status = 0;
		};

		std::vector<Node> nodes(numCourses);
		for (const std::vector<int>& requisites : prerequisites)
		{
			int childIndex = requisites[0];
			int parentIndex = requisites[1];
			nodes[parentIndex].children.emplace(childIndex);
		}

		std::function<bool(Node&)> hasCircle;
		hasCircle = [&hasCircle, &nodes](Node &node)
		{
			node.status = 1;
			for (int childIndex : node.children)
			{
				Node& child = nodes[childIndex];
				if (child.status == 0)
				{
					if (hasCircle(child))
					{
						return true;
					}
				}
				else if (child.status == 1)
				{
					return true;
				}
			}
			node.status = 2;
			return false;
		};

		for (Node& node : nodes)
		{
			if (node.status == 0)
			{
				if (hasCircle(node))
				{
					return false;
				}
			}
		}
		return true;
	}

public:
	std::string GetName() const
	{
		return "CourseSchedule";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<bool, int, std::vector<std::vector<int>>&> checker(
			[](int numCourses, std::vector<std::vector<int>>& prerequisites)
			{
				return "numCourses: " + std::to_string(numCourses) + "\nprerequisites:\n" + StringTools::GetMatrixString(prerequisites);
			},
			[](bool output)
			{
				return output ? "true" : "false";
			},
				[](bool output, bool answer)
			{
				return output == answer;
			});

		checker.AddFunction(canFinish_0);
		checker.AddFunction(canFinish_1);

		int numCourses;
		std::vector<std::vector<int>> prerequisites;
		bool answer;

		numCourses = 2;
		prerequisites = { { 1, 0 } };
		answer = true;
		checker.CheckAnswer(numCourses, prerequisites, answer);

		numCourses = 2;
		prerequisites = { { 1, 0 }, { 0, 1 } };
		answer = false;
		checker.CheckAnswer(numCourses, prerequisites, answer);

		numCourses = 5;
		prerequisites = { { 1, 4 }, { 2, 4 }, { 3, 1 }, { 3, 2 } };
		answer = true;
		checker.CheckAnswer(numCourses, prerequisites, answer);

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
