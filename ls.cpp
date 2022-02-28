#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <iomanip>

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

std::string getFileName(std::filesystem::directory_entry entry)
{
	std::string fullPath = entry.path().string();
	size_t startPos = fullPath.find_last_of("/\\") + 1; 
	std::string filename = fullPath.substr(startPos);
	return filename;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> parameterList = convertToStringList(argv, argc);
	std::filesystem::path currentPath = std::filesystem::current_path();
	for (const auto& entry : std::filesystem::directory_iterator(currentPath))
	{
		std::cout << getFileName(entry) <<"\t\t" <<entry.file_size() << std::endl;
	}
	return 0;
}