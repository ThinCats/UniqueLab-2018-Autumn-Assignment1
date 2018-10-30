#include "Set.hpp"

#include <iostream>
bool Set::empty() const {
	return (root == NULL);
}
Set::size_type Set::size() const {
	return siz;
}
void Set::clear(){
	delTree(root);
	siz=0;
}
Set::Set(){
	root = NULL;	
	siz=0;
}
Set::~Set(){
	delTree(root);
}
void Set::delTree(n_ptr &root){
	if(root == NULL) return ;
	delTree(root -> left);
	delTree(root -> right);
	delete(root);
	root = NULL;
}
void Set::test(){
	using std::cout;
	using std::endl;
	key_type a,b;
	a=1.0; b=2.0; 
	cout <<b<<" "<<a<<" "<< Compare()(b,a)<<endl;
	cout <<a<<" "<<b<<" "<< Compare()(a,b)<<endl;
	cout<< a<<" "<<a<<" "<<Compare()(a,a)<<endl;
}
int main(){ // test
	Set a; a.test();	
	return 0;
}