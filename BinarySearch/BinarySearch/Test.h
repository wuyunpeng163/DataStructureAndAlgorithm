#include <iostream>
class Test{
public:
	Test(int v = 0):value(v){};
	~Test(){};
	bool operator < (Test t);
	bool operator > (Test t);
	bool operator = (Test t);
	friend std::ostream & operator << (std::ostream & os,Test & t);
	friend std::istream & operator >> (std::istream  & is,Test & t);
private:
	int value;
};
