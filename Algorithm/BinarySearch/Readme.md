# 二分查找
也称折半查找, 对数查找, 是一种在有序数组中查找某一特定元素的查找算法.  
从数组的中间元素开始查找, 如果中间元素正好是要查找的元素, 则查找过程结束; 如果某一特定元素大于或者小于中间元素, 则在数组大于或小于中间元素的那一半中查找, 这种查找算法每一次比较都使查找范围缩小一半. 如下图在数组中查找 4.

![](https://i.imgur.com/eeCE94Z.png)

参考:  
[https://zh.wikipedia.org/wiki/二分搜索算法](https://zh.wikipedia.org/wiki/二分搜索算法)

## 前提条件
二分查找适用于对**有序**数据的查找

## 性能
每次把查找范围减少一半, 时间复杂度为 O(logN).

## 初步实现

	int BinarySearch(const int array[], int n, int target)
	{
	    int low = 0;
	    int high = n-1;        // 查找的数组范围为 array[0]~array[n-1]
	
	    while (low <= high)		// 存在 low == high 的情况
	    {
	        int mid = (low + high)/2;
	
	        if (array[mid] > target)
	        {
	            high = mid - 1;         // 为什么不是 high = mid; 中值大于目标值, 则目标值位置肯定比 mid 小.
	        }
	        else if (array[mid] < target)
	        {
	            low = mid + 1;
	        }
	        else
	            return mid;
	    }
	    return -1;
	}


## 存在的问题

### 中值计算溢出
上面的实现是有问题的, 在极端情况下, 数组比较大时, low+high 的和有可能超出 int 类型的最大值(2147483647), 此时运算结果溢出, 导致 mid 位置的计算错误. 为了避免溢出, mid 的计算如下:

	low + (high - low) >> 1

low + (high - low) 的最大值不会超过 high, 不会产生溢出, 并使用右移替代除法.  
进一步思考, (lo + hi)/2 有可能溢出导致最高位为1产生负数, 那么 >>> 无符号右移同样也可以避免这个问题, 因此在 Java 中, mid 的计算也可以:

	(lo + hi) >>> 1		// PS. C++ 不支持无符号右移 >>> 

### 参数有效性检查
在很多查找场景下, 需要检查 low/high 参数以确保 low/high 不相等, 其构成的区间是有效的.  
对于数组的大小 n, 要大于 1, 即 high=n-1>0 或者 high>low.

## 正确实现

	int BinarySearch(const int array[], int n, int target)
	{
	    assert(n > 1);

	    int low = 0;
	    int high = n-1;        // 查找的数组范围为 array[0]~array[n-1]
	
	    while (low <= high)     // 存在 low == high 的情况
	    {
	        int mid = low + ((high - low) >> 1);
	
	        if (array[mid] > target)
	        {
	            high = mid - 1;         // 为什么不是 high = mid; 中值大于目标值, 则目标值位置肯定比 mid 还小.
	        }
	        else if (array[mid] < target)
	        {
	            low = mid + 1;
	        }
	        else
	            return mid;
	    }
	    return -1;
	}


## 关键语法
1. 初始条件: low = 0, high = n-1. 以数组实际的 index 作为最大/最小值, 查找范围是左闭右闭区间
2. 向左查找: high = mid-1, 向右查找: low = mid+1. 由于初始查找空间是左闭右闭, mid 值也是闭区间, 已经比较过了
3. 循环终止: low > high,  当 low == high 时, mid = high/low, 仍然需要将 array[mid] 与 target 比较, 否则会漏查, 比如查找数组以外的任意数时

	![](https://i.imgur.com/jqB67Py.jpg)
	![](https://i.imgur.com/xrieYRl.jpg)
	 
## 修改边界条件的实现
	int BinarySearchV2(const int array[], int n, int target)
	{
	    assert(n > 0);
	
	    int low = 0;
	    int high = n;
	
	    while (low < high)
	    {
	        int mid = low + ((high - low) >> 1);
	        printSearch(array, n, target, low, high, mid);
	
	        if (array[mid] > target)
	        {
	            high = mid;
	        }
	        else if (array[mid] < target)
	        {
	            low = mid + 1;
	        }
	        else
	            return mid;
	    }

	    if (low != n && array[low] == target)
	        return low;
	    return -1;
	}

## 关键语法
1. 初始条件: low = 0, high = n. 查找范围是左闭右开区间
2. 向右查找: low = mid+1, 向左查找: high = mid. 由于 high 是开区间, 相对于闭区间, mid 的计算结果有可能大1, 需要将 array[mid] 放入下一次比较中. 比如 {0,1,2,3,4,5,6,7}, 闭区间时 mid=3, 开区间时 mid=4
3.  循环终止: low == high. 当相等时 mid = high/low, array[mid] 有可能越界, 因为 high 是开区间, 比如查找数组以外的任意数时
	![](https://i.imgur.com/NGJGNx1.jpg)
4. 后续处理. low == high 时循环退出, array[low] 没有参与比较, 但是有可能存在 array[low]==target.
5. 当 high=n-1, while (low <= high) 时, 最后一步查找时闭区间内的所有元素都被比较了. high=n, while (low < high)时, 每一次查找空间至少有 2 个元素, 最后一步查找时区间内还剩两个元素, 比较其中一个之后 low == high 退出, 还剩下 1 个元素, 需要评估是否符合条件


## 递归方式实现
二分查找也可以采用递归方式实现, 但是递归调用存在着压栈/出栈的开销, 其效率是一般比迭代的方式低.

	int BinarySearchByRecursion(const int array[], int low, int high, int target)
	{
	    if (low > high)
	        return -1;          // 递归结束条件
	
	    int mid = low + ((high - low) >> 1);
	
	    if (array[mid] > target)
	    {
	        return BinarySearchByRecursion(array, low, mid-1, target);
	    }
	    else if (array[mid] < target)
	    {
	        return BinarySearchByRecursion(array, mid+1, high, target);
	    }
	    else
	        return mid;
	}


## 二分查找的扩展

### 查找小于或等于 target 的值, 即通常意义上的 floor() 函数实现
floor() 实现有 3 个要点:  
1. 如果找到 target, 返回第一个 target 相应的索引 index  
2. 如果没有找到 target, 返回比 target 小的最大值相应的索引, 如果这个最大值有多个, 返回最大索引
3. 如果这个 target 比整个数组的最小元素值还要小, 则不存在这个 target 的 floor 值, 返回-1

	int floor(const int array[], int n, int target)
	{
	    assert(n >= 0);

	    if (target < array[0])
	        return -1;
	
	    int low = 0;
	    int high = n - 1;

	    while (low <= high)
	    {
	        int mid = low + ((high - low) >> 1);
	
	        if (array[mid] >= target)
	        {
	            high = mid - 1;
	        }
	        else
	        {
	            low = mid + 1;
	        }
	
	    }

	    if ((low - 1 >=0) && array[low] > target )
	        return low - 1;
	
	    return low;
	}

### 关键语法
1. 初始条件: low = 0, high = n-1. 查找范围是左闭右闭区间
2. 向左查找: high = mid-1. 这里包含了相等的情况, 因为相等时仍然需要向左查找
3. 向右查找: low = mid+1. 这里为什么不是 low = mid, 因为当循环到 low、high 接近时, 如果下一次计算 mid 时, mid = (low + high)/2 向下取整, low 一直等于 mid, array[mid] < target 陷入死循环
4. 循环终止: low > high,  当循环到 low == high 时, 区间内的值都被比较过了, 返回 low 值

	![](https://i.imgur.com/9iJSabO.jpg)

5. 后续处理. 当最后一次循环low == high 时, 如果 low = mid + 1, 有可能存在 array[low] > target 的情况

	![](https://i.imgur.com/aRuyPGg.jpg)

### 查找大于或等于 target 的值, 即通常意义上的 ceil() 函数实现
