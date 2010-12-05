int f[ len ];
f[0] = f[1] = 0;
FOR(i,2,len) {
    int j = f[i-1]; 
    while( true ) {
        if( s[j] == s[i-1] ) { f[i] = j + 1; break;
        }else if( !j ) { f[i] = 0; break;
        }else j = f[j]; 
    }   
}
i = j = 0;
while( true ) {
    if( i == len ) break;
    if( text[i] == s[j] ) { i++, j++;
        if( j == slen ) // match found
    }else if( j > 0 ) j = f[j]; 
    else i++;
}
