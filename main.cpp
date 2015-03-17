/*************************************************************************
	> File Name: line.cpp
	> Author: zxx
	> Mail: zxx178239@163.com 
	> Created Time: Tue 17 Mar 2015 06:12:10 PM CST
 ************************************************************************/

#include <iostream>
#include "line.h"

int main(int argc, char *argv[])
{
	Count myCount;
	if(argc < 2)
	{	
		std::cout << "argc is error, please input a dir" << std::endl;
		return 0;
	}
	myCount.saveFileToMap(argv[1]);
//	myCount.printFilename();
	int cnts;
	cnts = myCount.getAllLine();
	std::cout << cnts << std::endl;
}
