#include "../TestEngine.hpp"

class L0004_MedianOfTwoSortedArrays : public ITestable
{
private:
	static double findMedianSortedArrays_0(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		auto isOdd = [](int x)
		{
			return x & 1;
		};

		std::vector<int>* pM = &nums1;
		std::vector<int>* pN = &nums2;
		if (nums1.size() > nums2.size())
		{
			pM = &nums2;
			pN = &nums1;
		}
		std::vector<int>& m = *pM;
		std::vector<int>& n = *pN;

		int mSize = static_cast<int>(m.size());
		int nSize = static_cast<int>(n.size());
		int totalSize = mSize + nSize;

		if (mSize == 0)
		{
			int index = (totalSize - 1) / 2;
			return isOdd(totalSize) ? n[index] : (n[index] + n[index + 1]) / 2.0;
		}

		int jPlus = (totalSize + 1) / 2 - 2;

		int left = 0;
		int right = mSize - 1;
		while (true)
		{
			int i1 = (left + right) / 2;
			int j1 = jPlus - i1;
			int i2 = i1 + 1;
			int j2 = j1 + 1;

			int m1 = m[i1];
			int n2 = n[j2];
			if (m1 > n2)
			{
				right = i1 - 1;
				if (right < 0)
				{
					int index = (totalSize - 1) / 2;
					return isOdd(totalSize) ? n[index] : (n[index] + ((index + 1) >= nSize ? m[0] : std::min(n[index + 1], m[0]))) / 2.0;
				}
			}
			else
			{
				if (j1 < 0)
				{
					return isOdd(totalSize) ? std::max(m1, n2) : (m1 + n2) / 2.0;
				}
				else
				{
					int n1 = n[j1];
					if (i2 >= mSize)
					{
						double value1 = std::max(m1, n1);
						return isOdd(totalSize) ? value1 : (value1 + std::max(std::min(m1, n1), n2)) / 2.0;
					}
					else
					{
						int m2 = m[i2];

						if (n1 > m2)
						{
							left = i2;
							if (left >= mSize)
							{
								size_t index = (totalSize - 1) / 2 - mSize;
								return isOdd(totalSize) ? n[index] : (n[index] + n[index + 1]) / 2.0;
							}
						}
						else
						{
							double value1 = std::max(m1, n1);
							return isOdd(totalSize) ? value1 : (value1 + std::min(m2, n2)) / 2.0;
						}
					}
				}
			}
		}

		return 0.0;
	}

	// by osydunenko, C++: very simple & short, 20 ms, faster than 93.88%.
	static double findMedianSortedArrays_1(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		nums1.reserve(nums1.size() + nums2.size());
		move(nums2.begin(), nums2.end(), back_inserter(nums1));

		std::inplace_merge(nums1.begin(), next(nums1.begin(), nums1.size() - nums2.size()), nums1.end());

		if (nums1.size() % 2 != 0) {
			return nums1[nums1.size() / 2];
		}

		return (nums1[nums1.size() / 2 - 1] + nums1[nums1.size() / 2]) / 2.0;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<double, std::vector<int>&, std::vector<int>&> checker(
			[](std::vector<int>& nums1, std::vector<int>& nums2)
			{
				return StringTools::GetItemListString<std::vector<int>>({ &nums1 , &nums2 }, [](const std::vector<int>& nums)
					{
						return StringTools::GetVectorString(nums);
					});
			},
			[](double output)
			{
				return std::to_string(output);
			},
				[](double output, double answer)
			{
				return std::abs(output - answer) < DBL_EPSILON;
			});
		checker.AddFunction(findMedianSortedArrays_0);
		checker.AddFunction(findMedianSortedArrays_1);

		std::vector<int> nums1;
		std::vector<int> nums2;

		nums1.assign({ 3 });
		nums2.assign({ 1, 2, 4 });
		checker.CheckAnswer(nums1, nums2, 2.5);

		nums1.assign({ 3 });
		nums2.assign({ -2, -1 });
		checker.CheckAnswer(nums1, nums2, -1.0);

		nums1.assign({ 1, 3 });
		nums2.assign({ 2, 7 });
		checker.CheckAnswer(nums1, nums2, 2.5);

		nums1.assign({ 1, 2, 6 ,8 , 9 });
		nums2.assign({ 0, 3, 4, 5, 7, 10 });
		checker.CheckAnswer(nums1, nums2, 5.0);

		nums1.assign({ 1, 3 });
		nums2.assign({ 2 });
		checker.CheckAnswer(nums1, nums2, 2.0);

		nums1.assign({ 1, 2 });
		nums2.assign({ 3, 4 });
		checker.CheckAnswer(nums1, nums2, 2.5);

		nums1.assign({ 0, 0 });
		nums2.assign({ 0, 0 });
		checker.CheckAnswer(nums1, nums2, 0.0);

		nums1.assign({});
		nums2.assign({ 1 });
		checker.CheckAnswer(nums1, nums2, 1.0);

		nums1.assign({ 2 });
		nums2.assign({  });
		checker.CheckAnswer(nums1, nums2, 2.0);

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
