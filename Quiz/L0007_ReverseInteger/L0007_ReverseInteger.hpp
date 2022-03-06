#include "../TestEngine.hpp"

class L0007_ReverseInteger : public ITestable
{
private:
	static int reverse_0(int x)
	{
		bool isNegative = x < 0;
		std::string str = std::to_string(std::abs(x));

		std::reverse(str.begin(), str.end());

		int maxInt32Length = 10;
		if (str.length() >= maxInt32Length)
		{
			if (str.length() == maxInt32Length)
			{
				std::string maxStr = std::to_string(INT32_MAX);
				bool isDanger = true;
				for (int i = 0; i < maxInt32Length - 1; i++)
				{
					if (str[i] > maxStr[i])
					{
						return 0;
					}
					else if (str[i] < maxStr[i])
					{
						isDanger = false;
						break;
					}
				}
				if (isDanger)
				{
					char maxValue = isNegative ? '8' : '7';
					if (str[maxInt32Length - 1] > maxValue)
					{
						return 0;
					}
				}
			}
			else
			{
				return 0;
			}
		}

		return std::atoi(str.c_str()) * (isNegative ? -1 : 1);
	}

	static int reverse_1(int x)
	{
		int rev = 0;
		while (x != 0) {
			int pop = x % 10;
			x /= 10;
			if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
			if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
			rev = rev * 10 + pop;
		}
		return rev;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<int, int> checker(
			[](int x)
			{
				return std::to_string(x);
			},
			[](int output)
			{
				return std::to_string(output);
			},
				[](int output, int answer)
			{
				return output == answer;
			});
		checker.AddFunction(reverse_0);
		checker.AddFunction(reverse_1);

		checker.CheckAnswer(1463847412, 2147483641);
		checker.CheckAnswer(1534236469, 0);
		checker.CheckAnswer(123, 321);
		checker.CheckAnswer(-123, -321);
		checker.CheckAnswer(120, 21);
		checker.CheckAnswer(0, 0);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
