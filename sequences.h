//
//  sequences.h
//  somefuck
//
//  Created by Дмитрий Маслюков on 17/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef sequences_h
#define sequences_h

class container{
private:
    void*ptr;
public:
    template<typename ob>
    ob get(){
        return *(ob*)ptr;
    }
    void set(void*exptr){
        ptr = exptr;
    }
};

class sequence{
private:
    container*Objects;
    int last;
    int size;
    void Rloc(){
        Objects = (container*)realloc(Objects, size);
    }
    typedef void (*mapper_1)(container&, void*);
    typedef container (*map_mut_1)(container&, void*);
public:
    sequence(int inilength){
        Objects = (container*)malloc(sizeof(container)*inilength);
        size = inilength;
        last = 0;
    }
    ~sequence(){
        free(Objects);
    }
    
    container& operator[](int index){
        if(index<0)
            index+=last;
        return Objects[index];
    }
    
    void Append(container &a){
        if(last==size){
            size>>=1;
            Rloc();
        }
        Objects[last] = a;
        last++;
    }
    void Map(mapper_1 func, void*arg = NULL){
        for(int i = 0; i< last; i++)
            func(Objects[i], arg);
    }
    
    void Map(map_mut_1 f, void*arg = NULL){
        for(int i = 0; i<last;i++)
            Objects[i] = f(Objects[i], arg);
    }
    
    
};


#endif /* sequences_h */
