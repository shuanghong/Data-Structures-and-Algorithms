#include "Array.hpp"


int main(int argc, char* argv[])
{
    myArray<int, 3> array1; // 调用默认构造函数, 元素执行默认初始化, 值为随机值.

    std::cout << "array1 value:" << std::endl
              << "array1[0]=" << array1[0] << std::endl
              << "array1[1]=" << array1[1] << std::endl
              << "array1[2]=" << array1[2] << std::endl
              << std::endl;

// array[2], array[3]均调用myArray(std::initializer_list<T> list)
// 注意 array[3] 不是赋值， 而是使用列表初始化
    myArray<int, 3> array2{1, 2, 3}; 
    std::cout << "array2 value:" << std::endl
              << "array2[0]=" << array2[0] << std::endl
              << "array2[1]=" << array2[1] << std::endl
              << "array2[2]=" << array2[2] << std::endl
              << std::endl;

    myArray<int, 3> array3 = {4, 5, 6};
    std::cout << "array3 value:" << std::endl
              << "array3[0]=" << array3[0] << std::endl
              << "array3[1]=" << array3[1] << std::endl
              << "array3[2]=" << array3[2] << std::endl
              << std::endl;


// array3_copy 调用拷贝构造函数，两种形式相同
    myArray<int, 3> array3_copy = array3; // myArray<int, 3> array3_copy(array3);
    std::cout << "array3_copy value:" << std::endl
              << "array3_copy[0]=" << array3_copy[0] << std::endl
              << "array3_copy[1]=" << array3_copy[1] << std::endl
              << "array3_copy[2]=" << array3_copy[2] << std::endl
              << std::endl;
    
    array1 = array3; // 调用拷贝赋值
    std::cout << "after assignment " << "array1 value:" << std::endl
              << "array1[0]=" << array1[0] << std::endl
              << "array1[1]=" << array1[1] << std::endl
              << "array1[2]=" << array1[2] << std::endl
              << std::endl;


// array4 调用移动构造函数，两种形式相同
    myArray<int, 3> array4 = std::move(array3); // array4(std::move(array3));

/* 源对象资源已被接管, 不能访问
    std::cout << "after move, array3[] value:" 
              << array3[0]<< array3[1] << array3[2] << std::endl;
*/
    std::cout << "array4 value:" << std::endl
              << "array4[0]=" << array4[0] << std::endl
              << "array4[1]=" << array4[1] << std::endl
              << "array4[2]=" << array4[2] << std::endl
              << std::endl;

    myArray<int, 3> array4_move; 
    array4_move = std::move(array4); // 调用移动赋值
    std::cout << "array4_move value:" << std::endl
              << "array4_move[0]=" << array4_move[0] << std::endl
              << "array4_move[1]=" << array4_move[1] << std::endl
              << "array4_move[2]=" << array4_move[2] << std::endl
              << std::endl;

    try
    {
        auto temp = array1.at(3);
    }
    catch (const std::out_of_range except)
    {
        std::cout << except.what() << std::endl;
    }

    std::cout << "array1 front: " << array1.front() << std::endl
              << "array1 back: " << array1.back() << std::endl;

    myArray<int, 0> empty_numbers;
    std::cout << "empty_numbers size is: " << empty_numbers.size() << ", "
              << "empty is: " << (empty_numbers.empty()? "true" : "false")
              << std::endl; 

    return 0;
}
