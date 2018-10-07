# 数据结构之树(1)-树、二叉树基本概念

## 定义
树是n(n>=0)个结点的有限集. n=0时称为空树. 在任意一颗非空树中: 1) 有且仅有一个特定的称为 root 的结点, 2) n > 1时, 其余节点可分为m个互不相交的有限集 T1、T2...Tm, 每个集合又是一棵树, 并且称为根的子树.  
区别于线性表的一对一的元素关系, 树中的结点是一对多的关系, 具有如下特点:

- n > 0时, 根结点唯一, 不存在多个根结点.
- m > 0时, 子树的个数没有限制, 但子树之间一定是互不相交的.
- 每个结点有零个至多个子结点, 除根结点外每个结点有且仅有一个父结点, 根结点没有父结点.
![](http://i.imgur.com/thvGLNK.png)

### 子树

![](http://i.imgur.com/qlfKH54.png) ![](http://i.imgur.com/MqYE0ob.png)

### 树的高度

也称为树的深度, 树中结点的最大层次, 如图1中的树高为4.

### 结点分类

- 结点的度: 结点拥有的子树个数, 如图1中的A的度为2, B的度为1, C的度为2. 树的度是树内各结点的度的最大值.
- 分支结点: 度不为0的结点, 包括根结点.
- 内部结点: 除了根结点之外的分支结点.
- 叶子节点: 度为0的结点.

![](http://i.imgur.com/6GQOsS9.png)

### 结点间关系

- 孩子与双亲: 若一个结点有子树, 则子树的根是该结点的孩子, 该结点为子树根的双亲. 如图1中, B、C是A的孩子, A是B、C的双亲.
- 兄弟: 同一个双亲的孩子之间互称兄弟, 如图1中的B、C结点, E、F结点.
- 祖先/子孙: 祖先是从根到该结点所经过的分支上的所有结点, 如图1中的H的祖先是 D、B、A. 子孙是以某结点为根的子树中的任一结点, 如B的子孙有 D、G、H.

## 二叉树
二叉树或为空树, 或由一个根结点和两棵互不相交的、分别成为左子树和右子树的二叉树组成. 具有如下特点:

- 二叉树是有序树, 区分左子树和右子树, 不可以随意交换子树的位置.
- 一个节点的子树数量取值范围为0,1,2. 0 代表该节点是叶子节点; 1代表该节点只有左子树或只有右子树; 2代表该节点有左右子树.

![](http://i.imgur.com/wwIlIeT.png)

### 斜树
所有节点都只有左子树的二叉树叫做左斜树, 所有节点都只有右子树的二叉树叫做右斜树.  
斜树已经退化成线性结构, 二叉树在查找上表现出来优异性能在斜树得不到体现.

### 满二叉树
所有的节点都同时具有左子树和右子树, 所有的叶子节点都在同一层上. 在同样深度的二叉树中, 满二叉树的节点数目是最多的, 叶子数也是最多的.

### 完全二叉树
对一棵具有n个节点的二叉树按层序从左到右编序, 二叉树所有节点的编序与同样位置的满二叉树节点的编序相同, 则二叉树为完全二叉树.  
满二叉树一定是完全二叉树, 完全二叉树不一定是满二叉树.

### 二叉查找树
二叉查找树也称为二叉搜索树或二叉排序树, 二叉查找树的节点包含键值key, 二叉查找树或为一棵空树, 否则要求:

- 若它的左子树不为空, 那么左子树上所有节点的key都小于根节点的key.
- 若它的右子树不为空, 那么右子树上所有节点的key都大于根节点的key.
- 它的左右子树也分别为二叉查找树.

所以二叉查找树中没有重复key的节点.

![](http://i.imgur.com/TiW5k0k.png)

## 二叉树的性质

- 性质一：二叉树的第 i 层上至多有 2^(i-1) 个节点(i>=1)
- 性质二：深度为 k 的二叉树至多有 2^k-1 个节点
- 性质三：具有n个节点的完全二叉树的高度为至少为 log2(n+1)

	参考 [http://www.cnblogs.com/QG-whz/p/5168620.html](http://www.cnblogs.com/QG-whz/p/5168620.html)



## 二叉树的实现

### 结点存储结构
树的存储形式包括顺序存储（采用数组形式）和链式存储, 其中链式存储更为灵活, 可以表示任意形式的树.

	struct Node
	{
	    Node() = default;
	    Node(DataType key)
	    : m_key(key), pLeft(nullptr), pRight(nullptr), nMaxLeft(0u), nMaxRight(0)
	    {
	    }
	
	    DataType m_key;     // 节点的值
	    Node *pLeft;       // 指向节点的左孩子
	    Node *pRight;       // 指向节点的右孩子
	
	    LengthType nMaxLeft;    // 左子树的最长距离
	    LengthType nMaxRight;   // 右子树的最长距离
	};

### 构建二叉树

	/*brief: 构造二叉树, 采用自上而下、从左到右的顺序构造, 遇到-1或者'#'表示空结点.
	 *       实现分两步, 第一步为每个结点分配存储空间, 第二步将不为空的结点串联起来.
	 */

	Node* BinaryTree::buildTreeByLayer(std::vector<DataType> &nodes)
	{
	    int nodesize = nodes.size();
	    Node **treenode = new Node *[nodesize];
	    for (int i = 0; i < nodesize; ++i)
	    {
	        if (nodes[i] == '#' || nodes[i] == -1)
	            treenode[i] = nullptr;
	        else
	            treenode[i] = new Node(nodes[i]);
	    }
	    //i 索引当前结点, j 索引左结点和右结点
	    for (int i=0, j=0; i<nodesize && j<nodesize; i++)
	    {
	        //如果每个结点均有效,则每i次循环j移动两个位置,
	        //如{1,2,3,4,5},1的左右结点是2,3; 2的左右结点是4,5
	        if (treenode[i] != nullptr)
	        {
	            if ((j + 1) < nodesize)
	            {
	                j += 1;
	                treenode[i]->pLeft = treenode[j];//pLeft可能为空, 如{1,-1...}
	            }
	            if ((j + 1) < nodesize)
	            {
	                j += 1;
	                treenode[i]->pRight = treenode[j];
	            }
	        }
	        //如果结点为空,要看空结点的位置, 二叉树结点最多有两个,分奇偶位置,根节点、左结点、右结点、左结点...
	        //i为奇数,如{1,-1,3,4,5}, 空结点为左结点,其后面的右结点3的左右结点是4,5. j不变; 再如{1,-1,3,-1,5,6}
	        //i为偶数,{1,2,-1,4,5,6,7},空结点为右结点, 其前面的左结点4的左右结点是6，7. j仍不变
	        else
	        {
	        }
	    }
	    return *treenode;
	}

### 打印二叉树

	/*brief: 打印二叉树, 参考二叉树的层次遍历
	 *       1. 首先把二叉树根结点存入队列
	 *       2. 队首结点出队列并打印之, 再把它的左右子结点分别存入队列
	 *       3. 重复上面操作, 直至队列为空
	 */
	void BinaryTree::showTree(Node *root)
	{
	    if (root == nullptr)
	        return;

	    std::queue<Node*> tree_queue;
	    tree_queue.push(root);
	    while(!tree_queue.empty())
	    {
	        Node *current_node = tree_queue.front();
	        printf("current node is: %d\n",current_node->m_key);
	        fflush(stdout);
	        tree_queue.pop();
	        if (current_node->pLeft != nullptr)
	        {
	            printf("left node is: %d\n", current_node->pLeft->m_key);
	            tree_queue.push(current_node->pLeft);
	        }
	        if (current_node->pRight != nullptr)
	        {
	            printf("right node is: %d\n", current_node->pRight->m_key);
	            tree_queue.push(current_node->pRight);
	        }
	    }
	}

## 二叉树中节点的最大距离问题

### 问题定义
把二叉树看成一个图, 父子节点之间的连线看成是双向的, 定义“距离”为两个节点之间边的个数, 如图4中的结点最大距离为 4.

### 问题分析
二叉树中节点的最大距离必定是两个叶子节点的距离, 有两种情况:
- CaseA: 路径经过根节点, 两个叶子节点分别在左子树和右子树
- CaseB: 路径不经过节结点, 两个叶子节点都在左子树或者都在右子树

### 解法一: 《编程之美》 3.8节

	void BinaryTree::findMaxLen(Node* pRoot)
	{
	    // 递归遍历到叶子节点, 或者是空树.
	    if(pRoot == nullptr)
	    {
	        std::cout <<  __func__ << "() " << "root is null!" << std::endl;
	        return;
	    }
	    // 如果左子树为空，那么该节点的左边最长距离为0
	    if(pRoot -> pLeft == nullptr)
	    {
	        pRoot -> nMaxLeft = 0;
	    }
	    // 如果右子树为空，那么该节点的右边最长距离为0
	    if(pRoot -> pRight == nullptr)
	    {
	        pRoot -> nMaxRight = 0;
	    }
	
	    // 如果左子树不为空，递归寻找左子树最长距离
	    if(pRoot -> pLeft != nullptr)
	    {
	        findMaxLen(pRoot -> pLeft);
	    }
	
	    // 如果右子树不为空，递归寻找右子树最长距离
	    if(pRoot -> pRight != nullptr)
	    {
	        findMaxLen(pRoot -> pRight);
	    }
	
	    // 计算左子树最长节点距离
	    if(pRoot -> pLeft != nullptr)
	    {
	        int nTempMax = 0;
	        if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight)
	        {
	            nTempMax = pRoot -> pLeft -> nMaxLeft;
	        }
	        else
	        {
	            nTempMax = pRoot -> pLeft -> nMaxRight;
	        }
	        pRoot -> nMaxLeft = nTempMax + 1;
	    }
	
	    // 计算右子树最长节点距离
	    if(pRoot -> pRight != nullptr)
	    {
	        int nTempMax = 0;
	        if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight)
	        {
	            nTempMax = pRoot -> pRight -> nMaxLeft;
	        }
	        else
	        {
	            nTempMax = pRoot -> pRight -> nMaxRight;
	        }
	        pRoot -> nMaxRight = nTempMax + 1;
	    }
	
	    // 更新最长距离
	    if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen)
	    {
	        nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
	    }
	}

### 另外一种更优的解法
- CaseA 需要子树最远的叶子节点到根节点的距离, 就是子树的高度减1
- CaseB 需要子树内部两叶子节点之间的距离.

		int BinaryTree::findMaxLenBetter(Node *pRoot)
		{
		    if(pRoot == nullptr)
		        return 0;
		
			int lmax = findMaxLenBetter(pRoot->pLeft); // 左子树中的最大距离
			int rmax = findMaxLenBetter(pRoot->pRight); // 右子树中的最大距离
		
			int lh = 0, rh = 0;
			if(pRoot->pLeft != nullptr)
		    {
				lh = height(pRoot->pLeft);       // 左子树最远的叶子节点与根节点的距离
			}
			if(pRoot->pRight != nullptr)
		    {
				rh = height(pRoot->pRight);      // 右子树最远的叶子节点与根节点的距离
			}
			return std::max(std::max(lmax, rmax), lh + rh);
		}
		
		// 计算树的高度
		int BinaryTree::height(Node *pRoot)
		{
		    if(pRoot == nullptr)
		        return 0;
		
		    return std::max(height(pRoot->pLeft), height(pRoot->pRight)) + 1;
		}

时序图:
	
![](http://i.imgur.com/p8Jv4e7.png)

参考:  
[http://www.cnblogs.com/miloyip/archive/2010/02/25/binary_tree_distance.html](http://www.cnblogs.com/miloyip/archive/2010/02/25/binary_tree_distance.html)
[https://github.com/luofengmacheng/algorithms/blob/master/bop/3.8.md](https://github.com/luofengmacheng/algorithms/blob/master/bop/3.8.md)
[https://github.com/liangsonghua/algorithm/blob/master/5.6%20%E4%BA%8C%E5%8F%89%E6%A0%91_%E6%A0%91%E4%B8%8A%E6%9C%80%E8%BF%9C%E8%B7%9D%E7%A6%BB.cpp](https://github.com/liangsonghua/algorithm/blob/master/5.6%20%E4%BA%8C%E5%8F%89%E6%A0%91_%E6%A0%91%E4%B8%8A%E6%9C%80%E8%BF%9C%E8%B7%9D%E7%A6%BB.cpp)
