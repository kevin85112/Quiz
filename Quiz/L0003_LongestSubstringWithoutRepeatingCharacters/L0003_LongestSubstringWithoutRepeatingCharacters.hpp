#include "../TestEngine.hpp"

class L0003_LongestSubstringWithoutRepeatingCharacters : public ITestable
{
private:
	static int lengthOfLongestSubstring_0(std::string s)
	{
		int result = 0;
		const char* pStart = s.c_str();
		const char* pEnd = pStart;
		for (size_t i = 0; i < s.size(); i++)
		{
			pEnd++;
			for (const char* pCheck = pStart; pCheck < pEnd; pCheck++)
			{
				if (*pCheck == *pEnd)
				{
					int length = static_cast<int>(pEnd - pStart);
					if (length > result)
					{
						result = length;
					}
					pStart = pCheck + 1;
					break;
				}
			}
		}

		int length = static_cast<int>(pEnd - pStart);
		if (length > result)
		{
			result = length;
		}
		return result;
	}

	static int lengthOfLongestSubstring_1(std::string s)
	{
		int result = 0;
		int left = 0;
		std::map<char, int> substringCollector;
		const char* pChar = s.c_str();
		for (size_t right = 0; right < s.size(); right++)
		{
			auto findIterator = substringCollector.find(*pChar);
			if (findIterator != substringCollector.end())
			{
				int length = static_cast<int>(right - left);
				result = std::max(result, length);
				left = std::max(left, findIterator->second + 1);
			}
			substringCollector[*pChar] = static_cast<int>(right);
			pChar++;
		}
		int length = static_cast<int>(s.size() - left);
		result = std::max(result, length);
		return result;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<int, std::string> checker(
			[](std::string input)
			{
				return input;
			},
			[](int output)
			{
				return std::to_string(output);
			},
				[](int output, int answer)
			{
				return output == answer;
			});

		checker.AddFunction(lengthOfLongestSubstring_0);
		checker.AddFunction(lengthOfLongestSubstring_1);

		checker.CheckAnswer("abcabcbb", 3);
		checker.CheckAnswer("bbbbb", 1);
		checker.CheckAnswer("", 0);
		checker.CheckAnswer("dvdf", 3);
		checker.CheckAnswer("abba", 2);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
