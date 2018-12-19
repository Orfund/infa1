//
//  matrix.h
//  test
//
//  Created by Дмитрий Маслюков on 18/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef matrix_h
#define matrix_h
#include <iostream>
template<typename T>
class lvect{
protected:
    size_t size;
    size_t length;
    T*elems;
    void RLOC(){
        elems = (T*)realloc(elems, size*sizeof(T));
    }
    void check_ind(int index){
        if(index<0)
            index+=length;
        if(index<0 || index>length)
            throw "bad bounds";
    }
    void _Move(int startind, int endind, int num){
        memmove((elems+endind),(elems+startind),num*sizeof(T));
    }
    typedef T (*mfun)(T&, void*);
    typedef void (*mfun_)(T&, void*);
    
public:
    void Resize(size_t newsize){
        size = newsize;
        length = newsize;
        elems = (T*)realloc(elems,sizeof(T)*newsize);
    }
    int Length(){
        return length;
    }
    lvect(size_t siz=1){
        size = siz;
        length = siz;
        elems = (T*)malloc(sizeof(T)*size);
        //std::cout<<size;
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
    void operator=(lvect&v){
        if(v.Length() > size){
            size = v.Length();
            RLOC();
        }
        length = v.Length();
        for(int i = 0; i<length;i++)
            memcpy(elems+i,&(v[i]),sizeof(v[i]));
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
    
    lvect Map(mfun f, void*ptr = NULL){
        for(int i = 0; i<length;i++)
            elems[i] = f(elems[i],ptr);
    }
    void Map(mfun_ f, void*ptr = NULL){
        for(int i = 0; i<length;i++)
            f(elems[i],ptr);
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
    
    void Remove(int ind){
        this->check_ind(index);
        this->_Move(ind+1, ind, (--this->length-ind));
    }
};




template<typename F>
class matrix{
private:
    int cols;
    int rows;
    lvect<lvect<F>> Elements;
public:
    int getColn(){
        return cols;
    }
    int getRown(){
        return rows;
    }
    matrix(int row_n, int col_n ,lvect<lvect<F>> &elems){
        
        cols = col_n;
        rows = row_n;
        if(elems.Length()==rows && elems[0].Length()==cols)
            Elements = elems;
    }
    matrix(int row_n, int col_n):Elements(row_n){
        rows = row_n;
        cols = col_n;
        
        Elements.Resize(rows);
        Elements.Map([](lvect<F>&lv, void*ptr){lv.Resize(*(int*)ptr);},&col_n);
    }
    ~matrix(){
        //delete Elements;
    }
    matrix _get(int bannedrn, int*bannedrows, int bannedcln, int*bannedcols){
        //проверить надо, но мне лень
        matrix<F> m = matrix<F>(rows-bannedrn, cols-bannedcln);
        int real_r = 0, real_c = 0;
        bool nbr = true, nbc = true;
        for(int i = 0; i<rows;i++){
            nbr = true;
            for(int chec = 0; chec<bannedrn;chec++)
                if(i == bannedrows[chec])
                    nbr = false;
            if(nbr){
                for(int j = 0; j<rows;j++){
                    nbc = true;
                    for(int chec = 0; chec<bannedcln;chec++)
                        if(j == bannedcols[chec])
                            nbc = false;
                    if(nbc){
                        m[real_r][real_c] = Elements[i][j];
                        real_c++;
                    }
                }
                real_r++;
                real_c = 0;
            }
        }
        
        
        return m;
    }
    lvect<F> &operator[](int ind){
        return Elements[ind];
    }
    
    F det(){
        if(rows != cols)
            throw "Bad matrix";
        if(rows == 2){
            return Elements[0][0]*Elements[1][1] - Elements[1][0]*Elements[0][1];
        }
        else{
            F elem = F();
            for(int i = 0; i<cols;i++)
            {
                int bannedcol = i;
                int*bc = &bannedcol;
                int bannedrow = 0;
                int*br = &bannedrow;
                F minor =(this->_get(1,br,1,bc).det());
                if(i%2 == 1)
                    minor = -minor;
                elem = elem+Elements[0][i]*minor;
            }
            return elem;
        }
    }
    
    matrix operator+(matrix&m1){
        if(m1.getColn() != cols || m1.getRown()!=rows)
            throw "dimens not equal";
        matrix m = matrix(rows,cols);
        for(int i = 0; i<rows; i++){
            for(int j = 0; j<cols;j++)
                m[i][j] = Elements[i][j]+m1[i][j];
        }
        return m;
    }
    void operator=(matrix m2){
        if(m2.getColn() != cols || m2.getRown()!=rows)
            throw "dimens not equal";
        for(int i = 0; i<rows; i++){
            for(int j = 0; j<cols;j++)
                 Elements[i][j]=m2[i][j];
        }
    }
    matrix operator*(matrix&m1){
        if(m1.getRown() != cols)
            throw "dimens not equal";
        matrix m = matrix(rows,m1.getColn());
        
        for(int i = 0; i<rows;i++){
            for(int j = 0; j<m1.getColn();j++){
                F elem = F();
                for(int k = 0; k<cols;k++)
                    elem = elem+Elements[i][k]*m1[k][j];
                m[i][j] = elem;
                
            }
        }
        return m;
    }
    
    
    
};
#endif /* matrix_h */
