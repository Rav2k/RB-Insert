#include <iostream>
#include <cstring>

using namespace std;

#include "node.h"

node::node(){
  right = NULL;
  left = NULL;
  parent = NULL;
  color = 2;
}


node::node(int nodeColor, int num, node *left, node *right, node *parent){
  color = nodeColor;
  data = num;
  this->color = color;
  this->left = left;
  this->right = right;
  this->parent = parent;
}

void node::changeColor(node *newnode, int colors) {
  if(newnode->color == colors){
    //do nothing
  }else{
    newnode->color = colors;
  }
}

int node::getColor(node *node2){
  return node2->color;
}

void node::nodeInfo(node *node3){
  cout<< "Color: "<<node3->color<<endl;
  cout<< "Number: "<<node3->data<<endl;
}

node* node::getParent(){
  return parent;
}

node* node::getGrandParent(){
  if(parent != NULL){
    return parent->getParent();
  }
  return NULL;
}

node::~node(){
  //nothing to do here
}
