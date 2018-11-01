#include "Set.hpp"

#include <iostream>

inline void SHOU_DONG_YI_CHANG(bool x,std::string s){
	if(x) std::cout<<s<<"####################################################\n##################################################################################################################################################\n";
}

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
	if(!x) ins(root,key), siz++; 
	return ;
}

Set::size_type Set::erase(const key_type& key){
	size_type res = find(root,key);
	if(res) del(root,key),siz--;
	return res;
}

Set::size_type Set::count(const key_type& key){
	return find(root,key);
}

Set::Set(){
	root = nullptr;	
	siz = 0;
}

Set::~Set(){
	delTree(root);
}

void Set::delTree(n_ptr &px){
	if(px == nullptr) return ;
	delTree(px -> left);
	delTree(px -> right);
	delete(px);
	px = nullptr;
}

inline Set::n_ptr Set::newNode(const key_type &node_key)const{
	return new node(node_key);
}
Set::size_type Set::find(const n_ptr &px,const key_type& key) const{ // return 0 not find 1 find
	if(px == nullptr) return 0;

	bool is_less = Compare()(key, px->key);
	bool is_greater = Compare()(px->key, key);
	if(!is_less&&!is_greater) return 1;	
	if(is_less) return find(px->left, key);
		else return find(px->right, key);
	
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

void Set::r2L(n_ptr &px){ // x.right!=null rotate x to left son
	SHOU_DONG_YI_CHANG(px->right == nullptr,"r2Left x.right == nullptr");
	SHOU_DONG_YI_CHANG(px->left->color == BLACK,"r2Left x.left->color == BLACK");
	n_ptr py = px->right;
	px->right = py->left;
	py->left = px;
	py->color = px->color;
	px->color = RED;
	px = py;
}
 
void Set::r2R(n_ptr &px){ //x.left!=null rotate x to right son 
	SHOU_DONG_YI_CHANG(px->left == nullptr,"r2Right x.left == nullptr");
	SHOU_DONG_YI_CHANG(px->right->color == BLACK,"r2Right x.right->color == BLACK");
	n_ptr py = px->left;
	px->left = py->right; 
	py->right = px;
	py->color = px->color;
	px->color = RED;
	px = py;
}


void Set::d2R(n_ptr &px){ // pushdown the RED edge to right son 
	colorFlip(*px);
	if(px->left != nullptr && isRed(px->left->left)) {
		r2R(px);
		colorFlip(*px);
	}
}
void Set::d2L(n_ptr &px){ // pushdown the RED edge to left son 
	colorFlip(*px);
	if(px->right != nullptr && isRed(px->right->left)) {
		r2R(px->right);
		r2L(px);
		colorFlip(*px);
	}
}
void Set::fixUp(n_ptr &px){
	if(isRed(px->left) && isRed(px->right)) colorFlip(*px);
	if(isRed(px->left) && isRed(px->left->left)) {
		r2R(px);
		colorFlip(*px);
	}
	if(isRed(px->right)) r2L(px);
}

void Set::ins(n_ptr &px,const key_type& key){

	if(px == nullptr) {
		px = newNode(key);	
		return ;
	}
	bool is_less = Compare()(key, px->key);
	bool is_greater = Compare()(px->key,key);
	if(!is_less&&!is_greater) return ;
	if(isRed(px->left) && isRed(px->right)) colorFlip(*px);
	if(is_less) {
		ins(px->left, key);
		if(isRed(px->left) && isRed(px->left->left)) r2R(px);
	} else {
		ins(px->right, key);
		if(isRed(px->right)) r2L(px);
	}	
}

void Set::del(n_ptr &px,const key_type& key){
	SHOU_DONG_YI_CHANG(px == nullptr,"del px == nullptr");
	bool is_less = Compare()(key, px->key);
	bool is_greater = Compare()(px->key,key);
	if(is_less){
		if(!isRed(px->left)&&!isRed(px->left->left)) d2L(px);
		del(px,key);
	} else {
		if(isRed(px->left)) r2R(px);
		if(!is_greater && px->right == nullptr ) { // find at bottom
			delTree(px); 
			return ;
		}
		if(!isRed(px->right)&&!isRed(px->right->left)) d2R(px);
		if(!is_greater){ // find
			px->key = findMin(*(px->right));
			delMin(px->right);
			return ;
		} else del(px->right,key);

	}
}

void Set::delMin(n_ptr &px){
	SHOU_DONG_YI_CHANG(px == nullptr,"delMin px == nullptr");
	if(px->left==nullptr) {
		delTree(px);
		return ;
	}
	if(!isRed(px->left) && !isRed(px->left->left) ) d2L(px); 
	delMin(px);
	fixUp(px);
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
	using std::cin;
	using std::cout;
	using std::endl;
	int a[100], tot=0;
	freopen("testdata","r",stdin);
	freopen("testresult","w",stdout);
	debugTree(root);
	cout<<"??"<<endl;
	int n; cin>>n; cout<<n<<endl;

	for(int i=1;i<=n;i++){
		int x,y; cin>>y>>x; 
		a[++tot]=x;	
		if(y){
			cout<<"**********insert "<<x<<"*************\n";
			insert(x);
			cout<<"**********insert over**************\n";
		} else {
			cout<<"**********erase "<<x<<"*************\n";
			erase(x);
			cout<<"**********erase over**************\n";
		}
		cout<<"now siz = "<<size()<<endl;
		debugTree(root);
		for(int j=1;j<=tot;j++) {
			cout<<"count "<<a[j]<<" result is"<<count(a[j])<<endl;
		}
	}	
	cout<<"*************over clear"<<endl;
	clear();
	cout<<"empty result is "<<empty()<<endl;
	debugTree(root);
}
void ttest(){
	Set a; a.test();

}
int main(){ // test
	ttest();std::cout<<"ttest over"<<std::endl;
	return 0;
}