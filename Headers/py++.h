// ========
// = Py++ =
// ========
//
//  Created by Arjun  Aravind on 2018-01-16.
//  Copyright 2018 Arjun  Aravind. All rights reserved.
//


#include<iostream>
using namespace std;

/* Macros for the 'var' class */
#define STR_SIZE 100
#define _INT 1 /* This is a misnomer. All values are double values. */
#define _STR 2
#define _NONE 0
#define YES 1
#define NO 0

/* Macros for the list and dict classes */
#define FAIL 2
#define SUCCESS 1

/* Classes for var, dict and list */
class var{

/* Class Data Members */
	union Value{
		double d;
		char* c;
	};
	
	public: unsigned short int type;
	unsigned short int allocated;
	public: Value val;
	
/* Constructors and Destructors */
	public: var(){
		/* The constructor sets the allocation and type variables to the default values. (See Macro Definitions) */
			allocated=NO;
			type=_NONE;
	}
	public: var(double num){
		/* If a number is passed in, this function will store it in the 'double' variable inside the union. If any allocation has taken place, it is freed. The 'type' variable is accordingly updated. */
			setDefaultsAndFree();
			val.d=num;
			type=_INT;
	}
	public: var(const char* string){
		/* If string is passed, this constructor executes. The argument string is passed into the setString() function.*/
		setString(string);
	}
	public: var(const var &v){
		if(v.type==_INT) setNum(v.val.d);
		else if(v.type==_STR) setString(v.val.c);
	}
	public: ~var(){
		/* The destructor calls the sDaF() (abbr.) which frees allocated memory and sets defaults. */
			setDefaultsAndFree();
	}
	
/* Utility functions used internally */	
	private: void setDefaultsAndFree(){
		/* This function frees memory if dynamic allocation has occured. It also sets 'allocated' and 'type' variables to their default values. */
			if(allocated==YES){
				delete val.c;
				val.c=NULL;
			}
			allocated=NO;
			type=_NONE;
	}
	
	private: int getType(const char* string){
		/* This function analyzes the string passed in and determines whether it is a string or a number. */
			int len=length(string);
			int i, point=0;
		
			for(i=0; i<len; i++){
				if(string[i]<='9' && string[i]>='0'); /* If character is a number, nothing happens */
				else if(string[i]=='.'){
					if(point==1) return _STR; /* if only one point is present, then num. Otherwise, it is a string. */
					else point++;
				}
				else return _STR; /* if the character is not a number or a point, the entire string is a 'string' */
			}
			return _INT;
	}
	public: int Type(){
		return type;
	}
	
	private: double getNum(const char* input){
		/* This function converts the given string into a double which is then returned. */
			double num=0;
			int i, len=length(input), placesAfterPoint=0;
	
			for(i=0; ((input[i]!='.') && (i<len)); i++){
				num*=10.0;
				double digit=9-('9'-input[i]);
				num+=digit;
			}
	
			i++;
			double afterPoint=0;
			for(;i<len; i++){
				afterPoint*=10.0;
				double digit=9-('9'-input[i]);
				afterPoint+=digit;
				placesAfterPoint++;
			}
	
			for(i=0; i<placesAfterPoint; i++){
				afterPoint/=10.0;
			}
	
			return (num+afterPoint);
	}
	
	private: int getDecimal(double doubleNum){
		/* This function returns the decimal point values of a given double variable. */
			long longNum=doubleNum;
			double doubleDecimal=(doubleNum-longNum)*10;
	
			if(doubleDecimal!=0){
				long longDecimal=doubleDecimal;
	
				while(longDecimal%10!=0){
					doubleDecimal*=10;
					longDecimal=doubleDecimal;
				}
		
				return doubleDecimal/=10;
			}
			else return 0;
	}
	private: int getLength(long number){
		/* This function returns the number of digits (or the length) of a given long variable. */
			int i=0;
			for(i=0; number!=0; i++, number/=10);
			return i;
	}

	private: void setNum(double num){
		setDefaultsAndFree();
		val.d=num;
		type=_INT;
	}
	public: void setString(const char* string){
		/* If string is passed, this constructor executes. First, allocated memory is freed and defaults are restored. The string argument is copied into the 'char' variable in the union. Type and Allocation variables are updated. NOTE:- Updated this function so that it assigns the '\0' (null character) right after the string.*/
			setDefaultsAndFree();
			int len=length(string), i;
			
			val.c=new char[len];
			
			for(i=0; i<len; i++) val.c[i]=string[i];
			val.c[i]='\0';
			
			allocated=YES;
			type=_STR;
	}
	private: void appendString(const char* string){
		if(allocated==YES){
			int len1=length(val.c), len2=length(string), i, j;
			char* str=new char[len1+len2];
			
			for(i=0, j=0; i<len1; i++, j++) str[j]=val.c[i];
			for(i=0; i<len2; i++, j++) str[j]=string[i];
			
			setString(str);
		}
		else{
			int len1=length(string), i;
			char* str=new char[len1];
			
			for(i=0; i<len1; i++) str[i]=string[i];
			
			setString(str);
		}
	}
	public: char* append(const char* string){
		if(allocated==YES){
			int len1=length(val.c), len2=length(string), i, j;
			char* str=new char[len1+len2];
			
			for(i=0, j=0; i<len1; i++, j++) str[j]=val.c[i];
			for(i=0; i<len2; i++, j++) str[j]=string[i];
			
			return str;
		}
		else{
			int len1=length(string), i;
			char* str=new char[len1];
			
			for(i=0; i<len1; i++) str[i]=string[i];
			
			return str;
		}
	}
	
