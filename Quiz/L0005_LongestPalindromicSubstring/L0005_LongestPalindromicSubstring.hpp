#include "../TestEngine.hpp"

class L0005_LongestPalindromicSubstring : public ITestable
{
private:
	static std::string longestPalindrome_0(std::string s)
	{
		if (s.empty())
		{
			return "";
		}

		size_t resultLeft = 0;
		size_t reusltSize = 1;

		size_t left = 0;
		size_t maxRight = s.length() - 1;
		while (left <= maxRight)
		{
			size_t right = maxRight;
			while (right > left)
			{
				if (s[left] == s[right])
				{
					size_t tempLeft = left;
					size_t tempRight = right;

					bool isFound = true;
					while (tempLeft < tempRight)
					{
						if (s[tempLeft] != s[tempRight])
						{
							isFound = false;
							break;
						}
						tempLeft++;
						tempRight--;
					}
					if (isFound)
					{
						size_t foundSize = right - left + 1;
						if (foundSize > reusltSize)
						{
							resultLeft = left;
							reusltSize = foundSize;
						}
						break;
					}
				}
				right--;
				if ((right - left) < reusltSize)
				{
					break;
				}
			}

			left++;
			if ((maxRight - left) < reusltSize)
			{
				break;
			}
		}

		return s.substr(resultLeft, reusltSize);
	}

	static std::string longestPalindrome_1(std::string s)
	{
		const int sLength = static_cast<int>(s.length());

		auto GetLength = [&s, &sLength](int l, int r)
		{
			while (l >= 0 && r < sLength && s[l] == s[r])
			{
				l--;
				r++;
			}
			return r - l - 1;
		};

		int resultLength = 0;
		int resultStart = 0;
		for (int i = 0; i < sLength; i++)
		{
			int getLength = std::max(GetLength(i, i), GetLength(i, i + 1));
			if (getLength > resultLength)
			{
				resultLength = getLength;
				resultStart = i - (getLength - 1) / 2;
			}
		}
		return s.substr(resultStart, resultLength);
	}

	static std::string longestPalindrome_2(std::string s)
	{
		// Manacher's algorithm.

		std::string Sa;
		std::vector<int> PalindromeRadii;
		{
			std::stringstream ss;
			for (auto c : s)
			{
				ss << '|' << c;
			}
			ss << '|';
			Sa = ss.str();
			PalindromeRadii.assign(Sa.length(), 0);
		}

		int Center = 0;
		int Radius = 0;

		int maxValueIndexInPalindromeRadii = 0;

		while (Center < Sa.length())
		{
			while (Center - (Radius + 1) >= 0 && Center + (Radius + 1) < Sa.length() && Sa[Center - (Radius + 1)] == Sa[Center + (Radius + 1)])
			{
				Radius = Radius + 1;
			}

			PalindromeRadii[Center] = Radius;
			if (PalindromeRadii[Center] > PalindromeRadii[maxValueIndexInPalindromeRadii])
			{
				maxValueIndexInPalindromeRadii = Center;
			}

			int OldCenter = Center;
			int	OldRadius = Radius;
			Center = Center + 1;
			Radius = 0;

			while (Center <= OldCenter + OldRadius)
			{
				int MirroredCenter = OldCenter - (Center - OldCenter);
				int MaxMirroredRadius = OldCenter + OldRadius - Center;
				if (PalindromeRadii[MirroredCenter] < MaxMirroredRadius)
				{
					PalindromeRadii[Center] = PalindromeRadii[MirroredCenter];
					if (PalindromeRadii[Center] > PalindromeRadii[maxValueIndexInPalindromeRadii])
					{
						maxValueIndexInPalindromeRadii = Center;
					}
					Center = Center + 1;
				}
				else if (PalindromeRadii[MirroredCenter] > MaxMirroredRadius)
				{
					PalindromeRadii[Center] = MaxMirroredRadius;
					if (PalindromeRadii[Center] > PalindromeRadii[maxValueIndexInPalindromeRadii])
					{
						maxValueIndexInPalindromeRadii = Center;
					}
					Center = Center + 1;
				}
				else
				{
					Radius = MaxMirroredRadius;
					break;
				}
			}
		}

		int targetIndex = (maxValueIndexInPalindromeRadii - 1) / 2;
		int radius = (PalindromeRadii[maxValueIndexInPalindromeRadii] - 1) / 2;

		return s.substr(targetIndex - radius, PalindromeRadii[maxValueIndexInPalindromeRadii]);
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::string, std::string> checker(
			[](std::string input)
			{
				return input;
			},
			[](std::string output)
			{
				return StringTools::Replace(output, "_", ", ");
			},
				[](std::string output, std::string answer)
			{
				std::vector<std::string> answerList = StringTools::SplitString(answer, "_");
				for (const std::string& subAnswer : answerList)
				{
					if (output.compare(subAnswer) == 0)
					{
						return true;
					}
				}
				return false;
			});

		checker.AddFunction(longestPalindrome_0);
		checker.AddFunction(longestPalindrome_1);
		checker.AddFunction(longestPalindrome_2);

		checker.CheckAnswer("babad", "bab_aba");
		checker.CheckAnswer("abaxabaxabb", "baxabaxab");
		checker.CheckAnswer("opocdbbdcaasd", "cdbbdc");
		checker.CheckAnswer("cbbd", "bb");
		checker.CheckAnswer("a", "a");
		checker.CheckAnswer("ac", "a_c");
		std::string oneThousandB(1000, 'b');
		checker.CheckAnswer(oneThousandB, oneThousandB);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
