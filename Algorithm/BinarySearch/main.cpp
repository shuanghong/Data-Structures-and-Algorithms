#include <iostream>
#include <assert.h>

/* brief: 二分查找有序数组
 *
 * 入参: 数组, 数组大小, 查找目标值
 * 返回值: 找到, 返回该值所在的位置; 未找到, 返回 -1
 */

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


int main()
{
    int a[] = {0,1,2,5,5,6,6,7,8,9,11,12};

    //int ret = BinarySearch(a, sizeof(a)/sizeof(int), 5);
    int ret = BinarySearchByRecursion(a, 0, sizeof(a)/sizeof(int) - 1, 5);

    if (ret != -1)
    {
        std::cout << "Search success, index: " << ret << " value: "<< a[ret] << std::endl;
    }
    else
        std::cout << "Search failed!" << std::endl;

    return 0;
}
