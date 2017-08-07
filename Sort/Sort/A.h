#pragma once
#include <iostream>

class A
{
public:
	A(int num = 0):a(num){
		std::cout << "A construction" << std::endl;
	};
	virtual ~A(){
		std::cout << "A deconstruction" << std::endl;
	};
	int a;
};

class B : public virtual A
{
public:
	int b;
	B(int a = 0,int b = 0):b(a),A(b){
		std::cout << "B construction" << std::endl;
	}
	virtual ~B(){};
};



class C : public virtual A
{
public:
	int c;
	C(int a = 0,int b = 0):c(a),A(b){
		std::cout << "C construction" << std::endl;
	}
	virtual ~C(){};
};

class D : public B,public C
{
public:
	int d;
	D(int a = 0,int b = 0,int c = 0,int d = 0):d(a){
		std::cout << "D construction" << std::endl;
	}
};