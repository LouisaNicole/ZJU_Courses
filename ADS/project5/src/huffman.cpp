#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int weight[0x40];
char character[0x40];
int wpl;

typedef struct _HNode
{
    int weight;
    char ch = 'z' + 1;
    struct _HNode *left_child;
    struct _HNode *right_child;
} HNode;
typedef HNode *HTree;

struct cmp
{
    bool operator()(const HNode *a, const HNode *b)
    {
        if (a->weight == b->weight)
            return a->ch > b->ch;
        return a->weight > b->weight;
    }
};

priority_queue<HNode*, vector<HNode*>, cmp> q;

HTree CreateHuffmanTree();
void CalWpl(HTree HT);
bool isOpt(int n);

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> character[i] >> weight[i];
        HNode *newNode = new HNode();
        newNode->ch = character[i];
        newNode->weight = weight[i];
        newNode->left_child = newNode->right_child = nullptr;
        q.push(newNode);
    }
    HTree HT = CreateHuffmanTree();

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        if (isOpt(n))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}

HTree CreateHuffmanTree()
{
    HTree HT;
    while (!q.empty())
    {
        if (q.size() == 1)
        {
            HNode *root = q.top();
            q.pop();
            HT = root;
            break;
        }
        else
        {
            HNode *left = q.top();
            q.pop();
            HNode *right = q.top();
            q.pop();
            HNode *newNode = new HNode();
            newNode->weight = left->weight + right->weight;
            newNode->left_child = left;
            newNode->right_child = right;
            HT = newNode;
            q.push(newNode);
        }
    }
    CalWpl(HT);
    return HT;
}

void CalWpl(HTree HT)
{
    if (HT->left_child || HT->right_child)
        wpl += HT->weight;
    if (!HT->left_child && !HT->right_child)
        return;
    if (HT->left_child)
        CalWpl(HT->left_child);
    if (HT->right_child)
        CalWpl(HT->right_child);
    return;
}

bool isOpt(int n)
{
    int ansWpl = 0;
    char ch;
    vector<string> code(n);
    for (int i = 0; i < n; i++)
    {
        cin >> ch >> code[i];
        ansWpl += code[i].length() * weight[i];
    }
    if (ansWpl != wpl)
    {
        return false;
    }
    else
    {
        bool flag = true;
        for (int i = 0; i < n && flag; i++)
        {
            for (int j = i + 1; j < n && flag; j++)
            {
                for (int k = 0; k < static_cast<int>(code[i].length()) && k < static_cast<int>(code[j].length()); k++)
                {
                    if (code[i][k] != code[j][k])
                    {
                        flag = true;
                        break;
                    }
                    flag = false;
                }
            }
        }
        return flag;
    }
}