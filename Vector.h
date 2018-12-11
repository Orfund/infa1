/*
 * Vector.h
 *
 *  Created on: Dec 4, 2018
 *      Author: jernicozz
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include<math.h>
#include<stdio.h>

struct vector;
typedef struct vector vector;
typedef double (*vtoskal)(vector v);
vector Create_v(double x_1,double y_1, double x_0 = 0, double y_0 = 0);
void printf(vector v, FILE*f = stdout);
int scanf(vector v,FILE*f = stdin,int type = 0);
vector linear(vector*v, double*q, int n);
void Sort(vector*v, int num, vtoskal f, int dir=1 );





struct vector{
	public:
		double x_0;
		double y_0;
		double x_1;
		double y_1;


		vector operator+(vector v){
			return Create_v(v.x_1 - v.x_0 + x_1,v.y_1 - v.y_0 + y_1,x_0,y_0);
		}
		vector operator*(double n){
			return Create_v(x_0+n*(x_1-x_0),y_0+n*(y_1-y_0),x_0,y_0);
		}
		double operator*(vector v){
			return (x_1-x_0)*(v.y_1-v.y_0) - (y_1-y_0)*(v.x_1-v.x_0);
		}
		vector operator-(vector v){
				vector w = Create_v(0,0);
				w = *this + v*(-1);
				return w;
				}

		double d_as_p(vector v){
			return sqrt((x_1-v.x_1)*(x_1-v.x_1)+(y_1-v.y_1)*(y_1-v.y_1));
		}

		double length(){
			return sqrt((x_1-x_0)*(x_1-x_0)+(y_1-y_0)*(y_1-y_0));
		}
};
void printf(vector v, FILE*f){
	if(v.x_0 == 0 && v.y_0 == 0)
		fprintf(f,"( %lf, %lf )\n",v.x_1,v.y_1);
	else
		fprintf(f,"from ( %lf, %lf ) to ( %lf, %lf )\n",v.x_0,v.y_0, v.x_1, v.y_1);
}

int scanf(vector v,FILE*f,int type){
	double a,b,c = 0, d = 0;
	int k;
	if(type == 0)
		k = fscanf(f,"%lf%lf",&a,&b);
	else
		k = fscanf(f,"%lf%lf%lf%lf",&a,&b,&c,&d);
	v = Create_v(a,b,c,d);
	return k;
}



vector Create_v(double x_1,double y_1, double x_0, double y_0 ){
	vector v;
	v.x_0 = x_0;
	v.x_1 = x_1;
	v.y_0 = y_0;
	v.y_1 = y_1;
	return v;
}

vector linear(vector*v, double*q, int n){ //результат - свободный вектор
	vector w = Create_v(0,0);
	for(int i = 0; i<n;i++){
		w.y_1 += ((v+i)->y_1 - (v+i)->y_0)*(q[i]);
		w.x_1 += ((v+i)->x_1 - (v+i)->x_0)*(q[i]);
	}
	return w;
}
vector linear(vector*v, double q, int n){
	vector w = Create_v(0,0);
	for(int i = 0; i<n;i++){
		w.y_1 += ((v+i)->y_1 - (v+i)->y_0)*(q);
		w.x_1 += ((v+i)->x_1 - (v+i)->x_0)*(q);
	}
	return w;
}


void Sort(vector*v, int num, vtoskal f, int dir ){ //dir принимает значение 1 для сортировки по возрастанию и -1 для по убыванию
	int mid = num/2, j,k,i;
	vector buf;
	for(k = num/2; k > 0; k /=2)
	        for(i = k; i < num; i++)
	        {
	            buf = v[i];
	            for(j = i; j>=k; j-=k)
	            {
	                if(dir*f(buf) < dir*f(v[j-k]))
	                    v[j] = v[j-k];
	                else
	                    break;
	            }
	            v[j] = buf;
	        }




}


#endif /* VECTOR_H_ */
