const int N = 100 * 1000;
struct node { int value, weight, ch[2], size; } T[ N+10 ] ; int nodes;
#define Child(x,c) T[x].ch[c]
#define Value(x) T[x].value
#define Weight(x) T[x].weight
#define Size(x) T[x].size
#define Left Child(x,0)
#define Right Child(x,1)
void update(int x) { Size(x) = 1 + Size(Left)+Size(Right); }
int newnode(int value, int prio) {
    T[++nodes]=(node){value,prio,0,0};
    update(nodes);
    return nodes;
}
void rotate(int &x, int c) {
    int y = Child(x,c);
    Child(x,c) = Child(y,!c);
    Child(y,!c) = x;
    update(x);
    x=y;
}
void insert(int &x, int n) {
    if(!n) return; if(!x) { x=n; return; }
    int t = Value(n) > Value(x);
    insert(Child(x,t), n);
    if( Weight(Child(x,t)) < Weight(x)) rotate(x, t);
    update(x);
}
int find_GE(int x, int value) {
    int ret=0;
    while(x) {
        if(Value(x)==value)return x;
        if(Value(x)>value) ret=x, x=Left; else x=Right;
    }
    return ret;
}
int find(int x, int value) {
    for(; x; x=Child(x,Value(x)<value))
        if(Value(x)==value)return x;
    return 0;
}
void del(int &x, int value) { if(!x)return;
    if(value < Value(x)) { del(Left, value); update(x); return;}
    if(value > Value(x)) { del(Right, value); update(x); return;}
    if(Left || Right) rotate(x, Weight(Left) < Weight(Right)), del(x,value); else x=0;
}
int findmin(int x) { for(;Left;x=Left); return x; }
int findmax(int x) { for(;Right;x=Right); return x; }
int findkth(int x, int k) {
    while(x) {
        if(k<=Size(Left)) x=Left;
        else if(k==Size(Left)+1)return x;
        else { k-=Size(Left)+1; x=Right; }
    } }
void split(int &x, int &leftT, int &rightT, int value) {
    insert(x, newnode(value, INT_MIN)); leftT=Left; rightT=Right; }
void join(int &x, int leftT, int rightT) { insert(leftT, rightT); x = leftT; }
int queryrangekth(int &x, int a, int b, int k) {
    insert(x, newnode(a, INT_MIN+1));
    insert(x, newnode(b, INT_MIN));
    int ret = findkth(Child(Left,1),k);
    int root = Child(Left,0);
    insert(root, Child(Left,1));
    insert(root, Right);
    x=root;
    return ret;
}
