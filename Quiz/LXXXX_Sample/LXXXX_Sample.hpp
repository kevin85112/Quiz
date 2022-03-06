#include "../TestEngine.hpp"

class Sample : public ITestable
{
private:
	static int method_0(std::vector<int> input)
	{
		return 0;
	}

public:
	std::string GetName() const
	{
		return "Sample";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<int, std::vector<int>> checker(
			[](std::vector<int> input)
			{
				return StringTools::GetVectorString(input);
			},
			[](int output)
			{
				return std::to_string(output);
			},
				[](int output, int answer)
			{
				return output == answer;
			});

		checker.AddFunction(method_0);
	
		checker.CheckAnswer({ 0,1,0,2,1,0,1,3,2,1,2,1 }, 6);

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
