#include<iostream>
#include<memory>
#include<vector>
// 스마트(똑똑한) 포인터(포인터)
// 대체 뭐가 똑똑한데?
// 포인터: 주소를 담고있는 변수.
// 특징.
// 1. 스마트하다. = delete를 내가 해줄 필요가 없다.
// 2. ->, * 포인터만 들고있는 연산자인데 얘를 쓸수있다.(연산자 오버로딩)
// 3. 얘가 포인터긴 포인터야. *를 붙어야돼 이거 안붙여도돼.
// 종류
// 1. unique 포인터
// 2. shared 포인터
// 3. weak 포인터

class Data
{
public:
	/*Data() = delete;
	void test() override;*/
};
void something(std::unique_ptr<Data> _ptr)
{
}
int main()
{
//	// 2. shared 포인터
//	std::shared_ptr<Data> sptr1(new Data);
////	std::shared_ptr<Data> sptr1 = std::make_shared<Data>();
//	std::shared_ptr<Data> sptr2 = sptr1;
//
	std::unique_ptr<Data> uptr1 = std::make_unique<Data>();
	something(std::move(uptr1));
	int a = 0;
	//Data a;
	// c++11(modern c++)
	// 1. delete를 해줘야해. => 메모리 누수.
	// 2. double free
	//Data* pData = new Data;
	//Data* pData2 = pData;
	//delete pData;
	//delete pData2;

	// 1. unique포인터: 나만 갖고있을거야.
	int* ptr = new int;
	int* ptr2 = ptr;
	std::vector<int> v;
	//std::unique_ptr<int> uptr(new int);
	//`std::unique_ptr<Data> uptr1(new Data);

	// 안전하게 만들 수 있다. 
	
	//std::unique_ptr<Data> uptr2 = std::move(uptr1);
	//uptr1.get();
//	int a = 0;

}