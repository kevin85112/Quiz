#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "TestEngine.hpp"
#include "FlippingTheMatrix/FlippingTheMatrix.hpp"
#include "L0001_TwoSum/L0001_TwoSum.hpp"
#include "L0002_AddTwoNumbers/L0002_AddTwoNumbers.hpp"
#include "L0042_TrappingRainWater/L0042_TrappingRainWater.hpp"
#include "L0056_MergeIntervals/L0056_MergeIntervals.hpp"
#include "L0146_LRUCache/L0146_LRUCache.hpp"
#include "L0207_CourseSchedule/L0207_CourseSchedule.hpp"
#include "L0210_CourseScheduleII/L0210_CourseScheduleII.hpp"
#include "L0986_IntervalListIntersections/L0986_IntervalListIntersections.hpp"
#include "L1828_QueriesOnNumberOfPointsInsideACircle/L1828_QueriesOnNumberOfPointsInsideACircle.hpp"

int main()
{
	std::cout << "---- Start ----" << std::endl;

	std::vector<std::shared_ptr<ITestable>> testList
	{
		std::make_shared<FlippingTheMatrix>(),
		std::make_shared<L0001_TwoSum>(),
		std::make_shared<L0002_AddTwoNumbers>(),
		std::make_shared<L0042_TrappingRainWater>(),
		std::make_shared<L0056_MergeIntervals>(),
		std::make_shared<L0146_LRUCache>(),
		std::make_shared<L0207_CourseSchedule>(),
		std::make_shared<L0210_CourseScheduleII>(),
		std::make_shared<L0986_IntervalListIntersections>(),
		std::make_shared<L1828_QueriesOnNumberOfPointsInsideACircle>()
	};

	std::sort(testList.begin(), testList.end(), [](std::shared_ptr<ITestable> pTest1, std::shared_ptr<ITestable> pTest2) -> bool
		{
			std::string testName1 = typeid(*pTest1).name();
			std::string testName2 = typeid(*pTest2).name();
			return testName1.compare(testName2) < 0;
		});

	size_t maxNameLength = 0;
	for (std::shared_ptr<ITestable> pTest : testList)
	{
		std::string testName = typeid(*pTest).name();
		maxNameLength = std::max(maxNameLength, testName.size());
	}

	std::vector<std::string> errorMessageList(testList.size());
	for (size_t index = 0; index < testList.size(); index++)
	{
		ITestable& test = *testList[index];
		std::string testName = typeid(test).name();
		bool isSuccess = test.Test(&errorMessageList[index]);
		std::cout << "- Test " << index << " \"" << std::left << std::setw(maxNameLength) << testName << "\": " << (isSuccess ? "Pass" : "Fail") << std::endl;
	}

	for (size_t index = 0; index < testList.size(); index++)
	{
		const std::string& errorMessage = errorMessageList[index];
		if (!errorMessage.empty())
		{
			std::string testName = typeid(*testList[index]).name();
			std::cout << "\n- Test " << index << " \"" << testName << "\" error message:\n" << errorMessage << std::endl;
		}
	}

	std::cout << "---- End ----" << std::endl;
}
