#include "Unordered_map.hpp"
#include <cstdlib>
#include <ctime>

#include<iostream>
using namespace std;

typedef unsigned long long ull;
typedef unsigned int ui;

bool Unordered_map::empty() const{
	return (siz == 0);
}

Unordered_map::size_type Unordered_map::size() const{
	return siz;
}
void Unordered_map::clear(){
	release();
	init();
}
void Unordered_map::insert(const value_type& value){
	ull myKey = K2U(value.first);
	ui i = myKey % mod;
	n_ptr p = table[i].find(myKey);
	if(p == nullptr){
		table[i].insert(value.second, myKey);
		siz++;
	} else {
		p->val = value.second;
	}
	if(tooThin()) expand();
}
void Unordered_map::erase(const key_type& key){
	ull myKey = K2U(key);
	ui i = myKey % mod;
	n_ptr p = table[i].find(myKey);
	if(p != nullptr){
		table[i].erase(p);
		siz--;
	}
	if(tooFat()) shrink();
}
Unordered_map::mapped_type& Unordered_map::at(const Key& key){ // Why return a referrence?
	ull myKey = K2U(key);
	ui i = myKey % mod;
	n_ptr p = table[i].find(myKey);
	if(p == nullptr){
		std::cout<<"at null???\n";
	} else {
		return p->val;
	}
} 
Unordered_map::size_type Unordered_map::count(const Key& key){
	ull myKey = K2U(key);
	ui i = myKey % mod;
	n_ptr p = table[i].find(myKey);
	if(p!=nullptr)return 1;
	else return 0;
}
Unordered_map::Unordered_map(){
	init();
}
Unordered_map::~Unordered_map(){
	release();
}
void Unordered_map::release(){
	for(auto iter=table.begin();iter!=table.end();iter++) 
		iter->release();
	std::vector<List<T> >().swap(table);
}
void Unordered_map::init(){
	siz = 0;
	srand(time(0));
	mod = 127;
	base = 233 + (rand()|255);
	table.reserve(mod);
	table.resize(mod);
}
ull Unordered_map::K2U(key_type s){
	ull res = 0;
	for(auto iter=s.begin(); iter!=s.end(); iter++) res = res * base + (*iter) ;
	return res;
}
void Unordered_map::expand(){
	rebuild(mod<<2);
}
void Unordered_map::shrink(){
	rebuild(mod>>2);
}

void Unordered_map::rebuild(ull nmod){
std::vector<node<T>*> tmp;
	for(auto iter=table.begin();iter!=table.end();iter++){
			n_ptr x = iter->begin();
			while(x!=nullptr){
				tmp.push_back(x);
				x = x->next;
			}
			iter->_____clear();
		}
	mod = nmod;
	table.resize(mod);
	for(auto iter=tmp.begin();iter!=tmp.end();iter++){
		ui i = (*iter)->h % mod;
		table[i].insert(*iter);
	}
	std::vector< node<T>* >().swap(tmp);
	return ;
}
// Mytest double free or corruption (fasttop)
// 	testdata wrong...
// test2 malloc_consolidate(): invalid chunk size
// 	in construction resize() 
// 	not in List() 
// 	add reserve not effect  
//  something wrong when release
//  the release() is called		
//  List List.erase() delete() ?????
//  some other pointer -> the delete 
//  change the head when erase...