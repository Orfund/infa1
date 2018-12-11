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

		double getx(){
			return x;
		}
		double gety(){
			return y;
		}

		double length(){
			return sqrt(x*x+y*y);
		}

		double operator[](int n){
			n = n%2;
			if(n == 0)
				return x;
			else
				return y;
		}


		vector operator=(vector v){
			this->x = v.x;
			this->y = v.y;
			return *this;
		}

		vector operator*(double d){
			return vector(d*x,d*y);
		}

		double operator*(vector v){
			return x*v[Y]-y*v[X];
		}

		vector operator+(vector v){
			return vector(x + v.getx(),y + v.gety());
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






#endif /* ANGEM_H_ */
