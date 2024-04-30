#include <iostream> 

using namespace std; 

class Apple 
{ 
public: 
	static int i; 
	
	Apple(){}; 
}; 

int Apple::i = 0;

int main() 
{ 
    Apple obj1; 
    Apple obj2; 
    obj1.i = 2; 
    obj2.i = 3; 
        
    cout << obj1.i<<" "<<obj2.i;

    return 0;
}