#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<fstream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode():left(NULL),right(NULL){}
    TreeNode(int d)
    {
    	val=d;
    	right=left=NULL;
	}
};

class Tree
{

	public:
	TreeNode *r;
	Tree()
	{
		r=NULL;
	}

	void CreateTree(string str)
	{
		stack<TreeNode* > st;
		TreeNode *p;
		bool flag;
		int i=0;
		while(i<str.length())
		{
			switch(str[i])
			{
				case '(':
					st.push(p);
					flag=true;
					break;
				case ')':
					st.pop();
					break;
				case ',':
					flag=false;
					break;
				default:
					//p=new TreeNode(str[i]);
					int d=0;
					while(str[i]>='0' && str[i]<='9')
					{
						d=10*d+(str[i]-'0');
						i++;
					}
					i--;
					p=new TreeNode(d);
					if(r==NULL)
					  r=p;
					else
					{
						if(flag && !st.empty())
						  st.top()->left=p;
						else if(!st.empty())
						  st.top()->right=p;
					}
					break;
			}
			i++;
		}
	}
};

void dfs(TreeNode *root,vector<int> &num)
{
	int j;
	if(!root->left && !root->right)
	{
		j=root->val-'0';
		num.push_back(j);
		j=0;
	}
	else
	{
		if(root->left)
		  dfs(root->left,num);
		if(root->right)
          dfs(root->right,num);
	}
}


bool leafSimilar(TreeNode* root1, TreeNode* root2)
{
	vector<int> num1,num2;
	dfs(root1,num1);
	dfs(root2,num2);
	if(num1==num2)
	  return true;
	else return false;
}

int main()
{
	char str1[100],str2[100];
	ifstream fin;
	fin.open("in.txt");
	fin.getline(str1,100);
	fin.getline(str2,100);
	Tree Tree1,Tree2;
	Tree1.CreateTree(str1);
	Tree2.CreateTree(str2);
	bool flag_out=leafSimilar(Tree1.r,Tree2.r);
    if(flag_out)
      cout<<"true";
    else
      cout<<"false";
    return 0;
}
