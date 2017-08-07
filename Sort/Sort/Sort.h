/************************************************************************/
/*                                排序模板类                            */
/*                               日期:2016.9.2                          */
/************************************************************************/
#pragma once 
#include <vector>
#include <iostream>
#include <Windows.h>
#include <math.h>
//该类提供各种排序算法的测试
template <class T>
class Sort{
public:
	Sort():mVec(NULL){
		requestInput();
	}
	~Sort(){
		delete mVec;
	}
	void exchange(std::vector<T> & vec,int lIndex = 0,int rIndex = 0);//两值交换
	void selectSort();//选择排序 O(n^2)
	void insertSort();//插入排序 O(n^3/2)
	void shellSort();//希尔排序
	//归并排序递归法 O(n*log(n))
	void mergeSortUsingRecursion();
    //归并排序中，在每次分治中，分为以下两个步骤
	void mergeSort(std::vector<T> & resVec,int lFlag,int rFlag);//将resVec[lFlag...rFlag]归并排序到dstVec
	void merge(std::vector<T> & resVec,int lFlag,int middleFlag,int rFlag);//将一个二分有序序列，进行合并，变为完全有序序列
	//归并排序非递归法 
	void mergeSortNotUsingRecursion();
	void merge(std::vector<T> & resVec,int k,int endFlag);//将序列按步长k分组，然后让每相邻两组进行归并排序
	//快速排序法
    void quickSort();
	void qSort(std::vector<T> & resVec,int lFlag,int rFlag);//将resVec[lFlag...rFlag]按分界值进行排序，使之分为resVec[lFlag...threshold...rFlag],始终保证在分界值左边的要小于分界值，在分界值右边的要大于分界值
	int getThresholdIndex(std::vector<T> & resVec,int lFlag,int rFlag);//获得每次排序时分界值所在的索引位置
	//冒泡排序法
	void buddleSort();
	//堆排序法
	void heapSort();
	void adjustHeap(std::vector<T> & resVec,int lFlag,int rFlag);//调整序列变为大堆栈
	//
	void callThreeQuickSort();//调用三向切分排序
	void threeQuickSort(int lFlag,int rFlag);//三向切分排序，快排改进版
	//
	void requestInput();//请求输入
    bool isSorted();//判断序列是否是有序序列
	void show();//显示序列
private:
	std::vector<T> *mVec;
};

template<class T>
void Sort<T>::requestInput()
{
   std::cout << "输入序列长度" << std::endl;
   int length = 0;
   std::cin >> length;
   mVec = new std::vector<T>(length);
   std::cout << "输入序列" << std::endl;
   for (auto i = 0 ;i < mVec->size(); ++i)
	   std::cin >> (*mVec)[i];
	  //(*mVec)[i] = mVec->size()-i;
   std::cout << "输入完成" << std::endl;
}


template<class T>
void Sort<T>::selectSort()
{   
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	for (auto i =0;i < mVec->size()-1; ++i)
	{
		int minTemp = (*mVec)[i];
		int minIndex = i;
		//找到最小值以及其下标
		for (auto j = i+1;j < mVec->size(); ++j)
		{
			if (minTemp >= (*mVec)[j])
			{
				minTemp = (*mVec)[j];
				minIndex = j;
			}
		}
		exchange(*mVec,i,minIndex);
	}
	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::exchange(std::vector<T> & vec,int lIndex /* = 0 */,int rIndex /* = 0 */)
{
	T temp ;//默认构造函数,有隐患
	temp = vec[lIndex];
	vec[lIndex] = vec[rIndex];
	vec[rIndex] = temp;
}

template<class T>
void Sort<T>::show()
{
	for (auto i = 0 ;i < mVec->size() ; ++i)
	 std::cout << (*mVec)[i] << std::endl;
}


template<class T>
void Sort<T>::insertSort()
{   
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	for (auto i = 0;i < mVec->size(); ++i)
	{   
		int temp = (*mVec)[i];
		int index = i - 1;
		for (auto j = index;j >= 0 ;--j)
		{    
			if (temp < (*mVec)[j])
			{
				exchange(*mVec,i,j);
				i = j;
			}
			else
				break;
		}
	}
	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}


template<class T>
void Sort<T>::shellSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  

	int h = mVec->size()/2;//初始增量

	while(h >= 1 ){
		for (auto i = 0;i < mVec->size(); i+=h)//改变步长
		{   
			int temp = (*mVec)[i];
			int index = i;
			for (auto j = i;j >= 0 ;j-=h)//改变步长
			{    
				if (temp < (*mVec)[j])
				{
					exchange(*mVec,index,j);
					index = j;
					temp = (*mVec)[index];
				}
			}
		}
		h /= 2;
	}
	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}


