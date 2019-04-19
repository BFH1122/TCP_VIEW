//#include <iostream>
//#include <string>
//
//#include <vector>
//
//using namespace std;
//
//vector<string> split(const string& str, const string& delim);
//
//bool underOrder(char *pstr, int &n, int &len);
//
//int main() {
//	char *pstr = new char[100];
//	char *d = "&";
//	cin >> pstr;
//
//	int n = -1;
//	int len = -1;
//
//	if (!(underOrder(pstr, n, len))) {
//		cout << "输入的命令存在错误" << endl;
//	}
//	else {
//		cout << "n = " << n << "  len = " << len << endl;
//	}
//	system("pause");
//	return 0;
//}
//
//bool underOrder(char *pstr, int &n, int &len) {
//	char *d = "&";
//	int i = 0;
//	char *buf[3];
//	//首先判断命令起始是否正确
//	if (strncmp(pstr, "random", strlen("random")) != 0 || pstr[strlen("random")]!='&' ) {
//		return false;
//	}
//	//正确的情况下 读出 n len 长度数值
//	char *p = strtok(pstr, d);
//	while (p) {
//		buf[i] = p;
//		i++;
//		p = strtok(NULL, d);
//	}
//	if (i != 3) {
//		return false;
//	}
//	//获得
//	n = atoi(buf[1]);
//	len = atoi(buf[2]);
//	return true;
//}
//
////string str1 = "M135buffer.buffer,|M135data.data1,4.22424|M135data.data6,-0.0714111|M135data.data7,-0.53833|M135data.data11,145.569|M135data.data16,5.0354|M135data.data17,-112.906|M135data.data21,4.34509|M135data.data22,-0.115356|M135data.data23,0|M135data.data24,-14|M135data.data25,49521|M135data.data_lng,0|M135data.data26,-14|M135data.data27,49521|M135data.data_lati,0";
////string str2 = "|This is a test!\n";
////
////string str = str1 + str2;
////
////printf(str.c_str());
////
////vector<string> AllStr = split(str, "|");
////for (int i = 0; i<AllStr.size(); i++)
////{
////	vector<string> tempStr = split(AllStr[i], ",");
////	if (tempStr.size() >= 2)
////	{
////		printf("Name:%s  Value:%s\n", tempStr[0].c_str(), tempStr[1].c_str());
////	}
////}
//
//vector<string> split(const string& str, const string& delim) {
//	vector<string> res;
//	if ("" == str) return res;
//	//先将要切割的字符串从string类型转换为char*类型  
//	char * strs = new char[str.length() + 1]; //不要忘了  
//	strcpy(strs, str.c_str());
//
//	char * d = new char[delim.length() + 1];
//	strcpy(d, delim.c_str());
//
//	char *p = strtok(strs, d);
//	while (p) {
//		string s = p; //分割得到的字符串转换为string类型  
//		res.push_back(s); //存入结果数组  
//		p = strtok(NULL, d);
//	}
//
//	return res;
//}
