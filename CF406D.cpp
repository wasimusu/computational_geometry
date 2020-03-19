// Hill Climbing

#include <bits/stdc++.h>
using namespace std;

int xx[100000];
long long yy[100000];
int dd[100000];

long long cross3(int i, int j, int k){
    long long x1 = xx[j] - xx[i];
    long long y1 = yy[j] - yy[i];
    long long x2 = xx[j] - xx[k];
    long long y2 = yy[j] - yy[k];
    return x1 * y2 - x2 * y1;
}

// Obtain the convex hull starting from the start node to the end
void tree(map<int, int>& edges, int N){
    for(int i = 0; i < N; i++) dd[i] = 0;

    int path[N+1];
    int k = 0;
    for(int i = N-1; i >=0 ; i--){
        while(k >= 2 && cross3(path[k-2], i, path[k-1]) < 0) {
            edges[path[k-1]] = path[k-2];
            k -= 1;
        }
        path[k++] = i;
        if (k >= 2){
            edges[path[k-1]] = path[k-2];
        }
        if (k >=2) {
            dd[path[k-1]] = dd[path[k-2]] + 1;
        }
    }
    for(int i = 0; i < N; i++) dd[i] -= 1;
    return;
}
void query(map<int, int> &edges, int N, int* aa, int* bb, int M){
    int hh[N];
    for(int i = 0; i < N; i++) hh[i] = dd[i];

    // Build parents
    int col = max(1, (int)ceil(log2(N)));
    int pp[N][col];
    for(int r = 0; r < N; r++){
        for(int c = 0; c < col; c++)
            pp[r][c] = -1;
    }

    // Initialize the first parent
    for(int r = 0; r < N; r++){
        try{
            pp[r][0] = edges.at(r);
        } catch(...){
            pp[r][0] = -1;
        }
    }

    // Fill all other columns
    for(int c = 1; c < col; c++){
        int cc = c - 1;
        for(int r = 0; r < N - 1; r++){
            if (pp[r][cc] != -1)
                pp[r][c] = pp[pp[r][cc]][cc];
        }
    }
    edges.clear();

    int a, b;
    for(int i = 0; i < M; i++){
        a = *aa++ - 1;
        b = *bb++ - 1;

        // Balance the heights first
        int minh = min(hh[a], hh[b]);
        if (hh[a] > hh[b]) swap(a, b);
        int k = col;
        while(hh[b] >= minh && k > 0){
            k -= 1;
            if (pow(2, k) > hh[b] - minh) continue;
            if (hh[pp[b][k]] < minh) continue;
            b = pp[b][k];
        }

        // If while balancing height, both nodes become equal, that's lca
        if(a == b) {
            cout << a + 1 << " ";
            continue;
        }

        // Jumping up the nodes of the tree
        int lca = a;
        int j = col;
        while (j >= 0){
            j--;
            if (pp[a][j] != -1 && pp[b][j] != pp[a][j]){
                a = pp[a][j];
                b = pp[b][j];
            }
        }
        lca = pp[a][0];
        cout << lca + 1 << " ";
    }
    return;
}

int main(){
    //unsigned int 4294967295 long 4294967295

    int N;
    cin >> N;
    int a;
    long long b;
    for(int i = 0; i < N; i++){
        cin >> xx[i] >> yy[i];
    }

    map<int, int> edges;
    edges[N-1] = -1; // The last node is parent
    tree(edges, N);

    // Read teams position    
    int M;
    cin >> M;
    int aa[M], bb[M];
    for(int i = 0; i < M; i++){
        cin >> aa[i] >> bb[i];
    }

    query(edges, N, aa, bb, M);
    return 0;
}