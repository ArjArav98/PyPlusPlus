#include<iostream>
using namespace std;

#define STR_SIZE 100
#define _INT 1 /* This is a misnomer. All values are double values. */
#define _STR 2
#define _NONE 0
#define YES 1
#define NO 0

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
		/* If string is passed, this constructor executes. First, allocated memory is freed and defaults are restored. The string argument is copied into the 'char' variable in the union. Type and Allocation variables are updated.*/
			setDefaultsAndFree();
			int len=length(string), i;
		
			val.c=new char[len];
			for(i=0; i<len; i++) val.c[i]=string[i];
		
			allocated=YES;
			type=_STR;
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
	public: void setString(const char* string){
		/* If string is passed, this constructor executes. First, allocated memory is freed and defaults are restored. The string argument is copied into the 'char' variable in the union. Type and Allocation variables are updated.*/
			setDefaultsAndFree();
			int len=length(string), i;
			
			char* str=new char[len];
			
			for(i=0; i<len; i++) str[i]=string[i];
			for(i=0; i<length(str); i++) str[i]=string[i];
			
			val.c=str;
			
			allocated=YES;
			type=_STR;
	}
	private: void setNum(double num){
		setDefaultsAndFree();
		val.d=num;
		type=_INT;
	}
	public: int Type(){
		return type;
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
	
/* Operator Overloading Functions */
	public: void operator=(double num){
		/* This function overloads the = operator. If a number is passed in, this function will store it in the 'double' variable inside the union. If any allocation has taken place, it is freed. The 'type' variable is accordingly updated. */
			setDefaultsAndFree();
			val.d=num;
			type=_INT;
	}
	public: void operator=(const char* string){
		/* Overloads the = operator. If string is passed, this function executes. First, allocated memory is freed and defaults are restored. The string argument is copied into the 'char' variable in the union. Type and Allocation variables are updated.*/
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
		/*This function overloads the == operator. This function returns 0 if the argument and the double in THIS object are not equal and 1 if they are equal. If the type of THIS object is not a _INT, an exception is thrown.*/
			try{
				if(type==_STR) throw 1;
				else if(type==_INT){
					if(num==val.d) return 1;
					else return 0;
				}
			} catch (int exception){
				cout<<"error: cannot equate type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator==(const char* string){
		/* This function overloads the == operator. 1 or 0 is returned if the variables are equal or not equal respectively. If the type of THIS object is not a _STR, an exception is thrown. */
			try{
				if(type==_INT) throw 1;
				else if(type==_STR){
					if(strEquals(val.c, string)==1) return 1;
					else return 0;
				}
			} catch (int exception){
				if(exception==1) cout<<"error: cannot equate type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	public: int operator==(var &v){
		/* This function overloads the == operator. If the type of variable of THIS object and the type variable of the object passed in are not the same, then an exception is thrown. If not, then the values are checked and 1 or 0 is returned depending upon whether they are equal or not. */
			try{
				if(type==v.Type()){
					if(type==_INT){
						if(v.val.d==val.d) return 1;
						else return 0;
					}
					else if(type==_STR){
						if(strEquals(val.c, v.val.c)==1) return 1;
						else return 0;
					}
				}
				else throw 1;
			} catch (int exception){
				if(exception==1) cout<<"error: cannot equate type 'string' and type 'number'. Also, make sure that both variables are initialised.\n";
			}
			return -1;
	}
	
	public: friend ostream &operator<<(ostream &o, var &v);
	public: friend istream &operator>>(istream &i, var &v);
	
};

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