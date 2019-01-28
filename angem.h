/*
 * angem.h
 *
 *  Created on: Dec 9, 2018
 *      Author: jernicozz
 */

#ifndef ANGEM_H_
#define ANGEM_H_
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define out stdout;
#define in stdin;
struct vector;
typedef struct vector vector;
typedef double (*skalar)(vector v);
//typedef double (vector::*param)();
const char rpattern[] = "%lf%lf";
const char pattern1[] = "%lf %lf\n";
const char pattern2[] = "%d %d\n";
enum cords {X,Y};
const double e = 1e-4;




struct vector{
private:
	double x;
	double y;

	public:

		vector(double fx=0, double fy=0){
			x = fx;
			y = fy;
		}
		/*
		vector(vector&Other){
			x = Other.x;
			y = Other.y;
		}
		
		vector(vector&&Other){
			std::swap(x, Other.x);
			std::swap(y, Other.y);
		}
		
		vector& operator=(vector&&Other){
			std::swap(x, Other.x);
			std::swap(y, Other.y);
		}
		*/

		double getx(){ //double& ?
			return x;
		}
		double gety(){
			return y;
		}

		double length(){
			return sqrt(x*x+y*y);
		}

		double operator[](int n){ //double&
			n = n%2;
			if(n == 0)
				return x;
			else
				return y;
		}


		vector operator=(vector v){ //vector&
			this->x = v.x;
			this->y = v.y;
			return *this;
		}

		vector operator*(double d){
			return vector(d*x,d*y); //std::move()
		}

		double operator*(vector v){
			return x*v[Y]-y*v[X];
		}

		vector operator+(vector v){
			return vector(x + v.getx(),y + v.gety()); //std::move()
		}

		vector operator-(vector v){
			return vector(x-v[X],y-v[Y]);
		}

		int operator==(vector v){

			return (abs(x-v[X])<e && abs(y-v[Y])<e);
		}

		int operator%(vector V){
			return(abs(x*V[Y]-y*V[X])<e);
		}

		void operator>>(FILE*f){
			if(abs(floor(x)-x)<e && abs(floor(y)-y)<e)
				fprintf(f,pattern2,(int)x,(int)y);
			else
				fprintf(f,pattern1,x,y);
		}
		int operator<<(FILE*f){
			int res = 0;
			res = fscanf(f,rpattern,&x,&y);
			return res;

		}
};

vector linear(vector*v, double*q, int n){
	vector w = vector(0,0);
	for(int i = 0; i<n;i++){
		w = w+v[i]*q[i];
	}
	return w;
}
vector linear(vector*v, double q, int n){
	vector w = vector(0,0);
	for(int i = 0; i<n;i++){
		w = w+v[i]*q;
	}
	return w;
}


void sort(vector*V, int num, skalar f, int dir = 1){
	int mid = num/2, j,k,i;
		vector buf;
		for(k = num/2; k > 0; k /=2)
		        for(i = k; i < num; i++)
		        {
		            buf = V[i];
		            for(j = i; j>=k; j-=k)
		            {
		                if(dir*f(buf) < dir*f(V[j-k]))
		                    V[j] = V[j-k];
		                else
		                    break;
		            }
		            V[j] = buf;
		        }


}




typedef struct line{
private:
    double a;
    double b;
    double c;
    
public:
    double operator[](int ind){
        if(ind%3==0)
            return a;
        if(ind%3 ==1)
            return b;
        else
            return c;
    }
    line(double ai = 0, double bi = 0, double ci = 0){
        a = ai;
        b = bi;
        c = ci;
    }
    line(vector v1, vector v2){
        a = v2[Y]-v1[Y];
        b = v1[X]- v2[X];
        c = v1[Y]*v2[X]-v2[Y]*v1[X];
    }
    void move(vector&v){
        c-=v[Y]*b+v[X]*a;
    }
    
    vector ort(double len){
        vector v = vector(a,b);
        v = v*(1/v.length())*len;
        return v;
    }
}line;

vector linecross(line& lin1, line& lin2){
    if(lin1[0]*lin2[1]-lin2[0]*lin1[1]==0)
        throw "non crossing";
    else{
        double x, y;
        double ndet = lin1[0]*lin2[1] - lin1[1]*lin2[0];
        x = -1*(lin1[2]*lin2[1]-lin2[2]*lin1[1])/ndet;
        y = -1*(lin1[0]*lin2[2]-lin2[0]*lin1[2])/ndet;
        return vector(x,y);
    }
}


#endif /* ANGEM_H_ */
