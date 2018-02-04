#include"dict.h"

int main(){
	dict aravind;
	aravind.update(23, 25);
	aravind.update(23, "arjun");
	aravind.update("kinda", 25);
	aravind.update("ahmed", "adnan");

	cout<<"the dictiopnary is "<<aravind<<endl;
	
	return 0;
}
