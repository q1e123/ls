#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

std::vector<std::string> convertToStringList(char* stringArray[], int len)
{
	std::vector<std::string> stringList = std::vector<std::string>();
	for(int pos = 0; pos < len; ++pos)
	{
		std::string str = std::string(stringArray[pos]);
		stringList.push_back(str);
	}
	return stringList;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> parameterList = convertToStringList(argv, argc);
	std::filesystem::path currentPath = std::filesystem::current_path();
	for (const auto& entry : std::filesystem::directory_iterator(currentPath))
	{
		std::cout << entry.path() << std::endl;
	}
	return 0;
}