#include "Priority_queue.hpp"
#include <algorithm>

Priority_queue::const_reference Priority_queue::top() const{
	return v[root];
}

bool Priority_queue::empty() const{
	return v.size()<=1;		
}

Priority_queue::size_type Priority_queue::size() const{
	return v.size()-1;
}	
using namespace std;
void Priority_queue::push(const value_type& value){
	v.push_back(value);
	size_type i = this->size();
	while( i!=root && cmp(parent(i),i) ) {
		std::swap(v[parent(i)],v[i]);
		i = parent(i);
	}		
}
void Priority_queue::pop(){
	if(this->empty()) return ;
	size_type i = this->size();
	std::swap(v[i],v[root]);
	v.pop_back();
	i = root;
	while(!isNull(left(i))){
		size_type j = maxSon(i);
		if(Compare()(v[i],v[j])) std::swap(v[i],v[j]);
			else break;
		i = j;
	}
}
Priority_queue::Priority_queue(){
	v = Container(1,1);
}
Priority_queue::~Priority_queue(){
	Container().swap(v);
}
/*
void Priority_queue::out(){
	for(size_type i=1;i<=size();i++) std::cout<<v[i]<<" ";
		std::cout<<"\n";
}*/
inline Priority_queue::size_type Priority_queue::parent(const size_type &i) const { return i>>1;}
inline Priority_queue::size_type Priority_queue::left(const size_type &i) const { return i<<1;}
inline Priority_queue::size_type Priority_queue::right(const size_type &i) const { return i<<1|1;}
inline bool Priority_queue::inContainer(const size_type &i) const { return i<v.size();} 
inline bool Priority_queue::isNull(const size_type &i) const { return i>=v.size();} 
inline bool Priority_queue::cmp(const size_type &i,const size_type &j) const{ 
	return (isNull(i)) || 
			(!isNull(j) && !Compare()(v[j],v[i]) ) ;
}	
inline bool Priority_queue::judge(const size_type &i) const { 
	return cmp(left(i),i) && cmp(right(i),i);	
} 
inline Priority_queue::size_type Priority_queue::maxSon(const size_type &i) const{
	return cmp(left(i),right(i)) ? right(i) : left (i);
}
/*int test(){
	using namespace std;
	int n; cin>>n;
	Priority_queue q;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		if(x){
			q.push(y);
		} else q.pop();
	}
}
int main(){	
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);		
	test();
}*/