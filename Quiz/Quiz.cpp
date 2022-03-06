#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "TestEngine.hpp"
#include "FlippingTheMatrix/FlippingTheMatrix.hpp"
#include "L0001_TwoSum/L0001_TwoSum.hpp"
#include "L0042_TrappingRainWater/L0042_TrappingRainWater.hpp"
#include "L0056_MergeIntervals/L0056_MergeIntervals.hpp"
#include "L0146_LRUCache/L0146_LRUCache.hpp"
#include "L0207_CourseSchedule/L0207_CourseSchedule.hpp"
#include "L0210_CourseScheduleII/L0210_CourseScheduleII.hpp"
#include "L0986_IntervalListIntersections/L0986_IntervalListIntersections.hpp"
#include "L1828_QueriesOnNumberOfPointsInsideACircle/L1828_QueriesOnNumberOfPointsInsideACircle.hpp"

int main()
{
	std::vector<std::shared_ptr<ITestable>> testList
	{
		std::make_shared<FlippingTheMatrix>(),
		std::make_shared<L0001_TwoSum>(),
		std::make_shared<L0042_TrappingRainWater>(),
		std::make_shared<L0056_MergeIntervals>(),
		std::make_shared<L0146_LRUCache>(),
		std::make_shared<L0207_CourseSchedule>(),
		std::make_shared<L0210_CourseScheduleII>(),
		std::make_shared<L0986_IntervalListIntersections>(),
		std::make_shared<L1828_QueriesOnNumberOfPointsInsideACircle>()
	};

	std::cout << "---- Start ----" << std::endl;
	for (size_t index = 0; index < testList.size(); index++)
	{
		ITestable& test = *testList[index];
		std::cout << "\n---- Test " << index << " \"" << test.GetName() << "\" ----" << std::endl;
		std::string errorMessage;
		bool isSuccess = test.Test(&errorMessage);
		if (!errorMessage.empty())
		{
			std::cout << "Error message:\n{\n" << errorMessage << "}" << std::endl;
		}
		std::cout << "\nResult: " << (isSuccess ? "True" : "False") << std::endl;
		std::cout << "---- End test " << index << " \"" << test.GetName() << "\" ----" << std::endl;
	}
	std::cout << "\n---- End ----" << std::endl;
	std::cin;
}
