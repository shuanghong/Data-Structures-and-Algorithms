#include <iostream>
#include <algorithm>
#include <ctime>

/************************************
* 参考 https://www.cnblogs.com/lz3018/p/5742255.html
* 1. 在数组中选择第一个元素作为 “枢纽”(pivot), 设置两个游标 low 和 high. 初始时 low 指向首元素, high 指向尾元素
* 2. 从右向左扫描, 遇到小于枢纽值的元素停止扫描, 将 low, high 交换
* 3. 从左向右开始扫描, 遇到大于基准值的元素停止扫描, 同样将 low, high 交换
* 4. low == high 时分割完成
*************************************/

int partition(int array[], int low, int high)
{
    int pivotKey = array[low];   // 取数组第一个元素作为枢纽值

    while (low < high)
    {
        while (array[high] >= pivotKey && low < high)
        {
            high--;             // high 往左移, 直到找到第一个小于 pivotKey 的值
        }
        std::swap(array[low], array[high]);  // 将比枢纽值小的值交换到低端

        while(array[low] <= pivotKey && low < high)
        {
            low++;              // high 往右移, 直到找到第一个大于 pivotKey 的值
        }
        std::swap(array[low], array[high]);  // 将比枢纽值大的值交换到高端
    }

    std::cout << "pivot index: " << low << std::endl;
    return low;                 // 返回枢纽所在位置
}

void qSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(array, low, high);
        qSort(array, low, pivot-1);
        qSort(array, pivot+1, high);
    }
}

void quickSort(int array[], int n)
{
    qSort(array, 0, n-1);
}

int main(int argc, char *argv[])
{
    int array1[9] = {50, 10, 90, 30, 70, 40, 80, 60, 20};

    quickSort(array1, 9);

    for (auto &i : array1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int array2[10] = {35, 45, 25, 55, 15, 60, 20, 70, 10, 35};

    quickSort(array2, 10);

    for (auto &i : array2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Generate radom array: " << std::endl;
    const int MAX_NUMBER = 100;
    int array3[MAX_NUMBER] = {0};
    srand(time(NULL));
    
    for(int i = 0; i < MAX_NUMBER; ++i)
    {
        array3[i] = rand() % 100;
        std::cout << array3[i] << " ";
    }
    std::cout << std::endl;

    quickSort(array3, MAX_NUMBER);
    for (auto &i : array3)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}