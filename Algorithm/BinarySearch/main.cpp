#include <iostream>
#include <assert.h>

/* brief: ���ֲ�����������
 *
 * ���: ����, �����С, ����Ŀ��ֵ
 * ����ֵ: �ҵ�, ���ظ�ֵ���ڵ�λ��; δ�ҵ�, ���� -1
 */

int BinarySearch(const int array[], int n, int target)
{
    assert(n > 1);

    int low = 0;
    int high = n-1;        // ���ҵ����鷶ΧΪ array[0]~array[n-1]

    while (low <= high)     // ���� low == high �����
    {
        int mid = low + ((high - low) >> 1);

        if (array[mid] > target)
        {
            high = mid - 1;         // Ϊʲô���� high = mid; ��ֵ����Ŀ��ֵ, ��Ŀ��ֵλ�ÿ϶��� mid ��С.
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
        return -1;          // �ݹ��������

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
