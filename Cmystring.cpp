#include<iostream>
using namespace std;
class CMyString
{
public:
	CMyString(const char*p = nullptr)
	{
		//�����ַ���Ҫ��������,Ҫ�ǵô�����ַ��������Ρ�Ϊ�˺��洦��ķ��㣬����Կ��ַ�����Ϊ��/0����
		if (p != nullptr)
		{
			mptr = new char[strlen(p) + 1];
			strcpy(mptr, p);
		}
		else
		{
			mptr = new char[1];
			*mptr = 0;
		}
	}
	~CMyString()
	{
		delete[]mptr;
		mptr = nullptr;
	}
	CMyString(const CMyString &str)//��ֹ����ǳ����
	{
		//mptr = new char[str.length() + 1];//������Ҫ�ýӿ���ӿ�֮�������ϵ
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
	}
	CMyString(CMyString &&str)//����ֵ���õĿ������캯��������������ʱ����
	{
		mptr = str.mptr;
		str.mptr = nullptr;
	}
	CMyString& operator=(const CMyString &str)
	{
		if (this == &str)  return *this;
		mptr = new char[strlen(str.mptr) - 1];
		strcpy(mptr, str.mptr);
		return *this;
	}
	CMyString& operator=(CMyString &&str)
	{
		if (this == &str)  return *this;
		delete[]mptr;
		mptr = str.mptr;
		str.mptr = nullptr;
		return *this;
	}

	bool operator>(const CMyString &str)const//���ڶ���Ĳ�����ֻ����д     �ĺ�������ö���ɳ�����
	{
		return strcmp(mptr, str.mptr) > 0;

	}
	bool operator<(const CMyString &str)const
	{
		return strcmp(mptr, str.mptr) < 0;
	}

	bool operator==(const CMyString &str)const
	{
		return  0 == strcmp(mptr, str.mptr);
	}
	int length()const
	{
		return strlen(mptr);
	}
	char& operator[](int index)
	{
		return mptr[index];
	}
	const char* c_str()const
	{
		return mptr;
	}
	friend CMyString operator+(const CMyString &, const CMyString &);
	friend ostream & operator<<(ostream &out, const CMyString &str);
	    // CMyString::iterator
		// ʵ��CMyString�����ĵ�����
class iterator//��������Ϊ������Ƕ������ڡ�
	{
		// iterator()  operator!=   operator++() operator*
	public:
		iterator(char *p=nullptr)
		{
			_ptr = p;
		}
		bool operator!= (const iterator& it)
		{
			return _ptr != it._ptr;
		}
		void operator++()
		{
			_ptr++;
		}
		char& operator*()
		{
			return *_ptr;
		}
		//����д��const����    char tmp = *it ,  *it = 'a';
		//����д�ĵ������ײ�ľ��������±����ָ������������
	private:
		//int mindex;
		char *_ptr;
	};
	iterator begin()
	{
		return iterator(mptr);
	}
	iterator end()
	{	
		return iterator(mptr+strlen(mptr));
	}
private:
	char *mptr;
};
 
ostream & operator<<(ostream &out, const CMyString &str)
{
	out << str.mptr;
	return out;
}
CMyString operator+(const CMyString &l, const CMyString &r)
{
	int length = l.length() + r.length();
	char* p = new char[length + 1];
	strcpy(p, l.mptr);
	strcat(p, r.mptr);
	CMyString tmp;
	tmp.mptr = p;
	return tmp;
}
// char *p = "dddd" char arr[]="4444";
int main()
{
	CMyString str1; // string()
	CMyString str2 = "aaa"; // string(const char*p = nullptr)
	CMyString str3 = "bbb";
	CMyString str4 = str2 + str3;//tmp���ô���ֵ���õĿ�������һ����ʱ������ʱ������ô���ֵ���õĿ�������str4
	CMyString str5 = str2 + "ccc";//��ֱ�ӱ��Ż���  tmp���ô���ֵ���õĿ������� ����str4������
	CMyString str6 = "ddd" + str3;//str2=str3+str4   tmp���ô���ֵ���õĿ�������һ����ʱ������ʱ�����ٵ��ô���ֵ���õĸ�ֵ���غ�������str4
/*
	str6 = str2 + "eee" ;
	cout << str6 << endl ;

	if (str2 > str3)
	{
		cout << "str2 > str3" << endl;
	}

	int size1 = str2.length();
	int size2 = str3.length();

	for (int i = 0; i < str6.length(); ++i)
	{
		// char& operator[](int index)
		// str6[i] = 'a';
		cout << str6[i] << " ";
	}
	cout << endl;

	// string str = "elwiyuiyw7386529"    char* => string
	char *pbuf = new char[str6.length() + 1];
	strcpy(pbuf, str6.c_str()); // c_str()  const char*
	cout << pbuf << endl;
*/
	CMyString str = "hello world";
	CMyString::iterator it = str.begin();
	//auto it = str.begin();//auto���Զ����ݵȺ��ұߵ�������ƥ��
	for (; it != str.end(); ++it)//�������Ӽ�(Ҳ��������ļӼ�)��д��ǰ�üӼӣ�����Ч�ʻ��һ�㡣
	{
		cout << *it << " ";
	}
	cout << endl;
	//c++11��׼ �ṩ��foreach ����������(�ײ�Ҳ����ͨ����������ʵ�ֵ�)
	/*for (int inx : str)
	{
		cout << inx << " ";
	}
	cout << endl;*/
	return 0;
}

/*
c++ STL�������
���� vector
������ ��(���ܣ�����)
����ʱ���ʵ���  ��������������ʲô�ģ������㷨Ϊʲô��Ҫ���ܵ�������Ϊ������
������  ���������������� 

�����ĵײ������¼���ʵ�ֻ���(�ײ�����ݽṹ)�����飬������ϣ����

�������������������ķ�ʽһģһ����

�����㷨�������������������ģ�壬Ҫ�Ը������������ݽ��д�������Ҫ����������ݽ��б���������Ҫ�����������Ϊ������
*/
