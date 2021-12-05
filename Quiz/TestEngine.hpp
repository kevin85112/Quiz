#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class ITestable
{
public:
	virtual ~ITestable() {}
	virtual std::string GetName() const = 0;
	virtual bool Test(std::string* pErrorMessage = nullptr) = 0;
};

template <class OutputType, class... InputType>
class ProblemChecker
{
protected:
	std::vector<std::function<OutputType(InputType...)>> functionList;
	const std::function<std::string(OutputType)> getOutputString;
	const std::function<std::string(InputType...)> getInputString;
	const std::function<bool(OutputType output, OutputType answer)> checkAnswer;
	std::vector<std::vector<std::pair<bool, std::shared_ptr<std::string>>>> messageList;

	std::string GetMessage(std::function<bool(bool)> condition)
	{
		std::stringstream mesageStream;
		for (size_t questionIndex = 0; questionIndex < messageList.size(); questionIndex++)
		{
			const std::vector<std::pair<bool, std::shared_ptr<std::string>>>& questionMessages = messageList[questionIndex];
			for (size_t methodIndex = 0; methodIndex < questionMessages.size(); methodIndex++)
			{
				const std::pair<bool, std::shared_ptr<std::string>>& methodMessage = questionMessages[methodIndex];
				bool isSuccess = methodMessage.first;
				const std::string& message = *methodMessage.second;
				if (condition(isSuccess))
				{
					if (mesageStream.tellp() != 0)
					{
						mesageStream << "\n\n";
					}
					mesageStream << "[Method " << methodIndex << "]\n" << message;
				}
			}
		}
		if (mesageStream.tellp() != 0)
		{
			mesageStream << "\n";
		}
		mesageStream << std::flush;
		return mesageStream.str();
	}

public:
	std::vector<OutputType> CheckAnswer(const InputType&... input, OutputType answer)
	{
		std::vector<OutputType> outputList;
		std::vector<std::pair<bool, std::shared_ptr<std::string>>> messages;
		for (const auto& func : functionList)
		{
			auto output = func(input...);
			bool isSuccess = checkAnswer(output, answer);

			std::string message;
			{
				std::stringstream messageStream;
				messageStream << "input: \n" << getInputString(input...)
					<< "\noutput: \n" << getOutputString(output) << "\nanswer: \n"
					<< getOutputString(answer) << std::flush;
				message = messageStream.str();
			}
			messages.push_back({ isSuccess, std::make_shared<std::string>(message) });
			outputList.push_back(output);
		}
		messageList.push_back(messages);
		return outputList;
	}

	std::string GetSuccessMessage()
	{
		return GetMessage([](bool isSuccess)
			{
				return isSuccess == true;
			});
	}

	std::string GetErrorMessage()
	{
		return GetMessage([](bool isSuccess) 
			{
				return isSuccess == false;
			});
	}

	void AddFunction(const std::function<OutputType(InputType...)>& func)
	{
		functionList.push_back(func);
	}

	ProblemChecker(const std::function<std::string(InputType...)>& getInputString,
		const std::function<std::string(OutputType)>& getOutputString,
		const std::function<bool(OutputType output, OutputType answer)>& checkAnswer)
		: getInputString(getInputString),
		getOutputString(getOutputString),
		checkAnswer(checkAnswer)
	{
	}
};

class StringTools
{
private:
	StringTools() {}

public:
	template <class T>
	static std::string GetVectorString(const std::vector<T>& vector)
	{
		std::stringstream stream;
		for (size_t i = 0; i < vector.size(); i++)
		{
			stream << std::to_string(vector[i]);
			if (i + 1 != vector.size())
			{
				stream << ", ";
			}
		}
		return stream.str();
	};

	template <class T>
	static std::string GetMatrixString(const std::vector<std::vector<T>>& matrix)
	{
		std::stringstream stream;
		for (size_t i = 0; i < matrix.size(); i++)
		{
			stream << GetVectorString(matrix[i]);
			if (i + 1 != matrix.size())
			{
				stream << "\n";
			}
		}
		return stream.str();
	};

	template <class T>
	static std::string GetItemListString(const std::vector<T*> vector, const std::function<std::string(const T&)>& getString)
	{
		std::stringstream stream;
		int index = 1;
		for (T* item : vector)
		{
			stream << std::endl << "\t(" << std::to_string(index) << ") " << getString(*item);
			index++;
		}
		return stream.str();
	}

	static std::vector<std::string> SplitString(std::string value, std::string token)
	{
		std::vector<std::string> result;
		size_t findPosition;
		size_t preFindPosition = 0;
		while ((findPosition = value.find(token, preFindPosition)) != std::string::npos)
		{
			result.push_back(std::string(value, preFindPosition, findPosition - preFindPosition));
			preFindPosition = findPosition + 1;
		}
		result.push_back(std::string(value, preFindPosition));
		return result;
	}

	static std::string Replace(const std::string& value, const std::string& subString1, const std::string& subString2)
	{
		std::string result = value;

		if (!subString1.empty())
		{
			std::size_t findPostion;
			while ((findPostion = result.find(subString1)) != std::string::npos)
			{
				result.replace(findPostion, subString1.size(), subString2);
			}
		}
		return result;
	}
};
