#include<iostream>
#include<memory>

// ����Ʈ ������
// ��ü ���� �ȶ��ѵ�?
// ������ : �ּҸ� ��� �ִ� ����;
// Ư¡:
// 1. ����Ʈ�ϴ� = delete ���� �ʿ䰡 ����
// 2. ->, *�����͸� ����ִ� �������ε� �긦 ���� �ִ�.(������ �����ε�)

// ����
// 1. unique ������: ���� ���������ž�;
// 2. shared ������: 
// 3. weak ������

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