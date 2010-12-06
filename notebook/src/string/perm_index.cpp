int perm_index (char str[], int size) { 
    int index = 0; 
    REP(i,size-1) { 
        FOR(j,i+1,size-1) if (str[i] > str[j]) index ++; 
        index *= size-i-1; } 
    return index; 
}
