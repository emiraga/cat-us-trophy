/*
TASK: snip2tex
LANG: C++
USER: smilitude
DATE: 2010-02-05 Fri 02:35 PM
*/


#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<stack>
#include<list>
#include<iostream>
#include<fstream>
#include<numeric>
#include<string>
#include<vector>
#include<cstring>
#include<map>
#include<iterator>
using namespace std;

#define REP(i,n) for(int i=0; i<(n); i++)
#define FOR(i,a,b) for( __typeof(b) i=(a); i<=(b); i++)
#define FORD(i,a,b) for(__typeof(a) i=(a); i>=(b); i--)
#define SET(t,v) memset((t), (v), sizeof(t))
#define sz size()
#define pb push_back
#define i64 long long
#define ALL(x) x.begin(), x.end()
#define FORIT(i, m) for (__typeof((m).begin()) i=(m).begin(); i!=(m).end(); ++i)
#define REV(x) reverse( ALL( x ) )
#define IO freopen("cpp.snippets","r",stdin); freopen("out.tex","w",stdout);
#define bug(x) if(1) cerr << __LINE__ <<" "<< #x " = " << x << endl
#define VI vector<int>
#define VS vector<string>


string section = "\\section";
string stverb = "\\begin{verbatimtab}[4]";
string enverb = "\\end{verbatimtab}[4]";
string medskip = ""; // "\\smallskip";

bool issnip( char* line ) {
    stringstream ss( line );
    string s;
    ss >> s; if( s == "snippet" ) return 1;
    return 0;
}

void print( char* line ) {
    int perline = 115;
    int len = strlen( line );
    REP(i,len) {
        if( (i+1) % perline == 0 ) cout << endl;
        cout << line[i] ;
    }
    cout << endl;
}


string process( string s ) {
//    return s;
    string ret = "";
    s[0] = s[0] <= 'z' && s[0] >= 'a' ? s[0] - 'a' + 'A' : s[0];
    REP(i,s.sz) {
        if( s[i] == '_' ) {
//           cout << s << endl;
           s[i+1] = s[i+1] <= 'z' && s[i+1] >= 'a' ? s[i+1] - 'a' + 'A' : s[i+1], ret += s[i+1], ++i;
        }
        else ret += s[i];
    }
    return ret;
}

int main() {
    char line[10000];
    line[0] = '\0';

    IO

    cout <<"\\documentclass[a4paper,9pt]{article}" << endl;
    cout <<"\\setlength{\\parindent}{0pt}" << endl;
    cout <<"\\usepackage{moreverb}" << endl;
    cout <<"\\usepackage[letterpaper]{geometry}"<< endl;
    cout <<"\\geometry{verbose,tmargin=1cm,bmargin=2cm,lmargin=1cm,rmargin=1cm}"<< endl;

    cout << "\\begin{document}"<<endl;
    cout << "\\begin{center}" << endl;
    cout << "{\\Huge Serenity}" << endl;
    cout << "\\end{center}" << endl;
    cout << "\\tableofcontents{}"<<endl;

    cout << endl << endl;

    gets(line);
    while( true ) {
        stringstream ss( line );
        if( issnip( line ) ) {
            string s; ss >> s >> s;
            cerr << "processing snippet "<< process( s ) << endl;
            cout << section << "{"<< process(s)<<"}"<<endl;
            int n = 0;
            cout << stverb << endl;
            bool good = 0;
            while( gets( line ) ) {
                if( issnip( line ) )  { good = 1; break; }
                if(strlen(line) > 0)
                {
                    ++n;
                    //cout.width(2);
                    //cout << n ;
                    print(line);
                }
            }
            cout << enverb << endl;
            cout << medskip << endl;
            if( good ) continue;
        }else continue;
        if( !gets( line ) ) break;
    }

    cout <<"\\end{document}"<<endl;

    return 0;
}
