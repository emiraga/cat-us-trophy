int lf[205],mat[205][205],n; 
VVI adj; 
VI vis,inactive,match; 
int N; 
bool dfs(int x,VI &blossom){ 
    if(inactive[x]) return false; 
    int i,y; 
    vis[x] = 0; 
    for(i = adj[x].size()-1;i>=0;i--){ 
        y = adj[x][i]; 
        if(inactive[y]) continue; 
        if(vis[y]==-1){ 
            vis[y] = 1; 
            if(match[y]==-1 || dfs(match[y],blossom)){ 
                match[y] = x; 
                match[x] = y; 
                return true; 
            } 
        } 
        if(vis[y]==0 || blossom.size()){ 
            blossom.push_back(y); 
            blossom.push_back(x); 
            if(blossom[0]==x){ 
                match[x] = -1; 
                return true; 
            } 
            return false; 
        } 
    } 
    return false; 
} 
bool augment(){ 
    VI blossom,mark; 

    int i,j,k,s,x; 
    for(i = 0;i<N;i++){ 
        if(match[i]!=-1) continue; 
        blossom.clear(); 
        vis = VI(N+1,-1); 
        if(!dfs(i,blossom)) continue; 
        s = blossom.size(); 
        if(s==0) return true; 


        mark = VI(N+1,-1); 
        for(j = 0;j<s-1;j++){ 
            for(k = adj[blossom[j]].size()-1;k>=0;k--)
                mark[adj[blossom[j]][k]] = j;  
        } 
        for(j = 0;j<s-1;j++){ 
            mark[blossom[j]] = -1; 
            inactive[blossom[j]] = 1; 
        } 
        adj[N].clear(); 
        for(j = 0;j<N;j++){ 
            if(mark[j]!=-1) 
                adj[N].pb(j),adj[j].pb(N); 
        } 
        match[N] = -1; 
        N++; 
        if(!augment()) return false; 
        N--; 

        for(j = 0;j<N;j++){ 
            if(mark[j]!=-1) adj[j].pop_back(); 
        } 
        for(j = 0;j<s-1;j++){ 
            inactive[blossom[j]] = 0; 
        } 

        x = match[N]; 
        if(x!=-1){ 
            if(mark[x]!=-1){ 
                j = mark[x]; 
                match[blossom[j]] = x; 
                match[x] = blossom[j]; 
                if(j & 1)  
                    for(k = j+1;k<s;k+=2) { 
                        match[blossom[k]] = blossom[k+1]; 
                        match[blossom[k+1]] = blossom[k]; 
                    } 
                else 
                    for(k = 0;k<j;k+=2) { 
                        match[blossom[k]] = blossom[k+1]; 
                        match[blossom[k+1]] = blossom[k]; 
                    } 
            } 
        } 

        return true; 
    } 
    return false; 
} 

int edmond(int n){ 
    int i,j,ret = 0; 
    N = n; 
    adj = VVI(2*N+1); 
    for(i = 0;i<n;i++){ 
        for(j = i+1;j<n;j++){ 
            if(mat[i][j]){ 
                adj[i].pb(j); 
                adj[j].pb(i); 
            } 
        } 
    } 
    match = VI(2*N+1,-1); 
    inactive = VI(2*N+1); 
    while(augment()) ret++; 
    return ret; 
}
