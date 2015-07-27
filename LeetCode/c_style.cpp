#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include <cstddef>
#include <list>
#include<deque>

template<typename T>
class myClass{
public:
	T get_value()const;
	myClass();
	myClass(const T&);
private:
	T t;
};

template<typename T>
T myClass<T>::get_value()const
{
	return this->t;
}

template<typename T>
myClass<T>::myClass()
{
	this->t = 0;
}

template<typename T>
myClass<T>::myClass(const T&a)
{
	this->t = a;
}

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::list;

int main(int argc, char*argv[]){
	char *ptr1 = "xiaoman is a beautiful girl!";
	char *ptr2 = "i love xiaoman!";
	char str[] = { 'i', ' ', 'l', 'o', 'v', 'e' ,'\0'};
	cout << str << endl;
	cout << strlen(ptr1) << std::endl;
	cout << strcmp(ptr2, str) << std::endl;
	cout << ptr1 << endl;
	std::string str1(ptr1);
	cout << sizeof(ptr1)<< ' ' << str1.size() << endl;

	char *words[] = { "stately", "plump", "buck", "mulligan" };
	size_t words_size = sizeof(words) / sizeof(char*);
	std::vector<std::string> vstr(words, words + words_size);
	cout << words_size << endl;
	cout << vstr.size()<<endl;
	for (std::vector<std::string>::const_iterator ix = vstr.begin(); ix != vstr.end(); ix++)

		cout << *ix << ' ';
	cout << endl;
	cout << *words[1] << endl;

	const std::list<int>::size_type list_size = 62;
	std::list<std::string> slist(list_size, "xiaoman\n");
	for (std::list<std::string>::const_iterator ix = slist.begin(); ix != slist.end(); ix++)
		cout << *ix;
	int aa = 44;
	myClass<int> mint(33);
	cout << mint.get_value() << endl;
	vector<myClass<int>> vecm(10);
	vector<myClass<int>> vec2(10, 22);

	vector<int>vec(10, 100);
	vector<int>::iterator iter = vec.begin() + vec.size() / 2;
	list<int>ilist(vec.begin(), vec.end());
	list<int>::iterator itl = ilist.end() ;
	return EXIT_SUCCESS;
}

