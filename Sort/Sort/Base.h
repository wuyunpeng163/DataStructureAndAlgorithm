#include <iostream>

class Base{
public:
	Base(){
		std::cout << "Base Construction!" << std::endl;
	}
	virtual ~Base(){
		std::cout << "Base DeConstruction!" << std::endl;
	}
	Base(const Base & base){
		std::cout << "Copy Construction !" << std::endl;
		
	}
	const Base& operator=(const Base & base){
		std::cout << "base operator = !" << std::endl;
		return *this;

	}
	virtual void show()
	{
		std::cout << "show Base!" << std::endl;
	}
};


class Derived : public Base{
public:
	Derived(int num = 0):number(num){
		std::cout << "Derived Construction!" << std::endl;
	}

	Derived(const Derived & derivedObject){
		std::cout << "Derived Copy Construction!" << std::endl;
	}
	virtual ~Derived(){
        std::cout << "Derived DeConstruction!" << std::endl;
	}
	virtual void show()
	{
		std::cout << "show Derived!" << std::endl;
	}

private:
	int number ;
};