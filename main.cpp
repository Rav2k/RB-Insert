#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "node.h"
#include <random>

using namespace std;

void fileGeneration();
void insert(node *&cur, int number);
void print(node *cur2, int layers);
void cases(node*&cur3);
node *root = NULL;

int main(){//number 1 is black number 2 is red 
  char userInput[20];
  bool loop = false;
  
  do{
    cout<<"type 'gen' to generate 10 numbers from a file"<<endl;
    cin>>userInput;
    cin.get();

    if(strcmp(userInput, "gen") == 0){
      cout<<"Generating numbers..."<<endl;
      //fileGeneration();//put in the numbers from the file
      cout<<"Done!"<<endl;
      loop = true;
    }

    else{
      cout<<"Invalid!!"<<endl;
      cout<<endl;
      loop = true;
    }
    
  }while(!loop);

  char user[20];
  int userNum = 0;

  do{
  cout<<"to add type 'add'"<<endl;
  cout<<endl;
  cout<<"to print type 'print'"<<endl;
  cout<<endl;
  cout<<"to quit type 'quit'"<<endl;
    cout<<endl;
    cout<<"What do you want to do?: "<<endl;
    cin.get(user, 20);
    cin.get();
    if(strcmp(user, "add") == 0){
      cout<<"Enter the number: "<<endl;
      cin>>userNum;
      cin.get();
      insert(root, userNum);
      cout<<endl;
      cout<<"Number has been successfully added!"<<endl;
      cout<<endl;
    }
    else if(strcmp(user, "print") == 0){
      cout<<"printing..."<<endl;
      cout<<endl;
      cout<<"Tree: "<<endl;
      cout<<endl;
      print(root, 0);
      cout<<endl;
    }
    else{
      cout<<"type something valid"<<endl;
    }
  }while(strcmp(user, "quit")!=0);

  cout<<endl;
  cout<<"Updated printing..."<<endl;

  print(root, 0);
}

void insert(node *&cur, int number){//adding in a number to the tree!(all the numbers that are inserted should be red)
    if(cur == NULL){//if nothing is there then create the node with the number 
      cur = new node(1, number, NULL, NULL, root);//this would be the root therefore that would need to be black.
      cur->parent = NULL;
      return;
    }
    if(number>=cur->data){//if the number is greater than the current node which is the "root" this case then...
      if(cur->right == NULL){//... check to make sure the right is empty then put that number there
	cur->right = new node(2, number, NULL, NULL, cur);
	cur->right->parent = cur;
	cases(cur->right);
	cout<<endl;
	return;
      }
      else{
	insert(cur->right, number);//if there is something there already go to the right one which is the higher and run this function again to see where it can fit
	cur->right->parent = cur;
      }
    }
    else{//same idea as the right one but with when the data that will be inserted is less than that of the current's data
      if(cur->left == NULL){
	cur->left = new node(2, number, NULL, NULL, cur);
	cur->left->parent = cur;
	cases(cur->left);
	return;
      }
      else{
	insert(cur->left, number);
	cur->left->parent = cur;//set the parent of the left to the cur
      }
    }
      
  }

void print(node *cur2, int layers){
  if(cur2 == NULL){
    return;
  }
  print(cur2->right, layers+1);//right side printing 

  for(int i = 0; i<layers;i++){
    cout<<"     ";
  }

  cout<<cur2->data<<"("<<cur2->color<<")"<<endl;
  print(cur2->left, layers+1);//print the left side
}

 void cases(node*&cur3){  
  //case #1: Uncle is red
  if(cur3->parent != NULL &&cur3->parent->parent != NULL && cur3->parent->parent->right != NULL && cur3->parent->parent->left != NULL){
          cout<<"Nothing is NULL"<<endl;
        if(cur3->parent->data>cur3->parent->parent->data && cur3->parent->parent->left != NULL){
          cout<<"Uncle is on the left"<<endl;
          if(cur3->parent->parent->left->color == 2){
            cur3->parent->parent->left->color = 1;
            cur3->parent->color = 1;
	    cur3->parent->parent->color = 2;
	    if(cur3->parent->parent->parent == NULL){
              cur3->parent->parent->color = 1;
            }else if(cur3->parent->parent->parent != NULL){
              cur3->parent->parent->color = 2;
            }
          }
        }else if(cur3->parent->data<cur3->parent->parent->data && cur3->parent->parent->right != NULL){
          cout<<"Uncle is on right"<<endl;
          if(cur3->parent->parent->right->color == 2){
            cur3->parent->parent->right->color = 1;
	    cur3->parent->parent->color = 2;
	    cur3->parent->color = 1;
	    if(cur3->parent->parent->parent == NULL){
	      cur3->parent->parent->color = 1;	    
	    }else if(cur3->parent->parent->parent != NULL){
	      cur3->parent->parent->color = 2;
	      }
          }
        }
	
       }

  cout<<"check complete...proceed..."<<endl;
  return;
}
