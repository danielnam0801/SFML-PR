#include<iostream>
#include<memory>
#include<vector>
// ����Ʈ(�ȶ���) ������(������)
// ��ü ���� �ȶ��ѵ�?
// ������: �ּҸ� ����ִ� ����.
// Ư¡.
// 1. ����Ʈ�ϴ�. = delete�� ���� ���� �ʿ䰡 ����.
// 2. ->, * �����͸� ����ִ� �������ε� �긦 �����ִ�.(������ �����ε�)
// 3. �갡 �����ͱ� �����;�. *�� �پ�ߵ� �̰� �Ⱥٿ�����.
// ����
// 1. unique ������
// 2. shared ������
// 3. weak ������

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
//	// 2. shared ������
//	std::shared_ptr<Data> sptr1(new Data);
////	std::shared_ptr<Data> sptr1 = std::make_shared<Data>();
//	std::shared_ptr<Data> sptr2 = sptr1;
//
	std::unique_ptr<Data> uptr1 = std::make_unique<Data>();
	something(std::move(uptr1));
	int a = 0;
	//Data a;
	// c++11(modern c++)
	// 1. delete�� �������. => �޸� ����.
	// 2. double free
	//Data* pData = new Data;
	//Data* pData2 = pData;
	//delete pData;
	//delete pData2;

	// 1. unique������: ���� ���������ž�.
	int* ptr = new int;
	int* ptr2 = ptr;
	std::vector<int> v;
	//std::unique_ptr<int> uptr(new int);
	//`std::unique_ptr<Data> uptr1(new Data);

	// �����ϰ� ���� �� �ִ�. 
	
	//std::unique_ptr<Data> uptr2 = std::move(uptr1);
	//uptr1.get();
//	int a = 0;

}