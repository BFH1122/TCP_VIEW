
#include <iostream>
#include "random.h"
#include<cstdlib>
#include<ctime>


//类的具体实现
int* randomNums::getNums() {
	return nums;
}

//产生随机数的函数
void randomNums::randomN() {
	//随机种子

	nums = new int[n];
	for (int i = 0; i < n; i++) {
		nums[i] = rand() % 20 - 10;
	}
}

randomNums::randomNums() {

}
//构造函数
randomNums::randomNums(int nn) {
	n = nn;
	srand((unsigned)time(NULL));
}

//析构函数
randomNums::~randomNums() {
	//delete nums;
	//不在此处释放数组空间
}





//---------------------------------------
//构造函数
NumArrays::NumArrays() {

}
NumArrays::~NumArrays() {
	for (int i = 0; i < n; i++) {
		delete array[i];
	}
}

int** NumArrays::getArray(int n, int len) {
	array = new int*[n];
	randomNums *num = new randomNums(len);
	for (int i = 0; i < n; i++) {
		(*num).randomN();
		array[i] = (*num).getNums();
	}
	return array;
}


