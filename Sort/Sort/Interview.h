#pragma  once
#include <string>
#include <iostream>
#include <vector>
/************************************************************************/
/*                         笔试题目记录类                               */
/************************************************************************/
class InterView{
public:
	~InterView(){};
	void static questionOne(std::string & lStr,std::string & rStr);//题目1
	std::string static addPlusPLus(std::string & lStr,std::string & rStr,int resultTempLength);
	std::string static addPlusMinus(std::string & lStr,std::string & rStr,int resultTempLength);		
    std::string static add(std::string lStr,std::string rStr);

	void static pojProblem1000();//poj1000试题

	void static pojProblem1001();//poj1001试题
	std::string static strMultiplication(std::string lStr,std::string rStr);//字符串的乘法运算
	std::string static processResult(std::string str);
	
	unsigned int static findN(unsigned int n);//求数列问题
	unsigned int static f(unsigned int n);


private:
	InterView(){};//放在私有范围，不定义，用以屏蔽
	
	InterView(const InterView & InterViewObject);//放在私有范围，不定义，用以屏蔽
	
	const InterView & operator=(const InterView & InterViewObejct); //放在私有范围，不定义，用以屏蔽

};