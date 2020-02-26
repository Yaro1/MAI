#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_INT 2147483647
#define NOBODY -1
using namespace std;

bool bfs(std::vector<std::vector<int64_t> > &matrix, int s, int f, std::vector<int> &path)
{
    vector <bool> was(matrix.size(), false);
    queue<int> q;
    q.push(s);
    was[s] = true;
    path[s] = NOBODY;

    while (!q.empty()) {
        int now_element = q.front();
        q.pop();
        for (int next_element = 1; next_element < matrix.size(); ++next_element) {
            if (!was[next_element] && matrix[now_element][next_element]) {
                q.push(next_element);
                path[next_element] = now_element;
                was[next_element] = true;
            }
        }
    }
    //return was[f] == true;
    return was[f];
}

long long ford(std::vector<std::vector<int64_t> > &matrix, int s, int f) {
    long long answer = 0;
    vector <int> path(matrix.size());
    while(bfs(matrix,s,f,path)){
        int64_t potok = MAX_INT;
        for(int i = f;i != s;i = path[i])
            potok = min(potok, matrix[path[i]][i]);
        for(int i = f; i != s; i = path[i]) {
            matrix[path[i]][i] -= potok;
            matrix[i][path[i]] += potok;
        }
        answer += potok;
    }
    return answer;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector <vector <int64_t>> matrix(N + 1);
    for(int i = 0; i < N + 1;++i)
        matrix[i].resize(N + 1, 0);

    for(int i = 0; i < M;++i) {
        int64_t a,b,c;
        cin >> a >> b >> c;
        matrix[a][b] = c;
    }
   cout << ford(matrix, 1, N) << endl;
    return 0;
}