template<class T>
void Sort<T>::mergeSortUsingRecursion()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  

	mergeSort(*mVec,0,mVec->size()-1);

	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::mergeSort(std::vector<T> & resVec,int lFlag,int rFlag)
{
	int m = 0;
	if (lFlag == rFlag)
		return;
	else
	{
		m = ( lFlag + rFlag ) /2;
		mergeSort(resVec,lFlag,m);
		mergeSort(resVec,m+1,rFlag);
		merge(resVec,lFlag,m,rFlag);

	}
}

template<class T>
void Sort<T>::merge(std::vector<T> & resVec,int lFlag,int middleFlag,int rFlag)
{   
	std::vector<T> tempVec(rFlag - lFlag + 1);
	int i = lFlag;
	int j = middleFlag + 1;
	int k = 0;
	while(i <= middleFlag && j <= rFlag){
		if (resVec[i] <= resVec[j])
			tempVec[k++] = resVec[i++];
		else
			tempVec[k++] = resVec[j++];
 
	}
	if (i <= middleFlag)
		for (auto l = i;l <= middleFlag;++l)
		    tempVec[k++] = resVec[l];
	if (j <= rFlag)
		for (auto l = j;l <= rFlag;++l)
			tempVec[k++] = resVec[l];
	for (auto l = 0;l < tempVec.size();++l)
	   resVec[lFlag + l] = tempVec[l];
}


template<class T>
void Sort<T>::mergeSortNotUsingRecursion()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  

	int k = 1;
	while(k <= mVec->size()){
		merge(*mVec,k,mVec->size()-1);
		k *= 2;
	}
	
	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::merge(std::vector<T> & resVec,int k,int endFlag)
{   
	std::vector<T> * tempVec = new std::vector<T>(resVec.size());
	int groupNumbers = endFlag / k + 1;//分组数
	int previousGroupStartIndex = 0;
	int laterGroupStartIndex = previousGroupStartIndex + k;
	int index = 0;
	while(previousGroupStartIndex <= resVec.size()-1){
		int i = previousGroupStartIndex;
		int j = laterGroupStartIndex;
		int minLaterNumber = (laterGroupStartIndex + k -1 ) <= (resVec.size()-1) ? (laterGroupStartIndex + k -1 ) : (resVec.size()-1);
		int minPreviousNumber = (previousGroupStartIndex + k -1 ) <= (resVec.size()-1) ? (previousGroupStartIndex + k -1 ) : (resVec.size()-1);
		while(i <= minPreviousNumber && j <= minLaterNumber ){
			if(resVec[i] <= resVec[j])
				(*tempVec)[index++] = resVec[i++];
			else
				(*tempVec)[index++] = resVec[j++];
		}
		if (i <= minPreviousNumber)
			for(auto l = i;l <= minPreviousNumber;++l)
				(*tempVec)[index++] = resVec[l];
		if (j <= minLaterNumber )
		   for (auto l = j;l <= minLaterNumber;++l)
		        (*tempVec)[index++] = resVec[l];
		previousGroupStartIndex += k*2;
		laterGroupStartIndex = previousGroupStartIndex + k;
	}
	delete mVec;
	mVec = tempVec;
	
}


template<class T>
void Sort<T>::quickSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  

    qSort(*mVec,0,mVec->size()-1);//快排

	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  

}

