#include "Unordered_map.hpp"
#include <cstdlib>
#include <ctime>

#include<iostream>
using namespace std;

typedef unsigned long long ull;
typedef unsigned int ui;

bool Unordered_map::empty() const{
	return siz == 0;
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
	if(table[i] == nullptr ){
		table[i] = newnode(value.second, myKey);
		siz++;
	} else {
		n_ptr p = table[i]->findFollow(myKey);
		if(p==nullptr) table[i]->ins(newnode(value.second, myKey));
		else {
			siz++;
			p->setVal(value.second);
		}
	}
	if(overWeight()) expand();
}
void Unordered_map::erase(const key_type& key){
	ull myKey = K2U(key);
	ui i = myKey % mod;
	if(table[i] != nullptr ){
		n_ptr p = table[i]->findFollow(myKey);
		if(p!=nullptr) p->del(), siz--;
	} 
	if(tooThin()) shrink();
}
Unordered_map::mapped_type& Unordered_map::at(const Key& key){ // Why return a referrence?
	ull myKey = K2U(key);
	ui i = myKey % mod;
	if(table[i] != nullptr ){
		n_ptr p = table[i]->findFollow(myKey);
		if(p!=nullptr) return p->val;
	}  
	// expect to throw a Exception	
} 
Unordered_map::size_type Unordered_map::count(const Key& key){
	ull myKey = K2U(key);
	ui i = myKey % mod;
	if(table[i] != nullptr ){
		n_ptr p = table[i]->findFollow(myKey);
		if(p!=nullptr) return 1;
	} return 0;
}
Unordered_map::Unordered_map(){
	init();
}
Unordered_map::~Unordered_map(){
	release();
}
void Unordered_map::release(){
	for(auto iter=table.begin();iter!=table.end();iter++) 
		if((*iter)!=nullptr) (*iter)->delFollow();
	std::vector< node<T>* >().swap(table);
}
void Unordered_map::init(){
	siz = 0;
	srand(time(0));
	mod = 10;
	base = 233 + (rand()|255);
	table.resize(mod,nullptr);
}
Unordered_map::n_ptr Unordered_map::newnode(const mapped_type &V,const ull &H){
	return new node<T>(V,H);
}
ull Unordered_map::K2U(key_type s){
	cout<<"HASH!"<<endl;
	ull res = 0;
	for(auto iter=s.begin(); iter!=s.end(); iter++) res = res * base + (*iter);
	cout<<"aaa "<<s<<" "<<res<<" "<<res%mod<<endl;	
return res;
}
void Unordered_map::expand(){
//	rebuild(mod<<2);
}
void Unordered_map::shrink(){
//	rebuild(mod>>2);
}

void Unordered_map::rebuild(ull nmod){
	cout<<mod<<" "<<nmod<<endl;
	std::vector< node<T>*  > tmp;
	tmp.reserve(siz);
	for(auto iter=table.begin();iter!=table.end();iter++)
		if((*iter)!=nullptr){
			n_ptr x = (*iter);
			while(x!=nullptr){
				tmp.push_back(x);
				x = x->next;
				tmp.back()->next = tmp.back()->pre = nullptr;
			}
		}
	std::vector< node<T>* >().swap(table);
	mod = nmod;
	table.resize(mod,nullptr);
	for(auto iter=tmp.begin();iter!=tmp.end();iter++){
		ui i = (*iter)->h % mod;
		if(table[i] == nullptr ) table[i] = *iter;
		else table[i]->ins(*iter);
	}
	std::vector< node<T>* >().swap(tmp);
	return ;
}
#include<algorithm>
void test(){
	Unordered_map mp;
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		int op,x; 
		cin>>op>>s>>x;
		if(op){
			cout<<"ins "<<s<<" "<<x<<endl;
			mp.insert(make_pair(s,x));
			cout<<"over"<<endl;
		} else {
			cout<<"find "<<s<<endl;
			cout<<"over "<<mp.at(s)<<endl;
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	test();
	cout<<"over"<<endl;
}