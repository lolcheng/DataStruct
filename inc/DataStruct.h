#include <iostream>
#include <string.h>
#include <vector> //STL向量容器
#include <stack>  //STL栈容器
#include <queue>
#include <inc/MyMath.h>

template <typename T>
struct LinkNode // 链节点
{
    T data;
    LinkNode<T> *next;
    LinkNode() : next(NULL) {} // 构造函数
    LinkNode(T d) : data(d), next(NULL) {}
};

template <typename T>
struct BTNode // 二叉树节点：由该节点的数据和指向其左右子节点的指针构成
{
    T data;
    BTNode *lchild;
    BTNode *rchild;
    BTNode() : lchild(NULL), rchild(NULL) {}
    BTNode(T d) : data(d), lchild(NULL), rchild(NULL) {}
};

template <typename T>
struct HTNode // 哈夫曼树节点
{
    T data;        // 节点值
    double weight; // 权值
    int parent;
    int lchild;
    int rchild;
    bool flag; // 标识是双亲节点的左节点(true)还是右节点(false)
    HTNode() : parent(-1), lchild(-1), rchild(-1) {}
    HTNode(char d, double w) : parent(-1), lchild(-1), rchild(-1), data(d), weight(w), flag(true) {}
};

// 图的邻接表相关节点
template <typename T> // 邻接表其他节点
struct ArcNode
{
    int adjvex; // 当前节点的邻接点编号
    T weight;   // 权值，对于不带权的图weight固定为1
    ArcNode<T> *nextarc;
};

template <typename T> // 邻接表头结点
struct HNode
{
    std::string info; // 存储节点信息，可以不用
    ArcNode<T> *firstarc;
};

// TODO:给顺序栈和链栈做输出
// TODO:给pop重载不传参数的输出
// TODO:做动态数组和动态线性表
// TODO:重载动态线性表的SearchElem的cout输出，二分查找

