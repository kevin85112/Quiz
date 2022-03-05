#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "TestEngine.hpp"
#include "FlippingTheMatrix/FlippingTheMatrix.hpp"
#include "QueriesOnNumberOfPointsInsideACircle/QueriesOnNumberOfPointsInsideACircle.hpp"
#include "TrappingRainWater/TrappingRainWater.hpp"
#include "IntervalListIntersections/IntervalListIntersections.hpp"
#include "LRUCache/LRUCache.hpp"
#include "CourseSchedule/CourseSchedule.hpp"
#include "CourseScheduleII/CourseScheduleII.hpp"
#include "MergeIntervals/MergeIntervals.hpp"

int main()
{
	std::vector<std::shared_ptr<ITestable>> testList
	{
		std::make_shared<FlippingTheMatrix>(),
		std::make_shared<QueriesOnNumberOfPointsInsideACircle>(),
		std::make_shared<TrappingRainWater>(),
		std::make_shared<IntervalListIntersections>(),
		std::make_shared<LRUCache>(),
		std::make_shared<CourseSchedule>(),
		std::make_shared<CourseScheduleII>(),
		std::make_shared<MergeIntervals>(),
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
