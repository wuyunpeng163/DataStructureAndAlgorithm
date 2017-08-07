#pragma once
#include <iostream>
class B{
public:
	B(){
		i = 0;
	};
	~B(){
		std::cout << "deconstruction" << std::endl;
	};
private:
	int i ;
	static void * operator new(size_t size);
	static void  operator delete(void * ptr);
};

class C {
public:
	C(){	
	};
	~C(){};
	B b;
private:
	
	//static void * operator new(size_t size);

};