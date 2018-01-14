#include"dict.h"

int main(){
	dict d;
	d.update("name","arjun");
	d.update("age", 12);
	d.update("e", 24);
	
	cout<<"this dict is "<<d<<endl;
	
	return 0;
}