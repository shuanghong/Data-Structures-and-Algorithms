# 数据结构之队列
队列是日常生活中常见的一种现象, 如排队买票、进站、上车等, 打印机处理作业. 再比如当我们拨打运营商的客服电话时, 在所有客服人员都占线的情况下, 将所有拨打电话的客户进行排队处理, 直到有个客服人员空下来, 才让最先等待的客户接通电话.

## 定义
队列是一种特殊的(操作受限)的线性表, 只允许在一端(队尾)进行插入操作, 而在另一端(队首)进行删除操作, 即它是一种先进先出(FIFO)的线性表.

![](http://i.imgur.com/ciwnfDO.jpg)

## 特点
* 队列中的元素遵循先进先出的原则, 简称 FIFO 结构.
* 在队尾添加元素(入队), 在对头删除元素(出队).

## 实现

### 存储结构
线性表有顺序存储和链式存储, 队列作为一种特殊的线性表, 也同样有这两种存储方式.

![](http://i.imgur.com/mPR1IJ7.jpg)

### 基于链表的队列实现
顾名思义, 用链表来表示队列. 队列的结点结构和单链表一样, 只不过队列的插入和删除操作分别在队尾和对头进行, 因此除了设置头指针外还要设置尾指针指向队尾, 方便从队尾插入元素.  
如下图所示, 队首指针始终指向队列链表的头结点, 队尾指针指向当前队列的尾节点, 当队列为空时, 首指针和尾指针均指向空队列的头结点.

![](http://i.imgur.com/N3yxmUR.jpg)


### 结点结构
    using DataType = uint32_t;
	struct LinkNode
	{
    	DataType data;
    	Node *next;
	};

### 队列类

	class LinkQueue: public Queue
	{
	
	public:
	    LinkQueue();    
	    LinkQueue(const LinkQueue&) = delete;
	    LinkQueue& operator=(const LinkQueue&) = delete;
	    LinkQueue(LinkQueue&&) = delete;
	    LinkQueue& operator=(LinkQueue&&) = delete;
	    ~LinkQueue();
	
	    virtual void push(DataType data) override; 
	    virtual void pop() override; 
	
	    virtual DataType front() const override; 
	    virtual DataType back() const override; 
	
	    virtual Listlength size() override; 
	    virtual bool isEmpty() override; 
	}

### 主要操作
* 入队(push)
	
	过程如下图, 只需要改变队尾指针的 next 指向.

		Node *newnode = new Node(data);
	    m_rear->next = newnode;
    	m_rear = newnode;

	![](http://i.imgur.com/Gt65B87.jpg)

* 出队(pop)

	过程如下图, 改变队头指针的 next 指向, 如果出队的是最后一个结点, 更新队尾指针 rear 指向头结点.

		Node *removed_node = m_head->next;
		m_head->next = m_head->next->next;
	    if (removed_node->next == nullptr)
        	m_rear = m_head;
    	delete removed_node;

	![](http://i.imgur.com/1ax9cRT.jpg)


### 性能分析
- 基于单链表实现的 queue, push/pop、front/back 时间复杂度均为 O(1).

## 应用举例


## 相关问题及算法