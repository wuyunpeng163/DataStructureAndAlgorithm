#pragma  once
#include <string>
#include <iostream>
#include <vector>
/************************************************************************/
/*                         ������Ŀ��¼��                               */
/************************************************************************/
class InterView{
public:
	~InterView(){};
	void static questionOne(std::string & lStr,std::string & rStr);//��Ŀ1
	std::string static addPlusPLus(std::string & lStr,std::string & rStr,int resultTempLength);
	std::string static addPlusMinus(std::string & lStr,std::string & rStr,int resultTempLength);		
    std::string static add(std::string lStr,std::string rStr);

	void static pojProblem1000();//poj1000����

	void static pojProblem1001();//poj1001����
	std::string static strMultiplication(std::string lStr,std::string rStr);//�ַ����ĳ˷�����
	std::string static processResult(std::string str);
	
	unsigned int static findN(unsigned int n);//����������
	unsigned int static f(unsigned int n);


private:
	InterView(){};//����˽�з�Χ�������壬��������
	
	InterView(const InterView & InterViewObject);//����˽�з�Χ�������壬��������
	
	const InterView & operator=(const InterView & InterViewObejct); //����˽�з�Χ�������壬��������

};