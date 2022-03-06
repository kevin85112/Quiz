#include "../TestEngine.hpp"

class L0009_PalindromeNumber : public ITestable
{
private:
	static bool isPalindrome_0(int x)
	{
		if (x < 0)
		{
			return false;
		}

		std::string s = std::to_string(x);

		auto l = s.begin();
		auto r = s.end() - 1;

		while (l < r)
		{
			if (*l != *r)
			{
				return false;
			}
			l++;
			r--;
		}

		return true;
	}

	static bool isPalindrome_1(int x)
	{
		if (x < 0)
		{
			return false;
		}

		float countValue = 10;
		int targetValue = 0;
		int currentValue = x;
		while (countValue <= x)
		{
			targetValue = targetValue * 10 + currentValue % 10;
			currentValue /= 10;
			countValue *= 100;
		}
		if (countValue / 10 <= x)
		{
			currentValue /= 10;
		}

		return targetValue == currentValue;
	}

	static bool isPalindrome_2(int x)
	{
		// Special cases:
		// As discussed above, when x < 0, x is not a palindrome.
		// Also if the last digit of the number is 0, in order to be a palindrome,
		// the first digit of the number also needs to be 0.
		// Only 0 satisfy this property.
		if (x < 0 || (x % 10 == 0 && x != 0)) {
			return false;
		}

		int revertedNumber = 0;
		while (x > revertedNumber) {
			revertedNumber = revertedNumber * 10 + x % 10;
			x /= 10;
		}

		// When the length is an odd number, we can get rid of the middle digit by revertedNumber/10
		// For example when the input is 12321, at the end of the while loop we get x = 12, revertedNumber = 123,
		// since the middle digit doesn't matter in palidrome(it will always equal to itself), we can simply get rid of it.
		return x == revertedNumber || x == revertedNumber / 10;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<bool, int> checker(
			[](int x)
			{
				return std::to_string(x);
			},
			[](bool output)
			{
				return output ? "true" : "false";
			},
				[](bool output, bool answer)
			{
				return output == answer;
			});

		checker.AddFunction(isPalindrome_0);
		checker.AddFunction(isPalindrome_1);
		checker.AddFunction(isPalindrome_2);

		checker.CheckAnswer(0, true);
		checker.CheckAnswer(10, false);
		checker.CheckAnswer(6514156, true);
		checker.CheckAnswer(65141567, false);
		checker.CheckAnswer(121, true);
		checker.CheckAnswer(-121, false);
		checker.CheckAnswer(-101, false);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
