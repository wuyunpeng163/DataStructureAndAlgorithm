/************************************************************************/
/*                                ����ģ����                            */
/*                               ����:2016.9.2                          */
/************************************************************************/
#pragma once 
#include <vector>
#include <iostream>
#include <Windows.h>
#include <math.h>
//�����ṩ���������㷨�Ĳ���
template <class T>
class Sort{
public:
	Sort():mVec(NULL){
		requestInput();
	}
	~Sort(){
		delete mVec;
	}
	void exchange(std::vector<T> & vec,int lIndex = 0,int rIndex = 0);//��ֵ����
	void selectSort();//ѡ������ O(n^2)
	void insertSort();//�������� O(n^3/2)
	void shellSort();//ϣ������
	//�鲢����ݹ鷨 O(n*log(n))
	void mergeSortUsingRecursion();
    //�鲢�����У���ÿ�η����У���Ϊ������������
	void mergeSort(std::vector<T> & resVec,int lFlag,int rFlag);//��resVec[lFlag...rFlag]�鲢����dstVec
	void merge(std::vector<T> & resVec,int lFlag,int middleFlag,int rFlag);//��һ�������������У����кϲ�����Ϊ��ȫ��������
	//�鲢����ǵݹ鷨 
	void mergeSortNotUsingRecursion();
	void merge(std::vector<T> & resVec,int k,int endFlag);//�����а�����k���飬Ȼ����ÿ����������й鲢����
	//��������
    void quickSort();
	void qSort(std::vector<T> & resVec,int lFlag,int rFlag);//��resVec[lFlag...rFlag]���ֽ�ֵ��������ʹ֮��ΪresVec[lFlag...threshold...rFlag],ʼ�ձ�֤�ڷֽ�ֵ��ߵ�ҪС�ڷֽ�ֵ���ڷֽ�ֵ�ұߵ�Ҫ���ڷֽ�ֵ
	int getThresholdIndex(std::vector<T> & resVec,int lFlag,int rFlag);//���ÿ������ʱ�ֽ�ֵ���ڵ�����λ��
	//ð������
	void buddleSort();
	//������
	void heapSort();
	void adjustHeap(std::vector<T> & resVec,int lFlag,int rFlag);//�������б�Ϊ���ջ
	//
	void callThreeQuickSort();//���������з�����
	void threeQuickSort(int lFlag,int rFlag);//�����з����򣬿��ŸĽ���
	//
	void requestInput();//��������
    bool isSorted();//�ж������Ƿ�����������
	void show();//��ʾ����
private:
	std::vector<T> *mVec;
};

template<class T>
void Sort<T>::requestInput()
{
   std::cout << "�������г���" << std::endl;
   int length = 0;
   std::cin >> length;
   mVec = new std::vector<T>(length);
   std::cout << "��������" << std::endl;
   for (auto i = 0 ;i < mVec->size(); ++i)
	   std::cin >> (*mVec)[i];
	  //(*mVec)[i] = mVec->size()-i;
   std::cout << "�������" << std::endl;
}


template<class T>
void Sort<T>::selectSort()
{   
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	for (auto i =0;i < mVec->size()-1; ++i)
	{
		int minTemp = (*mVec)[i];
		int minIndex = i;
		//�ҵ���Сֵ�Լ����±�
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
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::exchange(std::vector<T> & vec,int lIndex /* = 0 */,int rIndex /* = 0 */)
{
	T temp ;//Ĭ�Ϲ��캯��,������
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
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
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
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}


template<class T>
void Sort<T>::shellSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  

	int h = mVec->size()/2;//��ʼ����

	while(h >= 1 ){
		for (auto i = 0;i < mVec->size(); i+=h)//�ı䲽��
		{   
			int temp = (*mVec)[i];
			int index = i;
			for (auto j = i;j >= 0 ;j-=h)//�ı䲽��
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
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}


template<class T>
void Sort<T>::mergeSortUsingRecursion()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  

	mergeSort(*mVec,0,mVec->size()-1);

	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
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
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  

	int k = 1;
	while(k <= mVec->size()){
		merge(*mVec,k,mVec->size()-1);
		k *= 2;
	}
	
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::merge(std::vector<T> & resVec,int k,int endFlag)
{   
	std::vector<T> * tempVec = new std::vector<T>(resVec.size());
	int groupNumbers = endFlag / k + 1;//������
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
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  

    qSort(*mVec,0,mVec->size()-1);//����

	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  

}

template<class T>
void Sort<T>::qSort(std::vector<T> & resVec,int lFlag,int rFlag)
{
	if (lFlag == rFlag)
	  return;
	int thresholdIndex = 0;
    if(lFlag < rFlag){
		thresholdIndex = getThresholdIndex(resVec,lFlag,rFlag);
		if (thresholdIndex != 0)//���ж���Ϊ�˷�ֹthresholdIndex = 0���
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
	//�������У��ж��Ƿ��������
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
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	for (auto i = 0;i < mVec->size() ;++i)
	{
		for(auto j = mVec->size()-1;j >= i+1; --j)
		{
			if ( (*mVec)[j] <= (*mVec)[j-1] )
			  exchange(*mVec,j-1,j);
		}
	}
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}

template<class T>
void Sort<T>::heapSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  

	T fillElement ;//���Ԫ�����׸�λ�ã�Ϊ�˱�֤�����ͽڵ�����һ�£����Ǵ�1��ʼ

	mVec->insert( (*mVec).begin(),1,fillElement);

	int Node = mVec->size()-1;//�ڵ����

	int noneLeafNode = std::floor((Node + 0.0f)/2); //��Ҷ�ӽڵ����

	//���Ƚ�δ�������е���Ϊ�󶥶�
	for (int i = noneLeafNode ; i > 0; --i)
	    adjustHeap(*mVec,i,Node);
	for (int i = Node;i >= 1;--i)
	{
		exchange(*mVec,1,i);

		adjustHeap(*mVec,1,i-1);
	}

	mVec->erase(mVec->begin(),mVec->begin()+1);
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}


//��lFlag֮��Ľڵ�������Ԫ�ز���Ѷ�Ԫ�ؽ��н���
template<class T>
void Sort<T>::adjustHeap(std::vector<T> & resVec,int lFlag,int rFlag)
{   
	T temp = resVec[lFlag];//����������ĶѶ�Ԫ��
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
	if(lFlag >= rFlag)//�߽�����Ĵ���
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
		threeQuickSort(lFlag,lIndex);//�����ƶ��������ݹ���ѭ��
		threeQuickSort(rIndex+1,rFlag);//�����ƶ��������ݹ���ѭ��
	}
};

template<class T>
void Sort<T>::callThreeQuickSort()
{
	LARGE_INTEGER nFreq;  
	LARGE_INTEGER nBeginTime;  
	LARGE_INTEGER nEndTime;  
	QueryPerformanceFrequency(&nFreq);  
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  

    threeQuickSort(0,(*mVec).size()-1);

	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	double time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	std::cout<<"����ʱ�䣺"<<time*1000<<"ms"<<std::endl;  
}