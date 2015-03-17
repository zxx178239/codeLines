/*************************************************************************
	> File Name: line.cpp
	> Author: zxx
	> Mail: zxx178239@163.com 
	> Created Time: Tue 17 Mar 2015 06:13:34 PM CST
 ************************************************************************/

#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "line.h"

void Count::saveFileToMap(const std::string rootDir)
{
	DIR *pDir = opendir(rootDir.c_str());
	if(pDir == NULL)
	{
		std::cout << "open dir fail" << std::endl;
		return;
	}
	struct dirent *myDirent;
	char allName[1024];
	struct stat cur_stat;
	while((myDirent = readdir(pDir)) != NULL)
	{
		if(strcmp(myDirent->d_name, ".") == 0 || strcmp(myDirent->d_name, "..") == 0)
		{
			continue;
		}
		memset(&cur_stat, 0, sizeof(cur_stat));
		memset(allName, 0, sizeof(allName));
		sprintf(allName, "%s/%s", rootDir.c_str(), myDirent->d_name);
		lstat(allName, &cur_stat);
		//判断当前文件名对应的是否是目录
		if(S_ISDIR(cur_stat.st_mode))
		{
			saveFileToMap(std::string(allName));
		}else
		{//将当前的文件名存储在string中便于查找后缀
			std::string fileName = allName;
			//查找出现.的位置从而确定后缀
			int index = fileName.find_last_of('.');
			//表明查找到
			if(index != std::string::npos)
			{
				//存储后缀
				std::string suffix = fileName.substr(index);
				if(suffix == ".c" || suffix == ".cpp" || suffix == ".h")
				{
					int lineCnts = 0;	//存储每个文件对应的行数
					std::ifstream ifs(fileName.c_str());
					if(!ifs.good())
					{
						return;
					}
					std::string str = "";
					while(getline(ifs, str))
					{//空行不算
						if(str != "")
							lineCnts ++;
					}
					//由于基本每一个文件都有头部，所以减去6
					lineCnts -= 6;
					allFileMap.insert(std::make_pair(fileName, lineCnts));
				}
			}
		}
	}
}

void Count::printFilename()
{
	SIMMAP::iterator it = allFileMap.begin();
	for(; it != allFileMap.end(); ++ it)
	{
		std::cout << it->first << std::endl;
	}
}

int Count::getAllLine()
{
	SIMMAP::iterator it = allFileMap.begin();
	int allLines = 0;
	for(; it != allFileMap.end(); ++ it)
	{
		allLines += it->second;
	}
	return allLines;
}
