/************************************************************************/
/*                        二分法查找模板类                              */
/*                      编写时间：2016.8.25                             */
/************************************************************************/
//支持的有序序列要求:序列的类对象必须具有能够比较大小的特性
#pragma once 
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <assert.h>
template <class T>
class BinarySearch{
public:
	BinarySearch():mVector(NULL){
		input();
	};
	~BinarySearch(){
		delete mVector;
	};
	void binarySearch(T num);
private:
	std::vector<T> * mVector;
	void input();//输入整数序列
   
};

template <class T>
void BinarySearch<T>::input()
{
	std::cout << "请输入有序的序列的大小:" << std::endl;
	int length  = 0;
	std::cin >> length;
	assert(length > 0);
	mVector = new std::vector<T>(length);
	std::cout << "请输入有序序列" << std::endl;
	for (auto i = 0;i < mVector->size();++i)
		std::cin >> (*mVector)[i];
	std::cout << "有序序列完成" << std::endl;
}

template <class T>
void BinarySearch<T>::binarySearch(T num)
{
	int leftFlag = 0;
	int rightFlag = mVector->size()-1;
	int middleFlag = 0;
	while(leftFlag <=  rightFlag ){
		middleFlag = (rightFlag + leftFlag ) / 2;
		if ( num < (*mVector)[middleFlag] )
			rightFlag = middleFlag - 1;
		else if (num > (*mVector)[middleFlag])
			leftFlag = middleFlag + 1 ;
		else{
			std::cout  <<  "在第" << middleFlag+1 << "位" << std::endl;
			return;
		}

	}
	std::cout << num << "不存在" << std::endl;
}

