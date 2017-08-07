#include "Interview.h"
#include <math.h>
#include <algorithm>
//一道机试题目
//求两个数的加法，假设输入的两个加数均是合法的整数，不过两个加数的范围为100位
//输入参数:两个字符串
//返回参数:结果字符串
//例如输入 10000000000 ， -1 
//输出 9999999999
void InterView::questionOne(std::string & lStr,std::string & rStr)
{     
	std::string str1 = "";
	std::string str2 = "";
	std::cout << "输入str1" << std::endl;
	std::cin >> str1;
	std::cout << "输入str2" << std::endl;
	std::cin >> str2;
	std::cout << str1 << " + " << str2 << "=" << add(str1,str2);
}

std::string  InterView::add(std::string lStr,std::string rStr)
{   
	auto lStrLength = lStr.size();//lStr的长度
	auto rStrLength = rStr.size();//rStr的长度
	auto lStrPositiveFlag = lStr[0] == '-' ? false : true;//判断lStr的正负
	auto rStrPositiveFlag = rStr[0] == '-' ? false : true;//判断rStr的正负
	//消除正负的符号
	if (!lStrPositiveFlag){
		lStr.erase(lStr.begin(),lStr.begin()+1);
		lStrLength -= 1;
	}
	if (!rStrPositiveFlag){
		rStr.erase(rStr.begin(),rStr.begin()+1);
		rStrLength -= 1;
	}
	//补齐位数使两个字符串保持一致
	if (lStrLength >= rStrLength)
		rStr.insert(rStr.begin(),lStrLength-rStrLength,'0');
	else
		lStr.insert(lStr.begin(),rStrLength-lStrLength,'0');
	int resultTempLength = lStrLength >= rStrLength ? lStrLength : rStrLength;
	//判断四种情况，++,--,+-,-+
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
	//最高位进位位的判断
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


//poj题号1000
//输入参数 a,b 范围0-9
//求a+b的值
//输出
void  InterView::pojProblem1000()
{
	int a = 0;
	int b = 0;
	std::cin >> a >> b;
	std::cout << a+b << std::endl;

}


//一个数列的规律是
//n 从 1 开始
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
	int N = floor(std::sqrt(n - 1.0f));//算出起始点，加速收敛
	while (N * N + N + 1 < n)
	   N++;
	return N;
}


//计算一个数的幂运算，要得出这个数幂运算的准确值
//其中 底数范围 (0,99.999) , 幂次范围 (0,25]
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
	unsigned int lStrPointIndex = lStr.find('.');//lStr小数点的位置
	unsigned int rStrPointIndex = rStr.find('.');//rStr小数点的位置
	unsigned int lStrPointLength = 0;//lStr小数点后面的位数
	unsigned int rStrPointLength = 0;//lStr小数点后面的位数
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
	 result.insert(result.end() - lStrPointLength - rStrPointLength,'.');//插入小数点
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
	//移除后导0
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
