#pragma once
#pragma once

#ifndef RANDOM_H_
#define RANDOM_H_

class randomNums {
private:
	//����������ɵ�����
	int* nums;
	int n;
public:
	//���������ɵ�����
	int* getNums();

	//����һ��������ɵ�����
	void randomN();

	//���캯��
	randomNums(int nn);

	randomNums();

	//��������
	~randomNums();
};

class NumArrays {
public:
	NumArrays();
	~NumArrays();
	int** getArray(int n, int len);
private:
	//��ʶһ����������������
	int n;
	//��ʶÿһ�����ݵĳ���
	int len;

	int **array;

};

#endif // !RANDOM_H_
