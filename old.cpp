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
int cases(node*&cur3);
void case0(node*&cur3);
int case2(node*&cur3);
int case3(node*&cur3);
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
	cout<<endl;
        //case0(cur->left);
        if(cases(cur->right) == 1){
          return;
        }//red
        else{
          //do nothing
        }
        if(case2(cur->right) == 1){
          return;
        }//triangle
        else{
          //do nothing
        }
        if(case3(cur->right) == 1){
          return;
        }///line
        else{
          return;
        }
      }
      else{
	insert(cur->right, number);//if there is something there already go to the right one which is the higher and run this function again to see where it can fit
	//cur->right->parent = cur;
      }
    }
    else{//same idea as the right one but with when the data that will be inserted is less than that of the current's data
      if(cur->left == NULL){
	cur->left = new node(2, number, NULL, NULL, cur);
	cur->left->parent = cur;
	//case0(cur->left);
        if(cases(cur->left) == 1){
	  return;
	}//red
	else{
	  cout<<"Did not do case 1"<<endl;
	  //do nothing
	}
	if(case2(cur->left) == 1){
	  cout<<"case 2 finished"<<endl;
	  return;
	}//triangle
	else{
	  cout<<"Did not do case 2"<<endl;
	  //do nothing
	}
        if(case3(cur->left)==1){
	  return;
	}///line
	else{
	  cout<<"Did not do case 3"<<endl;
	  return;
	}
      }
      else{
	insert(cur->left, number);
	//cur->left->parent = cur;//set the parent of the left to the cur
      }
    }
    case0(cur);
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

int cases(node*&cur3){  
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
	  return 1;
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
	return 1;
       }
  return 0;
}

//used the smae generating function as binary tree
void fileGen(){//taking the numbers from the text file and making the base tree
  ifstream numbers("numbers2.txt");
  srand(time(NULL));
  int num = 0;
  vector<int> nums;
  while (!numbers.eof()) {
    numbers >> num;
    nums.push_back(num);
  }
  int randomIndex = 0;
  int counter = 0;
  while (counter != 10) {
    randomIndex = (rand() % nums.size()) + 1;
    num = nums.at(randomIndex);
    insert(root, num);
    counter++;
    
  }
  cout<<"done";
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

int case2(node*&cur3){
  cout<<cur3<<endl;
  if(cur3->parent !=NULL && cur3->parent->parent != NULL){
    if(cur3->parent->data > cur3->parent->parent->data){
      //Uncle is on the left
      if((cur3->parent->parent->left == NULL || cur3->parent->parent->left->color == 1) && cur3->parent->left == cur3 && cur3->parent->color == 2){
	node *temp2 = cur3->parent;
	cur3->parent->parent->right = cur3;
        cur3->right = temp2;
        //making sure everthing points right
        cur3->parent->parent->right->parent = cur3->parent->parent;
        cur3->right->parent = cur3;
        return 1;
      }else{
        //do nothing
      }
    }

    else if(cur3->parent->data<cur3->parent->parent->data){
      //Uncle is on right
      if((cur3->parent->parent->right == NULL || cur3->parent->parent->right->color == 1) && cur3->parent->right == cur3 && cur3->parent->color == 2){
	node *temp = cur3->parent;
	cur3->parent->parent->left = cur3;
	cur3->left = temp;
        //making sure everthing points right
        cur3->parent->parent->left->parent = cur3->parent->parent;
        cur3->left->parent = cur3;
	return 1;
      }else{
        //do nothing
      }
    }
    
  }
return 0;
}


int case3(node*&cur3){
  if(cur3->parent != NULL && cur3->parent->parent != NULL){
      if(cur3->parent->data>cur3->parent->parent->data){
        //uncle on left
        if((cur3->parent->parent->left == NULL || cur3->parent->parent->left->color == 1)&& cur3->parent->right == cur3){
          if(cur3->parent->left!=NULL){
            cur3->parent->parent->right = cur3->parent->left;
          }
          cur3->parent->left = cur3->parent->parent;
          cur3->parent->parent->left = cur3->parent->parent->left;
          cur3->parent->right = cur3;
          cur3->parent->color = 1;
          cur3->parent->parent->color = 2;
          return 1;
      }

      else if(cur3->parent->data<cur3->parent->parent->data && cur3->parent->parent->right != NULL){
        //uncle is right
        if(cur3->parent->parent->right->color == 1 && cur3->parent->left == cur3){
          if(cur3->parent->right != NULL){
            cur3->parent->parent->left = cur3->parent->right;
          }
          cur3->parent->right = cur3->parent->parent;
          cur3->parent->parent->right = cur3->parent->parent->right;
          cur3->parent->left = cur3;
          cur3->parent->color = 1;
          cur3->parent->parent->color = 2;
          return 1;

	  /*
	     node *temp;
228        node *temp2;
229        temp = cur3->left;
230        temp2 = cur3->parent->parent;
231        cur3->parent->parent->left = cur3;
232        cur3->left = cur3->parent;
233        //making everything right
234        cur3->parent->right = temp;
235        cur3->parent->parent->left->parent = temp2;
236        cur3->left->parent = cur3;
	   */
        }
      }
      return 0;
      }
}
  return 0;
}
