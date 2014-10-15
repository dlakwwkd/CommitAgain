// 0714강의.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include<string>

namespace Busan
{
	std::string saram = "부산사는 사람";

	void Printsaram()
	{
		std::cout << saram << std::endl;
	}
}

namespace Seoul
{
	std::string saram = "서울사는 사람";

	void Printsaram()
	{
		std::cout << saram << std::endl;
	}
}


std::string saram = "걍 사람";

int _tmain(int argc, _TCHAR* argv[])
{

	std::cout << saram << std::endl;
	std::cout << Busan::saram << std::endl;

	// Printsaram(); //오류발생 이름공간 없는 곳에 정의 하지 않았으므로.. -using namespace Seoul; 하면 서울 이름공간의 프린트사람 함수 호출 
	// using namespace Seoul;
	// using namespace Busan; 이렇게 두개 다 써놓으면 컴파일 에러.. 어떤건지 모르므로..

	Seoul::Printsaram();
	Busan::Printsaram();

	getchar();
	return 0;
}

