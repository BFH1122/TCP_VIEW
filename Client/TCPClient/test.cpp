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
//		cout << "�����������ڴ���" << endl;
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
//	//�����ж�������ʼ�Ƿ���ȷ
//	if (strncmp(pstr, "random", strlen("random")) != 0 || pstr[strlen("random")]!='&' ) {
//		return false;
//	}
//	//��ȷ������� ���� n len ������ֵ
//	char *p = strtok(pstr, d);
//	while (p) {
//		buf[i] = p;
//		i++;
//		p = strtok(NULL, d);
//	}
//	if (i != 3) {
//		return false;
//	}
//	//���
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
//	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����  
//	char * strs = new char[str.length() + 1]; //��Ҫ����  
//	strcpy(strs, str.c_str());
//
//	char * d = new char[delim.length() + 1];
//	strcpy(d, delim.c_str());
//
//	char *p = strtok(strs, d);
//	while (p) {
//		string s = p; //�ָ�õ����ַ���ת��Ϊstring����  
//		res.push_back(s); //����������  
//		p = strtok(NULL, d);
//	}
//
//	return res;
//}
