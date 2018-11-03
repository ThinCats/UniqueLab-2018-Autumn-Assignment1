#ifdef TEST_DEBUG
#define _PRIORITY_QUEUE_HPP
#include <queue>
#include <vector>
typedef typename std::priority_queue<double, std::vector<double>> Priority_queue;
#endif // DEBUG

#ifndef _PRIORITY_QUEUE_HPP
#define _PRIORITY_QUEUE_HPP

#include <vector>
#include <functional>

using T = double;
using Container = std::vector<T>;
using Compare = std::less<T>;

class Priority_queue {
public:
typedef Container     container_type;
    typedef typename      container_type::value_type value_type;
    typedef typename      container_type::reference reference;
    typedef typename      container_type::const_reference const_reference;
typedef typename      container_type::size_type size_type;

public:
    const_reference top() const;
    bool empty() const;
    size_type size() const;
    void push(const value_type& value);
    void pop();
    Priority_queue();
    ~Priority_queue(); 
    void out();
private:        
    const size_type root = 1;         
    Container v;
    inline size_type parent(const size_type &i) const;
    inline size_type left(const size_type &i) const;
    inline size_type right(const size_type &i) const;
    inline bool inContainer(const size_type &i) const;
    inline bool isNull(const size_type &i) const;
    inline bool cmp(const size_type &i,const size_type &j) const;
    inline bool judge(const size_type &i) const;
    inline size_type maxSon(const size_type &i) const;
    // TODO
}; // TODO

#endif