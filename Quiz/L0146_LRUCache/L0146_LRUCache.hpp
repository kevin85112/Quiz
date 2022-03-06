#include "../TestEngine.hpp"
#include <algorithm>
#include <string>
#include <functional>
#include <list>
#include <unordered_set>
#include <unordered_map>

// source url: https://leetcode.com/problems/lru-cache/
class L0146_LRUCache : public ITestable
{
private:
	class ILRUCache
	{
	public:
		virtual ~ILRUCache() {};
		virtual int get(int key) = 0;
		virtual void put(int key, int value) = 0;
	};

	// use linked list -> Time Limit Exceeded.
	class LRUCache_0 : public ILRUCache
	{
	private:
		int _capacity;
		std::list<std::pair<int, int>> _list;
		std::unordered_set<int> _set;

	public:
		LRUCache_0(int capacity)
		{
			_capacity = capacity;
		}
		int get(int key) override
		{
			if (_set.find(key) == _set.end())
			{
				return -1;
			}
			for (auto it = _list.begin(); it != _list.end(); ++it)
			{
				if (it->first == key)
				{
					int value = it->second;
					_list.push_front(*it);
					_list.erase(it);
					return value;
				}
			}
			return -1;
		}
		void put(int key, int value) override
		{
			if (_set.find(key) == _set.end())
			{
				_set.emplace(key);
			}
			else
			{
				for (auto it = _list.begin(); it != _list.end(); ++it)
				{
					if (it->first == key)
					{
						_list.erase(it);
						break;
					}
				}
			}
			_list.push_front(std::make_pair(key, value));
			while (_list.size() > _capacity)
			{
				_set.erase(_list.back().first);
				_list.pop_back();
			}
		}
	};

	// use linked list with map.
	class LRUCache_1 : public ILRUCache
	{
	private:
		int _capacity;
		std::list<std::pair<int, int>> _list;
		std::unordered_map<int, std::list<std::pair<int, int>>::iterator> _set;

	public:
		LRUCache_1(int capacity)
		{
			_capacity = capacity;
		}
		int get(int key) override
		{
			auto findIt = _set.find(key);
			if (findIt == _set.end())
			{
				return -1;
			}

			auto listIt = findIt->second;
			int value = listIt->second;
			_list.erase(listIt);
			_list.push_front(std::make_pair(key, value));
			_set[key] = _list.begin();
			return value;
		}
		void put(int key, int value) override
		{
			auto findIt = _set.find(key);
			if (findIt != _set.end())
			{
				auto listIt = findIt->second;
				_list.erase(listIt);
			}
			_list.push_front(std::make_pair(key, value));
			_set[key] = _list.begin();
			while (_list.size() > _capacity)
			{
				_set.erase(_list.back().first);
				_list.pop_back();
			}
		}
	};

	static std::vector<std::shared_ptr<int>> DoTest
	(
		std::function<std::shared_ptr<ILRUCache>(int)> getCache,
		std::vector<std::string>& commands,
		std::vector<std::vector<int>>& inputs
	)
	{
		std::shared_ptr<ILRUCache> pNewCache = nullptr;
		std::vector<std::shared_ptr<int>> result;
		result.resize(commands.size());
		for (size_t i = 0; i < commands.size(); i++)
		{
			const std::string& command = commands[i];
			const std::vector<int>& input = inputs[i];

			if (command == "LRUCache")
			{
				pNewCache = getCache(input[0]);
			}
			else if (command == "put")
			{
				pNewCache->put(input[0], input[1]);
			}
			else if (command == "get")
			{
				result[i] = std::make_shared<int>(pNewCache->get(input[0]));
			}
			else
			{
				throw std::runtime_error("unknown command: " + command);
			}
		}
		return result;
	}

	static std::vector<std::shared_ptr<int>> DoTest_0
	(
		std::vector<std::string>& commands,
		std::vector<std::vector<int>>& inputs
	)
	{
		return DoTest([](int capacity)
			{
				return std::make_shared<LRUCache_0>(capacity);
			}, commands, inputs);
	}

	static std::vector<std::shared_ptr<int>> DoTest_1
	(
		std::vector<std::string>& commands,
		std::vector<std::vector<int>>& inputs
	)
	{
		return DoTest([](int capacity)
			{
				return std::make_shared<LRUCache_1>(capacity);
			}, commands, inputs);
	}

public:
	std::string GetName() const
	{
		return "LRUCache";
	}

	bool Test(std::string* pErrorMessage = nullptr)
	{
		ProblemChecker<
			std::vector<std::shared_ptr<int>>,
			std::vector<std::string>&,
			std::vector<std::vector<int>>&
		> checker(
			[](std::vector<std::string>& commands, std::vector<std::vector<int>>& inputs)
			{
				std::stringstream ss;
				for (size_t i = 0; i < commands.size(); i++)
				{
					ss << "command \"" << commands[i] << "\": " << StringTools::GetVectorString(inputs[i]) << std::endl;
				}
				return ss.str();
			},
			[](std::vector<std::shared_ptr<int>> output)
			{
				std::vector<std::string> strings(output.size());
				for (size_t i = 0; i < output.size(); i++)
				{
					strings[i] = "null";
					if (output[i] != nullptr)
					{
						strings[i] = std::to_string(*output[i]);
					}
				}
				return StringTools::GetVectorString(strings);
			},
				[](std::vector<std::shared_ptr<int>> output, std::vector<std::shared_ptr<int>> answer)
			{
				return std::equal(output.begin(), output.end(), answer.begin(), answer.end(),
					[](std::shared_ptr<int> A, std::shared_ptr<int> B)
					{
						if (A == nullptr && B == nullptr)
						{
							return true;
						}
						else if (A == nullptr || B == nullptr)
						{
							return false;
						}
						return *A == *B;
					});
			});

		checker.AddFunction(DoTest_0);
		checker.AddFunction(DoTest_1);

		std::vector<std::string> commands;
		std::vector<std::vector<int>> inputs;
		std::vector<std::shared_ptr<int>> answer;

		commands = { "LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get" };
		inputs = { {2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4} };
		answer = { nullptr, nullptr, nullptr, std::make_shared<int>(1), nullptr, std::make_shared<int>(-1), nullptr, std::make_shared<int>(-1), std::make_shared<int>(3), std::make_shared<int>(4) };
		checker.CheckAnswer(commands, inputs, answer);

		commands = { "LRUCache","get","put","get","put","put","get","get" };
		inputs = { {2},{2},{2,6},{1},{1,5},{1,2},{1},{2} };
		answer = { nullptr, std::make_shared<int>(-1), nullptr, std::make_shared<int>(-1), nullptr, nullptr, std::make_shared<int>(2), std::make_shared<int>(6) };
		checker.CheckAnswer(commands, inputs, answer);

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
