// 0714����.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include<string>

namespace Busan
{
	std::string saram = "�λ��� ���";

	void Printsaram()
	{
		std::cout << saram << std::endl;
	}
}

namespace Seoul
{
	std::string saram = "������ ���";

	void Printsaram()
	{
		std::cout << saram << std::endl;
	}
}


std::string saram = "�� ���";

int _tmain(int argc, _TCHAR* argv[])
{

	std::cout << saram << std::endl;
	std::cout << Busan::saram << std::endl;

	// Printsaram(); //�����߻� �̸����� ���� ���� ���� ���� �ʾ����Ƿ�.. -using namespace Seoul; �ϸ� ���� �̸������� ����Ʈ��� �Լ� ȣ�� 
	// using namespace Seoul;
	// using namespace Busan; �̷��� �ΰ� �� ������� ������ ����.. ����� �𸣹Ƿ�..

	Seoul::Printsaram();
	Busan::Printsaram();

	getchar();
	return 0;
}

