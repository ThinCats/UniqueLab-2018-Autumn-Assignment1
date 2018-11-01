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

Set::size_type Set::erase(const key_type& key){
	size_type res = find(*root,key);
// TODO delete()
	return res;
}

Set::size_type Set::count(const key_type& key){
	return find(*root,key);
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
Set::size_type Set::find(const node &x,const key_type& key) const{ // return 0 not find 1 find
	bool is_less = Compare()(key, x.key);
	bool is_greater = Compare()(x.key, key);
	if(!is_less&&!is_greater) return 1;	
	if(is_less) {
		if(x.left == nullptr) return 0;
		else return find(*x.left, key);
	} else {
		if(x.right == nullptr) return 0;
		else return find(*x.right, key);
	}
}
int Set::findMin(const node &x) const { // return key
	if(x.left == nullptr) return x.key;
	return findMin(*x.left);
}
int Set::findMax(const node &x) const { // return key
	if(x.right == nullptr) return x.key;
	return findMax(*x.right);
}

inline void Set::colorFlip(node &x){
	SHOU_DONG_YI_CHANG(x.left == nullptr,"colorFlip x.left == nullptr");
	SHOU_DONG_YI_CHANG(x.right == nullptr,"colorFlip x.right == nullptr");
	x.color ^= 1;
	x.left->color ^= 1;
	x.right->color ^= 1;
}

Set::n_ptr Set::r2L(node &x){ // x.right!=null rotate x to left son
	SHOU_DONG_YI_CHANG(x.right == nullptr,"r2Left x.right == nullptr");
	SHOU_DONG_YI_CHANG(x.left->color == BLACK,"r2Left x.left->color == BLACK");
	node &y = *x.right;
	x.right = y.left;
	y.left = &x;
	y.color = x.color;
	x.color = RED;
	return &y;
}

Set::n_ptr Set::r2R(node &x){ //x.left!=null rotate x to right son 
	SHOU_DONG_YI_CHANG(x.left == nullptr,"r2Right x.left == nullptr");
	SHOU_DONG_YI_CHANG(x.right->color == BLACK,"r2Right x.right->color == BLACK");
	node &y = *x.left;
	x.left = y.right; 
	y.right = &x;
	y.color = x.color;
	x.color = RED;
	return &y;
}
Set::n_ptr Set::d2R(node &x){ // pushdown the RED edge to right son 
	n_ptr xp = &x;
	colorFlip(x);
	if(x.left != nullptr && x.left->left != nullptr && 
		x.left->left->color == RED) {
		xp = r2R(x);
		colorFlip(*xp);
	}
	return xp;
}
Set::n_ptr Set::d2L(node &x){ // pushdown the RED edge to left son 
	n_ptr xp = &x;
	colorFlip(x);
	if(x.right != nullptr && x.right->left != nullptr && 
		x.right->left->color == RED) {
		x.right = r2R(*x.right);
		xp = r2L(x);
		colorFlip(*xp);
	}
	return xp;
}
//TODO 
Set::n_ptr Set::fixUp(node &x){
	n_ptr xp = &x;
	if( x.left != nullptr && x.left->color == RED &&
		x.right != nullptr && x.right->color == RED) colorFlip(x);
	if( x.left != nullptr && x.left->color == RED &&
		x.left->left != nullptr && x.left->left->color == RED ) {
		xp = r2R(x);
		colorFlip(*xp);
	}
	if( )

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
			x.left->left->color == RED ) xp = r2R(x);
	} else {
		ins(x.right, key);
		if( x.right->color == RED) xp = r2L(x);
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