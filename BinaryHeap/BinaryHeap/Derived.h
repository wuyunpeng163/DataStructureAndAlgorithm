#pragma once 
#include <iostream>

class A{
public:
	A(int number = 0): a(number){};
	virtual ~A(){
		std::cout << "A class destruction" << std::endl;
	};
	void func_A_3(){};
private:
	virtual void func_A_1(){
		std::cout << "func_A_1()" << std::endl;
	};
	virtual void func_A_2(){
		std::cout << "func_A_2()" << std::endl;
	};
	
	int a;
}; 


class B{
public:
	B(int number = 0):b(number){};
	virtual ~B(){
		std::cout << "B class destruction" << std::endl;
	}
	virtual void func_B_1(){
		std::cout << "func_B_1()" << std::endl;
	}
	virtual void func_B_2(){
		std::cout << "func_B_2()" << std::endl;
	}
	void func_B_3(){};
private:
	int b;
};

class C: public A,public B{
public:
	C(int numberA = 0,int numberB = 0,int numberC = 0):A(numberA),B(numberB),c(numberC){};
	virtual ~C(){
		std::cout << "C class destruction" << std::endl;
	}
	virtual void func_A_1(){
		std::cout << "overwrite func_A_1()" << std::endl;
	}
	virtual void func_B_1(){
		std::cout << "overwrite func_B_1()" << std::endl;
	}
	virtual void func_C_1(){
		std::cout << "func_C_1()" << std::endl;
	}
private:
	int c;
};


class D : public A {
public:
	D():A(0){};
	virtual ~D(){};
	virtual void func_D_1(){
		std::cout << "func_D_1()" << std::endl;
	};
};


class E : public D{
public:
	E():D(){};
	virtual ~E(){};
	virtual void func_E_1(){
		std::cout << "func_E_1()" << std::endl;
	}
};

class F {
public:
	F(int number):n(number){};
	~F(){};
	void print(int number){
		std::cout << number << " " << this->n << std::endl; 
	}
	void func_F_1(){
	};
private:
	int n;
};


