/************************************************************************/
/*                   二叉堆的数组实现类头文件                            */
/************************************************************************/
#pragma once 
#include <vector>
#include <iostream>
template<class T>
class BinaryHeap{
public:
	BinaryHeap(){
		m_Vec.push_back(T(0));//填充0位置，为了便于实现二叉堆，0位置并无任何意义
		//requestForInput();

	};
	~BinaryHeap(){
	};
private:
	std::vector<T> m_Vec;
	void requestForInput();
	void init();//初始化数组，使之乱序输入变为二叉大根堆
	bool isLess(int leftIndex,int rightIndex);//比较左右索引位置元素的大小，如果左边小，返回true
	void exchange(int leftIndex,int rightIndex);//交换元素
public:
	void heapSort();//堆排序
	void swim(int index);//由下到上的上浮调整二叉堆使之重新有序
	void sink(int index);//由上到下的下沉调整二叉堆使之重新有序
	void sink(int index,int endIndex);//index为索引值，endIndex为结尾位置
	void insert(T element);//向二叉堆中末尾中插入一个元素
	void deleteMax();//在二叉堆中删除根节点元素，即最大元素
	void display();//遍历显示


};


template<class T>
void BinaryHeap<T>::requestForInput()
{  
   std::cout << "请开始输入" << std::endl;
   T temp;
   while(std::cin >> temp)
   {
	  insert(temp);
   }
   std::cout << "输入完成" << std::endl;
   display();
}

template<class T>
void BinaryHeap<T>::display()
{
	for (auto i = 0;i < m_Vec.size();++i)
	{
		std::cout << m_Vec[i] << " " ;
	}
	std::cout << std::endl;
}

template<class T>
bool BinaryHeap<T>::isLess(int leftIndex,int rightIndex)
{
	return m_Vec[leftIndex] < m_Vec[rightIndex] ? true : false; 
}

template<class T>
void BinaryHeap<T>::exchange(int leftIndex,int rightIndex)
{
	T temp = m_Vec[leftIndex];
	m_Vec[leftIndex] = m_Vec[rightIndex];
	m_Vec[rightIndex] = temp;
}

template<class T>
void BinaryHeap<T>::swim(int index)
{   
	while(index > 1 && isLess(index/2,index))
	{
		exchange(index,index/2);
		index /= 2;
	}
}

//在假设节点处值一定会小于其孩子节点，即一定会发生交换这个前提
template<class T>
void BinaryHeap<T>::sink(int index)
{
	while(index * 2 <= m_Vec.size()-1)
	{
		int rightChildIndex = index * 2 +1;
		int leftChildIndex = index * 2;
		if (rightChildIndex <= m_Vec.size()-1)
		{
			if (isLess(leftChildIndex,rightChildIndex))
			{
				exchange(index,rightChildIndex);
				index = rightChildIndex;
			}
			else
			{
				exchange(index,leftChildIndex);
				index = leftChildIndex;
			}
		}
		else{
			if (isLess(index,leftChildIndex))
			{
				exchange(index,leftChildIndex);
				index = leftChildIndex;
			}
		}
	}
}

template<class T>
void BinaryHeap<T>::insert(T element)
{
	m_Vec.push_back(element);
	swim(m_Vec.size()-1);
}

template<class T>
void BinaryHeap<T>::deleteMax()
{
	exchange(1,m_Vec.size()-1);
	m_Vec.erase(m_Vec.end()-1);//删除末尾元素
	sink(1);
}

template<class T>
void BinaryHeap<T>::heapSort()
{   
	std::cout << "开始输入" << std::endl;
	T temp;
	while(std::cin >> temp)
	{
		m_Vec.push_back(temp);
	}
	std::cout << "输入完成" << std::endl;
	//最大的具有孩子节点的索引值 n/2
	//第一步:调整所有具有孩子的节点使之以该结点为首到后序剩余序列都是大根堆
	int nonLeafNodeIndex = (m_Vec.size()-1)/2;
	while(nonLeafNodeIndex >= 1)
	{
		sink(nonLeafNodeIndex--,m_Vec.size()-1);
	}
	display();
	//第二步:
    for (int i = m_Vec.size()-1;i >= 1;)
    {
		exchange(1,i);
		sink(1,--i);
    } 
	display();
}


//对在节点处的位置进行调整，使[index,endIndex]变为有序的大根堆
template<class T>
void BinaryHeap<T>::sink(int index,int endIndex)
{
	while(index * 2 <= endIndex)
	{
		int rightChildIndex = index * 2 +1;
		int leftChildIndex = index * 2;
		if (rightChildIndex <= endIndex)
		{
			if (isLess(leftChildIndex,rightChildIndex)&& isLess(index,rightChildIndex))
			{
				exchange(index,rightChildIndex);
				index = rightChildIndex;
			}
			else if(!isLess(leftChildIndex,rightChildIndex) && isLess(index,leftChildIndex))
			{
				exchange(index,leftChildIndex);
				index = leftChildIndex;
			}
			else
				break;
		}
		else if (isLess(index,leftChildIndex))
			{
				exchange(index,leftChildIndex);
				index = leftChildIndex;
			}
		else 
			break;
	}

}

