#include<iostream>
#include<memory>

// 스마트 포인터
// 대체 뭐가 똑똑한데?
// 포인터 : 주소를 담고 있는 변수;
// 특징:
// 1. 스마트하다 = delete 해줄 필요가 없다
// 2. ->, *포인터만 들고있는 연산자인데 얘를 쓸수 있다.(연산자 오보로딩)

// 종류
// 1. unique 포인터: 나만 갖고있을거야;
// 2. shared 포인터: 
// 3. weak 포인터

class Data
{
	
};

int main() {
	std::shared_ptr<Data> sptr1 = std::make_shared<Data>();
	std::shared_ptr<Data> sptr2 = sptr1;

	int* ptr;
	//std::unique_ptr<int> uptr(new int);
	std::unique_ptr<Data> uptr1 = std::make_unique<Data>();
	std::unique_ptr<Data> uptr2(new Data);

}