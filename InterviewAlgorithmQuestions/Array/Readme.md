# 面试中数组相关的算法题总结

## 循环左移/右移
将一个含有 N 个元素的数组循环左移/右移 K位. 例如: abcd12345 循环左移4位(相当于右移5位)，得到 12345abcd.   
- 原始解法1:

	// 左移 4 位
	void leftShift(char *a, int length, int shiftbits)
	{
	    while (shiftbits--)
	    {
	        char temp = a[0];
	        for (int i=0; i<length-1; ++i)
	        {
	            a[i] = a[i+1];
	        }
	        a[length-1] = temp;
	    }
	}
	
	int main(int argc, char *argv[])
	{
	    char a[9] = {'a', 'b', 'c', 'd', '1', '2', '3', '4', '5'};    
	    leftShift(a, 9, 4);    
	    for (int i = 0; i < 9; ++i)
	        printf("a[%d] = %c\n", i, a[i]);       
	    return 0;
	}

	// 右移5位
	void rightShift(char *a, int length, int shiftbits)
	{
	    while (shiftbits--)
	    {
	        char temp = a[length-1];
	        for (int i=length-1; i>0; --i)
	        {
	            a[i] = a[i-1];
	        }
	        a[0] = temp;
	    }
	}
此解法需要把整个数组移动 K 次, 时间复杂度为 O(K*N); 注意: K 有可能是一个远大于 N 的整数.  
-  优解2: 元素在移动 N 次之后都会回到自己的位置上, 如果 K > N, 那么右移K位之后的情形, 跟右移 K’=K%N 位之后的情形一样.

	void rightShift(char *a, int length, int shiftbits)
	{
	    shiftbits = shiftbits%length;
	    while (shiftbits--)
	    {
	        char temp = a[length-1];
	        for (int i=length-1; i>0; --i)
	        {
	            a[i] = a[i-1];
	        }
	        a[0] = temp;
	    }
	}
算法复杂度降为O(N^2), 和 K 无关.  
- 优解3: 把字符串看成有两段组成的，记位XY. 左旋转相当于要把字符串XY变成YX. 我们先在字符串上定义一种翻转的操作, 就是翻转字符串中字符的先后顺序. 把X翻转后记为XT. 显然有(XT)T=X.  
首先对X和Y两段分别进行翻转操作, 这样就能得到XTYT. 接着再对XTYT进行翻转操作, 得到(XTYT)T=(YT)T(XT)T=YX. 正好是期待的结果.  

对原数组 abcd12345, 循环右移5位变换成的数组为 12345abcd. 比较之后能看出, 其中有两段的顺序是不变的: 12345 和 abcd, 可把这两段看成两个整体, 右移K位的过程就是把数组的两部分前 N-K 和 后 K 位交换一下,  变换的过程通过一下步骤完成:  
1, 逆序排列前 N-K位 abcd: abcd12345--->dcba12345;  
2, 逆序排列后K位 12345: dcba12345--->dcba54321;  
3, 全部逆序: dcba54321--->12345abcd.
可以在线性时间内实现右移操作.

	void reverse(char *a, int begin, int end)      //逆序排列  
	{  
	    for (; begin < end; begin++, end--)    //从数组的前、后一起遍历  
	    {  
	        int temp = a[end];  
	        a[end] = a[begin];  
	        a[begin] = temp;  
	    }  
	}
	
	void rightShift(char *a, int length, int shiftbits)
	{
	    shiftbits = shiftbits%length;
	    reverse(a, 0, length-shiftbits-1);     		//前面N-K部分逆序  
	    reverse(a, length-shiftbits, length-1);     //后面K部分逆序  
	    reverse(a, 0, length-1);       				//全部逆序
	}
	
	int main(int argc, char *argv[])
	{
	    char a[9] = {'a', 'b', 'c', 'd', '1', '2', '3', '4', '5'};	    
	    rightShift(a, 9, 14);    
	    for (int i = 0; i < 9; ++i)
	        printf("a[%d] = %c\n", i, a[i]);        
	    return 0;
	}

如果是左移 K位, 则变换的过程如下:  
1, 逆序排列前 K位 abcd: abcd12345--->dcba12345;  
2, 逆序排列后 N-K位 12345: dcba12345--->dcba54321;  
3, 全部逆序: dcba54321--->12345abcd.
