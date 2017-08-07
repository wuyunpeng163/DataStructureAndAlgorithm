#include "Interview.h"
#include <math.h>
#include <algorithm>
//һ��������Ŀ
//���������ļӷ�����������������������ǺϷ����������������������ķ�ΧΪ100λ
//�������:�����ַ���
//���ز���:����ַ���
//�������� 10000000000 �� -1 
//��� 9999999999
void InterView::questionOne(std::string & lStr,std::string & rStr)
{     
	std::string str1 = "";
	std::string str2 = "";
	std::cout << "����str1" << std::endl;
	std::cin >> str1;
	std::cout << "����str2" << std::endl;
	std::cin >> str2;
	std::cout << str1 << " + " << str2 << "=" << add(str1,str2);
}

std::string  InterView::add(std::string lStr,std::string rStr)
{   
	auto lStrLength = lStr.size();//lStr�ĳ���
	auto rStrLength = rStr.size();//rStr�ĳ���
	auto lStrPositiveFlag = lStr[0] == '-' ? false : true;//�ж�lStr������
	auto rStrPositiveFlag = rStr[0] == '-' ? false : true;//�ж�rStr������
	//���������ķ���
	if (!lStrPositiveFlag){
		lStr.erase(lStr.begin(),lStr.begin()+1);
		lStrLength -= 1;
	}
	if (!rStrPositiveFlag){
		rStr.erase(rStr.begin(),rStr.begin()+1);
		rStrLength -= 1;
	}
	//����λ��ʹ�����ַ�������һ��
	if (lStrLength >= rStrLength)
		rStr.insert(rStr.begin(),lStrLength-rStrLength,'0');
	else
		lStr.insert(lStr.begin(),rStrLength-lStrLength,'0');
	int resultTempLength = lStrLength >= rStrLength ? lStrLength : rStrLength;
	//�ж����������++,--,+-,-+
	int symbolJudgement = 0;
	if (lStrPositiveFlag && rStrPositiveFlag )
		symbolJudgement = 0;
	else if (!lStrPositiveFlag && !rStrPositiveFlag)
		symbolJudgement = 1;
	else if (lStrPositiveFlag && !rStrPositiveFlag)
		symbolJudgement = 2;
	else 
		symbolJudgement = 3;
	std::string result = "";
	switch(symbolJudgement){
	case  0:
		result = addPlusPLus(lStr,rStr,resultTempLength);
		break;
	case  1:
		result = addPlusPLus(lStr,rStr,resultTempLength);
		result.insert(result.begin(),'-');
		break;
	case  2:
		result = addPlusMinus(lStr,rStr,resultTempLength);
		break;
	case  3:
		result = addPlusMinus(rStr,lStr,resultTempLength);
		break;
	default:
		break;
	}
	return result;
}

std::string InterView::addPlusPLus(std::string & lStr,std::string & rStr,int resultTempLength)
{
	std::string result(resultTempLength,'0');
	bool carryFlag = false;
	for (int i = result.size()-1; i >= 0 ; --i)
	{
		result[i]  =  ( (lStr[i] - '0') + (rStr[i] - '0') ) % 10 + (carryFlag == true ? '1' : '0');
		carryFlag =   ( (lStr[i] - '0') + (rStr[i] - '0') ) / 10  + '0' == '1' ? true : false;
	}
	//���λ��λλ���ж�
	if (carryFlag)
		result.insert(result.begin(),1,'1');

	return result;

}


std::string InterView::addPlusMinus(std::string & lStr,std::string & rStr,int resultTempLength){
	std::string result(resultTempLength,'0');
	bool borrowFlag = false;
	bool exchangeFlag =lStr < rStr ? true : false;
	if (exchangeFlag)
	{
		std::string temp = rStr;
		rStr = lStr;
		lStr = temp;
	}
	for (int i = result.size()-1 ; i >= 0 ; --i)
	{   
		result[i] =  borrowFlag == true ? ((lStr[i] - '0') + 9 - (rStr[i] - '0')) % 10 + '0' : ((lStr[i] - '0')  - (rStr[i] - '0') + 10) % 10 + '0' ;
		borrowFlag = (lStr[i] < rStr[i]) || borrowFlag ? true : false;
	}
	if(exchangeFlag)		
		result.insert(result.begin(),1,'-');
	return result;
}