	private: int length(const char* string){
		/* This function returns the length of the given string. */
			int i=0;
			for(i=0; string[i]!='\0'; i++);
			return i;
	}
	private: int strEquals(const char* str1, const char* str2){
		int len1=length(str1), len2=length(str2);
		if(len1==len2){
			int i;
			for(i=0; i<len1; i++)
				if(str1[i]!=str2[i]) return 0;
			return 1;
		}
		else return 0;
	}
	public: int strCompare(const char* str1, const char* str2){
		/* This function compares two strings lexicologically. If the first string is greater lexicologically, then 1 is returned, otherwise, 2 is returned. If the two strings are equal, then 0 is returned. */
			if(strEquals(str1, str2)==1) return 0;
			else{
				int i, len1=length(str1), len2=length(str2);
				if(len1>len2 || len1==len2){
					for(i=0; i<len2; i++)
						if(str2[i]>str1[i])
							return 2;
					return 1;
				}
				else{
					for(i=0; i<len1; i++)
						if(str1[i]>str2[i])
							return 1;
					return 2;
				}
			}
		
			return 0;
	}
	
/* Utility functions available to the user */

	public: char* toString(){
		/* This function checks what type is currently stored in THIS object and converts it into a string and returns it. */
			try{
				if(type==_NONE) throw 1;
				else if(type==_INT){
					/*
						* We first get the length of the wholeNum part of val.d and the decimalNum part of val.d. We then convert each digit of these two numbers and we then store it into a string. This string is then returned.
						* The algorithm for conversion is pretty self-evident.
					*/
					long wholeNum=val.d, decimalNum=getDecimal(val.d);
					int wholeNumLen=getLength(wholeNum), decimalNumLen=getLength(decimalNum);
	
					if(decimalNumLen!=0){
						char* str=new char[wholeNumLen+decimalNumLen+1];
						int i=0, j=0;
		
						for(i=(wholeNumLen+decimalNumLen); decimalNum!=0; i--, decimalNum/=10) str[i]='0'+(decimalNum%10);
						str[i--]='.';
						for(; wholeNum!=0; i--, wholeNum/=10) str[i]='0'+(wholeNum%10);
	
						return str;
					}
					else{
						char* str=new char[wholeNumLen];
	
						int i=0, j=0;
						for(i=wholeNumLen-1; wholeNum!=0; i--, wholeNum/=10) str[i]='0'+(wholeNum%10);
	
						return str;
					}
				}
				else if(type==_STR) return val.c;
			} catch (int exception){
				if(exception==1) cout<<"error: variable of type 'var' must be initialised first to perform toString()\n";
			}
			
			char* a=NULL;
			return a;
	} /* This function might result in memory leakage */
	public: int toInt(){
		/* This function, when called, will return an integer if the current type of the object is _INT (a number). If _STR, then an excpeion is thrown. If type is _NONE (var is not initialised), an exception is thrown. */
			try{
				if(type==_NONE) throw 1;
				else if(type==_INT){
					int num=val.d;
					return num;
				}
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: variable of type 'var' must be initialised first to perform toInt()\n";
				else if(exception==2) cout<<"error: variable must contain a number for toInt() to be performed\n";
			}
			return 0; //Some dummy value
	}
	public: double toDouble(){
		/* This function when called, will return a douible if the current type of the object is _INT (a number). If _STR, then an exception is thrown. If type is _NONE (var is not initialised), an exception is thrown. */
			try{
				if(type==_NONE) throw 1;
				else if(type==_INT) return val.d;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: variable of type 'var' must be initialised first to perform toDouble()\n";
				else if(exception==2) cout<<"error: variable must contain a number for toDouble() to be peformed\n";
			}
			return 0; //Some dummy value
	}
	
/* Operator Overloading Functions */
	public: void operator=(double num){
		/* This function overloads the = operator. If a number is passed in, this function will store it in the 'double' variable inside the union. If any allocation has taken place, it is freed. The 'type' variable is accordingly updated. */
			setDefaultsAndFree();
			val.d=num;
			type=_INT;
	}
	public: void operator=(const char* string){
		/* We are overloading the = operator. */
			setString(string);
	}
	public: void operator=(var &v){
		/* This function equates two variables together. */
			if(v.Type()==_INT) setNum(v.val.d);
			else if(v.Type()==_STR) setString(v.val.c);
	}
	
