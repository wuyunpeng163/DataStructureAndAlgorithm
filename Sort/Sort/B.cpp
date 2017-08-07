#include "B.h"
void * B::operator new(size_t size)
{   
	std::cout << "B operator new " << std::endl;
	return ::operator new(size);
}

void  B::operator delete(void * ptr)
{
	::operator delete(ptr);
}

/*
void * C::operator new(size_t size)
{   
	std::cout << "C operator new " << std::endl;
	return ::operator new(size);
}*/
