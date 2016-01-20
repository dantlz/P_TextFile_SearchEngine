#ifndef MYSET_H
#define MYSET_H
#include <set>
#include <string>

template<class T>
class myset : public std::set<T> {
public:
  	myset<T>(): std::set<T>() {}
  	myset<T> set_intersection(const myset<T>& other){
		typename myset<T>::iterator it;
		typename myset<T>::iterator it2;
		myset<T> newSet;

		for(it = this->begin();it != this->end();++it){
			for(it2=other.begin();it2 != other.end();++it2){
				if(*it==*it2){
					newSet.insert(*it);
				}
			}
		}
		return newSet;
	}
  	myset<T> set_union(const myset<T>& other){
		typename myset<T>::iterator it;
		typename myset<T>::iterator it2;
		myset<T> newSet;
		for(it = this->begin();it != this->end();++it){
			newSet.insert(*it);
		}
		for(it2=other.begin();it2 != other.end();++it2){
			if(newSet.count(*it2)==0){
				newSet.insert(*it2);
			}
		}
		return newSet;
	}
};

#endif