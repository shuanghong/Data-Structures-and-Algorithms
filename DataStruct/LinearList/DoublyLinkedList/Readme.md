# 数据结构之线性表(3)-双向链表

## 双向链表
单链表中, 访问任一结点的后继结点直接通过 next 指针完成(O(1)), 但是访问其前驱结点, 则必须从表头结点遍历查找(O(n)). 在结点结构中多加一个指针域, 指向前驱结点, 这种链表即为双向链表. 

## 结点结构
![](http://i.imgur.com/bZMTb8N.png)

## 结点代码描述

    using DataType = uint32_t;
	struct Node
	{
    	DataType data;
    	Node *prior;
    	Node *next;
	};

## 双向链表的实现

### 定义

	using Listlength = uint32_t;
    class DoublyLinkedList
	{
	public:
	    DoublyLinkedList();
	    DoublyLinkedList(Listlength length);
	    ~DoublyLinkedList();
	
	    Node* createNode(const DataType value);
	    Node* getNodeAtPosition(const Listlength position) const;
	    Node* getNodeValue(const DataType value) const;
	
	    bool insertNodeAtPosition(const DataType value, const Listlength position);
	    bool insertNodeAtHead(const DataType value);
	    bool insertNodeAtEnd(const DataType value);
	
	    bool removeNodeAtPosition(const Listlength position);
	    bool removeNodeValue(const DataType value);
	
	    bool isListEmpty() const;
	    void printfList() const;
	    void clearList();
	
	    Listlength getListLength() const;
	
	private:
	    Listlength m_length;
	    Node *m_head;
	};

### 基本操作

#### 插入结点
![](http://i.imgur.com/fHhSUSP.png)

	s->prior = p;			// ① 新结点 s 的前驱
	s->next = p->next;		// ② 新结点 s 的后继
	p->next->prior = s;		// ③ 后结点的前驱
	p->next = s;				// ④ 前结点的后继
	
#### 删除结点
![](http://i.imgur.com/gZSZDXJ.png)

	p->prior->next = p->next;		// ① 前结点的后继改为后结点
	p->next->prior = p->prior;		// ② 后结点的前驱改为前结点


### 时间复杂度(对比单链表)

双向链表增加了空间需求, 对于一些如计算表长, 获取元素位置和查找元素等只涉及一个方向的指针操作, 与单链表的操作相同, 但是对于插入删除操作来说比起单链表就有较大差异. 双链表提高了单链表的倒序遍历效率.

- 查找 O(n): 最坏情况需要遍历所有结点
- 插入: 
	1. 头插入: O(1). 已知头指针和头结点, 只需修改 头结点->next 和 新结点-> prior.
    2. 尾插入: 链表本身的插入是 O(1).
  		- O(1): 已经尾结点的情况.
  		- O(n): 尾结点未知, 需要先找到尾结点的位置.
    3. 中间插入: O(n). Search Time + O(1).
- 删除: O(n): 与插入类似, 需要先确定被删结点的位置, 再删除.