template<class T>
void Sort<T>::qSort(std::vector<T> & resVec,int lFlag,int rFlag)
{
	if (lFlag == rFlag)
	  return;
	int thresholdIndex = 0;
    if(lFlag < rFlag){
		thresholdIndex = getThresholdIndex(resVec,lFlag,rFlag);
		if (thresholdIndex != 0)//加判断是为了防止thresholdIndex = 0溢出
		   qSort(resVec,lFlag,thresholdIndex - 1);
		qSort(resVec,thresholdIndex + 1,rFlag);
	}
}

template<class T>
int Sort<T>::getThresholdIndex(std::vector<T> & resVec,int lFlag,int rFlag)
{
	T threshold = resVec[lFlag];
	while(lFlag < rFlag){
		while(lFlag < rFlag && resVec[rFlag] >= threshold)
			rFlag--;
		exchange(resVec,lFlag,rFlag);
		while(lFlag < rFlag && resVec[lFlag] <= threshold)
			lFlag++;
		exchange(resVec,lFlag,rFlag);
	}
	return lFlag;
}


template<class T>
bool Sort<T>::isSorted()
{
	bool result = false;
	//遍历序列，判定是否排序完毕
	int i= 0;
	for (;i < mVec->size()-1; ++i)
	{  
		if ( (*mVec)[i] <= (*mVec)[i+1])
			continue;    	  
		else
		    break;
	}
	if (i == mVec->size()-1)
	  return true;
	else
	  return false;
}


template<class T>
void Sort<T>::buddleSort()
{   
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	for (auto i = 0;i < mVec->size() ;++i)
	{
		for(auto j = mVec->size()-1;j >= i+1; --j)
		{
			if ( (*mVec)[j] <= (*mVec)[j-1] )
			  exchange(*mVec,j-1,j);
		}
	}
	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::heapSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  

	T fillElement ;//填充元素在首个位置，为了保证索引和节点索引一致，都是从1开始

	mVec->insert( (*mVec).begin(),1,fillElement);

	int Node = mVec->size()-1;//节点个数

	int noneLeafNode = std::floor((Node + 0.0f)/2); //非叶子节点个数

	//首先将未排序序列调整为大顶堆
	for (int i = noneLeafNode ; i > 0; --i)
	    adjustHeap(*mVec,i,Node);
	for (int i = Node;i >= 1;--i)
	{
		exchange(*mVec,1,i);

		adjustHeap(*mVec,1,i-1);
	}

	mVec->erase(mVec->begin(),mVec->begin()+1);
	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}


//找lFlag之后的节点中最大的元素并与堆顶元素进行交换
template<class T>
void Sort<T>::adjustHeap(std::vector<T> & resVec,int lFlag,int rFlag)
{   
	T temp = resVec[lFlag];//保存待交换的堆顶元素
	for (int i = 2 * lFlag; i < rFlag;i *= 2)
	{   
		if (i < rFlag && resVec[i] <= resVec[i+1])
			++i;
		if (temp >= resVec[i])
		    break;
		resVec[lFlag] = resVec[i];
		lFlag = i;     
	}
    resVec[lFlag] = temp;
}

template<class T>
void Sort<T>::threeQuickSort(int lFlag,int rFlag)
{
	if(lFlag >= rFlag)//边界问题的处理
		return;
	else{
		int lIndex = lFlag;
		int i = lIndex + 1;
		int rIndex = rFlag;
		T temp =  (*mVec)[lIndex];
		while(i <= rIndex)
		{
			if( (*mVec)[i]== temp)
				++i;
		    else if((*mVec)[i] < temp)
			{
	            exchange(*mVec,lIndex,i);
				++lIndex;
				++i;
			}
			else{
				exchange(*mVec,i,rIndex);
				--rIndex;
			}
		}
		threeQuickSort(lFlag,lIndex);//必须移动，否则会递归死循环
		threeQuickSort(rIndex+1,rFlag);//必须移动，否则会递归死循环
	}
};

template<class T>
void Sort<T>::callThreeQuickSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//开始计时  

    threeQuickSort(0,(*mVec).size()-1);

	QueryPerformanceCounter(&nEndTime);//停止计时  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s  
	std::cout<<"消耗时间："<<time*1000<<"ms"<<std::endl;  
}