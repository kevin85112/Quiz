#include "../TestEngine.hpp"

class L0008_StringToInteger : public ITestable
{
private:
	static int myAtoi_0(std::string s)
	{
		int l = 0;
		int r = static_cast<int>(s.length()) - 1;
		bool isNegative = false;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				l = i;
				break;
			}
		}

		if (s[l] == '+')
		{
			l += 1;
		}
		else if (s[l] == '-')
		{
			isNegative = true;
			l += 1;
		}

		while (s[l] == '0')
		{
			l += 1;
		}

		if (!isdigit(s[l]))
		{
			return 0;
		}

		for (int i = l + 1; i < s.length(); i++)
		{
			if (!isdigit(s[i]))
			{
				r = i - 1;
				break;
			}
		}

		bool isOutOfRange = false;
		int size = r - l + 1;
		if (size > 10)
		{
			isOutOfRange = true;
		}
		else if (size == 10)
		{
			std::string maxString = std::to_string(INT_MAX);
			bool isDanger = true;
			for (size_t i = 0; i < maxString.length() - 1; i++)
			{
				char currentMaxChar = maxString[i];
				char sChar = s[l + i];
				if (sChar > currentMaxChar)
				{
					isOutOfRange = true;
					break;
				}
				else if (sChar != currentMaxChar)
				{
					isDanger = false;
					break;
				}
			}
			if (!isOutOfRange && isDanger)
			{
				isOutOfRange = isNegative ? (s[l + 9] > '7') : (s[l + 9] > '6');
			}
		}

		if (isOutOfRange)
		{
			return isNegative ? INT_MIN : INT_MAX;
		}

		return std::atoi(s.substr(l, size).c_str()) * (isNegative ? -1 : 1);
	}

	static int myAtoi_1(std::string s)
	{
		int start = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != ' ')
			{
				start = i;
				break;
			}
		}

		int negativeNumber = 1;
		if (s[start] == '-')
		{
			negativeNumber = -1;
			start += 1;
		}
		else if (s[start] == '+')
		{
			start += 1;
		}

		while (s[start] == '0')
		{
			start += 1;
		}

		int result = 0;
		for (int i = start, currentTime = 0; i < s.length(); i++, currentTime++)
		{
			char currentChar = s[i];
			if (isdigit(currentChar))
			{
				if (currentTime >= 10)
				{
					return negativeNumber == -1 ? INT32_MIN : INT32_MAX;
				}

				int currentNumber = static_cast<int>(currentChar - '0');
				if (currentTime == 9)
				{
					bool isOutOfRange = false;
					int maxNumber = ((negativeNumber == -1 ? INT32_MIN : INT32_MAX) / 10) * negativeNumber;
					if (result > maxNumber)
					{
						isOutOfRange = true;
					}
					else if (result == maxNumber)
					{
						int currentMaxNumber = ((negativeNumber == -1 ? INT32_MIN : INT32_MAX) % 10) * negativeNumber;
						if (currentNumber >= currentMaxNumber)
						{
							isOutOfRange = true;
						}
					}
					if (isOutOfRange)
					{
						return negativeNumber == -1 ? INT32_MIN : INT32_MAX;
					}
				}

				result = 10 * result + (currentChar - '0');
			}
			else
			{
				break;
			}
		}

		return result * negativeNumber;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<int, std::string> checker(
			[](std::string s)
			{
				return s;
			},
			[](int output)
			{
				return std::to_string(output);
			},
				[](int output, int answer)
			{
				return output == answer;
			});
		checker.AddFunction(myAtoi_0);
		checker.AddFunction(myAtoi_1);

		checker.CheckAnswer("-2147483648", -2147483648);
		checker.CheckAnswer("-000000000000001", -1);
		checker.CheckAnswer("  0000000000012345678", 12345678);
		checker.CheckAnswer("42", 42);
		checker.CheckAnswer("   -42", -42);
		checker.CheckAnswer("4193 with words", 4193);
		checker.CheckAnswer("words and 987", 0);
		checker.CheckAnswer("-91283472332", -2147483648);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
