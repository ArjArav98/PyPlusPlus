// ===============================
// = PythonPlusPlus - Dictionary =
// ===============================
//
//  Created by Arjun Aravind on 2018-01-15.
//  Copyright 2018 Arjun Aravind. All rights reserved.
//


#include"var.h"

#define FAIL 2
#define SUCCESS 1

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
	
	public: void update(var key, var data){
		pos=head;
		while(pos!=NULL){
			if(pos->key==key){
				pos->data=data;
				return;
			}
			pos=pos->next;
		}
		
		temp=new struct Node;
		temp->next=NULL;
		temp->key=key;
		temp->data=data;
		
		pos=head;
		while(pos!=NULL){
			if(pos->next==NULL){
				pos->next=temp;
				return;
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

ostream &operator<<(ostream &o, dict &d){
	
	o<<"{";
	
	d.pos=d.head->next;
	while(d.pos!=NULL){
		int keyType=d.pos->key.Type();
		int dataType=d.pos->data.Type();
		if(d.pos->next!=NULL){
			if(keyType==_INT) o<<d.pos->key<<", ";
			else if(keyType==_STR) o<<"\""<<d.pos->key<<"\": ";
			{
				if(dataType==_INT) o<<d.pos->data<<", ";
				else if(dataType==_STR) o<<"\""<<d.pos->data<<"\", ";
			}
		}
		else{
			if(keyType==_INT) o<<d.pos->key;
			else if(keyType==_STR) o<<"\""<<d.pos->key<<"\": ";
			{
				if(dataType==_INT) o<<d.pos->data;
				else if(dataType==_STR) o<<"\""<<d.pos->data<<"\"";
			}
		}
		d.pos=d.pos->next;
	}
	
	o<<"}";
	
	return o;
}