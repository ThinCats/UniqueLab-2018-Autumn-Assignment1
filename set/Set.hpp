#ifndef _SET_HPP
#define _SET_HPP
#include <iostream>
#include <functional>
using T = double;
using Compare = std::less<T>;

class Set {
public:
	typedef T                 key_type;   
	typedef key_type&         reference;
	typedef const key_type&   const_reference;
	typedef size_t            size_type;
	typedef Compare           key_compare;

public:
	bool empty() const;
	size_type size() const;
	void clear();
	void insert(const key_type& key);
	size_type erase(const key_type& key);
	size_type count(const key_type& key);
	Set();
	~Set();
	void test();


private: 
	typedef short color_type;
	static const color_type RED = 1; // why static 
	static const color_type BLACK = 0;

	struct node;
	typedef node* n_ptr;
	inline bool isRed(const n_ptr &px) const;
	inline n_ptr newNode(const key_type &node_key) const;

	n_ptr root; 
	size_type siz;
	

	void debugTree(n_ptr x);
	void delTree(n_ptr &root); 
	

	size_type find(const n_ptr &px,const key_type& key) const; // return 0 not find 1 find
 	int findMin(const node &x) const; // return key
	int findMax(const node &x) const; // return key

	void colorFlip(node &px);
	void r2L(n_ptr &px); // x.right!=null rotate x to left son
	void r2R(n_ptr &px); // x.left!=null rotate x to right son 
	void fixUp(n_ptr &px);
	void d2R(n_ptr &px); // pushdown the RED edge to right son 
	void d2L(n_ptr &px); // pushdown the RED edge to left son 

	void ins(n_ptr &px,const key_type& key);
	void del(n_ptr &px,const key_type& key);
	void delMin(n_ptr &px);

	struct node{
		n_ptr left, right;
		color_type color; 
		key_type key;
		node(){
			left = right = nullptr;
			color = RED;
			key = (key_type)-1ll;
		}
		node(const key_type &node_key){
			left = right = nullptr;
			color = RED;
			key = node_key;
		}

		void debug(){
			using std::cout;
			using std::endl;
			cout<<"=============node "<<key<<endl;
			cout<<"left   ";
			if(left != nullptr) cout<<left -> key<<endl;
				else cout<<"null"<<endl;
			cout<<"right  ";
			if(right != nullptr) cout<<right -> key<<endl;
				else cout<<"null"<<endl;
			if(color) cout<<"red"<<endl;
			else cout<<"black"<<endl;
			cout<<"==========================="<<endl;
		}
	};
}; // TODO

#endif