//
// Created by colors_wind on 2020/11/25.
//
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
static const int VISITED = 1;
static const int UNVISITED = 0;
static const int INF = -1;
class Graph {
private:
    int** matrix;
    int* mask;
    int n;
    int e;
public:
    Graph(int n) {
        matrix = new int*[n];
        mask = new int[n];
        for(int k=0;k<n;k++) {
            matrix[k] = new int[n];
            mask[k] = UNVISITED;
            for(int l=0;l<n;l++)
                matrix[k][l] = INF;
        }
        this->n = n;
    }

    int first(int v) {
        for(int k=0;k<n;k++)
            if (matrix[v][k] >= 0)
                return k;
        return INF;
    }

    int next(int v1, int v2) {
        for(int k=v2+1;k<n;k++)
            if (matrix[v1][k] >= 0)
                return k;
        return INF;
    }

    void addEdge(int v1, int v2) {
        matrix[v1][v2] = 1;
        matrix[v2][v1] = 1;
        e++;
    }


    int firstUnvisitedNeighbor(int v) {
        int f = first(v);
        while(mask[f] == VISITED) {
            f = next(v, f);
            if (f < 0) break;
        }
        return f;
    }

    void DFS(int v) {
        stack<int> stack;
        stack.push(v);
        visit(v);
        while(!stack.empty()) {
            int curr = stack.top();
            int to = firstUnvisitedNeighbor(curr);
            if (to < 0) {
                stack.pop();
            } else {
                stack.push(to);
                visit(to);
            }

        }
        clearMask();
    }

    void BFS(int v) {
        queue<int> queue;
        queue.push(v);
        visit(v);
        while(!queue.empty()) {
            int curr = queue.front();
            int to = firstUnvisitedNeighbor(curr);
            if (to < 0) {
                queue.pop();
            } else {
                queue.push(to);
                visit(to);
            }

        }
        clearMask();
    }



    void visit(int v) {
        mask[v] = VISITED;
        cout << "Visit: " << v << endl;
    }

    void clearMask() {
        for(int k=0;k<n;k++)
            mask[k] = UNVISITED;
    }
};

int main() {
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int n, e, s;
        cin >> n >> e >> s;
        Graph graph(n);
        for (int k = 0; k < e; k++) {
            int i, j;
            cin >> i >> j;
            graph.addEdge(i, j);
        }
        graph.BFS(s);
    }
}

