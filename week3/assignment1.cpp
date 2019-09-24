#include <iostream>

static int data = 0; // 전역변수나 static 변수의 영역
static int bss ; // 초기화 되지 않은 전역변수, static 변수

int code(){ // 실행해야 할 함수와 코드의 영역
        return 0;
}

int main() {

        const char * rodata = "ABC";
        int * heap = new int[2];
        int stack = 0; // 지역변수를 저장하기 위한 메모리 공간  

        // (void*)주소값을 출력하기위해

        std::cout << "code\t" << (void*) code << std::endl;
        std::cout << "Rodata\t" << (void*) rodata << std::endl;
        std::cout << "data\t" << &data << std::endl;
        std::cout << "BSS\t" << &bss  << std::endl;
        std::cout << "HEAP\t" << heap << std::endl;
        std::cout << "Stack\t" <<  &stack << std::endl;
}
