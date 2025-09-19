
#include <iostream>
#include "DataStructure/Container_Adaptor/MyQueue.h"

int main()
{
	//테스트용 메뉴 만들기
	//1. Enqueue
	//2. Dequeue
	//3. Peek
	//4. TestPrintQueue
	//5. 종료
	/*MyQueue q;
	
	while (true)
	{
		printf("큐 테스트 프로그램\n");
		printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. TestPrintQueue\n5. 종료\n");

		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int value;
			std::cout << "Enqueue할 값 입력: ";
			std::cin >> value;
			q.Enqueue(value);
			q.TestPrintQueue();
			break;
		}
		case 2:
		{
			q.Dequeue();
			q.TestPrintQueue();
			break;
		}
		case 3:
		{
			try
			{
				int frontValue = q.Peek();
				std::cout << "Peek한 값: " << frontValue << std::endl;
			}
			catch (const std::out_of_range& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		case 4:
		{
			q.TestPrintQueue();
			break;
		}
		case 5:
		{
			std::cout << "프로그램 종료" << std::endl;
			return 0;
		}
		}
	}
	*/
	//Circular Queue 2만들기 (생성자에서 파라미터 받아 크기 조절 가능하도록)


}