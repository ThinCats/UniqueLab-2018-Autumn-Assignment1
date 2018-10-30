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
	typedef bool color_type;
	static const color_type red = true; // why static 
	static const color_type black = false;
	struct node;
	typedef node* n_ptr;
	
	size_type siz;
	n_ptr root; 
	
	void delTree(n_ptr &root);
	struct node{
		n_ptr parent, left, right;
		color_type color; 
		key_type key;
		int cnt;
		node(){
			parent = left = right = NULL;
			color = black;
			key = (key_type)-1ll;
			cnt = 0;
		}
		void debug(){
			using std::cout;
			using std::endl;
			cout<<"node "<<key<<endl;
			cout<<"parent "<<parent -> key<<endl;
			cout<<"left   "<<left -> key<<endl;
			cout<<"right  "<<right -> key<<endl;
			if(color) cout<<"red"<<endl;
			else cout<<"black"<<endl;
			cout<<cnt<<endl;
			cout<<"==========================="<<endl;
		}
	};
	n_ptr newNode();
}; // TODO

#endif