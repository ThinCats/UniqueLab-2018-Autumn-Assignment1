#ifdef TEST_DEBUG
#define _UNORDERD_MAP_HPP
#include <unordered_map>
#include <string>
typedef typename std::unordered_map<std::string, double> Unordered_map;
#endif // DEBUG

#ifndef _UNORDERD_MAP_HPP
#define _UNORDERD_MAP_HPP

#include <string>
#include <vector>

#include "node.hpp"
#include "List.hpp"
using Key = std::string;
typedef unsigned long long ull;
using T = double;

class Unordered_map {

public:
	typedef node<T>* 		n_ptr;
	typedef Key             key_type;
	typedef T               mapped_type;
	typedef key_type&       reference;
	typedef const key_type& const_reference;
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef size_t          size_type;

public:
	bool empty() const;
	size_type size() const;
	void clear();
	void insert(const value_type& value);
	void erase(const key_type& key);
	mapped_type& at(const Key& key);
	size_type count(const Key& key);
	Unordered_map();
	~Unordered_map();
private:
	
	ull base,mod;
	size_type siz;
	std::vector< List<T>  > table;
	
	n_ptr newnode(const mapped_type &V,const ull &H);
	ull K2U(key_type s);
	void add();
	void release();
	void init();
	void expand();
	void shrink();
	void rebuild(ull nmod);
	inline bool tooFat(){ return mod>=64&&siz*8<=mod; } 
	inline bool tooThin(){ return mod<=1e7&&siz*4>=3*mod; }
}; // TODO
#endif