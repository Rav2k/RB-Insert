#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "node.h"
#include <random>

using namespace std;

void fileGen();
void insert(node *&cur, int number);
void print(node *cur2, int layers);
void cases(node*&cur3);
void case0(node*&cur3);
void case2(node*&cur3);
void case3(node*&cur3);
node *root = NULL;

int main(){//number 1 is black number 2 is red 
  int userInput = 0;
  bool loop = false;
  
  do{
    cout<<"type '1' to generate 10 numbers from a file"<<endl;
    cin>>userInput;
    cin.get();

    if(userInput== 1){
      cout<<"Generating numbers..."<<endl;
      fileGen();//put in the numbers from the file
      cout<<"Done!"<<endl;
      loop = true;
    }

    else{
      cout<<"Invalid!!"<<endl;
      cout<<endl;
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
    case0(cur);
    cases(cur);
    case2(cur);
    cout<<"done with all cases"<<endl;
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
  return;
}

void fileGen(){
  vector<int> numText;
  ifstream text("numbers_for_Red_Black_Tree.txt");
  srand(time(NULL));
  int number =0;
  while(!text.eof()){
    text>>number;
    numText.push_back(number);
  }
  int index=0;
  int count=0;
  while(count != 10){
    index = (rand() % 999) +1;
    number = numText.at(index);
    cout<<number<<" ";
    insert(root, number);
    count++;
  }
  //done
  return;
}

void case0(node*&cur3){
  node *temp;
   temp = cur3;
   while(temp->parent !=NULL){
     temp = temp->parent;
   }
   if(temp->color != 1){
     temp->color =1;
   }else{
     //do notthing
   }

}

void case2(node*&cur3){
  if(cur3->parent != NULL &&cur3->parent->parent != NULL && cur3->parent->parent->right != NULL && cur3->parent->parent->left != NULL){

    if(cur3->parent->data>cur3->parent->parent->data && cur3->parent->parent->left != NULL){
      //Uncle is on the left
      if(cur3->parent->parent->left->color = 1 && cur3->parent->left == cur3){
        cur3->parent->parent->right = cur3;
        cur3->right = cur3->parent;

        //making sure everthing points right
        cur3->parent->parent->right->parent = cur3->parent->parent;
        cur3->right->parent = cur3;
        //return;
      }else{
        //do nothing
      }
    }

    else if(cur3->parent->data<cur3->parent->parent->data && cur3->parent->parent->right != NULL){
      //Uncle is on right
      if(cur3->parent->parent->right->color = 1 && cur3->parent->right == cur3){
        node *temp;
        node *temp2;
        temp = cur3->left;
        temp2 = cur3->parent->parent;
        cur3->parent->parent->left = cur3;
        cur3->left = cur3->parent;
        //making everything right
        cur3->parent->right = temp;
        cur3->parent->parent->left->parent = temp2;
        cur3->left->parent = cur3;
        //return;
      }else{
        //do nothing
      }
    }
  }
  return;
}

void case3(node*&cur3){
  if(cur3->parent != NULL &&cur3->parent->parent != NULL && cur3->parent->parent->right != NULL && c\
ur3->parent->parent->left != NULL){

      if(cur3->parent->data>cur3->parent->parent->data && cur3->parent->parent->left != NULL){
        //uncle on left
        if(cur3->parent->parent->left->color = 1 && cur3->parent->right == cur3){
          if(cur3->parent->left!=NULL){
            cur3->parent->parent->right = cur3->parent->left;
          }
          cur3->parent->left = cur3->parent->parent;
          cur3->parent->parent->left = cur3->parent->parent->left;
          cur3->parent->right = cur3;
          cur3->parent->color = 1;
          cur3->parent->parent->color = 2;
          return;
        }else{
          //do nothing
          return;
        }
      }

      else if(cur3->parent->data<cur3->parent->parent->data && cur3->parent->parent->right != NULL){
        //uncle is right
        if(cur3->parent->parent->right->color = 1 && cur3->parent->left == cur3){
          if(cur3->parent->right != NULL){
            cur3->parent->parent->left = cur3->parent->right;
          }
          cur3->parent->right = cur3->parent->parent;
          cur3->parent->parent->right = cur3->parent->parent->right;
          cur3->parent->left = cur3;
          cur3->parent->color = 1;
          cur3->parent->parent->color = 2;
          return;
        }else{
          //do nothing
          return;
        }
      }
      }
  
}
