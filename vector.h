//
//  vector.h
//  test
//
//  Created by Дмитрий Маслюков on 20/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef vector_h
#define vector_h
#include"Comparer.h"




template<typename T>
class lvect{
protected:
    size_t size;
    size_t length;
    T*elems;
    void RLOC(){
        elems = (T*)realloc(elems, size*sizeof(T));
    }
    void check_ind(size_t index){
        if(index<0)
            index+=length;
        if(index<0 || index>length)
            throw "bad bounds";
    }
    void _Move(size_t startind, size_t endind, size_t num){
        memmove((elems+endind),(elems+startind),num*sizeof(T));
    }
    typedef T (*mfun)(T&, void*);
    typedef void (*mfun_)(T&, void*);
    
public:
    void Resize(size_t newsize){
        
        length = newsize;
        if(length>size){
            size = newsize;
            elems = (T*)realloc(elems,sizeof(T)*newsize);
        }
        
    }
    
    size_t Length(){
        return length;
    }
    T*getelems(){
        return elems;
    }
    lvect(size_t siz=1){
        size = siz;
        length = siz;
        elems = (T*)malloc(sizeof(T)*size);
        //std::cout<<length;
        for(int i = 0; i<size;i++)
            new (&elems[i])T();
        
    }
    
    
    ~lvect(){
        free(elems);
    }
    T& operator[](int ind){
        check_ind(ind);
        return elems[ind];
    }
    virtual const T&get(size_t ind){
        check_ind(ind);
        return elems[ind];
    }
    void operator=(lvect&v){
        if(v.Length() > size){
            size = v.Length();
            RLOC();
        }
        length = v.Length();
        memcpy(elems,v.getelems(),length*sizeof(T*));
        /*for(int i = 0; i<length;i++)
         memcpy(elems+i,&(v[i]),sizeof(v[i]));*/
    }
    void set(int num, T*objects){
        if(num>size){
            size = num;
            RLOC();
        }
        length = num;
        for(int i = 0; i<length;i++)
            memcpy(elems+i,(objects+i),sizeof(T));
    }
    
    void Insert(T&obj, int index = -1){
        check_ind(index);
        if(length==size){
            size>>=1;
            RLOC();
        }
        _Move(index, index+1, (length-index));
        elems[index] = obj;
        length++;
    }
    
    void Map(mfun f,void*ptr = NULL){
        for(int i = 0; i<length;i++)
            elems[i] = f(elems[i],ptr);
    }
    void Map(mfun_ f, void*ptr = NULL){
        for(int i = 0; i<length;i++)
            f(elems[i],ptr);
    }
    
    
    class iterator{
    protected:
        lvect<T>*ptr;
        bool cyclic;
        size_t curind;
        size_t step;
    public:
        iterator(lvect&v,bool cycli = false, size_t curin=0, size_t as_step = 1){
            ptr = &v;
            curind = curin;
            cyclic = cycli;
            step = as_step;
        }
        virtual const T&get(){
            return ptr->elems[curind%(ptr->Length())];
        }
        void operator++(){
            if(ptr!=NULL){
                if(cyclic)
                    curind = (curind+step)%ptr->length;
                else
                    if(ptr->Length()>=curind)
                        curind+=step;
            }
        }
        size_t pos(){
            return curind;
        }
        bool active(){
            if(ptr!=NULL)
                return cyclic || (curind < ptr->Length());
            else
                return false;
        }
        void reset(size_t ind = 0){
            if(ptr!=NULL)
                curind = ind%(ptr->Length());
        }
        
        void set_step(size_t as_step){
            step = as_step;
        }
        void set(lvect&v){
            ptr = &v;
        }
    };
    
    void Sort(Comparer<T> &comp){
        T buf;
        int i,j;
        for(int k = length/2; k > 0; k /=2)
            for(i = k; i < length; i++)
            {
                buf = elems[i];
                for(j = i; j>=k; j-=k)
                {
                    if(comp.compare(buf,elems[j-k])==1)
                        elems[j] = elems[j-k];
                    else
                        break;
                }
                elems[j] = buf;
            }

    }
    void Sort(int dir = 1){
        T buf;
        int i,j;
        for(int k = length/2; k > 0; k /=2)
            for(i = k; i < length; i++)
            {
                buf = elems[i];
                for(j = i; j>=k; j-=k)
                {
                    if(dir*buf<dir*elems[j-k])
                        elems[j] = elems[j-k];
                    else
                        break;
                }
                elems[j] = buf;
            }
        
    }
    
};




template<typename F>
class vect:public lvect<F>{
public:
    vect(size_t size):lvect<F>(size){
        this->length = 0;
    }
    
    void Append(F&obj){
        if(this->length==this->size){
            this->size<<=1;
            this->RLOC();
        }
        this->elems[this->length] = obj;
        this->length++;
    }
    
    void Remove(size_t ind){
        this->check_ind(ind);
        this->_Move(ind+1, ind, (--this->length-ind));
    }
    
    class iterator: public lvect<F>::iterator{
    private:
        vect<F>*ptr;
    public:
        iterator(vect<F>&v, bool cycli = false, size_t startind = 0, size_t as_step = 1):lvect<F>::iterator(v,cycli,startind,as_step){
            ptr = &v;
        }
        F&get() override{
            return ptr->elems[this->curind%(ptr->Length())];
        }
        
    };
    
    F&get(size_t ind)override{
        this->check_ind(ind);
        return (*this)[ind];
    }
    
};




#endif /* vector_h */
