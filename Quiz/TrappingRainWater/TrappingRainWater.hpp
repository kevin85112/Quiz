#include "TestEngine.hpp"
#include <unordered_map>
#include <deque>
#include <stack>

// source url: https://leetcode.com/problems/trapping-rain-water/
class TrappingRainWater : public ITestable
{
private:
	// Time Limit Exceeded.
	static int trap_0(std::vector<int> height)
	{
		int result = 0;
		std::vector<int> heightHistoryTable;
		for (int step = 0; step < static_cast<int>(height.size()); step++)
		{
			int currentHeight = height[step];
			if (currentHeight != 0)
			{
				if (currentHeight > static_cast<int>(heightHistoryTable.size()))
				{
					heightHistoryTable.resize(currentHeight, -1);
				}

				for (int checkHeight = 0; checkHeight < currentHeight; checkHeight++)
				{
					if (heightHistoryTable[checkHeight] >= 0)
					{
						result += (step - heightHistoryTable[checkHeight] - 1);
					}
					heightHistoryTable[checkHeight] = step;
				}
			}
		}
		return result;
	}

	// Time Limit Exceeded.
	static int trap_1(std::vector<int> height)
	{
		std::list<int> leftmostList;
		std::list<int> rightmostList;
		int elevationArea = 0;
		for (int i = 0; i < static_cast<int>(height.size()); i++)
		{
			int currentHeight = height[i];
			if (currentHeight <= 0)
			{
				continue;
			}

			while (currentHeight > static_cast<int>(leftmostList.size()))
			{
				leftmostList.push_back(i);
				rightmostList.push_back(i);
			}

			int index = 0;
			for (auto it = rightmostList.begin(); index < currentHeight; ++it, ++index)
			{
				*it = i;
			}

			elevationArea += currentHeight;
		}

		int result = 0;
		for (auto it1 = rightmostList.begin(), it2 = leftmostList.begin(); it1 != rightmostList.end(); ++it1, ++it2)
		{
			result += *it1 - *it2 + 1;
		}
		result -= elevationArea;
		return result;
	}

	static int trap_2(std::vector<int> height)
	{
		if (height.empty())
		{
			return 0;
		}

		int maxHeight = 0;
		int maxHeightIndex = 0;
		int elevationValue = 0;
		for (int i = 0; i < static_cast<int>(height.size()); i++)
		{
			int currentHeight = height[i];
			if (currentHeight > maxHeight)
			{
				maxHeight = currentHeight;
				maxHeightIndex = i;
			}
			elevationValue += currentHeight;
		}

		int resultValue = 0;

		int leftMaxHeight = 0;
		for (int i = 0; i < maxHeightIndex; i++)
		{
			int currentHeight = height[i];
			leftMaxHeight = std::max(currentHeight, leftMaxHeight);
			resultValue += leftMaxHeight;
		}
		int rightMaxHeight = 0;
		for (int i = static_cast<int>(height.size() - 1); i >= maxHeightIndex; i--)
		{
			int currentHeight = height[i];
			rightMaxHeight = std::max(currentHeight, rightMaxHeight);
			resultValue += rightMaxHeight;
		}

		return resultValue - elevationValue;
	}

	// From leetcode solution: Dynamic Programming.
	static int trap_3(std::vector<int> height)
	{
		using std::vector;
		using std::max;
		using std::min;

		if (height.empty())
			return 0;
		int ans = 0;
		int size = static_cast<int>(height.size());
		vector<int> left_max(size), right_max(size);
		left_max[0] = height[0];
		for (int i = 1; i < size; i++) {
			left_max[i] = max(height[i], left_max[i - 1]);
		}
		right_max[size - 1] = height[size - 1];
		for (int i = size - 2; i >= 0; i--) {
			right_max[i] = max(height[i], right_max[i + 1]);
		}
		for (int i = 1; i < size - 1; i++) {
			ans += min(left_max[i], right_max[i]) - height[i];
		}
		return ans;
	}

	// From leetcode solution: Using stacks.
	static int trap_4(std::vector<int> height)
	{
		using std::stack;
		using std::min;

		int ans = 0, current = 0;
		stack<int> st;
		while (current < static_cast<int>(height.size())) {
			while (!st.empty() && height[current] > height[st.top()]) {
				int top = st.top();
				st.pop();
				if (st.empty())
					break;
				int distance = current - st.top() - 1;
				int bounded_height = min(height[current], height[st.top()]) - height[top];
				ans += distance * bounded_height;
			}
			st.push(current++);
		}
		return ans;
	}

	// From leetcode solution: Using 2 pointers.
	static int trap_5(std::vector<int> height)
	{
		int left = 0, right = static_cast<int>(height.size() - 1);
		int ans = 0;
		int left_max = 0, right_max = 0;
		while (left < right) {
			if (height[left] < height[right]) {
				height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
				++left;
			}
			else {
				height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
				--right;
			}
		}
		return ans;
	}

public:
	std::string GetName() const
	{
		return "Trapping Rain Water";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<int, std::vector<int>> checker(
			[](std::vector<int> height)
			{
				return StringTools::GetVectorString(height);
			},
			[](int output)
			{
				return std::to_string(output);
			},
				[](int output, int answer)
			{
				return output == answer;
			});

		checker.AddFunction(trap_0);
		checker.AddFunction(trap_1);
		checker.AddFunction(trap_2);
		checker.AddFunction(trap_3);
		checker.AddFunction(trap_4);
		checker.AddFunction(trap_5);

		checker.CheckAnswer({ 0,1,0,2,1,0,1,3,2,1,2,1 }, 6);
		checker.CheckAnswer({ 4,2,0,3,2,5 }, 9);

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
