#include <iostream>
#include <cstring>

using namespace std;

class node{
 public:
  node();
  node* next;
  node* left;//for the left pointer
  node* right;//for the right pointer
  //node* uncle;
  int color = 0;//1 is black  2 is red
  int data =0;
  int getColor(node *node2);
  void nodeInfo(node *node3);
  void changeColor(node *newnode, int colors);
  node(int nodeColor, int num, node *left, node *right, node *parent);
  node* getParent();
  node* getGrandParent();
  ~node();
  node *getNext();
  node* parent;
};

