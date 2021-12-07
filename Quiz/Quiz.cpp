#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "TestEngine.hpp"
#include "FlippingTheMatrix/FlippingTheMatrix.hpp"
#include "QueriesOnNumberOfPointsInsideACircle/QueriesOnNumberOfPointsInsideACircle.hpp"
#include "TrappingRainWater/TrappingRainWater.hpp"

int main()
{
	std::vector<std::shared_ptr<ITestable>> testList
	{
		std::make_shared<FlippingTheMatrix>(),
		std::make_shared<QueriesOnNumberOfPointsInsideACircle>(),
		std::make_shared<TrappingRainWater>(),
	};

	std::cout << "---- Start ----" << std::endl;
	for (size_t index = 0; index < testList.size(); index++)
	{
		ITestable& test = *testList[index];
		std::cout << "\n---- Test " << index << " \"" << test.GetName() << "\" ----" << std::endl;
		std::string errorMessage;
		bool isSuccess = test.Test(&errorMessage);
		std::cout << "Result: " << (isSuccess ? "True" : "False") << std::endl;
		if (!errorMessage.empty())
		{
			std::cout << "Error message:\n{\n" << errorMessage << "}" << std::endl;
		}
		std::cout << "---- End test " << index << " \"" << test.GetName() << "\" ----" << std::endl;
	}
	std::cout << "\n---- End ----" << std::endl;
	std::cin;
}
