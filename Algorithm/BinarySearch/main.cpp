#include <iostream>
#include <cassert>

void printSearch(const int array[], int size, int target, int low, int high, int mid)
{
    static bool flag = true;
    static int counter = 0;
    auto printArray = [](const int array[], int size, int target)
    {
        std::cout << "array: ";
        for (auto i = 0; i < size; ++i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << "  target:" << target << std::endl;
    };
    if (flag)
    {
        printArray(array, size, target);
        flag = false;
    }
    std::cout << "low:" << low << " high:" << high << " mid:" << mid
              << " array[mid]=" << array[mid] << (array[mid] >= target ? " >= " : " < ") << target
              << "  compare counter: " << ++counter
              << std::endl;
}


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
        printSearch(array, n, target, low, high, mid);

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

void testBinarySearch()
{
    int a[] = {0,1,2,3,4,5,6,7};
    int size = sizeof(a)/sizeof(int);

    int ret = BinarySearchV2(a, size, 3);
    //int ret = BinarySearchByRecursion(a, 0, size-1, i);
    if (ret != -1)
    {
        std::cout << "Search success, index: " << ret << std::endl;
    }
    else
        std::cout << "Search failed!" << std::endl;

}

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
        printSearch(array, n, target, low, high, mid);

        if (array[mid] >= target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }

    }
    std::cout << "while exit, low:" << low << " high:" << high << std::endl;
    if ((low - 1 >=0) && array[low] > target )
        return low - 1;

    return low;
}

void testFloor()
{
    int a[] = {0,1,1,2,2,2,3,3,3,3,4,4,4,6,7};
    int size = sizeof(a)/sizeof(int);

    int ret = floor(a, size, 5);
    if (ret != -1)
    {
        std::cout << "Search success, index: " << ret << std::endl;
    }
    else
        std::cout << "Search failed!" << std::endl;
}

int ceil(const int array[], int n, int target)
{
    assert(n > 1);

    int low = 0;
    int high = n;

    while (low < high)
    {
        int mid = low + ((high - low) >> 1);
        printSearch(array, n, target, low, high, mid);

        if (array[mid] <= target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    std::cout << "while exit, low:" << low << " high:" << high << std::endl;
    if ((high - 1 >= 0) && array[high-1] >= target)
        return high-1;

    return high;
}

void testCeil()
{
    int a[] = {0,1,1,2,2,2,3,3,3,3,4,4,4,6,7};
    int size = sizeof(a)/sizeof(int);

    int ret = ceil(a, size, 9);

    std::cout << "Search success, first index: " << ret << std::endl;
}

int main()
{
    //testBinarySearch();

    testFloor();

    //testCeil();

    return 0;

}
