#include "Set.hpp"

inline bool Set::isRed(const n_ptr &px) const{
	return (px != nullptr && px->color == RED);
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
	int x = find(root,key);
	if(!x) ins(root,key); 
	return ;
}

Set::size_type Set::erase(const key_type& key){
	size_type res = find(root,key);
	if(res) del(root,key);
	return res;
}

Set::size_type Set::count(const key_type& key){
	return find(root,key);
}
//Complete Review
Set::Set(){
	root = nullptr;	
	siz = 0;
}
//Complete Review
Set::~Set(){
	delTree(root);
}
//Complete Review
void Set::delTree(n_ptr &px){
	if(px == nullptr) return ;
	delTree(px -> left);
	delTree(px -> right);
	delete(px);
	px = nullptr;
	siz--;
}
//Complete Review
inline Set::n_ptr Set::newNode(const key_type &node_key) const{
	return new node(node_key);
}
//Complete Review
Set::size_type Set::find(const n_ptr &px,const key_type& key) const{ // return 0 not find 1 find
	if(px == nullptr) return 0;
	bool is_less = Compare()(key, px->key);
	bool is_greater = Compare()(px->key, key);
	if(!is_less&&!is_greater) return 1;	
	if(is_less) return find(px->left, key);
		else return find(px->right, key);
}
//Complete Review
Set::key_type Set::findMin(const node &x) const { // return key
	if(x.left == nullptr) return x.key;
	return findMin(*x.left);
}
//Complete Review
Set::key_type Set::findMax(const node &x) const { // return key
	if(x.right == nullptr) return x.key;
	return findMax(*x.right);
}
//Complete Review
inline void Set::colorFlip(node &x){
	x.color ^= 1;
	if(x.left!=nullptr) x.left->color ^= 1;
	if(x.right!=nullptr) x.right->color ^= 1;
}
//Complete Review
void Set::r2L(n_ptr &px){ // x.right!=null rotate x to left son
	n_ptr py = px->right;
	px->right = py->left;
	py->left = px;
	py->color = px->color;
	px->color = RED;
	px = py;
}
 //Complete Review
void Set::r2R(n_ptr &px){ //x.left!=null rotate x to right son 
	n_ptr py = px->left;
	px->left = py->right; 
	py->right = px;
	py->color = px->color;
	px->color = RED;		
	px = py;
}
//Complete Review
void Set::d2R(n_ptr &px){ // pushdown the RED edge to right son 
	colorFlip(*px);
	if(px->left != nullptr && isRed(px->left->left)) {
		r2R(px);
		colorFlip(*px);
	}
}
//Complete Review
void Set::d2L(n_ptr &px){ // pushdown the RED edge to left son 
	colorFlip(*px);	
	if(px->right != nullptr && isRed(px->right->left)) {
		r2R(px->right);
		r2L(px);
		colorFlip(*px);
	}
}
//Complete Review
void Set::fixUp(n_ptr &px){
	if(isRed(px->right)) r2L(px);
	if(isRed(px->left) && isRed(px->left->left)) r2R(px);
	if(isRed(px->left) && isRed(px->right)) colorFlip(*px);	
}
//Complete Review
void Set::ins(n_ptr &px,const key_type& key){	
	if(px == nullptr) {
		px = newNode(key);
		siz++;
		return ;	
	}
	bool is_less = Compare()(key, px->key);
	bool is_greater = Compare()(px->key,key);
	if(!is_less&&!is_greater) return ;
	if(is_less) ins(px->left, key);
		else ins(px->right, key);	
	fixUp(px);
	return ;
}
using std::cout;
using std::endl;
//TODO d2L/d2R change the px, px only describe the position(some node's son),
//	after the change the cmp is changed
// d2L might r2L 
// d2R might r2R 
// update the is_greater solve the problem
void Set::del(n_ptr &px,const key_type& key){
	bool is_less = Compare()(key, px->key);
	bool is_greater = Compare()(px->key,key);
	if(is_less){
		if(!isRed(px->left)&&!isRed(px->left->left)) d2L(px);
		del(px->left,key);
	} else {
		if(isRed(px->left)) {
			r2R(px); 
			is_greater = Compare()(px->key,key);
		}
		if(!is_greater && px->right == nullptr ) { // find at bottom
			delTree(px); 
			return ;
		}
		if(!isRed(px->right)&&!isRed(px->right->left)) {
			d2R(px);
			is_greater = Compare()(px->key,key);
		}
		if(!is_greater){ // find not at bottom
			px->key = findMin(*(px->right));
			delMin(px->right);
		} else del(px->right,key); // find in right
	}
	fixUp(px);
	return ;
}
// TODO same problem with del()
// NOT the problem the change of px don't impact the following process  
// Complete Review
void Set::delMin(n_ptr &px){
	if(px->left==nullptr) {
		delTree(px);
		return ;
	}
	if(!isRed(px->left) && !isRed(px->left->left) ) d2L(px); 
	delMin(px->left);
	fixUp(px);
	return ;
}