template <typename T>
class DynamicArray // 动态数组
{
public:
    DynamicArray() : data(NULL), size(0), capacity(0) {}
    ~DynamicArray() { delete[] data; }
    void AddOneByOne(int e) // 添加一个元素，重新分配内存，扩展一个空间
    {
        if (data == NULL)
        {
            data = new int[1]; // 当前数组为空，分配大小为1的内存空间，使用指针和动态内存分配来实现
            data[0] = e;
            size = 1;
            capacity = 1;
        }
        else // 当前数组不为空，重新分配内存空间
        {
            int *newData = new int[capacity + 1];
            for (int i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            newData[size] = e;
            delete[] data;
            data = newData;
            size++;
            capacity++;
        }
    }

private:
    int *data;    // 指向动态数组的指针
    int size;     // 当前动态数组中元素的个数
    int capacity; // 当前动态数组的容量
};

template <typename T, int InitialSize> // InitialSize是线性表的初始容量
class DynamicSqList                    // 动态线性表
{
public:
    DynamicSqList() // 构造函数：初始化
    {
        data = new T[InitialSize]; // 类似于new int[size]，分配一个大小为InitialSize，类型为T的空间
        capacity = InitialSize;
        length = 0;
    }
    DynamicSqList(DynamicSqList<T, InitialSize> &s) // 重载：深拷贝构造函数
    {
        this->capacity = s.GetCapacity();
        this->length = s.GetLength();
        data = new int[this->capacity];
        int i = 0;
        while (s.GetElem(i, this->data[i]))
            i++;
    }
    ~DynamicSqList() { delete[] data; }
    void CreateList(T a[], int n) // 利用数组a整体建立线性表
    {
        for (int i = 0; i < n; i++)
        {
            if (length == capacity)
                this->Recap(2 * length); // 超过容量则扩容2倍
            data[length] = a[i];
            length++;
        }
    }
    bool GetElem(int i, T &e) // 求位置为i（首位置为0）处线性表的元素值
    {
        if (i < 0 || i >= this->length)
            return false;
        e = data[i];
        return true;
    }
    bool SetElem(int i, T e) // 设置位置为i（首位置为0）处线性表的元素值
    {
        if (i < 0 || i >= this->length)
            return false;
        data[i] = e;
        return true;
    }
    bool SearchElem(T e, int *index) // 顺序查找线性表中所有值为e的元素下标并存放在index里
    {
        int i = 0, cnt = 0;
        while (i < this->length)
        {
            if (data[i] == e)
            {
                index[cnt] = i;
                cnt++;
            }
            i++;
        }
        if (cnt == 0)
            return false;
        return true;
    }
    bool SearchElem(T e, int *index, int n) // 重载：顺序查找线性表中前n个值为e的元素下标
    {
        int i = 0, cnt = 0;
        while (i < this->length)
        {
            if (data[i] == e)
            {
                index[cnt] = i;
                cnt++;
                if (cnt >= n)
                    return true;
            }
            i++;
        }
        if (cnt == 0)
            return false;
        return true;
    }
    bool Insert(int i, T e) // 将元素e插入位置i处，之后的元素后移（首位置为0）
    {
        if (i < 0 || i >= this->length)
            return false;
        if (this->length == this->capacity)
            this->Recap(2 * this->length); // 过容量时倍增
        for (int j = this->length; j > i; j--)
            data[j] = data[j - 1];
        data[i] = e;
        this->length++;
        return true;
    }
    bool Delete(int i)
    {
        if (i < 0 || i >= this->length)
            return false;
        for (int j = i; j < this->length - 1; j++)
            data[j] = data[j + 1];
        length--;
        if (this->capacity > InitialSize && length <= this->capacity / 4) // 长度变为原来四分之一时缩容一半
            this->Recap(this->capacity / 2);
        return true;
    }
    void DispDynamicSqList()
    {
        for (int i = 0; i < this->length; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    int GetLength()
    {
        return this->length;
    }
    int GetCapacity()
    {
        return this->capacity;
    }

private:
    void Recap(int newcap) // 重构线性表容量
    {
        if (newcap <= 0)
            return;
        T *olddata = data;
        data = new T[newcap];
        capacity = newcap;
        for (int i = 0; i < length; i++)
            data[i] = olddata[i];
        delete[] olddata;
    }
    T *data;
    int capacity;
    int length;
};

template <typename T, int MaxSize> // MaxSize是栈的最大容量
class SqStack                      // 顺序栈，先进先出
{
public:
    SqStack()
    {
        this->data = new T[MaxSize]; // 为data申请容量为MaxSize的空间
        this->top = -1;              // 初始化栈顶指针
    }
    ~SqStack() { delete[] data; }              // 释放data所在的空间
    bool Empty() { return top == -1; }         // 栈空判断
    bool Full() { return top == MaxSize - 1; } // 栈满判断
    bool Push(T e)
    {
        if (this->Full())
            return false;
        top++;
        data[top] = e;
        return true;
    }
    bool Pop(T &e)
    {
        if (this->Empty())
            return false;
        e = data[top];
        top--;
        return true;
    }
    bool GetTop(T &e)
    {
        if (this->Empty())
            return false;
        e = data[top];
        return true;
    }

private:
    T *data; // 栈元素数组
    int top; // 栈顶指针，栈空时指向-1，其他时候指向栈顶（序号从零开始）
};

template <typename T>
class LinkStack // 链栈，先进先出
{
public:
    LinkStack() { head = new LinkNode<T>; } // 构造函数
    ~LinkStack()                            // 析构函数，将链表从头至尾依序删除
    {
        LinkNode<T> *pre = head, *p = pre->next;
        while (p != NULL)
        {
            delete pre;
            pre = p;
            p = p->next;
        }
        delete pre;
    }
    bool Empty() // 判断栈空
    {
        return head->next == NULL;
    }
    bool Push(T e) // 入栈：头插法，新元素插在头结点之后，这也是栈顶的位置
    {
        LinkNode<T> *p = new LinkNode<T>(e); // new一个值为e的新节点
        p->next = head->next;
        head->next = p;
        return true;
    }
    bool Pop(T &e) // 出栈：将栈顶元素值取出后（引用），删除首节点（栈空返回false）
    {
        LinkNode<T> *p;
        if (head->next == NULL)
            return false;
        p = head->next;
        e = p->data;
        head->next = p->next;
        delete p;
        return true;
    }
    bool GetTop(T &e) // 仅返回栈顶元素（引用），不出栈
    {
        LinkNode<T> *p;
        if (head->next == NULL)
            return false;
        p = head->next;
        e = p->data;
        return true;
    }

private:
    LinkNode<T> *head; // 头结点
};

template <typename T, int MaxSize> // MaxSize为队列容量
class CSqQueue                     // 循环队列，先进后出
{
public:
    CSqQueue()
    {
        data = new T[MaxSize];
        front = rear = 0; // 队头和队尾赋初值
    }
    ~CSqQueue() { delete[] data; }
    bool Empty() { return this->GetLength() == 0; }
    bool Full() { return this->GetLength() == MaxSize - 1; } // 队尾指针与队首指针相隔1时认为队满（为了区分队空与队满）
    int GetLength() { return (rear - front + MaxSize) % MaxSize; }
    bool Push(T e)
    {
        if (this->Full())
            return false;
        rear = (rear + 1) % MaxSize;
        data[rear] = e;
        return true;
    }
    bool Pop(T &e) // 出队，头结点始终指向队首的前一个位置
    {
        if (this->Empty())
            return false;
        front = (front + 1) % MaxSize;
        e = data[front];
        return true;
    }
    bool Pop() // 重载Pop：直接出队，不输出数据
    {
        if (this->Empty())
            return false;
        front = (front + 1) % MaxSize;
        return true;
    }
    bool GetHead(T &e) // 取队头，但不出队
    {
        if (this->Empty())
            return false;
        e = data[(front + 1) % MaxSize];
        return true;
    }
    bool DispCSqQueue() // 全显示
    {
        int OralFront = front;
        while (!this->Empty())
        {
            front = (front + 1) % MaxSize;
            std::cout << data[front] << " ";
        }
        std::cout << std::endl;
        front = OralFront;
    }

private:
    T *data;         // 存放队中元素
    int front, rear; // 队头和队尾指针
};

template <typename T>
class LinkList // 单链表
{
public:
    LinkList() { head = new LinkNode<T>(); } // 构造链表，即创建一个头结点
    ~LinkList()                              // 析构链表，从头删除到尾
    {
        LinkNode<T> *pre, *p;
        pre = head;
        p = pre->next;
        while (p != NULL)
        {
            delete pre;
            pre = p;
            p = p->next;
        }
        delete pre;
    }
    void CreateListF(T a[], int n) // 整体头插法建表，新节点插在头结点之后，数据由数组a导入,链表结果是数组元素的倒序
    {
        for (int i = 0; i < n; i++)
        {
            LinkNode<T> *s = new LinkNode<T>(a[i]);
            s->next = head->next;
            head->next = s;
        }
    }
    void CreateListR(T a[], int n) // 整体尾0插法建表，新节点插在尾结点之后，数据由数组a导入，链表结果是数组元素的正序
    {

        LinkNode<T> *s, *r; // r始终指向尾结点
        r = head;
        for (int i = 0; i < n; i++)
        {
            s = new LinkNode<T>(a[i]);
            r->next = s;
            r = s;
        }
        r->next = NULL;
    }
    int GetLength() // 求链表节点个数
    {
        LinkNode<T> *p = head;
        int cnt = 0;
        while (p->next != NULL)
        {
            cnt++;
            p = p->next;
        }
        return cnt;
    }
    bool GetIData(int i, T &res) // 引用返回序号为i的data值
    {
        LinkNode<T> *p = this->GetI(i);
        if (p != NULL)
        {
            res = p->data;
            return true;
        }
        return false;
    }
    bool Insert(int i, T e) // 将节点插入序列i处（显然原序列i处变为i+1）,p(i-1),s(i)
    {
        LinkNode<T> *p = this->GetI(i - 1);
        if (p != NULL)
        {
            LinkNode<T> *s = new LinkNode<T>(e);
            s->next = p->next;
            p->next = s;
            return true;
        }
        else
            return false;
    }
    bool Delete(int i) // 删除序号为i（0为首节点）的节点,p(i-1),q(i)
    {
        LinkNode<T> *p = this->GetI(i - 1);
        if (p != NULL)
        {
            LinkNode<T> *q = p->next;
            if (q != NULL)
            {
                p->next = q->next;
                delete q;
                return true;
            }
            return false;
        }
        return false;
    }
    void DispLinkList() // 顺链表方向输出各节点值
    {
        LinkNode<T> *p = head->next;
        while (p != NULL)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

private:
    LinkNode<T> *head;       // 头结点，外部不会调用到。首节点下标为0
    LinkNode<T> *GetI(int i) // 查找序号为i（-1为头结点,0为首节点）的节点
    {
        if (i < -1 || i >= this->GetLength())
            return NULL;
        LinkNode<T> *p = head;
        int j = 0;
        while (j <= i)
        {
            p = p->next;
            j++;
        }
        return p;
    }
};

template <typename T>
class BTree // 二叉树，目前模板只支持char，主要问题在CreateBTree中p = new BTNode<T>(str[i]);能否将一段字符串直接视为数字形式呢?
{
public:
    BTree() : r(NULL) {} // 初始化一棵树，即建立一个空的根节点
    ~BTree()
    {
        DestroyBTreeUnit(r);
        r = NULL;
    }
    void CreateBTree(std::string str) // 用括号表示法建立一棵树，例如A(B(C,D),E);A(B(C),D)(B只有左节点C);A(B(,C),D)(B只有右节点C)
    {
        std::stack<BTNode<T> *> st; // 定义一个类型为BTNode的STL栈
        BTNode<T> *p;
        bool flag;
        int i = 0;
        while (i < str.length())
        {
            switch (str[i])
            {
            case '(':
                st.push(p);
                flag = true; // 接下来要处理的是父节点的左子节点
                break;
            case ')':
                st.pop();
                break;
            case ',':
                flag = false; // 接下来要处理的是父节点的右子节点
                break;
            default:
                p = new BTNode<T>(str[i]);
                if (r == NULL) // p为首个节点，让它成为根节点
                    r = p;
                else // p不为首节点，根据flag的值判断他应该是父节点的左子节点还是右子节点
                {
                    if (flag && !st.empty())
                        st.top()->lchild = p; // 栈顶总是指向新节点p的最小父节点
                    else if (!st.empty())
                        st.top()->rchild = p;
                }
                break;
            }
            i++;
        }
    }
    void DispBTree() // 将二叉树显示为括号表达式的形式
    {
        DispBTreeUnit(r); // 从根节点开始递归显示全树.
    }
    BTNode<T> *FindNode(T x) // 查找data值为x的节点并返回该节点的地址
    {
        return FindNodeUnit(r, x);
    }
    int Height() // 求树的高度
    {
        return HeightUnit(r);
    }
    void PreOrderRecursion()
    {
        PreOrderUnit(r);
    }
    void PreOrderConventional() // 常规非递归先序遍历
    {
        if (this->r == NULL)
            return;
        std::stack<BTNode<T> *> st;
        BTNode<T> *p;
        st.push(this->r);
        while (!st.empty())
        {
            p = st.top();
            st.pop();
            std::cout << p->data;
            if (p->rchild != NULL)
                st.push(p->rchild);
            if (p->lchild != NULL)
                st.push(p->lchild);
        }
    }
    void InOrderRecursion() // 中序遍历
    {
        InOrderUnit(r);
    }
    void PostOrderRecursion()
    {
        PostOrderUnit(r);
    }

private:
    BTNode<T> *r;                    // root根节点
    void DispBTreeUnit(BTNode<T> *b) // DispBTree()的递归单元，输出当前值，如果左右子节点存在则递归
    {
        if (b != NULL)
        {
            std::cout << b->data;
            if (b->lchild != NULL || b->rchild != NULL)
            {
                std::cout << "(";
                DispBTreeUnit(b->lchild);
                if (b->rchild != NULL)
                    std::cout << ",";
                DispBTreeUnit(b->rchild);
                std::cout << ")";
            }
        }
    }
    BTNode<T> *FindNodeUnit(BTNode<T> *b, T x) //
    {
        BTNode<T> *p;
        if (b == NULL)
            return NULL; // 两个递归出口
        else if (b->data == x)
            return b;
        else
        {
            p = FindNodeUnit(b->lchild, x);
            if (p != NULL)
                return p;
            else
                return FindNodeUnit(b->rchild, x);
        }
    }
    BTNode<T> *FindAllNodeUnit(BTNode<T> *b, T x) //
    {
        std::vector<BTNode<T> *> vt;
        BTNode<T> *p;
        if (b == NULL)
            return NULL; // 两个递归出口
        else if (b->data == x)
            return b;
        else
        {
            p = FindNodeUnit(b->lchild, x);
            if (p != NULL)
                vt.push_back(p);
            return FindNodeUnit(b->rchild, x);
        }
    }
    int HeightUnit(BTNode<T> *b)
    {
        if (b == NULL)
            return 0;
        else
            return max(HeightUnit(b->lchild), HeightUnit(b->rchild)) + 1;
    }
    void DestroyBTreeUnit(BTNode<T> *b)
    {
        if (b != NULL)
        {
            DestroyBTreeUnit(b->lchild);
            DestroyBTreeUnit(b->rchild);
            delete b;
        }
    }
    void PreOrderUnit(BTNode<T> *b)
    {
        if (b != NULL)
        {
            std ::cout << b->data;
            PreOrderUnit(b->lchild);
            PreOrderUnit(b->rchild);
        }
    }
    void InOrderUnit(BTNode<T> *b)
    {
        if (b != NULL)
        {
            InOrderUnit(b->lchild);
            std::cout << b->data;
            InOrderUnit(b->rchild);
        }
    }
    void PostOrderUnit(BTNode<T> *b)
    {
        if (b != NULL)
        {
            PostOrderUnit(b->lchild);
            PostOrderUnit(b->rchild);
            std::cout << b->data;
        }
    }
};

template <typename T, int MAXV>
class MatGraph // 图的邻接矩阵存储
{
public:
    MatGraph() // 按规则初始化
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
    void SetMatGraphSize(int size)
    {
        this->n = size;
    }
    void CreateNewDirectEdge(int start, int target, int weight)
    {
        this->edges[start][target] = weight;
    }
    void CreateNewDirectlessEdge(int start, int target, int weight)
    {
        this->edges[start][target] = weight;
        this->edges[target][start] = weight;
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
            std::cout << std::endl;
        }
    }
    void Prim(int v) // 普里姆算法得到带权无向图以顶点v为根的最小生成树
    {
        int lowcost[MAXV], closest[MAXV]; // closest为最小边在U中的顶点，lowcost为该边的权值
        for (int i = 0; i < this->n; i++)
        {
            lowcost[i] = this->edges[v][i];
            closest[i] = v;
        }
        std::cout << "The minimum spanning tree is:" << std::endl;
        for (int i = 1; i < this->n; i++)
        {
            int min = INF;
            int k = -1;                       // k记录最短点的标号
            for (int j = 0; j < this->n; j++) // 在V-U中寻找离U最近的顶点k
            {
                if (lowcost[j] != 0 && lowcost[j] < min)
                {
                    min = lowcost[j];
                    k = j;
                }
            }
            std::cout << "Edge(" << closest[k] << "," << k << "),weight " << min << std::endl;
            lowcost[k] = 0;                   // 标记k进入U集
            for (int j = 0; j < this->n; j++) // 修改U和V的关系
            {
                if (lowcost[j] != 0 && this->edges[k][j] < lowcost[j])
                {
                    lowcost[j] = this->edges[k][j];
                    closest[j] = k;
                }
            }
        }
    }
    void Kruskal() // 克鲁斯卡尔算法得到带权无向图的最小生成树（与顶点无关）
    {
    }

private:
    T edges[MAXV][MAXV]; // 权值
    int n, e;            // 顶点数和边数
    int vexs[MAXV];      // 顶点编号
};

template <typename T, int MAXV>
class AdjGraph // 图的邻接表存储，记录每个节点出边构成
{
public:
    AdjGraph()
    {
        for (int i = 0; i < MAXV; i++)
            adjlist[i].firstarc = NULL;
    }
    ~AdjGraph() {} // TODO:析构
    void CreateNewArcNode(int start, int target, T weight)
    {
        ArcNode<T> *p = new ArcNode<T>();
        p->adjvex = target;
        p->weight = weight;
        p->nextarc = adjlist[start].firstarc;
        adjlist[start].firstarc = p; // 头插法建表
    }
    void SetAdjGraphSize(int size)
    {
        this->n = size;
    }
    void DispAdjGraph()
    {
        ArcNode<T> *p;
        for (int i = 0; i < this->n; i++)
        {
            std::cout << i;
            p = adjlist[i].firstarc;
            while (p != NULL)
            {
                std::cout << "->" << p->adjvex << " " << p->weight;
                p = p->nextarc;
            }
            std::cout << std::endl;
        }
    }
    void DFS(int v) // 图的深度优先遍历，起始点为v；由BFS得到的生成树称为BFS生成树
    {
        static int visited[MAXV]; // 已访问数组，初始为0，置静态设置初值并避免递归时重复定义
        std::cout << v << " ";
        visited[v] = 1;
        ArcNode<T> *p = this->adjlist[v].firstarc;
        while (p != NULL)
        {
            int w = p->adjvex;
            if (visited[w] == 0)
                DFS(w); // 递归访问更深的节点
            p = p->nextarc;
        }
    }
    void BFS(int v) // 图的广度优先遍历，起始点为v；由DFS得到的生成树称为DFS生成树
    {
        int visited[MAXV];                   // 已访问数组，初始为0，这里用memset，与DFS作对比
        memset(visited, 0, sizeof(visited)); // 经典用法
        std::queue<int> qu;                  // 定义队列
        std::cout << v << " ";
        visited[v] = 1;
        qu.push(v);
        while (!qu.empty())
        {
            int u = qu.front();
            qu.pop();
            ArcNode<T> *p = this->adjlist[u].firstarc;
            while (p != NULL)
            {
                if (visited[p->adjvex] == 0)
                {
                    std::cout << p->adjvex << " ";
                    visited[p->adjvex] = 1;
                    qu.push(p->adjvex);
                }
                p = p->nextarc;
            }
        }
    }

private:
    HNode<T> adjlist[MAXV];
    int n, e;
};