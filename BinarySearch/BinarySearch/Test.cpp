#include "Test.h"
bool Test::operator<(Test t){
	return this->value < t.value ? true : false;
}

bool Test::operator>(Test t){
	return this->value > t.value ? true : false;
}

bool Test::operator=(Test t){
	return this->value = t.value ? true : false;
}

std::istream & operator >> (std::istream & is,Test & t){
	is >> t.value;
	return is;
}

std::ostream & operator << (std::ostream & os,Test & t){
	os << t.value;
	return os ;
}