	public: double operator+(double num){
		/*This function overloads the + operator. This function returns a double which is the sum of the argument and the value of the double of THIS object. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) return (val.d + num);
			} catch (int exception){
				cout<<"error: cannot perform addition on string and number. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: char* operator+(const char* string){
		/* This function overloads the + operator. This function returns a char* which contains a string which is the concatenation of the string passed in as an argument and the string in THIS object. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					return append(string);
				}
			} catch (int exception){
				cout<<"error: cannot perform addition on string and number. Also, make sure that both variables are initialised.\n";
			}
			char* ret=NULL;
			return ret;
	}
	public: var operator+(var &v){
		/* This function overloads the + operator. This function returns a var object. If both the type variables of THIS object and the object passed in match, then the values in the respective objects are added or concatenated and stored in a newly-created object. This is then returned. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						var a=(val.d + v.val.d);
						return a;
					}
					else if(type==_STR){
						var a = val.c;
						a=a.append(v.val.c);
						return a;
					}
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: performing addition on string and number is not possible. Also, make sure that both variables are initialised.\n";
			}
			var a;
			return a;
	}
	
	public: double operator-(double num){
		/*This function overloads the - operator. This function returns a double which is the difference of the argument and the value of the double of THIS object. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) return (val.d - num);
			} catch (int exception){
				cout<<"error: cannot perform subtraction on string and number. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: char* operator-(const char* string){
		/* This function overloads the - operator. Only an exception is thrown, since subtraction cannot be performed on two strings. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform subtraction on type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform subtraction on two strings\n";
			}
			char* ret=NULL;
			return NULL;
	}
	public: var operator-(var &v){
		/* This function overloads the - operator. Similar to description for 'var operator+(var &v)'. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						var a=(val.d + v.val.d);
						return a;
					}
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform subtraction on string and number. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform subtraction on two strings\n";
			}
			var a;
			return a;
	}
	
	public: double operator*(double num){
		/*This function overloads the * operator. This function returns a double which is the product of the argument and the value of the double of THIS object. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) return (val.d * num);
			} catch (int exception){
				cout<<"error: cannot perform multiplication on string and number. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: char* operator*(const char* string){
		/* This function overloads the * operator. Only an exception is thrown, since multiplication cannot be performed on two strings. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform multiplication on type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform multiplication on two strings\n";
			}
			char* ret=NULL;
			return NULL;
	}
	public: var operator*(var &v){
		/* This function overloads the * operator. Similar to description for 'var operator+(var &v)'. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						var a=(val.d + v.val.d);
						return a;
					}
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform multiplication on string and number. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform multiplication on two strings\n";
			}
			var a;
			return a;
	}
	
	public: double operator/(double num){
		/*This function overloads the / operator. This function returns a double which is the result of division of the argument and the value of the double of THIS object. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) return (val.d / num);
			} catch (int exception){
				cout<<"error: cannot perform division on string and number. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: char* operator/(const char* string){
		/* This function overloads the / operator. Only an exception is thrown, since division cannot be performed on two strings. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform division on type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
			char* ret=NULL;
			return NULL;
	}
	public: var operator/(var &v){
		/* This function overloads the / operator. Similar to description for 'var operator+(var &v)'. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						var a=(val.d / v.val.d);
						return a;
					}
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform division on type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
			var a;
			return a;
	}
	
	public: double operator%(double num){
		/*This function overloads the % operator. This function returns a double which is the remainder of the division of the argument and the value of the double of THIS object. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT){
					long a=val.d;
					long b=num;
					num=a%b;
					return num;
				}
			} catch (int exception){
				cout<<"error: cannot perform division on string and number. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: char* operator%(const char* string){
		/* This function overloads the % operator. Only an exception is thrown, since division cannot be performed on two strings. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform division on type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
			char* ret=NULL;
			return NULL;
	}
	public: var operator%(var &v){
		/* This function overloads the % operator. Similar to description for 'var operator+(var &v)'. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						long a=val.d;
						long b=v.val.d;
						double num=a%b;
						var ab=num;
						return ab;
					}
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform division on type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
			var a;
			return a;
	}
	
	public: int operator==(double num){
		/*This function overloads the == operator. This function returns 0 if the argument and the double in THIS object are not equal and 1 if they are equal. If the type of THIS object is not a _INT, 0 is returned because they cannot equal.*/
			if(type==_STR) return 0;
			else if(type==_INT){
				if(num==val.d) return 1;
				else return 0;
			}
			else if(type==_NONE) return 0;
			else return -1; //Dummy return value
	}
	public: int operator==(const char* string){
		/* This function overloads the == operator. 1 or 0 is returned if the variables are equal or not equal respectively. If the type of THIS object is not a _STR, 0 is thrown because the number and the string cannot be equal. */
			if(type==_INT) return 0;
			else if(type==_STR){
				if(strEquals(val.c, string)==1) return 1;
				else return 0;
			}
			else if(type==_NONE) return 0;
			else return -1; //Dummy return value
	}
	public: int operator==(var &v){
		/* This function overloads the == operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then 0 is returned because they cannot be equal. If not, then the values are checked and 1 or 0 is returned depending upon whether they are equal or not. */
			if(type==v.Type()){
				if(type==_INT){
					if(v.val.d==val.d) return 1;
					else return 0;
				}
				else if(type==_STR){
					if(strEquals(val.c, v.val.c)==1) return 1;
					else return 0;
				}
				else if(type==_NONE) return 0;
			}
			else return 0;
			return -1; //Dummy return value
	}
	
