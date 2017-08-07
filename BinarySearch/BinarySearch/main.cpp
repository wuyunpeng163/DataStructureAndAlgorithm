#include <vector>
#include <iostream>
void binarySearch(int num)
{   
	std::vector<int> Code;
	int MinNumber = -90;
	int MaxNumber = 90;
	int MiddleNumber = (MinNumber + MaxNumber)/2;
	int size = Code.size();
	while(size <=  6){
		if(size == 6)
			break;
		if(num >= MiddleNumber){
			MinNumber = MiddleNumber;
		    Code.push_back(1);
		}
		else{
			MaxNumber = MiddleNumber;
			 Code.push_back(0);
		}   
		    size++;
	        MiddleNumber = (MinNumber + MaxNumber)/2;
	}

	for(int i = 0;i < Code.size();++i)
		std::cout << Code[i] ;

	std::cout << std::endl;
	return ;
	
}
int main()
{   
	binarySearch(80);
    

	system("pause");
}