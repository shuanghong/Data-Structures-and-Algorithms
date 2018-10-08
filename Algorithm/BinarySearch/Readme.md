# 二分查找
也称折半查找, 对数查找, 是一种在有序数组中查找某一特定元素的查找算法.  
从数组的中间元素开始查找, 如果中间元素正好是要查找的元素, 则查找过程结束; 如果某一特定元素大于或者小于中间元素, 则在数组大于或小于中间元素的那一半中查找, 这种查找算法每一次比较都使查找范围缩小一半. 如下图在数组中查找 4.

![](https://i.imgur.com/eeCE94Z.png)

参考:  
[https://zh.wikipedia.org/wiki/二分搜索算法](https://zh.wikipedia.org/wiki/二分搜索算法)

## 前提条件
二分查找适用于对**有序**数组的查找

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
上面的实现是有问题的, 在极端情况下, 数组比较大时, low+high 的和有可能超出 int 类型的最大值(2147483647), 此时运算结果溢出, 导致 mid 位置的计算错误. 为了必秒溢出, mid 的计算如下:

	low + (high - low) >> 1

low + (high - low) 的最大值不会超过 high, 不会产生溢出, 并使用右移替代除法.  
进一步思考, (lo + hi)/2 有可能溢出导致最高位为1产生负数, 那么 >>> 无符号右移同样也可以避免这个问题, 因此在 Java 中, mid 的计算也可以:

	(lo + hi) >>> 1		// PS. C++ 不支持无符号右移 >>> 

### 参数有效性检查
对于数组的大小 n, 至少要保证大于 1, 即 high = n-1 > 0 或者 high>low, 确保 low/high 构成的区间是有效的.

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

### 查找第一个(floor)/最后一个等值(ceil)
