
/**
void dfsVisit(vector<vector<int> >&graph, int node, vector<int>&visit,
               vector<int>&father)
{
    int n = graph.size();
    visit[node] = 1;
    //cout<<node<<"-\n";
    for(int i = 0; i < n; i++)
        if(i != node && graph[node][i] != INT_MAX)
        {
            if(visit[i] == 1 && i != father[node])//找到一个环
            {
                int tmp = node;
                cout<<"cycle: ";
                while(tmp != i)
                {
                    cout<<tmp<<"->";
                    tmp = father[tmp];
                }
                cout<<tmp<<endl;
            }
            else if(visit[i] == 0)
            {
                father[i] = node;
                dfsVisit(graph, i, visit, father);
            }
        }
    visit[node] = 2;
}

void dfs(vector<vector<int> >&graph)
{
    int n = graph.size();
    vector<int> visit(n, 0); //visit按照算法导论22.3节分为三种状态
    vector<int> father(n, -1);// father[i] 记录遍历过程中i的父节点
    for(int i = 0; i < n; i++)
        if(visit[i] == 0)
            dfsVisit(graph, i, visit, father);
}
*/

//Not verified yet
static void dfsVisit(int** graph, const int N, int node, int* visited, int* trace) {
    visited[node] = 1;

    for (int i = 0; i < N; i++) {
        if ((i != node) && (graph[node][i] != INT_MAX)) {
            if ((visited[i] == 1) && (i != trace[node])) {
                //Cycle found
                printf("Found cycle:");
                for (int j = i; j < traceTail; j++) printf(",%d", trace[j]);
                printf("\n");
            } else if (visited[i] == 0) {
                trace[i] = node;
                dfsVisit(graph, N, i, visited, trace);
            }
        }
    }
    visited[node] = 2;
}

void dfs(int** graph, const int N) {
    if (!graph || (N <= 0)) return;
    int visited[N];
    int trace[N];
    memset(visited, 0, sizeof(int) * N);
    memset(trace, -1, sizeof(int) * N);
    for (int i = 0; i < n; i++) if (!visited[i]) dfsVisit(graph, N, i, visited, trace, 0);
}
