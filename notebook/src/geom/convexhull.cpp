struct Point { LL x,y; bool operator<(const Point &p)const{
	return(x==p.x) ? y<p.y : x<p.x; } };
LL cross(const Point &O, const Point &A, const Point &B)
{ return (A.x-O.x) * (B.y-O.y) - (A.y-O.y) * (B.x-O.x); }
// Returns a list of convex hull in counter-clockwise order.
// In case of collinear points, only end-points are taken (not middle).
// The last point is the same as the first one.
vector<Point> ConvexHull(vector<Point> P) {
    int n = P.size(), k = 0; vector<Point> H(2*n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; i++)
    { while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--; H[k++] = P[i]; }
    for (int i = n-2, t = k+1; i >= 0; i--)
    { while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--; H[k++] = P[i]; }
    H.resize(k); return H; }
