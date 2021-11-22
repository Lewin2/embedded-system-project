#pragma warning(disable:4996)
#include <iostream>
#include <vector>
using namespace std;

const int INSTALLED = 2;
const int DEFENDED = 1;
const int NOT_DEFENDED = 0;

int n, m;
int s, e;
vector<vector<int>> adjArray;
vector<int> visited;

int numTuret = 0;

void AddEdge(int start, int end) {
    adjArray[start].push_back(end);
    adjArray[end].push_back(start);
}

int aDFS(int v) {
    bool hasNOT_DEFENDED = false;
    bool hasINSTALLED = false;

    visited[v] = 1;

    if (adjArray[v].size() == 0) return NOT_DEFENDED;

    for (int i = 0; i < adjArray[v].size(); i++) {
        int x = adjArray[v][i];
        if (visited[x] == 0) {

            switch (aDFS(x)) {
            case NOT_DEFENDED:
                hasNOT_DEFENDED = true;
                break;
            case INSTALLED:
                hasINSTALLED = true;
                break;
            }

        }
    }

    if (hasNOT_DEFENDED) {
        numTuret++;
        return INSTALLED;
    }
    else if (hasINSTALLED) {
        return DEFENDED;
    }
    else {
        return NOT_DEFENDED;
    }

}

void DFS() {
    for (int v = 1; v <= n; v++)
        visited[v] = 0;

    for (int v = 1; v <= n; v++) {
        if (visited[v] == 0) {
            if (aDFS(v) == NOT_DEFENDED) {
                numTuret++;
            }
        }
    }
}

int main() {
    freopen("turet.txt", "r", stdin);
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        numTuret = 0;
        adjArray.clear();
        visited.clear();

        cin >> n >> m;

        adjArray.resize(n + 1);
        visited.resize(n + 1);

        for (int j = 0; j < m; j++) {
            cin >> s >> e;
            AddEdge(s, e);
        }
        DFS();

        printf("%d\n", numTuret);
    }

}