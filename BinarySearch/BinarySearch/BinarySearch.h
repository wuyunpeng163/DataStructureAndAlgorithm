/************************************************************************/
/*                        ���ַ�����ģ����                              */
/*                      ��дʱ�䣺2016.8.25                             */
/************************************************************************/
//֧�ֵ���������Ҫ��:���е�������������ܹ��Ƚϴ�С������
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
	void input();//������������
   
};

template <class T>
void BinarySearch<T>::input()
{
	std::cout << "��������������еĴ�С:" << std::endl;
	int length  = 0;
	std::cin >> length;
	assert(length > 0);
	mVector = new std::vector<T>(length);
	std::cout << "��������������" << std::endl;
	for (auto i = 0;i < mVector->size();++i)
		std::cin >> (*mVector)[i];
	std::cout << "�����������" << std::endl;
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
			std::cout  <<  "�ڵ�" << middleFlag+1 << "λ" << std::endl;
			return;
		}

	}
	std::cout << num << "������" << std::endl;
}

