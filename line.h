#pragma once
#include <string>
#include <map>
#include <vector>
typedef std::multimap<std::string, int> SIMMAP;
class Count
{
public:
	//将所有的文件存储在map中
	void saveFileToMap(const std::string rootDir);
	//测试使用
	void printFilename();
	//统计整个map中的行数
	int getAllLine();
private:
	//存储所有的文件名字和行数
	SIMMAP allFileMap;
};

