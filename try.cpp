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
void search(node*cur, int num);
void deletion(node *cur, int num);
void correctDelete(node *cur, node *par);
node *root = NULL;

int main(){//number 1 is black number 2 is red 
  int userInput = 0;
  bool loop = false;
  
  do{
    cout<<"type '1' to generate 10 numbers from a file; type '2' to skip and do manual adding"<<endl;
    cin>>userInput;
    cin.get();

    if(userInput== 1){
      cout<<"Generating numbers..."<<endl;
      fileGen();//put in the numbers from the file
      cout<<"Done!"<<endl;
      loop = true;
    }

    else{
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
    cout<<"to search type 'search'"<<endl;
    cout<<endl;
    cout<<"to delete type 'delete'"<<endl;
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
    else if(strcmp(user, "search")==0){
      cout<<"Enter number: "<<endl;
      cin>>userNum;
      cin.get();
      search(root, userNum);
    }
    else if(strcmp(user, "delete")==0){
      cout<<"Number to delete: "<<endl;
      cin>>userNum;
      cin.get();
      deletion(root, userNum);
      cout<<"Deleted"<<endl;
    }
    else{
      cout<<"type something valid"<<endl;
    }
  }while(strcmp(user, "quit")!=0);

  cout<<endl;
  cout<<"Updated printing..."<<endl;

  print(root, 0);
}

void insert(node *&cur, int number){//adding in a number to the tree!(all the numbers that are inserte\
d should be red)
  int cas3=0;
    if(cur == NULL){//if nothing is there then create the node with the number
      cur = new node(1, number, NULL, NULL, root);//this would be the root therefore that would need t\
o be black.
      cur->parent = NULL;
      case0(cur);
      return;
    }

    if(number>=cur->data){//if the number is greater than the current node which is the "root" this ca\
se then...
      if(cur->right == NULL){//... check to make sure the right is empty then put that number there
        cur->right = new node(2, number, NULL, NULL, cur);
        cur->right->parent = cur;
        node *temp2= cur->right;
        cout<<endl;
        case0(cur->right);
        if(cases(cur->right) == 1){
          cout<<"case 1 finished"<<endl;
          return;
        }//red
        else{
          cout<<"Did not do case 1"<<endl;
          //do nothing
        }
        if(case2(cur->right) == 1){
          cout<<"case 2 finished"<<endl;
	  return;
        }//triangle
        else{
          cout<<"Did not do case 2"<<endl;
          //do nothing
	}
	if(case3(cur->right) == 1){//temp2
          cout<<"case 3 finished"<<endl;
          return;
        }//line
        else{
          cout<<"Did not do case 3"<<endl;
          return;
	  }
      }
      else{
        insert(cur->right, number);//if there is something there already go to the right one which is \
the higher and run this function again to see where it can fit
        //cur->right->parent = cur;
      }
    }
    else{//same idea as the right one but with when the data that will be inserted is less than that o\
f the current's data
      if(cur->left == NULL){
        cur->left = new node(2, number, NULL, NULL, cur);
        cur->left->parent = cur;
        node *temp=cur->left;
        case0(cur->left);
	if(cases(cur->left) == 1){
          cout<<"case 1 finished"<<endl;
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
        if(case3(cur->left)==1){//if problem do temp
	  cout<<"case 3 finished"<<endl;
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
  }

void print(node *cur2, int layers){
  if(cur2 == NULL){
    return;
  }
  print(cur2->left, layers+1);//right side printing 

  for(int i = 0; i<layers;i++){
    cout<<"     ";
  }

  cout<<cur2->data<<"("<<cur2->color<<")"<<endl;
  print(cur2->right, layers+1);//print the left side
}

int cases(node*&cur3){  
  //case #1: Uncle is red
  //in case the current node's parent is the root therefore the grandparent doesn't exist
  if(cur3->parent != NULL){
    if(cur3->parent->parent == NULL){
      if(cur3->data>cur3->parent->data && cur3->parent->left != NULL && (cur3->left !=NULL || cur3->right != NULL || cur3->parent->left->left != NULL || cur3->parent->left->right != NULL)){
	if(cur3->parent->left->color == 2){
            cur3->parent->left->color = 1;
            cur3->color = 1;
            cur3->parent->color = 2;
            if(cur3->parent->parent == NULL){
              cur3->parent->color = 1;
            }else if(cur3->parent->parent != NULL){
              cur3->parent->color = 2;
            }
      }
	
      }else if(cur3->data<cur3->parent->data && cur3->parent->right != NULL && (cur3->left !=NULL || cur3->right != NULL || cur3->parent->right->left != NULL || cur3->parent->right->right != NULL)){
	if(cur3->parent->right->color == 2){
            cur3->parent->right->color = 1;
            cur3->parent->color = 2;
            cur3->color = 1;
            if(cur3->parent->parent == NULL){
              cur3->parent->color = 1;
            }else if(cur3->parent->parent != NULL){
              cur3->parent->color = 2;
              }
          }
        }
      }
    //if grandparent exists
    if(cur3->parent->parent != NULL){
        if(cur3->parent->data>cur3->parent->parent->data && cur3->parent->parent->left != NULL){
          if(cur3->parent->parent->left->color == 2){
            cur3->parent->parent->left->color = 1;
            cur3->parent->color = 1;
	    cur3->parent->parent->color = 2;
	    if(cur3->parent->parent->parent == NULL){
              cur3->parent->parent->color = 1;
            }else if(cur3->parent->parent->parent != NULL){
              cur3->parent->parent->color = 2;
            }
	    cout<<"Case 1 checked(done)"<<endl;
          return 1;
	  }
	  
        }else if(cur3->parent->data<cur3->parent->parent->data && cur3->parent->parent->right != NULL){
          //cout<<"Uncle is on right"<<endl;
          if(cur3->parent->parent->right->color == 2){
            cur3->parent->parent->right->color = 1;
	    cur3->parent->parent->color = 2;
	    cur3->parent->color = 1;
	    if(cur3->parent->parent->parent == NULL){
	      cur3->parent->parent->color = 1;	    
	    }else if(cur3->parent->parent->parent != NULL){
	      cur3->parent->parent->color = 2;
	      }
	    cout<<"Case 1 checked(done)"<<endl;
          return 1;
	  }
        }
        
    }
   }
  cout<<"Case 1 checked"<<endl;
  return 0;
}

//used the smae generating function as binary tree
void fileGen(){//taking the numbers from the text file and making the base tree
  ifstream numbers("numbers2.txt");
  srand(time(NULL));
  int num = 0;
  while (!numbers.eof()) {
    numbers >> num;
    insert(root, num);
  }
  
}

void case0(node*&cur3) {
  node *temp;
  temp = cur3;
  while (temp->parent != NULL) {
    temp = temp->parent;
  }
  if (temp->color != 1) {
    temp->color = 1;
  }
}

int case2(node*&cur3){
  if(cur3->parent !=NULL && cur3->parent->parent != NULL){
    if(cur3->parent->data > cur3->parent->parent->data){
      //Uncle is on the left
      if((cur3->parent->parent->left == NULL || cur3->parent->parent->left->color == 1) && cur3->parent->left == cur3 && cur3->parent->color == 2&&cur3->parent->parent !=NULL){
        node *temp = cur3->parent;
        node *temp2 = cur3;
        node *temp4 = cur3->parent->parent;
        //delete cur3->parent->right;
        temp2->parent->parent->right = temp2;
        temp2->right = temp;
        temp2->parent = temp4;
        temp->parent = temp2;//?
        //temp2->left->parent = temp2;
        temp2->right->left= NULL;
        //making sure everthing points right
        //temp->right = temp4;
        //temp->parent = cur3;
        //cur3->left->parent = cur3;
        cout<<"Case 2 checked(done)"<<endl;
	case3(temp2->right);
	return 1;
      }else{
        //do nothing
      }
    }

    else if(cur3->parent->data<cur3->parent->parent->data){
      //Uncle is on right
      if((cur3->parent->parent->right == NULL || cur3->parent->parent->right->color == 1) && cur3->parent->right == cur3 && cur3->parent->color == 2 && cur3->parent->parent != NULL){
	node *temp = cur3->parent;
	node *temp2 = cur3;
	node *temp4 = cur3->parent->parent;
	//delete cur3->parent->right;
	temp2->parent->parent->left = temp2;
	temp2->left = temp;
	temp2->parent = temp4;
	temp->parent = temp2;//?
	//temp2->left->parent = temp2;
	temp2->left->right= NULL;
        //making sure everthing points right
	//temp->right = temp4;
        //temp->parent = cur3;
	//cur3->left->parent = cur3;
	cout<<"Case 2 checked(done)"<<endl;
	case3(temp2->left);
	return 1;
      }else{
        //do nothing
      }
    }   
  }
  cout<<"Case 2 checked"<<endl;
return 0;
}
int case3(node*&cur3){
  if(cur3->parent != NULL && cur3->parent->parent != NULL){
      if(cur3->parent->data>cur3->parent->parent->data && (cur3->parent->parent->left == NULL||c\
ur3->parent->parent->left->color == 1)&&cur3->parent->left==NULL&&cur3->color==2&&cur3->parent->color==2){//node and parent must be red.
        //uncle on left
        if(cur3->parent->right == cur3){
          node *grand2 = cur3->parent->parent;
          node *par2 =cur3->parent;
          node *save2 = par2->left;
          if(cur3->parent->left == NULL){
            if(root->data == grand2->data){
            root=par2;
            par2->right=cur3;
            par2->left= grand2;

            grand2->left = save2;//?
            par2->parent= grand2->parent;
            grand2->parent=par2;
            grand2->right=NULL;//?
            par2->color=1;
            grand2->color=2;
            }else{
	      grand2->parent->right=par2;
	      par2->right=cur3;
              par2->left= grand2;

            grand2->left = save2;//?
            par2->parent= grand2->parent;
	    
            grand2->parent=par2;
            grand2->right=NULL;//?
            par2->color=1;
            grand2->color=2;
            }
	    }else{
            node *unc2 = grand2->left;
            if(root->data == par2->data){
              root =par2;
              par2->right=cur3;
              par2->left= grand2;

            grand2->left->left = unc2;
            grand2->left = save2;//?
            par2->parent= grand2->parent;
            grand2->parent=par2;
            //grand2->right=NULL;
            par2->color=1;
            grand2->color=2;

            }else{
              par2->right=cur3;
               par2->left= grand2;
            grand2->left->left = unc2;
            grand2->left = save2;//?
            par2->parent= grand2->parent;
            grand2->parent=par2;
            //grand2->right=NULL;
            par2->color=1;
            grand2->color=2;
              /*par2->right=cur3;
            grand2->left->left = unc2;
            par2->left= grand2;
            grand2->left = save2;//?
            par2->parent= grand2->parent;
            grand2->parent=par2;
            par2->color=1;
            grand2->color=2;*/
            }

          }
	  cout<<"Case 3 checked(done)"<<endl;
          return 1;
        }
      }
      else if(cur3->parent->data<cur3->parent->parent->data && (cur3->parent->parent->right == NULL||cur3->parent->parent->right->color == 1)&&cur3->parent->right==NULL&&cur3->color==2&&cur3->parent->color==2){//node and parent must be red.
        //uncle is right
        if(cur3->parent->left == cur3){
          node *grand = cur3->parent->parent;
          node *par =cur3->parent;
          node *save = par->right;
          if(cur3->parent->right == NULL){
            //par->right = grand->left;
            if(root->data == grand->data){
              root=par;
            par->right=grand;
            par->left= cur3;
            grand->left = save;
            par->parent= grand->parent;
            grand->parent=par;
            //par->parent->left=par;
            par->color=1;
            grand->color=2;
	    return 1;
	    }else{
              par->right=grand;
            par->left= cur3;
            par->parent= grand->parent;
            grand->left = save;
            grand->parent=par;
            par->parent->left=par;//?
            par->color=1;
            grand->color=2;
	    return 1;
            }

          }else{
            node *unc = grand->right;
            if(root->data==grand->data){
            root=par;
            par->right=grand;
            grand->right->right = unc;
            par->left= cur3;
            grand->left = save;
            par->parent= grand->parent;
            grand->parent=par;
	    //par->parent->left=par;
            //grand2->left=NULL;
            par->color=1;
            grand->color=2;
	    return 1;
            }else{
	      par->right=grand;
            grand->right->right = unc;
            par->left= cur3;
            grand->left = save;
            par->parent= grand->parent;
            grand->parent=par;
	    par->parent->left=par;
            //grand2->left=NULL;
            par->color=1;
            grand->color=2;
	    return 1;
          }
          cout<<"Case 3 checked(done)"<<endl;
        }
      }

      }
  cout<<"Case 3 checked"<<endl;
  return 0;
  }

  cout<<"Case 3 checked"<<endl;
  return 0;
}

void search(node* cur, int num){//cur should start at the root
  if(cur == NULL){
    cout<<"Number is not in the tree"<<endl;
    return;
  }else if(cur->data == num){
    cout<<"Number found"<<endl;
    return;
  }
  else{
    if(num>cur->data){//recursively transverse down the tree
      search(cur->right, num);
    }else{
      search(cur->left, num);
    }
  }
}


void deletion(node *cur, int num){
  if(cur==NULL){
    return;
  }
  else if(num>cur->data){
    deletion(cur->right, num);
  }
  else if(num<cur->data){
    deletion(cur->left, num);
  }

  else if(num == cur->data){
    if(cur->right == NULL && cur->left == NULL){
      if(cur==root){
	delete cur;
	return;
      }
      if(cur->color == 2){
	delete cur;
	return;
      }
      else{
	node *temp = cur->right;
	node *temp2 = cur->parent;
	node *temp3= cur->parent->right;
	if(cur->parent->left == cur){
	  cur->parent->left = NULL;
	  delete cur;
	  temp2->right = temp2->right->left;
	  temp2->right->parent = temp2;
	  temp2->right->right = temp3;
	  temp3->left = NULL;
	  temp2->right->color = 1;
	  temp2->parent->right = temp2->right;
	  temp2->right->left = temp2;
	  temp2->parent = temp2->right;
	  temp2->right = NULL;
	  temp2->color = 1;
	  temp2->parent->color =2;
	  temp2->parent->right->color =1;
	}
	else if(cur->parent->right == cur){
	   cur->parent->right = NULL;
	   delete cur;
	}
	 
	//correctDelete(temp, temp2);
	return;
      }
      return;
    }
    //one left child
    else if(cur->right == NULL){
      if(cur->color==2){
	node *temp = cur->left;
	delete cur;
	return;
      }
      else{
	if(cur->left->color ==2){
	  node *temp = cur->left;
	  delete cur;
	  temp->color=1;
	  return;
	}
	else{
	  node *temp = cur->left;
	  delete cur;
	  correctDelete(temp, temp->parent);
	  return;
	}
      }
      return;
    }
    else if(cur->left == NULL){//right
      if(cur->color == 2){
	node *temp =cur->right;
	delete cur;
	return;
      }
      else{
	if(cur->right->color == 2){
	  node *temp = cur->right;
	  delete cur;
	  temp->color = 1;
	  return;
	}
	else{
	  node *temp = cur->right;
	  delete cur;
	  correctDelete(temp, temp->parent);
	  return;
	}
      }
      return;
    }
    else{//two children 
      node *successor = cur->left;
      node *succParent = cur;

      while(successor->right != NULL){
	succParent = successor;
	successor = successor->right;
      }
      if(succParent != cur){
	succParent->right = successor->left;
	if(successor->color == 2){
	  if(succParent->right != NULL && succParent->right->color == 2){
	    succParent->right->color = 2;
	  }
	  else{
	    correctDelete(succParent->right, succParent);
	  }
	}
      }
      else{
	succParent->left = successor->left;
	if(successor->color==2){
	  if(succParent->left != NULL && succParent->left->color == 2){
	    succParent->left->color = 1;
	  }
	  else{
	    correctDelete(succParent->left, succParent);
	    
	  }
	}
      }
      cur->data = successor->data;
      delete successor;
      return;
    }
  }
  return;
}

void correctDelete(node *cur, node *par){
  node *temps =NULL;//sibiling holder
  if(cur==NULL){
    return;
  }
  else{
    if(par->left == cur){
      temps = par->right;
    }else{
      temps =par->left;
    }
    if(temps != NULL){
      if(temps->color == 2 && par->color == 1){
	temps->color = 1;
	par->color=2;
	if(temps->parent->right == temps){
	  //rotate the par left
	  node *temp = par->right;
          par->right = temp->left;
          if(temp->left!=NULL){
            temp->left->parent=par;
          }
          temp->left= par;
          temp->parent = par->parent;
          if(par->parent==NULL){
            root=temp;
          }
          else if(par==par->parent->left){
            par->parent->left = temp;
          }
          else{
            par->parent->right = temp;
          }
          par->parent = temp;
        }else{
	  //rotate par right
	  node *temp = par->left;
	  par->left = temp->right;
	  if(temp->right!=NULL){
	    temp->right->parent=par;
	  }
	  temp->right = par;
	  temp->parent = par->parent;
	  if(par->parent==NULL){
	    root=temp;
	  }
	  else if(par==par->parent->left){
	    par->parent->left = temp;
	  }
	  else{
	    par->parent->right = temp;
	  }
	  par->parent = temp;
	}
    }
      if(temps->color == 1 && par->color == 1 && (temps->left == NULL || temps->left->color == 1) &&(temps->right == NULL || temps->right->color==1)){
	temps->color = 2;
	correctDelete(par, par->parent);
      }
      else if(temps->color == 2 && par->color == 1 && (temps->left == NULL || temps->left->color == 1) &&(temps->right == NULL || temps->right->color==1)){
	par->color=1;
	temps->color=2;
	return;
      }
      else if(temps->parent->left == temps && temps->color == 1 && (temps->left==NULL || temps->left->color == 1)&& temps->right != NULL && temps->right->color == 2){
	temps->color = 2;
	temps->right->color = 1;
	//rotate temps left
	node *temp = temps->right;
          temps->right = temp->left;
          if(temp->left!=NULL){
            temp->left->parent=temps;
          }
          temp->left = temps;
          temp->parent = temps->parent;
          if(temps->parent==NULL){
            root=temp;
          }
          else if(temps==temps->parent->left){
            temps->parent->left = temp;
          }
          else{
            temps->parent->right = temp;
          }
          temps->parent = temp;
        
      }
      else if(temps->parent->right==temps && temps->color == 1 &&(temps->right == NULL || temps->right->color == 1) && temps->left->color==2){
	temps->color = 2;
	temps->left->color = 1;
	//rotate right temps
	node *temp = temps->left;
          temps->left = temp->right;
          if(temp->right!=NULL){
            temp->right->parent=temps;
          }
          temp->right = temps;
          temp->parent = temps->parent;
          if(temps->parent==NULL){
            root=temp;
          }
          else if(temps==temps->parent->left){
            temps->parent->left = temp;
          }
          else{
            temps->parent->right = temp;
          }
          temps->parent = temp;
      }
      if(temps->color == 1 && temps->parent->left==temps && temps->left != NULL && temps->left->color == 2){
	temps->color = par->color;
	par->color = 1;
	//rotate right par
	node *temp = par->left;
          par->left = temp->right;
          if(temp->right!=NULL){
            temp->right->parent=par;
          }
          temp->right = par;
          temp->parent = par->parent;
          if(par->parent==NULL){
            root=temp;
          }
          else if(par==par->parent->left){
            par->parent->left = temp;
          }
          else{
            par->parent->right = temp;
          }
          par->parent = temp;
	return;
      }
      else if(temps->color == 1 && temps->parent->left==temps && temps->left != NULL && temps->left->color == 2){
	temps->color = par->color;
	par->color = 1;
	//rotate left par
	node *temp = par->right;
          par->right = temp->left;
          if(temp->left!=NULL){
            temp->left->parent=par;
          }
          temp->left= par;
          temp->parent = par->parent;
          if(par->parent==NULL){
            root=temp;
          }
          else if(par==par->parent->left){
            par->parent->left = temp;
          }
          else{
            par->parent->right = temp;
          }
          par->parent = temp;
	return;
      }
    }
  }
}

