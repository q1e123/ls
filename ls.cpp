#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <iomanip>
#include <map>

const char FILL_SEPARATOR = ' ';

struct size_less
{
	template<class T> bool operator()(T const& a, T const& b) const
	{
		return a.size() < b.size();
	}
};

size_t getMaxLength(std::vector<std::string> const& stringList)
{
	return std::max_element(stringList.begin(), stringList.end(), size_less())->size();
}

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

std::map<std::string, std::filesystem::directory_entry> directoryToMap(std::filesystem::directory_iterator directory)
{
	std::map<std::string, std::filesystem::directory_entry> directoryMap;
	for (const auto& entry : directory)
	{
		std::string filename = getFileName(entry);
		directoryMap[filename] = entry;
	}
	return directoryMap;
}

std::vector<std::string> mapToList(std::map<std::string, std::filesystem::directory_entry> map)
{
	std::vector<std::string> list;
	for(auto item : map)
	{
		std::string key = item.first;
		list.push_back(key);
	}
	return list;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> parameterList = convertToStringList(argv, argc);
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::filesystem::directory_iterator currentDirectory = std::filesystem::directory_iterator(currentPath);

	std::map<std::string, std::filesystem::directory_entry> directoryMap = directoryToMap(currentDirectory);
	std::vector<std::string> pathList = mapToList(directoryMap);

	size_t filename_width = getMaxLength(pathList);

	for (auto item : directoryMap)
	{
		std::filesystem::directory_entry entry = item.second;
		std::cout << item.first << std::setw(filename_width + 10 - item.first.length()) << std::setfill(FILL_SEPARATOR) <<entry.file_size() << std::endl;
	}
	return 0;
} 