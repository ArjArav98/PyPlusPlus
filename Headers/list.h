// ==========================
// == PythonPlusPlus - List =
// ==========================
//
//  Created by Arjun Aravind on 2017-12-30.
//  Copyright 2017 Arjun Aravind. All rights reserved.
//

#include"var.h"

#define FAIL 2
#define SUCCESS 1

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
			head->data=10;
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
			var a=23.4; /* random dummy value */
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

ostream &operator<<(ostream &o, list &l){
	/* This function overloads the output stream "<<" operator. The list is printed in the following format:- [34,23,12]; the exact same way a 'list' is printed in python. */
		o<<"[";
		l.pos=l.head->next;
		while(l.pos!=NULL){
			if(l.pos->next==NULL){
				if(l.pos->data.type==_STR) o<<"\""<<l.pos->data<<"\"";
				else o<<l.pos->data;
			}
			else{
				if(l.pos->data.type==_STR) o<<"\""<<l.pos->data<<"\""<<", ";
				else o<<l.pos->data<<", ";
			}
			l.pos=l.pos->next;
		}
		o<<"]";
		return o;
}