//poj���1000
//������� a,b ��Χ0-9
//��a+b��ֵ
//���
void  InterView::pojProblem1000()
{
	int a = 0;
	int b = 0;
	std::cin >> a >> b;
	std::cout << a+b << std::endl;

}


//һ�����еĹ�����
//n �� 1 ��ʼ
//  n  = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
//f(n) = 1 2 1 2 3 2 1 2 3  4 3  2  1  2
unsigned int InterView::f(unsigned int n)
{
  if (n == 1)
	  return 1;
  else
  {
	  int number  = findN(n);
	  if ( (n -number * number + number - 1) <= number )
		  return  f(n-1) + 1;
	  else
		  return  f(n-1) - 1;
  }
    
}

unsigned int InterView::findN(unsigned int n )
{
	int N = floor(std::sqrt(n - 1.0f));//�����ʼ�㣬��������
	while (N * N + N + 1 < n)
	   N++;
	return N;
}


//����һ�����������㣬Ҫ�ó�������������׼ȷֵ
//���� ������Χ (0,99.999) , �ݴη�Χ (0,25]
void InterView::pojProblem1001()
{
	std::string baseNumber;
	int n ;
	while(std::cin >> baseNumber >> n){
		std::string result = baseNumber ;
		if (n == 1)
			result = processResult(baseNumber);
		else {
			for (int i = 1;i < n;++i){
				result =  strMultiplication(result,baseNumber);
				result = processResult(result);
			}
		}
		if (result.find('.')==1)
		 result.erase(result.begin(),result.begin()+1);
		std::cout << result << std::endl;
	}
}

std::string InterView::strMultiplication(std::string lStr,std::string rStr)
{
	unsigned int lStrPointIndex = lStr.find('.');//lStrС�����λ��
	unsigned int rStrPointIndex = rStr.find('.');//rStrС�����λ��
	unsigned int lStrPointLength = 0;//lStrС��������λ��
	unsigned int rStrPointLength = 0;//lStrС��������λ��
	if(lStrPointIndex != std::string::npos)
		lStrPointLength = lStr.size()-1 - lStrPointIndex;
	if(rStrPointIndex != std::string::npos)
		rStrPointLength = rStr.size()-1 - rStrPointIndex;
	lStr.erase(lStr.begin()+lStrPointIndex,lStr.begin()+lStrPointIndex+1);
	rStr.erase(rStr.begin()+rStrPointIndex,rStr.begin()+rStrPointIndex+1);
	std::reverse(lStr.begin(),lStr.end());
	std::reverse(rStr.begin(),rStr.end());
	std::string result(1000,'0');
	for (int i = 0;i < lStr.size();++i)
		for (int j = 0;j < rStr.size();++j)
		{
			int temp = (lStr[i] - '0') * (rStr[j] - '0');
			int n = ( result[i+j] - '0' + temp );
			result[i+j] = n % 10 + '0';
			result[i+j+1] = result[i+j+1] + n / 10 ;
		}
	std::reverse(result.begin(),result.end());
	unsigned int nonZeroIndex =result.find_first_not_of('0');
	result = result.substr(nonZeroIndex);
	if( (lStrPointLength + rStrPointLength) > 0 && (lStrPointLength + rStrPointLength) < result.size() )
	 result.insert(result.end() - lStrPointLength - rStrPointLength,'.');//����С����
	else
	{ 
	  int supplementZeroSize = lStrPointLength + rStrPointLength - result.size() + 1;
      for (int i = 1 ;i <= supplementZeroSize;++i)
      {
		  result.insert(result.begin(),'0');
      }
	 result.insert(result.end() - lStrPointLength - rStrPointLength,'.');
	}
	 return result;
}


std::string InterView::processResult(std::string str)
{   
	//�Ƴ���0
	int pointFlag = str.rfind('.');
	if (pointFlag == std::string::npos)
	{
		return str;
	}
	else{
		int nonZeroFlag = str.find_last_not_of('0');
		if (nonZeroFlag > pointFlag )
		  str = str.substr(0,nonZeroFlag+1);
		 return str;
	}
}
