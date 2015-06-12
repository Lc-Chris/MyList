# include <iostream>
using namespace std;

template <class T> class MyList;
template <class T> ostream & operator<< (ostream &os ,const MyList<T> &obj);
template <class T> MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2);
template <class T> MyList<T> operator+(const MyList<T> &l1, const T &item);

template <class T>
class MyList{
	friend ostream& operator << <>(ostream & os, const MyList<T> & obj);
	friend MyList<T> operator + <>(const MyList<T> &l1,const MyList<T> &l2);
	friend MyList<T> operator + <> (const MyList<T> &l1, const T &item);
private:
	T *a;
	int size;   // the length of MyList
	int _size; // the length of array in data member
	void double_space();
public:
	MyList(){
		_size=100;
		size = 0;
		a = new T [_size];
	}
	MyList(int num, const T &item);
	MyList(const MyList &l);
    MyList(T* arr, int len);

	void push(const T &item);
	T pop();
	void insert(int index, const T &item);
	void clean();
	int get_size();
	void erase(int start, int end);
	T get_item(int index);
	MyList get_item(int start, int end);
	int count(const T &item);
	void remove(const T&item);
	void reverse();
	void sort(bool less=true);

	MyList<T> &operator = (const MyList<T> &l);
	MyList<T> &operator += (const T &item);
	MyList<T> &operator += (const MyList<T> &l);
	T &operator [] (int index);

	~MyList(){delete [] a;}
};

//------------------------------------------------------
// double space
template <class T>
void MyList<T>::double_space()
{
	T *b;
	_size*=2;
	b=new T[_size];
	for (int i=0;i<size;++i) b[i]=a[i];
	a=b;
}

//-----------------------------------------------------
//constructor
template <class T>
MyList<T>::MyList(int num,const T &item)
{
	_size=size=num;
	a=new T [_size];
	for (int i=0;i<num;++i) a[i]=item;
}

template <class T>
MyList<T>::MyList(const MyList<T> &l)
{
	_size=size=l.size;
	a=new T [_size];
	for (int i=0;i<size;++i) a[i]=l.a[i];
}

template <class T>
MyList<T>::MyList(T *arr,int len)
{
	_size=size=len;
	a=new T [_size];
	for (int i=0;i<size;++i) a[i]=arr[i];
}
//-------------------------------------------------------
// basic functions

template <class T>
void Qsort(T a[], int low, int high)
{
    if(low >= high) return;

    int first = low,last = high;
    int t1 = a[first];

    while(first < last){
        while(first < last && a[last] >= t1) --last;
        a[first] = a[last];
        while(first < last && a[first] <= t1) ++first;
        a[last] = a[first];
    }
    a[first] = t1;
    Qsort(a,low, first-1);
    Qsort(a,first+1, high);
}

template <class T>
void MyList<T>::push(const T &item)
{
	insert(size,item);
}

template <class T>
T MyList<T>::pop()
{
	try{
		if(size==0) throw(0);
		--size;
		return a[size];
	}
	catch (int) {
		cout<<"Empty list!"<<endl; exit(0);
	}
}

template <class T>
void MyList<T>::insert(int index, const T &item)  
{
	try{
		if (index<0 || index>size) throw(0.0);
		++size;
		if (size>_size) double_space();
		for (int i=size;i>=index+1;--i) a[i]=a[i-1];
		a[index]=item;
	}
	catch (double) {
		cout<<"Index Overflow!"<<endl;  exit(0);
	}
}

template <class T>
void MyList<T>::clean() {size=0;}

template <class T>
int MyList<T>::get_size(){return  size;}

template <class T>
void MyList<T>::erase(int start,int end)
{
	try{
		if (start+size<0 || start>=size || end+size<0 || end>=size) throw(0.0);
		if (start<0) start+=size;
		if (end<0) end+=size;
		if (start>end) {size=0;return ;}
		for (int i=0;i<size-end-1;++i) a[start+i]=a[end+i+1];
		size-=(end-start+1);
	}
	catch (double){
		cout<<"Index Overflow!"<<endl; exit(0);
	}
}

