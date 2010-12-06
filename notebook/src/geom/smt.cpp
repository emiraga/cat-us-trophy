struct point
{
	double x,y,z;
	point():x(0),y(0),z(0){}
	point(double x,double y,double z):x(x),y(y),z(z){}
	point operator-(point v) { return point(x-v.x, y-v.y, z-v.z); }
};

double trip(point a, point b, point c)
{
	return a.x * ( b.y * c.z - b.z * c.y )
		- a.y *  ( b.x * c.z - b.z * c.x )
		+ a.z *  ( b.x * c.y - b.y * c.x );
}

double len(point a)
{
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

point cross(point a, point b)
{
	return point(
			a.y*b.z - a.z*b.y,
			a.z*b.x - a.x*b.z,
			a.x*b.y - a.y*b.x);
}
