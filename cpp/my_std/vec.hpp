#ifndef __THREE_VEC__
#define __THREE_VEC__
#include <stdlib.h> //malloc
#include "../js_external.h"

template <class T>
class polygon_vec
{
public:
private:
    unsigned int _size;
    unsigned int _capacity;
    T* _data;
public:
    polygon_vec()
    {
        _size = 0;

        _capacity = 0;
        _data = 0;
        // _data = new T[10];
    }
    ~polygon_vec()
    {
        // deleteRange(_data, _data + _size);
        // free(_data);
        //gotta free
    }

    // needs some other constructors
    // size(), empty() and a bunch of other methods!
    unsigned int size() const{
      return _size;
    }

    bool empty() const{
      return _size == 0;
    }

    T& back(){
      return _data[_size - 1];
    }

    void pop_back(){
      _size -= 1;
    }

    void clear(){
      _size = 0;
    }



    void
    push_back(const T& value)
    {
      //we are full, reallocate
      if(this->_size == this->_capacity){
        //allocate array with double capacity
        unsigned int new_capacity = this->_capacity * 2;
        if(new_capacity == 0){
          new_capacity = 2; //0, 2, 4, 8
        }



        T* new_data = (T*) malloc(new_capacity * sizeof(T));


        //move old contents
        for(unsigned int i = 0; i < this->_capacity; i++){
          new_data[i] = this->_data[i];
        }



        //TODO
        // free(this->_data);


        // console_log( (int)(void*) value);
        //add new element
        new_data[this->_size] = value;
        //update state
        this->_capacity = new_capacity;
        this->_data = new_data;
      }else{
        _data[_size] = value;
      }
      this->_size += 1;
    }

    T&
    operator[](unsigned int index)
    {
        return _data[index];
    }
    const T&
    operator[](unsigned int index) const
    {
        return _data[index];
    }
    T*
    begin() const
    {
        return _data;
    }
    T*
    end() const
    {
        return _data + _size;
    }
};

#endif
