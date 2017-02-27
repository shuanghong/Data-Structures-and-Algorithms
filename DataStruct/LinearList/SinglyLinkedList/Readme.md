# 数据结构之线性表(2)-单链表

## 单链表
一个线性表的链式存储结构中, 每个结点只包含一个指针域, 这种线性表为单链表.

## 结点结构
![](http://i.imgur.com/VbeZ0eI.png)

## 结点代码描述

    using DataType = uint32_t;

	struct Node
	{
    	DataType data;
    	Node *next;
	};

## 单链表的实现

### 定义

	using Listlength = uint32_t;
    class SinglyLinkedList
	{
	public:
	    SinglyLinkedList();
	    ~SinglyLinkedList();
	
	    Node* createNode(const DataType value);
	    Node* getNodeAtPosition(const Listlength position) const;
	    Node* getNodeValue(const DataType value) const;
	
	    bool insertNodeAtPosition(const DataType value, const Listlength position);
	    bool insertNodeAtHead(const DataType value);
	    bool insertNodeAtEnd(const DataType value);
	
	    bool removeNode(const Listlength position);
	
	    bool isListEmpty() const;
	    void printfList() const;
	    void clearList();
	
	    Listlength getListLength() const;
	
	private:
	    Listlength m_length;
	    Node *m_head;
	};


### 关于头指针和头结点

如图:

![](http://i.imgur.com/3Vc7WVl.jpg)
![](http://i.imgur.com/IZNyHwF.jpg)

##### 头指针
- 在线性表的链式存储中, 头指针是指链表指向第一个结点的指针. 若链表有头结点, 则头指针指向链表头结点; 若链表没有头结点, 则指向第一个结点.
- 无论链表是否为空, 头指针均不为空, 头指针是链表的必要元素.
- 头指针具有标识作用, 故常用头指针冠以链表的名字.

##### 头结点
- 头结点是为了操作的统一与方便而设立的, 为了所有结点的插入删除操作统一.

	加了头结点之后, 在第一个结点位置插入或者删除第一个结点时, 操作 head->next 指针. 头指针 head 不用变, 插入删除其他结点也是操作 next 指针.	若没有头结点, 插入或者删除第一个结点时需要修改头指针指向, 与操作其他结点行为不统一.
	
- 无论链表是否为空, 其头指针都是指向头结点的非空指针(空表中头结点的指针域为空), 因此空表和非空表的处理也就统一了
- 头结点不是链表所必需的.



### 基本操作及时间复杂度
- 查找 O(n): 最坏情况需要遍历所有结点
- 插入: 
	1. 头插入: O(1). 已知头指针和头结点, 只需修改 head->next 的指向.
    2. 尾插入: 链表本身的插入是 O(1).
  		- O(1): 已经尾结点的情况.
  		- O(n): 尾结点未知, 需要先找到尾结点的位置.
    3. 中间插入: O(n). Search Time + O(1).
- 删除: O(n): 与插入类似, 需要先确定被删结点的位置, 再删除.
	
