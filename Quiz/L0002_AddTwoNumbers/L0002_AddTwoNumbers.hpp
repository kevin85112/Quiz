#include "../TestEngine.hpp"

class L0002_AddTwoNumbers : public ITestable
{
private:
	struct ListNode
	{
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};

	static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* pl1Node = l1;
		ListNode* pl2Node = l2;
		ListNode* pRoot = new ListNode();
		ListNode* pNode = pRoot;
		while (true)
		{
			int l1Value = pl1Node == nullptr ? 0 : pl1Node->val;
			int l2Value = pl2Node == nullptr ? 0 : pl2Node->val;
			int valSum = pNode->val + l1Value + l2Value;
			pNode->val = valSum % 10;
			pl1Node = pl1Node == nullptr ? nullptr : pl1Node->next;
			pl2Node = pl2Node == nullptr ? nullptr : pl2Node->next;
			int carry = valSum / 10;
			if (pl1Node == nullptr && pl2Node == nullptr)
			{
				if (carry > 0)
				{
					pNode->next = new ListNode(carry);
				}
				break;
			}
			pNode->next = new ListNode(carry);
			pNode = pNode->next;
		}
		return pRoot;
	}

	static ListNode* NewListNode(std::vector<int> values)
	{
		ListNode* root{ new ListNode };
		ListNode* node{ root };
		for (int value : values)
		{
			node->next = new ListNode(value);
			node = node->next;
		}
		node = root;
		root = root->next;
		delete node;
		return root;
	}

	static void DeleteListNode(ListNode*& pRoot)
	{
		ListNode* pNode = pRoot;
		while (pNode != nullptr)
		{
			ListNode* pDeleteNode = pNode;
			pNode = pNode->next;
			delete pDeleteNode;
		}
		pRoot = nullptr;
	}

	static std::string GetListNodeString(ListNode* node)
	{
		std::stringstream stream;
		for (bool isFirstTime = true; node != nullptr; node = node->next)
		{
			stream << node->val;
			if (node->next != nullptr)
			{
				stream << ", ";
			}
		}
		return stream.str();
	}

	static bool CompareListNode(ListNode* node1, ListNode* node2)
	{
		while (node1 != nullptr || node2 != nullptr)
		{
			bool isNode1Null = node1 == nullptr;
			bool isNode2Null = node2 == nullptr;
			if (isNode1Null != isNode2Null)
			{
				return false;
			}
			if (node1->val != node2->val)
			{
				return false;
			}
			node1 = node1->next;
			node2 = node2->next;
		}
		return true;
	}

public:
	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<ListNode*, ListNode*, ListNode*> checker(
			[](ListNode* input1, ListNode* input2)
			{
				return StringTools::GetItemListString<ListNode*>({ &input1 , &input2 }, GetListNodeString);
			},
			[](ListNode* output)
			{
				std::stringstream stream;
				stream << std::endl << "\t" << GetListNodeString(output);
				return stream.str();
			},
				[](ListNode* output, ListNode* answer)
			{
				return CompareListNode(output, answer);
			});

		checker.AddFunction(addTwoNumbers);
		ListNode* input1 = NewListNode({ 9, 9, 9, 9, 9, 9, 9 });
		ListNode* input2 = NewListNode({ 9, 9, 9, 9 });
		ListNode* answer = NewListNode({ 8, 9, 9, 9, 0 ,0 ,0 , 1 });
		std::vector<ListNode*> deleteList = checker.CheckAnswer
		(
			input1,
			input2,
			answer
		);
		DeleteListNode(input1);
		DeleteListNode(input2);
		DeleteListNode(answer);
		for (auto node : deleteList)
		{
			DeleteListNode(node);
		}

		std::string errorMessage = checker.GetErrorMessage();
		if (pErrorMessage != nullptr)
		{
			*pErrorMessage = errorMessage;
		}
		bool isSuccess = errorMessage.empty();
		return isSuccess;
	}
};
