//
//  dict.h
//  somefuck
//
//  Created by Дмитрий Маслюков on 17/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef dict_h
#define dict_h
#include"collections.h"
#include<stdlib.h>
class dict{
private:
    container*Keys;
    container*Values;
    int last;
    int mem;
    
    
    void Resize(int newsize){
        if(last>newsize)
            last =newsize;
        mem = newsize;
        Keys = (container*)realloc(Keys, sizeof(container)*mem);
        Values = (container*)realloc(Values, sizeof(container)*mem);
        
    }
public:
    dict(int initsize){
        Keys = (container*)malloc(initsize*sizeof(container));
        Values = (container*)malloc(initsize*sizeof(container));
        mem = initsize;
        last = 0;
    }
    ~dict(){
        free(Keys);
        free(Values);
    }
    template<typename objtype>
    container& get(container &key){
        for(int i = 0; i<last;i++)
            if(Keys[i].get<objtype>() == key.get<objtype>())
                return Values[i];
        throw "not found";
    }
    void set(container &key, container & value){
        if(last==mem)
            Resize(mem<<=1);
        Keys[last] = key;
        Values[last] = value;
        last++;
    }
    sequence keys(){
        sequence sq = sequence(last);
        for(int i = 1; i<last;i++)
            sq.Append(Keys[i]);
        return sq;
    }
};

#endif /* dict_h */