template <class T>
T MyList<T>::get_item(int index)
{
	try{
		if (index<0||index>=size) throw(0.0);
		return a[index];
	}
	catch (double) {
		cout<<"Index Overflow!"<<endl; exit(0);
	}
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end) 
{

	try{
		if (start+size<0 || start>=size || end+size<0 || end>=size) throw(0.0);
		if (start<0) start+=size;
		if (end<0) end+=size;
		MyList<T> tmp;
		if (start>end) return tmp;
		for (int i=start;i<=end;++i) tmp.push(a[i]);
		return tmp;
	}
	catch (double){
		cout<<"Index Overflow!"<<endl; exit(0);
	}
}

template <class T>
int MyList<T>::count(const T &item)
{
	int cnt=0;
	for (int i=0;i<size;++i)
		if (a[i]==item) ++cnt;
	return cnt;
}

template <class T>
void MyList<T>::remove(const T&item)
{
	bool flag=true;
	int i;
	for (i=0;i<size;++i)
		if (a[i]==item){flag=false;break;}
	if (!flag){
		for (int j=i;j<size-1;++j)
			a[j]=a[j+1];
		--size;
	}
}

template <class T>
void MyList<T>::reverse()
{
	MyList<T> tmp;
	while (tmp._size<_size) tmp.double_space();
	tmp.size=size;
	for (int i=size-1;i>=0;--i) tmp.a[size-1-i]=a[i];
	for (int i=0;i<size;++i) a[i]=tmp.a[i];
}

template <class T>
void MyList<T>::sort(bool less)
{
	Qsort(a,0,size-1);
	if (!less) this->reverse();
}

//------------------------------------------------------------------
// re-construct

template <class T>
ostream & operator<<(ostream &os, const MyList<T> &obj)
{
	if (obj.size==0) {cout<<"[]"<<endl; return os;}
	cout<<'[';
	for (int i=0;i<obj.size-1;++i) cout<<obj.a[i]<<',';
	cout<<obj.a[obj.size-1]<<']';
	cout<<endl;
	return os;
}

template <class T>
T & MyList<T>::operator[](int index)
{
	try{
		if (index<0||index>=size) throw(0.0);
		return a[index];
	}
	catch(double)	{
		cout<<"Index Overflow! "; exit(0);
	}
}

template <class T>
MyList<T> & MyList<T>::operator=(const MyList<T> &l)
{
	while (_size<l._size) double_space();
	size=l.size;
	for (int i=0;i<size;++i) a[i]=l.a[i];
}

template <class T>
MyList<T> operator +(const MyList<T> &l1,const MyList<T> &l2)
{
	MyList<T> l;
	while (l._size<(l1._size+l2._size)) l.double_space();
	l.size=l1.size+l2.size;
	for (int i=0;i<l1.size;++i) l.a[i]=l1.a[i];
	for (int i=0;i<l2.size;++i) l.a[i+l1.size]=l2.a[i];
	return l;
}

template <class T>
MyList<T> operator +(const MyList<T> &l1,const T &item)
{
	MyList<T> tmp;
	while (tmp._size<l1._size+1) tmp.double_space();
	tmp.size=l1.size+1;
	for (int i=0;i<l1.size;++i) tmp.a[i]=l1.a[i];
	tmp.a[tmp.size-1]=item;
	return tmp;
}

template <class T>
MyList<T> &MyList<T>::operator += (const T &item)
{
	*this=*this+item;
}

template <class T>
MyList<T> &MyList<T>::operator +=(const MyList<T> &l)
{
	*this=*this+l;
}


//-----------------------------------------------
// main function for test
int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *Èôstart > end£¬·µ»Ø¿ÕÊý×é
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1 , 0, 12]
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	b.insert(3, 116); 
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}









