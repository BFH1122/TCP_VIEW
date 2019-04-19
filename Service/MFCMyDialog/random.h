#pragma once
#pragma once

#ifndef RANDOM_H_
#define RANDOM_H_

class randomNums {
private:
	//保存随机生成的数组
	int* nums;
	int n;
public:
	//获得随机生成的数组
	int* getNums();

	//产生一组随机生成的数组
	void randomN();

	//构造函数
	randomNums(int nn);

	randomNums();

	//析构函数
	~randomNums();
};

class NumArrays {
public:
	NumArrays();
	~NumArrays();
	int** getArray(int n, int len);
private:
	//标识一共产生多少组数据
	int n;
	//标识每一组数据的长度
	int len;

	int **array;

};

#endif // !RANDOM_H_
