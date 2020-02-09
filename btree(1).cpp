#include <iostream>

using namespace std;

template <class T>
 struct btree {
   class btree<T> *right, *left, *parent;
   typedef enum { LEFT, RIGHT } side;
   T value;

   void replace(class btree<T>* exist, class btree<T>* repl, side s ) {
     if(!exist || !repl )
       return; // throw error?
     class btree<T>*parent = exist->parent;
     if (s == LEFT) {
       class btree<T>* oldLeft = exist->left;
       parent->left = repl;
       repl->left = oldLeft;
     } else {
       class btree<T>* oldRight = exist->right;
       parent->right = repl;
       repl->right = oldRight;
     }
   }
       
 void insert(T v) {
     if( v <= value ) {
     	 if(!left) {
	   left = new btree<T>;
	   left->value = v;
	   left->parent = this;
	   cout << "NO LEFT" << endl;
	 } else if (left && left->value <= v) {
	   struct btree<T>* newLeft = new btree<T>;
	   newLeft->value = v;
	   newLeft->parent = this;
	   newLeft->left = left;
	   left->parent = newLeft;
	   left = newLeft;
	   cout << "REPLACE LEFT" << endl;
	 } else {
	   left->insert(v);
	   cout << "INSERT LEFT" << endl;
	 }
     } else {
       if( !right ) {
	 right = new btree<T>;
	 right->value = v;
	 right->parent = this;
	 cout << "NO RIGHT" << endl;
       } else if (right && right->value >= v) {
	 struct btree<T>* newRight = new btree<T>;
	 newRight->value = v;
	 newRight->right=right;
	 right->parent=newRight;
	 newRight->parent=this;
	 right=newRight;
	 cout << "REPLACE RIGHT" << endl;
       } else {
	 right->insert(v);
	 cout << "INSERT RIGHT" << endl;
       }
     }
   };

 void insert(struct btree<T>* node) {
   if (!node)
     return;
   if( node->value <= value ) {
     if(!left) {
       left = node;
       left->parent = this;
     } else if (left && left->value <= node->value) {
       replace(left, node, LEFT);
     } else {
       left->insert(node);
     }
   } else {
       if( !right ) {
	 right = node;
	 right->parent = this;
	 cout << "NO RIGHT" << endl;
       } else if (right && right->value >= node->value) {
	 cout << "REPLACE RIGHT" << endl;
	 replace(right, node, RIGHT);
       } else {
	 right->insert(node);
	 cout << "INSERT RIGHT" << endl;
       }
   }
 };

 btree() : left(NULL), right(NULL), parent(NULL) {};

   struct btree<T>* find(T v) {
     if (value == v)
       return this;
     else if (left && value > v)
       return (left->find(v));
     else if (right && value < v)
       return(right->find(v));
     else
       return NULL;
   }

   void remove(T val) {
     struct btree<T>* found = find(val);
     if( found ) {
       struct btree<T>* parent = found->parent;
       if( parent && parent->left == found ) {
	 if( found->right ) { //move right to current pos
	   replace ( found, found->right, LEFT);
	   if (found->left) 
	     found->right->insert(found->left->value); 
	   //leak?
	 } else if (found->left) {
	   parent->left=found->left;
	 } else {
	   parent->left=NULL;
	 }
	 delete found;
       } else if (parent && parent->right == found ) {
	 if (found->left) {
	   replace( found, found->left, RIGHT);
	   if (found->right)
	     found->left->insert(found->right);
	 } else if (found->right) {
	   parent->right = found->right;
	 } else {
	   parent->right = NULL;
	 }
	 delete found;
       }
     }
   }

  void dump() {
    cout << "VAL: " << value << endl;
    if (left) {
      cout << "LEFT: ";
      left->dump();
    }
    if (right) {
      cout << "RIGHT: ";
      right->dump();
    }
  }

  int num() {
    int count=1;
    count += left ? left->num() : 0;
    count += right ? right->num() : 0;
    return count;
  }
};

main() {
  struct btree<int> it;
  it.value=9;
  cout << "1 Num: " << it.num() << endl;
  it.insert(8);
  cout << "2 Num: " << it.num() << endl;
  it.insert(1);
  cout << "3 Num: " << it.num() << endl;
  it.insert(33);
  cout << "4 Num: " << it.num() << endl;
  it.insert(44);
  cout << "5 Num: " << it.num() << endl;
  it.insert(7);
  cout << "6 Num: " << it.num() << endl;
  it.insert(13);
  cout << "7 Num: " << it.num() << endl;
  it.dump();
  it.remove(8);
  cout << "Rem Num: " << it.num() << endl;
  it.dump();
  it.insert(12);
  it.insert(14);
  cout << "Add Num: " << it.num() << endl;
  it.dump();
}
