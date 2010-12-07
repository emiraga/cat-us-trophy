#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;
double eps = 1e-8;
struct point2d {
    double x,y;
	point2d operator-(point2d v) { return (point2d){x-v.x, y-v.y}; }
	point2d operator+(point2d v) { return (point2d){x+v.x, y+v.y}; }
};
struct point3d {
    double x,y,z;
    point3d operator-(point3d v) { return (point3d){x-v.x, y-v.y, z-v.z}; }
};
double trip(point3d a, point3d b, point3d c) {
    return a.x * ( b.y * c.z - b.z * c.y )
        - a.y *  ( b.x * c.z - b.z * c.x )
        + a.z *  ( b.x * c.y - b.y * c.x );
}
double len(point2d a) { return sqrt(a.x*a.x+a.y*a.y); }
double len(point3d a) { return sqrt(a.x*a.x+a.y*a.y+a.z*a.z); }
point3d cross(point3d a, point3d b) {
	return (point3d){
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x};
}
double dot(point3d a, point3d b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
double dot(point2d a, point2d b) { return a.x*b.x + a.y*b.y; }
double cross(point2d a, point2d b) {
	return a.x*b.y - a.y*b.x;
}
point2d rotate(point2d c, double angle) {
	return (point2d) {
	    c.x*cos(angle)-c.y*sin(angle),
		c.x*sin(angle)+c.y*cos(angle) };
}
//distance AB to C
double linePointDist(point2d A, point2d B, point2d C, bool isSegment){
    double dist = cross(B-A,C-A) / len(B-A);
    if(isSegment){
        if( dot(C-B,B-A) > eps) return len(B-C);
        if( dot(C-A,A-B) > eps) return len(A-C);
    }
    return fabs(dist);
}
struct Line { double A,B,C; };//Ax + By = C
Line makeline(point2d a1, point2d a2)
{
	Line ret = (Line){ a2.y-a1.y, a1.x-a2.x };
	ret.C = ret.A * a1.x + ret.B * a1.y;
	return ret;
}
double dist(Line l, point2d p)
{
	return fabs(p.x * l.A + p.y * l.B - l.C)/sqrt(l.A*l.A+l.B*l.B);;
}
Line rot90(Line l, point2d p)
{
	Line ret = (Line){ -l.B, l.A };
	ret.C = ret.A * p.x + ret.B * p.y;
	return ret;
}
point2d intersect(Line l1, Line l2)
{
	double det = l1.A*l2.B - l2.A*l1.B;
	if(fabs(det) < eps) det=0;//zero means parallel
	return (point2d) { (l2.B*l1.C - l1.B*l2.C)/det, (l1.A*l2.C - l2.A*l1.C)/det};
}
//for segment segment intersection, check additionally
//min(x1,x2) <= x <= max(x1,x2)
//min(y1,y2) <= x <= max(y1,y2)
bool segmentsIntersect( point2d A, point2d B, point2d C, point2d E )
{
	point2d in = intersect( makeline(A,B), makeline(C,E) );
    return linePointDist(A,B,in,true) < eps && linePointDist(C,E,in,true) < eps;
}

// get a line passing between two points
Line getmidline(point2d a, point2d b)
{
    point2d mid(a+b); mid.x/=2; mid.y/=2;
	return rot90( makeline(a,b), mid );
}
//reflect a point into it's "mirror" with repect to a line
point2d reflectPoint(Line l, point2d p)
{
    Line r = rot90(l, p);
    point2d Y=intersect(l,r);
    return Y-(p-Y);
}
void printline(Line l1)
{
	cout << l1.A << "x + " << l1.B << "y = " << l1.C << endl;
}
void printpoint(point2d p)
{
	cout << "x=" << p.x << " y=" << p.y << endl;
}

double getr()
{
	return -10000 + rand()%20000;
}
double eq(double a, double b)
{
	return fabs(a-b)<eps;
}

int main()
{
	point2d A={1,0}, B={-3,-4};
	point2d C={-1,-1};
	Line l1 = makeline(A,B);
	assert(dist(l1, A) < eps && dist(l1,B) < eps);

	point2d A1={0,5}, B1={-5,0};
	Line l2 = getmidline(A1,B1);
	
	point2d D = intersect(l1,l2);

	for(int i=0;i<20000;i++)
	{
		point2d A={getr(), getr()}, B={getr(),getr()};
		point2d C={getr(),getr()};
		Line AB = makeline(A,B);
		assert(eq(dist(AB,C),  linePointDist(A,B,C,false)));

		Line mid = getmidline(A,B);
		assert(eq( dist(mid, A), dist(mid,B) ));

		point2d M = intersect(AB,mid);
		assert(eq(M.x*2 , A.x+B.x));
		assert(eq(M.y*2 , A.y+B.y));

		point2d A2 = reflectPoint(mid, B);
		point2d B2 = reflectPoint(mid, A);
		assert( eq(A.x, A2.x) && eq(A.y, A2.y) );
		assert( eq(B.x, B2.x) && eq(B.y, B2.y) );

		point2d B3 = reflectPoint(AB, B);
		point2d A3 = reflectPoint(AB, A);
		assert( eq(A.x, A2.x) && eq(A.y, A2.y) );
		assert( eq(B.x, B2.x) && eq(B.y, B2.y) );
	}

	return 0;
}

