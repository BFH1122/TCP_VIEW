
#include <iostream>
#include "random.h"
#include<cstdlib>
#include<ctime>


//��ľ���ʵ��
int* randomNums::getNums() {
	return nums;
}

//����������ĺ���
void randomNums::randomN() {
	//�������

	nums = new int[n];
	for (int i = 0; i < n; i++) {
		nums[i] = rand() % 20 - 10;
	}
}

randomNums::randomNums() {

}
//���캯��
randomNums::randomNums(int nn) {
	n = nn;
	srand((unsigned)time(NULL));
}

//��������
randomNums::~randomNums() {
	//delete nums;
	//���ڴ˴��ͷ�����ռ�
}





//---------------------------------------
//���캯��
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


