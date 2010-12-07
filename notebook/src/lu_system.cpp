double A[N][N], B[N]; //input
double X[N], L[N][N], U[N][N], D[N];

for(i=0;i<N;i++)
    for(j=0;j<N;j++)
        if(i == j)
            L[i][j] = 1.0;
        else
            L[i][j] = 0.0;

for(i=0;i<N;i++)
    for(j=0;j<N;j++)
        U[i][j] = A[i][j];

for(k=0;k<N-1;k++)
{
    for(i=k+1;i<N;i++)
    {
        double m=U[i][k]/U[k][k];
        L[i][k] = m;
        for(j=k+1;j<N;j++)
        {
            U[i][j] -= m * U[k][j];
        }
    }
}

D[0] = B[0] / L[0][0];
for(i=1;i<N;i++)
{
    double s = 0;
    for(j=0;j<i;j++)
    {
        s += L[i][j] * D[j];
    }
    D[i] = (B[i] - s)/L[i][i];
}

X[N-1] = D[N-1] / U[N-1][N-1];
for(i=N-2;i>=0;i--)
{
    double s = 0;
    for(j=i+1;j<N;j++)
    {
        s += U[i][j] * X[j];
    }
    X[i] = (D[i] - s)/U[i][i];
}
