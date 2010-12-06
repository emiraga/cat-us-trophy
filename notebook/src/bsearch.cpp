/*LE*/ int down = start, int up = end+1;
while(down+1 < up) { int mid = (down+up)/2; if(f1(mid)) down = mid; else up = mid;
} assert(down == L);
/*GE*/ int down = start-1, int up = end;
while(down+1 < up) { int mid = (down+up)/2; if(f2(mid)) up = mid; else down = mid;
} assert(down+1 == L);
