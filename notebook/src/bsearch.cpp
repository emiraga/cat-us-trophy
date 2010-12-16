/*LE*/
while(l <= h){ m = (l+h) / 2; if(works(m))  l=m+1; else h=m-1; }
return l-1;
/*GE*/
while(l <= h){ m = (l+h) / 2; if(works(m))  h=m-1; else l=m+1; }
return h+1;
