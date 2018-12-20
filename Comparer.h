//
//  Comparer.h
//  test
//
//  Created by Дмитрий Маслюков on 20/12/2018.
//  Copyright © 2018 Дмитрий Маслюков. All rights reserved.
//

#ifndef Comparer_h
#define Comparer_h

template<typename T>
class Comparer{
protected:
    enum type_c {nul, by_func, by_s_param, by_i_param, by_d_param};
    typedef int(*Ord_Rel)(T&,T&);
    typedef size_t(T::*sparam)();
    typedef int(T::*iparam)();
    typedef double(T::*dparam)();
    int type;
    Ord_Rel func;
    sparam Sp;
    iparam Ip;
    dparam Dp;
    //returns 1 if first arg is considered to be less than second, 0 if they are equal, -1 if first argument is considered to be more than second
public:
    int show(){
        return type;
    }
    Comparer(Ord_Rel foo){
        func = foo;
        Sp = NULL;
        Ip = NULL;
        Dp = NULL;
        type = by_func;
        
    }
    Comparer(){
        func = NULL;
        Sp = NULL;
        Ip = NULL;
        Dp = NULL;
        type = nul;
    }
    int isEqual(T&first, T&second){
        return !compare(first,second);
    }
    int compare(T&first, T&second){
        if(type == by_func)
            return func(first,second);
        if(type == by_s_param){
            if((first.*Sp)()>(second.*Sp)())
                return -1;
            if((first.*Sp)()==(second.*Sp)())
                return -0;
            else
                return 1;
        }
        if(type== by_i_param){
            if((first.*Ip)()>(second.*Ip)())
                return -1;
            if((first.*Ip)()==(second.*Ip)())
                return -0;
            else
                return 1;
        }
        if(type== by_d_param){
            if((first.*Dp)()>(second.*Dp)())
                return -1;
            if((first.*Dp)()==(second.*Dp)())
                return -0;
            else
                return 1;
        }
        else
            throw "Comparance not set";
    }
    void set_compare(sparam P){
        Sp = P;
        type = by_s_param;
    }
    void set_compare(iparam P){
        Ip = P;
        type = by_i_param;
    }
    void set_compare(dparam P){
        Dp = P;
        type = by_d_param;
    }
    void set_compare(Ord_Rel foo){
        func = foo;
        type = by_func;
    }
    
};

#endif /* Comparer_h */
