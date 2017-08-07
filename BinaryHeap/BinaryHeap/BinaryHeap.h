/************************************************************************/
/*                   ����ѵ�����ʵ����ͷ�ļ�                            */
/************************************************************************/
#pragma once 
#include <vector>
#include <iostream>
template<class T>
class BinaryHeap{
public:
	BinaryHeap(){
		m_Vec.push_back(T(0));//���0λ�ã�Ϊ�˱���ʵ�ֶ���ѣ�0λ�ò����κ�����
		//requestForInput();

	};
	~BinaryHeap(){
	};
private:
	std::vector<T> m_Vec;
	void requestForInput();
	void init();//��ʼ�����飬ʹ֮���������Ϊ��������
	bool isLess(int leftIndex,int rightIndex);//�Ƚ���������λ��Ԫ�صĴ�С��������С������true
	void exchange(int leftIndex,int rightIndex);//����Ԫ��
public:
	void heapSort();//������
	void swim(int index);//���µ��ϵ��ϸ����������ʹ֮��������
	void sink(int index);//���ϵ��µ��³����������ʹ֮��������
	void sink(int index,int endIndex);//indexΪ����ֵ��endIndexΪ��βλ��
	void insert(T element);//��������ĩβ�в���һ��Ԫ��
	void deleteMax();//�ڶ������ɾ�����ڵ�Ԫ�أ������Ԫ��
	void display();//������ʾ


};


template<class T>
void BinaryHeap<T>::requestForInput()
{  
   std::cout << "�뿪ʼ����" << std::endl;
   T temp;
   while(std::cin >> temp)
   {
	  insert(temp);
   }
   std::cout << "�������" << std::endl;
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

//�ڼ���ڵ㴦ֵһ����С���亢�ӽڵ㣬��һ���ᷢ���������ǰ��
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
	m_Vec.erase(m_Vec.end()-1);//ɾ��ĩβԪ��
	sink(1);
}

template<class T>
void BinaryHeap<T>::heapSort()
{   
	std::cout << "��ʼ����" << std::endl;
	T temp;
	while(std::cin >> temp)
	{
		m_Vec.push_back(temp);
	}
	std::cout << "�������" << std::endl;
	//���ľ��к��ӽڵ������ֵ n/2
	//��һ��:�������о��к��ӵĽڵ�ʹ֮�Ըý��Ϊ�׵�����ʣ�����ж��Ǵ����
	int nonLeafNodeIndex = (m_Vec.size()-1)/2;
	while(nonLeafNodeIndex >= 1)
	{
		sink(nonLeafNodeIndex--,m_Vec.size()-1);
	}
	display();
	//�ڶ���:
    for (int i = m_Vec.size()-1;i >= 1;)
    {
		exchange(1,i);
		sink(1,--i);
    } 
	display();
}


//���ڽڵ㴦��λ�ý��е�����ʹ[index,endIndex]��Ϊ����Ĵ����
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

