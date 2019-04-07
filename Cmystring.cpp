#include<iostream>
using namespace std;
class CMyString
{
public:
	CMyString(const char*p = nullptr)
	{
		//对于字符串要留个心眼,要记得处理空字符串的情形。为了后面处理的方便，这里对空字符串置为‘/0’。
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
	CMyString(const CMyString &str)//防止发生浅拷贝
	{
		//mptr = new char[str.length() + 1];//尽量不要让接口与接口之间产生联系
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
	}
	CMyString(CMyString &&str)//带右值引用的拷贝构造函数，用来利用临时对象
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

	bool operator>(const CMyString &str)const//对于对象的操作是只读不写     的函数，最好定义成常方法
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
		// 实现CMyString容器的迭代器
class iterator//迭代器作为容器的嵌套类存在。
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
		//不能写成const方法    char tmp = *it ,  *it = 'a';
		//这里写的迭代器底层的就是依靠下标或者指针来遍历容器
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
	CMyString str4 = str2 + str3;//tmp调用带右值引用的拷贝构造一个临时对象，临时对象调用带右值引用的拷贝构造str4
	CMyString str5 = str2 + "ccc";//就直接被优化成  tmp调用带右值引用的拷贝构造 构造str4？？？
	CMyString str6 = "ddd" + str3;//str2=str3+str4   tmp调用带右值引用的拷贝构造一个临时对象，临时对象再调用带右值引用的赋值重载函数产生str4
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
	//auto it = str.begin();//auto会自动根据等号右边的类型来匹配
	for (; it != str.end(); ++it)//迭代器加加(也包括对象的加加)都写成前置加加，这样效率会高一点。
	{
		cout << *it << " ";
	}
	cout << endl;
	//c++11标准 提供了foreach 来遍历容器(底层也就是通过迭代器来实现的)
	/*for (int inx : str)
	{
		cout << inx << " ";
	}
	cout << endl;*/
	return 0;
}

/*
c++ STL六大组件
容器 vector
迭代器 ：(功能：遍历)
面试时候问道：  迭代器是用来干什么的？泛型算法为什么都要接受迭代器作为参数？
迭代器  是用来遍历容器的 

容器的底层有以下几种实现机制(底层的数据结构)：数组，链表，哈希表，树

迭代器遍历所有容器的方式一模一样。

泛型算法是用来处理各种容器的模板，要对各种容器的数据进行处理，就需要对里面的数据进行遍历。就需要传入迭代器作为参数。
*/