	public: int operator!=(double num){
		/*This function overloads the != operator. This function returns 1 if the argument and the double in THIS object are not equal and 0 if they are equal. If the type of THIS object is not a _INT, 1 is returned because they cannot be equal.*/
			if(type==_STR) return 1;
			else if(type==_INT){
				if(num==val.d) return 0;
				else return 1;
			}
			else if(type==_NONE) return 1;
			else return -1; //Dummy return value
	}
	public: int operator!=(const char* string){
		/* This function overloads the != operator. 0 or 1 is returned if the variables are equal or not equal respectively. If the type of THIS object is not a _STR, 0 is returned because they cannot be equal. */
			if(type==_INT) return 1;
			else if(type==_STR){
				if(strEquals(val.c, string)==1) return 0;
				else return 1;
			}
			else if(type==_NONE) return 1;
			else return -1; //Dummy return value
	}
	public: int operator!=(var &v){
		/* This function overloads the != operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then 0 is returned bceause they cannot be equal. If not, then the values are checked and 1 or 0 is returned depending upon whether they are equal or not. */
			if(type==v.Type()){
				if(type==_INT){
					if(v.val.d==val.d) return 0;
					else return 1;
				}
				else if(type==_STR){
					if(strEquals(val.c, v.val.c)==1) return 0;
					else return 1;
				}
			}
			else return 1;
			return -1; //Dummy return value
	}
	
