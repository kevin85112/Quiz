#include "../TestEngine.hpp"

class L0001_TwoSum : public ITestable
{
private:
	template <class T1, class T2>
	class IndexableBinaryTree
	{
	protected:
		class Node
		{
		public:
			std::unique_ptr<Node> pRight;
			std::unique_ptr<Node> pLeft;
			T1 Value;

			Node(T1 value)
			{
				Value = value;
			}

			void AppendNode(const std::vector<T2>& nums, T1 value)
			{
				std::unique_ptr<Node>* pChild{ &pRight };

				if (nums[value] < nums[Value])
				{
					pChild = &pLeft;
				}

				if (*pChild == nullptr)
				{
					pChild->reset(new Node(value));
				}
				else
				{
					(*pChild)->AppendNode(nums, value);
				}
			}

			T1* FindValue(const std::vector<T2>& nums, int value)
			{
				std::unique_ptr<Node>* pChild{ &pLeft };

				const T2& getValue{ nums[Value] };
				if (value > getValue)
				{
					pChild = &pRight;
				}
				else if (value == getValue)
				{
					return &Value;
				}

				if ((*pChild) != nullptr)
				{
					return (*pChild)->FindValue(nums, value);
				}
				return nullptr;
			}

			bool DFS(const std::vector<T2>& nums, const std::function<bool(const T1& index, const T2& value)> getNode) const
			{
				bool isContinue = getNode(Value, nums[Value]);
				if (isContinue)
				{
					for (Node* pNode : { pRight.get(),pLeft.get() })
					{
						if (pNode != nullptr)
						{
							if (!pNode->DFS(nums, getNode))
							{
								break;
							}
						}
					}
				}
				return isContinue;
			}
		};

		std::unique_ptr<Node> pRoot;
		const std::vector<T2>& nums;

		size_t _size;

	public:
		IndexableBinaryTree(const std::vector<T2>& Nums)
			: nums(Nums)
		{
			_size = 0;
		}
		void push(T1 value)
		{
			if (pRoot == nullptr)
			{
				pRoot.reset(new Node(value));
			}
			else
			{
				pRoot->AppendNode(nums, value);
			}
			_size += 1;
		}
		T1* find(int value) const
		{
			if (pRoot != nullptr)
			{
				return pRoot->FindValue(nums, value);
			}
			return nullptr;
		}
		bool empty() const
		{
			return pRoot == nullptr;
		}
		void DFS(const std::function<bool(const T1& index, const T2& value)> getNode) const
		{
			if (pRoot != nullptr)
			{
				pRoot->DFS(nums, getNode);
			}
		}
		size_t size()
		{
			return _size;
		}
	};

	template <class T1, class T2>
	static std::vector<T1>* FindPair(T2 target, const IndexableBinaryTree<T1, T2>& smallerTree, const IndexableBinaryTree<T1, T2>& largerTree)
	{
		std::unique_ptr<std::vector<T1>> pResult{ nullptr };
		smallerTree.DFS([&target, &largerTree, &pResult](const T1& index, const T2& value)
			{
				T2 targetLargerValue = target - value;
				T1* pFindIndex = largerTree.find(targetLargerValue);
				if (pFindIndex != nullptr)
				{
					pResult.reset(new std::vector<T1>{ index , *pFindIndex });
					return false;
				}

				return true;
			});
		return pResult.release();
	}

	static std::vector<int> twoSum_0(std::vector<int>& nums, int target)
	{
		IndexableBinaryTree<int, int> largerTree(nums);
		IndexableBinaryTree<int, int> negativeTree(nums);
		std::vector<int> zeroIndices;
		std::vector<int> targetIndices;
		IndexableBinaryTree<int, int> normalLargerTree(nums);
		IndexableBinaryTree<int, int> normalSmallerTree(nums);
		std::vector<int> halfTargetIndices;

		bool isReverseSign = target < 0;

		if (isReverseSign)
		{
			target = -target;
		}

		int halfTarget = target / 2;
		bool useHalfTargetIndices = target == halfTarget + halfTarget;

		for (int index = 0; index < static_cast<int>(nums.size()); index++)
		{
			if (isReverseSign)
			{
				nums[index] = -nums[index];
			}

			int value = nums[index];

			if (value > target)
			{
				largerTree.push(index);
			}
			else if (value < 0)
			{
				negativeTree.push(index);
			}
			else
			{
				if (value == target)
				{
					targetIndices.push_back(index);
				}

				if (value == 0)
				{
					zeroIndices.push_back(index);
				}
				else
				{
					if (useHalfTargetIndices && value == halfTarget)
					{
						halfTargetIndices.push_back(index);
					}
					else
					{
						if (value > halfTarget)
						{
							normalLargerTree.push(index);
						}
						else
						{
							normalSmallerTree.push(index);
						}
					}
				}
			}
		}

		if (!zeroIndices.empty())
		{
			if (target == 0)
			{
				if (zeroIndices.size() >= 2)
				{
					return std::vector<int>{zeroIndices[0], zeroIndices[1]};
				}
			}
			else if (!targetIndices.empty())
			{
				return std::vector<int>{zeroIndices[0], targetIndices[0]};
			}
		}
		if (halfTargetIndices.size() >= 2)
		{
			return std::vector<int>{halfTargetIndices[0], halfTargetIndices[1]};
		}

		for (std::pair<IndexableBinaryTree<int, int>*, IndexableBinaryTree<int, int>*> doPair :
			{ std::make_pair(&normalLargerTree, &normalSmallerTree),
			std::make_pair(&largerTree, &negativeTree) })
		{
			const IndexableBinaryTree<int, int>* pSmallerTree{ doPair.first };
			const IndexableBinaryTree<int, int>* pLargerTree{ doPair.second };
			if (doPair.first->size() > doPair.second->size())
			{
				auto* pTemp = pSmallerTree;
				pSmallerTree = pLargerTree;
				pLargerTree = pTemp;
			}
			if (!pSmallerTree->empty() && !pLargerTree->empty())
			{
				std::unique_ptr<std::vector<int>> pResult{ FindPair(target, *pSmallerTree, *pLargerTree) };
				if (pResult != nullptr)
				{
					return { *pResult };
				}
			}
		}

		return std::vector<int>();
	}

	static std::vector<int> twoSum_1(std::vector<int>& nums, int target)
	{
		std::map<int, int> numMap{};
		for (int index = 0; index < static_cast<int>(nums.size()); index++)
		{
			int value{ nums[index] };

			int findValue = target - value;
			auto findIterator = numMap.find(findValue);
			if (findIterator != numMap.end())
			{
				return std::vector<int>{findIterator->second, index};
			}
			numMap[value] = index;
		}
		return std::vector<int>();
	}

public:
	std::string GetName() const
	{
		return "Two Sum";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<std::vector<int>, std::vector<int>&, int> checker(
			[](std::vector<int>& nums, int target)
			{
				return "nums:\n" + StringTools::GetVectorString(nums) + "\ntarget:\n" + std::to_string(target);
			},
			[](std::vector<int> output)
			{
				return StringTools::GetVectorString(output);
			},
				[](std::vector<int> output, std::vector<int> answer)
			{
				std::sort(output.begin(), output.end());
				std::sort(answer.begin(), answer.end());
				return std::equal(output.begin(), output.end(), answer.begin(), answer.end());
			});

		checker.AddFunction(twoSum_0);
		checker.AddFunction(twoSum_1);

		std::vector<int> nums;
		int target;
		std::vector<int> answer;

		nums = { 3, 2, 4 };
		target = 6;
		answer = { 1, 2 };
		checker.CheckAnswer(nums, target, answer);

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
