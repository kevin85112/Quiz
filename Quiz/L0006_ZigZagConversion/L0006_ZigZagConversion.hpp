#include "../TestEngine.hpp"

class L0006_ZigZagConversion : public ITestable
{
private:
	class CharNode
	{
	public:
		char Char;
		CharNode* pSibling;

		CharNode()
		{
			Char = 0;
			pSibling = nullptr;
		}
		CharNode(char c) : CharNode()
		{
			Char = c;
		}
	};

	static std::string convert_0(std::string s, int numRows)
	{
		if (s.length() <= numRows || numRows <= 1)
		{
			return s;
		}

		std::vector<CharNode*> nodes(numRows, nullptr);
		std::vector<CharNode*> rightmostNodes(numRows, nullptr);

		int currentRow = 0;
		int maxRow = numRows - 1;
		bool isDown = true;
		for (char c : s)
		{
			CharNode*& pNode = rightmostNodes[currentRow];
			if (pNode == nullptr)
			{
				pNode = new CharNode(c);
				nodes[currentRow] = pNode;
			}
			else
			{
				pNode->pSibling = new CharNode(c);
				pNode = pNode->pSibling;
			}

			currentRow = isDown ? currentRow + 1 : currentRow - 1;
			if (currentRow == maxRow || currentRow == 0)
			{
				isDown = !isDown;
			}
		}

		std::stringstream result;
		for (CharNode* pNode : nodes)
		{
			do
			{
				result << pNode->Char;
				auto pTempNode = pNode;
				pNode = pNode->pSibling;
				delete pTempNode;
			} while (pNode != nullptr);
		}

		return result.str();
	}

	static std::string convert_1(std::string s, int numRows)
	{
		int sLength = static_cast<int>(s.length());

		if (numRows <= 1 || sLength <= numRows)
		{
			return s;
		}

		std::string result;

		int f1 = numRows + numRows - 2;
		for (int i = 0; i < sLength; i += f1)
		{
			result += s[i];
		}
		for (int i = 1; i < numRows - 1; i++)
		{
			int v2 = -i - i;
			int v1 = f1 + v2;
			v2 += v1;

			for (int j = i; j < sLength;)
			{
				result += s[j];
				j += v1;
				v1 += (v2 *= -1);
			}
		}
		for (int i = numRows - 1; i < sLength; i += f1)
		{
			result += s[i];
		}

		return result;
	}

	static std::string convert_2(std::string s, int numRows)
	{
		if (numRows == 1) return s;

		std::vector<std::string> rows(std::min(numRows, int(s.size())));
		int curRow = 0;
		bool goingDown = false;

		for (char c : s) {
			rows[curRow] += c;
			if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
			curRow += goingDown ? 1 : -1;
		}

		std::string ret;
		for (std::string row : rows) ret += row;
		return ret;
	}

	static std::string convert_3(std::string s, int numRows)
	{
		if (numRows == 1) return s;

		std::string ret;
		int n = static_cast<int>(s.size());
		int cycleLen = 2 * numRows - 2;

		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j + i < n; j += cycleLen)
			{
				ret += s[j + i];
				if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
				{
					ret += s[j + cycleLen - i];
				}
			}
		}
		return ret;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::string, std::string, int> checker(
			[](std::string s, int numRows)
			{
				return s;
			},
			[](std::string output)
			{
				return output;
			},
				[](std::string output, std::string answer)
			{
				return output.compare(answer) == 0;
			});

		checker.AddFunction(convert_0);
		checker.AddFunction(convert_1);
		checker.AddFunction(convert_2);
		checker.AddFunction(convert_3);
	
		checker.CheckAnswer("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
		checker.CheckAnswer("PAYPALISHIRING", 4, "PINALSIGYAHRPI");
		checker.CheckAnswer("A", 1, "A");
		checker.CheckAnswer("AB", 1, "AB");

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
