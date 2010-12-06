bool isInside(const Vector &P) {
    Vector a = C - A, b = B - A, c = P - A;
    T under = a.x*b.y-b.x*a.y;
    T u = (c.x*b.y-c.y*b.x), v = (a.x*c.y-a.y*c.x);
    return u >= 0 && v >= 0 && u+v <= under || u<=0 && v<=0 && u+v >= under;
} //remove equalities if you dont want the boundary
