#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int MAXV = 10; // 最多的顶点数
const int INF = 0x3f3f3f3f;

using namespace std;

class MatGraph // 图的邻接矩阵
{
public:
    MatGraph()
    {
        for (int i = 0; i < MAXV; i++)
        {
            for (int j = 0; j < MAXV; j++)
            {
                if (i == j)
                    this->edges[i][j] = 0;
                else
                    this->edges[i][j] = INF;
            }
        }
        this->e = 0;
        this->n = 0;
    }
    void DispMatGraph()
    {
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->n; j++)
            {
                if (this->edges[i][j] == INF)
                    std::cout << "INF"
                              << " ";
                else
                    std::cout << this->edges[i][j] << " ";
            }
            std::cout << endl;
        }
    }
    int edges[MAXV][MAXV]; // 边长
    int n, e;              // 顶点数和边数
    int vexs[MAXV];        // 顶点编号
};

class Solution
{
public:
    void Dijkstra(MatGraph &g, int v) // 求从v到其他节点的最短路径，需要提前得知图的邻接矩阵
    {
        int dist[MAXV]; // 从源点v到节点i的最短路径长度
        int path[MAXV]; // path[j]指向j的前置节点u，从而形成路径，置初值为-1
        int S[MAXV];    // 集合标志位，S[i]=0表示位于未处理U集合，S[i]=1表示位于已处理S集合

        for (int i = 0; i < g.n; i++) // 初始化
        {
            dist[i] = g.edges[v][i];
            S[i] = 0;
            if (g.edges[v][i] != 0 && g.edges[v][i] < INF)
                path[i] = v;
            else
                path[i] = -1;
        }
        S[v] = 1;

        int mindis, u = -1; // mindis置最小距离
        for (int i = 0; i < g.n - 1; i++)
        {
            mindis = INF;
            for (int j = 0; j < g.n; j++) // 找到此时位于U集合中且距离源点最近的点j
            {
                if (S[j] == 0 && dist[j] < mindis)
                {
                    u = j;
                    mindis = dist[j];
                }
            }
            S[u] = 1;

            for (int j = 0; j < g.n; j++)
            {
                if (S[j] == 0)
                {
                    if (g.edges[u][j] < INF && dist[u] + g.edges[u][j] < dist[j])
                    {
                        dist[j] = dist[u] + g.edges[u][j];
                        path[i] = u;
                    }
                }
            }
        }

        // for (int i = 0; i < g.n; i++)
        // {
        //     cout << dist[i] << " ";
        // }

        int MaxNum = 0;
        for (int i = 0; i < g.n; i++)
        {
            if (dist[i] == INF)
            {
                std::cout << -1;
                return;
            }
            if (dist[i] > MaxNum && dist[i] < INF)
                MaxNum = dist[i];
        }
        std::cout << MaxNum;
    }
};

int main()
{
    string str1;
    ifstream fin;
    MatGraph m = MatGraph();
    Solution *s = new Solution();
    int NodeNum = 0, StartNode = 0;
    int temp = 0;
    // fin.open("D:\\codebox\\DataStruct\\in.txt");
    fin.open("in.txt");
    getline(fin, str1);
    for (int i = 0; i < str1.length(); i++)
    {
        if (str1[i] != ' ')
            temp = temp * 10 + (str1[i] - 48);
        else
        {
            NodeNum = temp;
            temp = 0;
        }
    }
    StartNode = temp;
    temp = 0;

    int a[3], cnt = 0;
    while (!fin.eof())
    {
        getline(fin, str1);
        // m.edges[str1[0] - 48 - 1][str1[2] - 48 - 1] = str1[4] - 48;
        for (int i = 0; i < str1.length(); i++)
        {
            if (str1[i] != ' ')
                temp = temp * 10 + (str1[i] - 48);
            else
            {
                a[cnt] = temp;
                temp = 0;
                cnt++;
            }
        }
        a[cnt] = temp;
        cnt = 0;
        temp = 0;
        if (a[0] != 0)
        {
            m.edges[a[0] - 1][a[1] - 1] = a[2];
            // cout << a[0] << " " << a[1] << " " << a[2] << endl;
        }
    }

    m.n = NodeNum;
    s->Dijkstra(m, StartNode - 1);
    return 0;
}