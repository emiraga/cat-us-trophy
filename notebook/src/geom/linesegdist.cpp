if (dot(B-A, P-A) < 0) return dist(A,P);
if (dot(A-B, P-B) < 0) return dist(B,P);
return fabs(cross(P,A,B) / dist(A,B));
