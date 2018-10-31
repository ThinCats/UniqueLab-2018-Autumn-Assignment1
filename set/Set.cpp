#include "Set.hpp"

#include <iostream>
inline void SHOU_DONG_YI_CHANG(bool x,std::string s){
	if(x) std::cout<<s<<"####################################################\n##################################################################################################################################################\n";
}
bool Set::empty() const {
	return (root == nullptr);
}
Set::size_type Set::size() const {
	return siz;
}
void Set::clear(){
	delTree(root);
	siz=0;
}
void Set::insert(const key_type& key){
	ins(root,key); return ;
}
Set::Set(){
	root = nullptr;	
	siz = 0;
}
Set::~Set(){
	delTree(root);
}
void Set::delTree(n_ptr &x){
	if(x == nullptr) return ;
	delTree(x -> left);
	delTree(x -> right);
	delete(x);
	x = nullptr;
}
inline Set::n_ptr Set::newNode(const key_type &node_key)const{
	return new node(node_key);
}
inline void Set::colorFlip(node &x){
	SHOU_DONG_YI_CHANG(x.left == nullptr,"colorFlip x.left == nullptr");
	SHOU_DONG_YI_CHANG(x.right == nullptr,"colorFlip x.right == nullptr");
	x.color = !x.color;
	x.left->color = BLACK;
	x.right->color = BLACK;
	x.color = RED;
}
Set::n_ptr Set::r2Left(node &x){ // x.right!=null rotate x.right up
	SHOU_DONG_YI_CHANG(x.right == nullptr,"r2Left x.right == nullptr");
	node &y = *x.right;
	x.right = y.left;
	y.left = &x;
	y.color = x.color;
	x.color = RED;
	return &y;
}
Set::n_ptr Set::r2Right(node &x){ //x.left!=null rotate x.left up 
	SHOU_DONG_YI_CHANG(x.left == nullptr,"r2Right x.left == nullptr");
	if(root == &x) root = x.left;
	node &y = *x.left;
	x.left = y.right; 
	y.right = &x;
	y.color = x.color;
	x.color = RED;
	return &y;
}
void Set::ins(n_ptr &xp,const key_type& key){
	if(xp == nullptr) {
		xp = newNode(key);	
		return ;
	}
	node &x = *xp;
	bool is_less = Compare()(key, x.key);
	bool is_greater = Compare()(x.key,key);
	if(!is_less&&!is_greater) return ;
	if(x.left != nullptr && x.left->color == RED &&
		x.right != nullptr && x.right->color == RED) colorFlip(x);
	if(is_less) {
		ins(x.left, key);
		if(	x.left->color == RED &&
			x.left->left != nullptr && 
			x.left->left->color == RED ) xp = r2Right(x);
	} else {
		ins(x.right, key);
		if( x.right->color == RED) xp = r2Left(x);
	}	
}
void Set::debugTree(n_ptr x){
	if(x == nullptr) {
		std::cout<<"======NODE NULL========\n";
		return;
	}
	x->debug();
	debugTree(x->left);
	debugTree(x->right);
}
void Set::test(){
	using std::cout;
	using std::endl;
	const int t[10]={2,5,1,3,4,9,6,8,7,0};
	freopen("testresult","w",stdout);
	debugTree(root);
	for(int i=0;i<10;i++) {
		cout<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwinsert "<<t[i]<<"wwwwwwwwwwwwwwwww"<<endl;
		insert((key_type)t[i]);
		cout<<"insert over"<<endl;
		debugTree(root);
	}
}
void ttest(){
	Set a; a.test();

}
int main(){ // test
	ttest();std::cout<<"ttest over"<<std::endl;
	return 0;
}