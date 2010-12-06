#include <iostream>
#include <algorithm>
using namespace std;

struct point3d {
    double x,y,z;
    point operator-(point v) { return point(x-v.x, y-v.y, z-v.z); }
};

//include

double trip(point3d a, point3d b, point3d c) {
    return a.x * ( b.y * c.z - b.z * c.y )
        - a.y *  ( b.x * c.z - b.z * c.x )
        + a.z *  ( b.x * c.y - b.y * c.x );
}

double len(point3d a) { return sqrt(a.x*a.x+a.y*a.y+a.z*a.z); }

point3d cross(point3d a, point3d b) {
	return point(
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x);
}

double dot(point3d a, point3d b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

    T operator%(const Vec<2> &a)const{assert(d==2);return c[0]*a[1]-c[1]*a[0]; }//2d cross product
    Vec operator%(const Vec<3> &a)const{assert(d==3);return Vec(c[1]*a[2]-c[2]*a[1],c[2]*a[0]-c[0]*a[2],c[0]*a[1]-c[1]*a[0]);}//3d cross
    Vec rotate(LD angle) {assert(d==2);return Vec(c[0]*cos(angle)-c[1]*sin(angle),c[0]*sin(angle)+c[1]*cos(angle));}
    bool operator<(const Vec &v)const{ Rep(i,d)if(c[i]!=v[i])return c[i]<v[i];return false; }

LD linePointDist(Vec<> A, Vec<> B, Vec<> C, bool isSegment){
    LD dist = ((B-A)%(C-A)) / sqrt((B-A)*(B-A));
    if(isSegment){
        if( (C-B)*(B-A) > eps) return (B-C).len();
        if( (C-A)*(A-B) > eps) return (A-C).len();
    }
    return iabs(dist);
}

bool segmentsIntersect( Vec<> A, Vec<> B, Vec<> C, Vec<> E )
{
    Vec<> in = Line<>(A,B).intersect(Line<>(C,E));
        return linePointDist(A,B,in,true) < eps && linePointDist(C,E,in,true) < eps;
}

template<class T=LD> struct Line
{
    T A,B,C;
    Line(){A=B=C=0;}
    Line(T x1,T y1,T x2,T y2) { A=y2-y1; B=x1-x2; C=A*x1+B*y1; }//construct from 4 values
    T dist(T a0, T a1) const { return iabs( a0*A + a1*B - C ) / sqrt(A*A+B*B); }
    Line rot90(T x,T y)const{Line ret;ret.A=-B;ret.B=A;ret.C=ret.A*x+ret.B*y;return ret;}//rot line
    friend ostream& operator<<(ostream& os,const Line &a){return os<<a.A<<"*x + "<<a.B<<"*y = "<<a.C; }
    //requires Vec
    Line(Vec<2,T>a,Vec<2,T>b){A=b[1]-a[1];B=a[0]-b[0];C=A*a[0]+B*a[1];} //construct from two points
    T dist(Vec<2,T> a) const { return ( a[0]*A + a[1]*B - C ) / sqrt(A*A+B*B); }
    Vec<2,T> intersect(const Line &l) const {T det = A*l.B - l.A*B; if(iabs(det) < eps)det=0; return Vec<2,T>((l.B*C - B*l.C)/det, (A*l.C - l.A*C)/det); }
};
//for segment segment intersection, check additionally
//min(x1,x2) <= x <= max(x1,x2)

// get a line passing between two points
template<class T>
Line<T> getmidline(Vec<2,T> a, Vec<2,T> b)
{
    Vec<2,T> mid(a+b);
        return Line<T>(a,b).rot90(mid[0]/2,mid[1]/2);
}

//reflect a point into it's "mirror" with repect to a line
template<class T>
Vec<2,T> reflectPoint(Vec<2,T> p, Line<T> l)
{
    Line<T> r = l.rot90(p[0],p[1]);
        Vec<2,T> Y=l.intersect(r);
        return Y - (p-Y);
}