	public: int operator>(double num){
		/*This function overloads the > operator. This function returns 1 if THIS double is greater than the argument passed in and 0 if not. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT){
					if(val.d>num) return 1;
					else return 0;
				}
			} catch (int exception){
				cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator>(const char* string){
		/* This function overloads the > operator. 0 or 1 is returned if the argument string is greater than THIS string. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					if(strCompare(val.c, string)==1) return 1;
					else return 0;
				}
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator>(var &v){
		/* This function overloads the > operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then an exception is thrown. If not, then the values are checked and 1 or 0 is returned depending upon whether the argument 'var' is greater than THIS var. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						if(val.d>v.val.d) return 1;
						else return 0;
					}
					else if(type==_STR){
						if(strCompare(val.c, v.val.c)==1) return 1;
						else return 0;
					}
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	
	public: int operator>=(double num){
		/*This function overloads the >= operator. This function returns 1 if THIS double is greater than or equal to the argument passed in and 0 if not. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) return 0;
				else if(type==_INT){
					if(num>=val.d) return 1;
					else return 0;
				}
			} catch (int exception){
				cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator>=(const char* string){
		/* This function overloads the >= operator. 1 or 0 is returned if the argument string is greater than or equal to THIS string or not. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					if(strCompare(val.c, string)==1 || strCompare(val.c, string)==0) return 1;
					else return 0;
				}
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator>=(var &v){
		/* This function overloads the >= operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then an exception is thrown. If not, then the values are checked and 1 or 0 is returned depending upon whether the argument 'var' is greater than or equal to than THIS var or not respectively. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						if(val.d>=v.val.d) return 1;
						else return 0;
					}
					else if(type==_STR){
						if(strCompare(val.c, v.val.c)==1 || strCompare(val.c, v.val.c)==0) return 1;
						else return 0;
					}
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	
	public: int operator<(double num){
		/*This function overloads the < operator. This function returns 1 if THIS double is lesser than the argument passed in and 0 if not. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT){
					if(val.d<num) return 1;
					else return 0;
				}
			} catch (int exception){
				cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator<(const char* string){
		/* This function overloads the < operator. 1 is returned if the argument string is lesser than THIS string. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					if(strCompare(val.c, string)==1) return 0;
					else return 1;
				}
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator<(var &v){
		/* This function overloads the < operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then an exception is thrown. If not, then the values are checked and 1 or 0 is returned depending upon whether the argument 'var' is lesser than THIS var or not respectively. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						if(val.d<v.val.d) return 1;
						else return 0;
					}
					else if(type==_STR){
						if(strCompare(val.c, v.val.c)==1) return 0;
						else return 1;
					}
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	
	public: int operator<=(double num){
		/*This function overloads the <= operator. This function returns 1 if THIS double is lesser than or equal to the argument passed in and 1 if not. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT){
					if(num<=val.d) return 1;
					else return 0;
				}
			} catch (int exception){
				cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator<=(const char* string){
		/* This function overloads the <= operator. 1 or 0 is returned if the argument string is lesser than or equal to THIS string or not. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					if(strCompare(val.c, string)==1 || strCompare(val.c, string)==0) return 0;
					else return 1;
				}
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator<=(var &v){
		/* This function overloads the <= operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then an exception is thrown. If not, then the values are checked and 1 or 0 is returned depending upon whether the argument 'var' is lesser than or equal to than THIS var or not respectively. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						if(val.d<=v.val.d) return 1;
						else return 0;
					}
					else if(type==_STR){
						if(strCompare(val.c, v.val.c)==1 || strCompare(val.c, v.val.c)==0) return 0;
						else return 1;
					}
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot compare type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	
	public: void operator+=(double num){
		/*This function overloads the += operator. This function increments the double value of THIS object by 'num'. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) val.d+=num;
			} catch (int exception){
				cout<<"error: cannot perform addition on string and number. Also, make sure that both variables are initialised.\n";
			}
	}
	public: void operator+=(const char* string){
		/* This function overloads the += operator. This function appends the argument to the string of THIS object. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					appendString(string);
				}
			} catch (int exception){
				cout<<"error: cannot perform addition on string and number. Also, make sure that both variables are initialised.\n";
			}
	}
	public: void operator+=(var &v){
		/* This function overloads the += operator. This function checks if both the type variables of THIS object and the object passed in match, then the values in the respective objects are added or concatenated and stored in THIS object. */
			try{
				if(type==v.Type()){
					if(type==_INT) val.d+=v.val.d;
					else if(type==_STR) appendString(v.val.c);
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: performing addition on string and number is not possible. Also, make sure that both variables are initialised.\n";
			}
	}
	
	public: void operator-=(double num){
		/*This function overloads the -= operator. This function decrements the double value of THIS object by 'num'. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) val.d-=num;
			} catch (int exception){
				cout<<"error: cannot perform subtraction on string and number. Also, make sure that both variables are initialised.\n";
			}
	}
	public: void operator-=(const char* string){
		/* This function overloads the -= operator. This function throws only an exception as strings cannot be subtracted. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform subtraction on string and number. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform subtraction on two strings\n";
			}
	}
	public: void operator-=(var &v){
		/* This function overloads the -= operator. This function checks if both the type variables of THIS object and the object passed are of type _INT, then the value in THIS object is decremented by 'v.val.d'. If they are of type _STR, then an exception is thrown. */
			try{
				if(type==v.Type()){
					if(type==_INT) val.d-=v.val.d;
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: performing subtraction on string and number is not possible. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform subtraction on two strings\n";
			}
	}
	
	public: void operator*=(double num){
		/*This function overloads the *= operator. This function multiplies the double value of THIS object by 'num'. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) val.d*=num;
			} catch (int exception){
				cout<<"error: cannot perform multiplication on string and number. Also, make sure that both variables are initialised.\n";
			}
	}
	public: void operator*=(const char* string){
		/* This function overloads the *= operator. This function throws only an exception as strings cannot be multiplied. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform multiplication on string and number. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform multiplication on two strings\n";
			}
	}
	public: void operator*=(var &v){
		/* This function overloads the *= operator. This function checks if both the type variables of THIS object and the object passed are of type _INT, then the value in THIS object is multiplied by 'v.val.d'. If they are of type _STR, then an exception is thrown. */
			try{
				if(type==v.Type()){
					if(type==_INT) val.d*=v.val.d;
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: performing multiplication on string and number is not possible. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform multiplication on two strings\n";
			}
	}
	
	public: void operator/=(double num){
		/*This function overloads the /= operator. This function divides the double value of THIS object by 'num'. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT) val.d/=num;
			} catch (int exception){
				cout<<"error: cannot perform division on string and number. Also, make sure that both variables are initialised.\n";
			}
	}
	public: void operator/=(const char* string){
		/* This function overloads the /= operator. This function throws only an exception as strings cannot be divided. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform division on string and number. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
	}
	public: void operator/=(var &v){
		/* This function overloads the /= operator. This function checks if both the type variables of THIS object and the object passed are of type _INT, then the value in THIS object is divided by 'v.val.d'. If they are of type _STR, then an exception is thrown. */
			try{
				if(type==v.Type()){
					if(type==_INT) val.d/=v.val.d;
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: performing division on string and number is not possible. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
	}
	
	public: void operator%=(double num){
		/*This function overloads the %= operator. This function divides the double value of THIS object by 'num' and stores the remainder in THIS object. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT){
					long num1=val.d, num2=num;
					val.d=num1%num2;
				}
			} catch (int exception){
				cout<<"error: cannot perform division on string and number. Also, make sure that both variables are initialised.\n";
			}
	}
	public: void operator%=(const char* string){
		/* This function overloads the %= operator. This function throws only an exception as strings cannot be divided. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR) throw 2;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot perform division on string and number. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
	}
	public: void operator%=(var &v){
		/* This function overloads the %= operator. This function checks if both the type variables of THIS object and the object passed are of type _INT, then the value in THIS object is divided by 'v.val.d' and the remainder is stored in val.d. If they are of type _STR, then an exception is thrown. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						long num1=val.d, num2=v.val.d;
						val.d=num1%num2;
					}
					else if(type==_STR) throw 2;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: performing division on string and number is not possible. Also, make sure that both variables are initialised.\n";
				else if(exception==2) cout<<"error: cannot perform division on two strings\n";
			}
	}
	
	public: char operator[](int index){
		/* This function overloads the [] operator. The character at the specified index of 'val.c' is returned. If the index is out of bounds, an exception is thrown. */
			try{
				if(type==_INT) throw 2;
				else if(type==_STR){
					if(index<length(val.c) && index>=0) return val.c[index];
					else throw 1;
				}
			} catch (int exception){
				if(exception==1) cout<<"error: index out of bounds for '[]' operator\n";
				else if(exception==2) cout<<"error: [] operator cannot function for 'var' of type 'number'\n";
			}
			return '\0';
	}
	
	public: friend ostream &operator<<(ostream &o, var &v);
	public: friend istream &operator>>(istream &i, var &v);
	
	public: class list;
};
class list{

/* Structs, Variables and Typedefs */
	struct Node{
		var data;
		struct Node* next;
	};
	
	typedef struct Node* node;
	typedef node Head;
	typedef node Pos;
	typedef node Temp;

	Head head;
	Pos pos;
	Temp temp;

/* Constructors and Destructors */
	public: list(){
		/*When the object is declared, then the list is created.*/
		create();
	}
	public: list(list &l){
		/* Overloads the constructor in the case that another list object is equated to it during initialisation. */
			create(); /* We call 'create()' which initialises the 'list' variable and creates the 'head' node. */
			int len=l.size(), i; /* We then add the elements of the passed in list one by one to THIS list using the append() function. */
			for(i=0; i<len; i++) append(l[i]);
	}
	
	public: ~list(){
		/* Called when the object is no longer in use */
			free();
	}
	
/* Utility functions for users */
	public: void append(var num){
		/* We add a node containing the variable to the end of the list. */
			temp=new struct Node;
			temp->next=NULL;
			temp->data=num;
			
			pos=head;
			while(pos!=NULL){
				if(pos->next==NULL){
					pos->next=temp;
					break;
				}
				pos=pos->next;
			}
	}
	public: void insert(int index, var num){
		/* This function inserts an element into the list at the specified index number. */
			try{
				if(index>=0 && index<size()){ /* The index must be between 0 and (ListSize-1) */
					int i=0;
				
					temp=new struct Node;
					temp->data=num;
					temp->next=NULL;
				
					pos=head;
					while(pos!=NULL){
						if(i==index){
							temp->next=pos->next;
							pos->next=temp;
							break;
						}
						pos=pos->next;
						i++;
					}
				}
				else throw 1; /* If not, an exception is thrown. */
			} catch (int exception){
				if(exception==1) cout<<"\nerror: insert() argument 1 must be between 0 and (listSize-1)\n";
				byebye(FAIL);
			}
	}
	public: void pop(int index=-1){
		/* This function removes the element of the list whose index matches the index passed. If not argument is provided on function call, the last element of the list is removed by default. The function also checks if the argument passed is within bounds of the array. */
			try{
				if((index==(-1)) || (index>=0 && index<size())){ /* Either default argument or argument must be within bounds */
					if(index==(-1)) index=size()-1; /* If argument is default (-1), then last element is deleted */
					int i;
					for(i=0, pos=head; pos!=NULL; i++, pos=pos->next){
						if(i==index){
							temp=pos->next;
							pos->next=pos->next->next;
							delete temp;
							break;
						}
					}
				}
				else throw 1;
			} catch (int exception){
				cout<<"\nerror: argument for pop() must be within 0 to (ListSize-1)\n";
				byebye(FAIL);
			}
	}
	public: void remove(var num){
		/* This function removes the first occurence of the element whose values equals 'num' */
			int found=count(num);
			if(found!=0){
				pos=head;
				while(pos!=NULL){
					if(pos->next->data==num){
						temp=pos->next;
						pos->next=pos->next->next;
						delete temp;
						break;
					}
					pos=pos->next;
				}
			}
	}
	public: void change(int index, var num){
		/* This function changes the data in the specified index to 'num'. */
			int count=0;
			for(pos=head->next; pos!=NULL; pos=pos->next, count++)
				if(count==index)
					pos->data=num;
	}
	public: void extend(list &l){
		/* This function takes the list passed in and appends all of its contents to THIS list */
			int len=l.size(), i;
			for(i=0; i<len; i++) append(l[i]);
	}
	public: void clear(){
		/* We clear the list of any current contents. */
			free(); /* We free the allocated memory. */
			setDefaults(); /* Values set to default. */
			create(); /* We initialise the head node again. */
	}
	public: void reverse(){
		/* This function reverses the linked list. */
			if(head->next!=NULL){ /* We first make sure the list is not empty */
				if(head->next->next!=NULL){ /* We then check if the list has more than one item */
					
					Pos prev=head->next; /* We simplify all the pointer-changing by using prev, succ and current */
					Pos current=prev->next; /* prev is the first node and current is the second */
					Pos succ=current->next; /* succ is the third node */
			
					do{
						prev->next=current->next; /* We attach prev and succ */
						succ=current->next; /* defining succ as the node after current */
						current->next=head->next; /* We attach the first node (head->next) to current */
						head->next=current; /* We attach head to current */
				
						if(succ==NULL) break; /* If succ is NULL, we have reached end of list */
						else{
							/* the prev node will never change (trace the whole thing if you want) */
							current=succ; /* the current node is the previous 'succ' node */
						}
					}while(succ!=NULL);
				}
			}
	}
	
	public: int count(var num){
		/* This function returns the number of times the value passed is found in the list. */
			int count=0;
			pos=head->next;
		
			while(pos!=NULL){
				if(pos->data==num) count++;
				pos=pos->next;
			}
			return count;
	}
	public: int size(){
		/* This function returns the size of the list. */
			int count=0;
			pos=head->next;
		
			while(pos!=NULL){
				count++;
				pos=pos->next;
			}
		
			return count;
	}

/* Utility functions used internally */
	private: void create(){
		/* We initialise the head node of a list. */
			head=new struct Node;
			head->next=NULL;
	}
	private: void free(){
		/* This functions frees the dynamically allocated elements of the linked list */
			pos=head;
			while(pos!=NULL){
				temp=pos;
				pos=pos->next;
				delete temp;
			}
	}
	private: void setDefaults(){
		/* We set the head, pos and temp variables to NULL. */
			head=NULL;
			pos=NULL;
			temp=NULL;
	}
	private: void byebye(int outcome){
		/* A set of protocols that must be executed if the program encounters an exception so that a natural termination is ensured. */
			free();
			if(outcome==1) exit(EXIT_SUCCESS);
			else if(outcome==2) exit(EXIT_FAILURE);
	}
	
/* Operator Overloading functions*/	
	public: var operator[](int index){
		/*
			This functions overloads the [] operator. It takes in the integer value and then returns the value present at the specified node. If the integer value is greater than the size of the list, exception is thrown. There is also functionality for negative indices just like Python.
		*/
			try{
				if(index<size() && index>=0){ /* Index is positive */
					int i=0;
					for(pos=head->next; pos!=NULL; i++, pos=pos->next)
						if(i==index)
							return pos->data;
				}
				else if(index<0 && index>=(-size())){ /* Index is negative */
					int i=0;
					index=size()+index;
					for(pos=head->next; pos!=NULL; i++, pos=pos->next)
						if(i==index)
							return pos->data;
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"\nerror: index ["<<index<<"] is out of bounds!\n";
				byebye(FAIL);
			}
			var a=19.98; /* random dummy value */
			return a;
	}
	public: void operator=(list &l){
		/* This functions overloads the = operator.*/
		
			free(); /* We must first free THIS object of any original content. */
			setDefaults(); /* We must then set the head, pos and temp values to NULL (defaults). */
			create(); /* We then call 'create()' which initialises the 'list' variable and creates the 'head' node. */
		
			int len=l.size(), i;
			for(i=0; i<len; i++) append(l[i]);
	}
	public: friend ostream &operator<<(ostream &o, list &l);
	
};
class dict{
	
/* Structs, typedefs and variables */
	struct Node{
		var key;
		var data;
		struct Node* next;
	};
	
	typedef struct Node* node;
	typedef node Head;
	typedef node Pos;
	typedef node Temp;

	Head head;
	Pos pos;
	Temp temp;
	
/* Constructors and Destructors */
	public: dict(){
		/*When the object is declared, then the list is created.*/
		create();
	}
	
	/*We need to write that adding new item method to write the function which takes in another dict as initilisation*/
	
	public: ~dict(){
		/* Called when the object is no longer in use */
			free();
	}
	
/* Utility functions available to users */
	
	public: void update(var key, var data="NULL"){
		
		/* This is one of the most integral functions for this class. This function takes in a key and data (both objects of type 'var'). If no data is entered, then the data is taken as "NULL", which is a default value. 
			--> This function first searches if the key is present in the dictionary already. If it is present, then the 'data' object of that dictionary pair is assigned the value of the argument 'data' object. If the key is not present, a new dictionary pair is created and is assigned the values of the key and data objects which have been passed in.*/
		
			pos=head; /* We check if the key already exists and, if yes, we update it. */
			while(pos!=NULL){
				if(pos->key==key){
					pos->data=data;
					return; /* We update the 'data' object and return out of the function. */
				}
				pos=pos->next;
			}
		
			Temp tmp=new struct Node; /* We create a new node. */
			tmp->next=NULL;
			tmp->key=key;
			tmp->data=data;
		
			pos=head;
			while(pos!=NULL){
				if(pos->next==NULL){
					pos->next=tmp;
					return; /* After inserting this node, we return out of the function. */
				}
				pos=pos->next;
			}
		
			return;
	}
	
/* Utility functions used internally */
	private: void create(){
		/* We initialise the head node of a dictionary. */
			head=new struct Node;
			head->next=NULL;
			/* No need to initialise the 'key' and 'data' vars with dummy values */
	}
	private: void free(){
		/* This functions frees the dynamically allocated elements of the dictionary */
			pos=head;
			while(pos!=NULL){
				temp=pos;
				pos=pos->next;
				delete temp;
			}
	}
	private: void setDefaults(){
		/* We set the head, pos and temp variables to NULL. */
			head=NULL;
			pos=NULL;
			temp=NULL;
	}
	private: void byebye(int outcome){
		/* A set of protocols that must be executed if the program encounters an exception so that a natural termination is ensured. */
			free();
			if(outcome==1) exit(EXIT_SUCCESS);
			else if(outcome==2) exit(EXIT_FAILURE);
	}
	
/* Operator Overloading functions */
	
	public: friend ostream &operator<<(ostream &o, dict &v);
};

/* Output stream and input stream overload functions */
ostream &operator<<(ostream &o, dict &d){
	/* This function overloads the output stream << operator. We print the dictionary object in the same way as it might be printed in Python. */
		o<<"{";
	
		d.pos=d.head->next;
		while(d.pos!=NULL){
			int keyType=d.pos->key.Type();
			int dataType=d.pos->data.Type();
			if(d.pos->next!=NULL){
				if(keyType==_INT) o<<d.pos->key<<", ";
				else if(keyType==_STR) o<<"'"<<d.pos->key<<"': ";
				{
					if(dataType==_INT) o<<d.pos->data<<", ";
					else if(dataType==_STR) o<<"'"<<d.pos->data<<"', ";
				}
			}
			else{
				if(keyType==_INT) o<<d.pos->key;
				else if(keyType==_STR) o<<"'"<<d.pos->key<<"': ";
				{
					if(dataType==_INT) o<<d.pos->data;
					else if(dataType==_STR) o<<"'"<<d.pos->data<<"'";
				}
			}
			d.pos=d.pos->next;
		}
	
		o<<"}";
	
		return o;
}
ostream &operator<<(ostream &o, list &l){
	/* This function overloads the output stream "<<" operator. The list is printed in the following format:- [34,23,12]; the exact same way a 'list' is printed in python. */
		o<<"[";
		l.pos=l.head->next;
		while(l.pos!=NULL){
			if(l.pos->next==NULL){
				if(l.pos->data.type==_STR) o<<"'"<<l.pos->data<<"'";
				else o<<l.pos->data;
			}
			else{
				if(l.pos->data.type==_STR) o<<"'"<<l.pos->data<<"'"<<", ";
				else o<<l.pos->data<<", ";
			}
			l.pos=l.pos->next;
		}
		o<<"]";
		return o;
}
ostream &operator<<(ostream &o, var &v){
	/* If type is _INT, the double is printed. If _STR, the string is printed. */
		if(v.type==_INT) o<<v.val.d;
		else if(v.type==_STR) o<<v.val.c;
		return o;
}
istream &operator>>(istream &i, var &v){
	/* This overloads the input stream >> operator. First, allocated memory, if any, is freed and all defaults are restored. The string is analysed in the getType() function and if it is an _INT, it is stored in the double after conversion and if it is a _STR, it is copied into the char array. */
		v.setDefaultsAndFree();
		char* string=new char[STR_SIZE];
		i>>string;
	
		if(v.getType(string)==_INT){
			v.type=_INT;
			v.val.d=v.getNum(string);
		}
		else{
			v.type=_STR;
			v=string;
		}
		delete[] string;
		return i;
}