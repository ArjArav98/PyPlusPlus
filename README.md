# PyPlusPlus
PyPlusPlus is a library written wholly in C++ that gives programmers the ability to introduce some of Python's core features and functionality into C++. Features like Dynamic Typing, Lists, Dictionaries, Tuples, etc that were once not easily available in C++ can now be used in programs effortlessly. 

This library aims to re-create Pythonic features almost exactly albeit some minor changes and absences. The vast majority of Python Objects and their built-in functions will be available to C++ developers at the completion of this project.

**Note**: Currently, only the headers for Dynamic Typing and Lists have been completed. Try it out and send over your thoughts and criticisms. :-)

## Why?
You might ask, why would anybody want Python features in C++? Can't they just use Python instead?

Well, yes. Yes they can.

PyPlusPlus was developed for programmers who love coding and developing in C++. Python's a good language but the control, flexibility and speed that C++ offers one is unmatched.
Not to mention:- 
* Pointers
* Memory management
* Semi-colons and Brackets (Why Python programmers hate this is beyond me)

However, one must admit there are certain features in Python that are helpful. Lists and Dynamic Typing are very good examples. So, I wanted to combine the parts that I enjoyed about both languages. That's the idea behind PyPlusPlus.

## Getting Started
Using these header files is very simple.

* Navigate to the **Code** section of this repository and download the project. Usually, the entire project is downloaded in the form of a zip file. Unzip it. 
* The headers required are present in the ```Headers``` folder.
* Now, if your C++ file is present in the same directory as that of these headers, a simple ```#include"yourHeaderName"``` might suffice. However, if the headers are present in a different directory, you might have to alter your include statement accordingly. Like this; ```#include"FolderName/Folder2Name/list.h"``` or ```#include"FolderName/list.h"```.
* Be sure to read the list of built-in functions for each PyPlusPlus object available and how to use them before you proceed.

### Sample Programs
```
#include"list.h"

int main(){
	
	list numList;
	int i, val;
	
	for(i=0; i<4; i++){
		cout<<"Enter a number --> ";
		cin>>val;
		numList.append(val);
	}
	
	cout<<"The number of times that 2 appears in the list is --> "<<numList.count(2)<<endl;
	
	cout<<"The list is "<<numList<<endl;
	numList.reverse();
	cout<<"The list is now "<<numList<<endl;
	
	numList.pop();
	numList.pop(0);
	
	cout<<"The list is now "<<numList<<endl;
	
	return 0;
}
```
**Output**
```
Enter a number --> 23
Enter a number --> 101
Enter a number --> 2
Enter a number --> 24
The number of times that 2 appears in the list is --> 1
The list is [23, 101, 2, 4]
The list is now [4, 2, 101, 23]
The list is now [2, 101]
```