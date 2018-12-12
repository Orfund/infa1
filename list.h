//
//  list.h
//  somefuck
//
//  Created by Дмитрий Маслюков on 11/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef list_h
#define list_h
#include<stdlib.h>
enum order {ASC=1, DESC=-1};
template <typename obj>
class List{
private:
    obj*Objects;
    
public:
    typedef int(*ordrel)(obj,obj);
    typedef int(*eqrel)(obj,obj);
    typedef int(*sigma)(int);
    int length;
    List(int n = 1){
        length = n;
        Objects = (obj*)malloc(n*sizeof(obj));
    }
    ~List(){
        free(Objects);
    }
    
    List &operator=(List &l){
        Objects = (obj*)realloc(Objects,l.length*sizeof(obj));
        length = l.length;
        for(int i = 0; i<length; i++)
            Objects[i] = l[i];
        return *this;
    }
    
    obj &operator[] (int n) {
        if(n<length)
            return Objects[n];
        else
            throw("Index out of bounds");
    }
    
    int Find(obj O, eqrel F=[](obj a, obj b)->int{return a ==b;}){
        for(int i = 0;i<length;i++)
            if(F(Objects[i],O)==1)
                return i;
        return -1;
    }
    
    List Reshuffle(sigma s){ //sigma must be biective
        List<obj> list = List<obj>(length);
        list = *this;
        for(int i = 0; i<length; i++)
            list[s(i)] = Objects[i];
        return list;
    }
    
    void Append(obj O){
        Objects = (obj*)realloc(Objects,(length+1)*sizeof(obj));
        Objects[length] = O;
        length++;
    }
    
    void Sort(ordrel f){
        int j,k,i;
        obj buf;
        for(k = length/2; k > 0; k /=2)
            for(i = k; i < length; i++)
            {
                buf = Objects[i];
                for(j = i; j>=k; j-=k)
                {
                    if(f(buf,Objects[j-k])==0)
                        Objects[j] = Objects[j-k];
                    else
                        break;
                }
                Objects[j] = buf;
            }
        

    }
    
   
    
    
};




#endif /* list_h */
