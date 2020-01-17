#ifndef __THREE_MAP__
#define __THREE_MAP__

// #include <vector>

#include "vec.hpp"
#include "../js_external.h"

template <class K, class V>
class polygon_map{

  public:
  polygon_vec<V> elements;
  polygon_vec<K> keys;

  void put(const K &key, const V &value) {
    elements.push_back(value);
    keys.push_back(key);
  }

  V& get(const K &key){
    for(int i = 0; i < keys.size(); i++){
      if(key == keys[i]){
        return elements[i];
      }
    }
    console_error(1);
    return elements[0];
  }

  int count (const K& key) const{
    for(int i = 0; i < keys.size(); ++i){ //needs to be ++i not i++?
      if(key == keys[i]){
        return 1;
      }
    }
    return 0;
  };

};

#endif
