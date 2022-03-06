#include "../TestEngine.hpp"

class L0010_RegularExpressionMatching : public ITestable
{
private:
	static bool isMatch(std::string s, std::string p)
	{
		if (s.empty() && p.empty())
		{
			return true;
		}

		int np = static_cast<int>(p.length() - 1);
		int ns = static_cast<int>(s.length() - 1);
		while (np >= 0)
		{
			if (p[np] == '*')
			{
				np -= 2;
			}
			else
			{
				std::string lp(p, 0, np);
				std::string rp(p, np + 1, p.length() - np);
				while (ns >= 0)
				{
					if (p[np] == s[ns] || p[np] == '.')
					{
						std::string ls(s, 0, ns);
						std::string rs(s, ns + 1, s.length() - ns);
						if (isMatch(rs, rp) && isMatch(ls, lp))
						{
							return true;
						}
					}
					ns -= 1;
				}
				return false;
			}
		}

		np = static_cast<int>(p.length() - 1) - 1;
		while (np >= 0 && ns >= 0)
		{
			char starChar = p[np];

			if (starChar == '.')
			{
				return true;
			}

			while (ns >= 0 && s[ns] == starChar)
			{
				ns--;
				if (ns < 0)
				{
					return true;
				}
			}

			np -= 2;
		}

		return ns < 0;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<bool, std::string, std::string> checker(
			[](std::string s, std::string p)
			{
				std::stringstream ss;
				ss << std::endl << "\ts: " << s << std::endl << "\tp: " << p << std::endl;
				return ss.str();
			},
			[](bool output)
			{
				return output ? "true" : "false";
			},
				[](bool output, bool answer)
			{
				return output == answer;
			});

		checker.AddFunction(isMatch);

		checker.CheckAnswer("bab", "..*", true);
		checker.CheckAnswer("a", ".*..a", false);
		checker.CheckAnswer("aaa", ".a", false);
		checker.CheckAnswer("aaa", "aaaa", false);
		checker.CheckAnswer("aaa", "ab*ac*a", true);
		checker.CheckAnswer("mississippi", "mis*is*ip*.", true);
		checker.CheckAnswer("ab", ".*", true);
		checker.CheckAnswer("aaa", "ab*a*c*a", true);
		checker.CheckAnswer("aaa", "a*a", true);
		checker.CheckAnswer("aa", "a", false);
		checker.CheckAnswer("aa", "a*", true);
		checker.CheckAnswer("aab", "c*a*b", true);
		checker.CheckAnswer("mississippi", "mis*is*p*.", false);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
