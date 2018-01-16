# Py++
Py++ (or PyPlusPlus) is a library written wholly in C++ that gives programmers the ability to introduce some of Python's core features and functionality into C++. Features like Dynamic Typing, Lists, Dictionaries, Tuples, etc that were once not easily available in C++ can now be used in programs effortlessly. 

This library aims to re-create Pythonic features almost exactly albeit some minor syntax and function changes. The vast majority of Python Objects and their built-in functions will be available to C++ developers at the completion of this project.

**Note**: Currently, only the headers for Dynamic Typing, Lists and Dictionaries are available. Try it out and send over your thoughts and criticisms. :-)

## Why?
You might ask, why would anybody want Python features in C++? Can't they just use Python instead?

Well, yes. Yes they can.

Py++ was developed for programmers who love coding and developing in C++. Python's a good language but the control, flexibility and speed that C++ offers one is unmatched.
Not to mention:- 
* Pointers
* Memory management
* Semi-colons and Brackets (Why Python programmers hate this is beyond me)

However, one must admit there are certain features in Python that are helpful. Lists and Dynamic Typing are very good examples. So, I wanted to combine the parts that I enjoyed about both languages. That's the idea behind Py++.

## Getting Started
Using these header files is very simple.

* Navigate to the **Code** section of this repository and download the project. Usually, the entire project is downloaded in the form of a zip file. Unzip it. 
* The headers required are present in the ```Headers``` folder.
* Now, if your C++ file is present in the same directory as that of these headers, a simple ```#include"yourHeaderName"``` might suffice. However, if the headers are present in a different directory, you might have to alter your include statement accordingly. Like this; ```#include"FolderName/Folder2Name/list.h"``` or ```#include"FolderName/list.h"```.
* Be sure to read the list of built-in functions for each PyPlusPlus object available and how to use them before you proceed.

### Sample Programs
The following programs only demonstrate how the objects can be used and a few functions. For the complete reference, scroll down to **Reference**.

#1
```
#include"py++.h"

int main(){
	int num, i=0;
	cout<<"Enter the number of items you would like to enter --> ";
	cin>>num;
	
	list li;
	
	while(i<num){
		var data;
		cin>>data;
		
		li.append(data);
		i++;
	}
	
	cout<<"The list is --> "<<li;
	return 0;
}
```
**Output**
```
Enter the number of items you would like to enter --> 3
arjun
234
helooooo
The list is --> ['arjun', 234, 'helooooo']
```
#2
```
#include"py++.h"

int main(){
	
	var yoda="do or do not, there is no try";
	var yoda_Age=10000;
	
	cout<<"Yoda said: "<<yoda<<"! His age is "<<yoda_Age<<endl;
	
	yoda="Hello ";
	yoda+="World!";
	
	cout<<yoda;
	
	return 0;
}
```
**Output**
```
Yoda said: do or do not, there is no try. His age is 10000.
Hello World!
```
#3
```
#include"py++.h"

int main(){
	int num, i=0;
	cout<<"Enter the number of people --> ";
	cin>>num;
	
	dict people;
	
	while(i<num){
		var name, age;
		cin>>name;
		cin>>age;
		
		people.update(name, age);
		i++;
	}
	
	cout<<"This dictionary is "<<people<<endl;
	
	return 0;
}
```
**Output**
```
Enter the number of people --> 5
Harry
17
Ron
45
Hermione
23
Dobby
20
Voldemort
54
This dictionary is {'Harry': 17, 'Ron': 45, 'Hermione': 23, 'Dobby': 20, 'Voldemort': 54}
```
## Reference
This section details the Py++ objects which are available currently and the functions that are built into them.
