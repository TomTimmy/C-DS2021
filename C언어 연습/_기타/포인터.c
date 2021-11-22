#include <stdio.h>

int main() {
    //* 포인터 기초 
    // 참고:https://khu.goorm.io/learn/lecture/201/%ED%95%9C-%EB%88%88%EC%97%90-%EB%81%9D%EB%82%B4%EB%8A%94-c%EC%96%B8%EC%96%B4-%EA%B8%B0%EC%B4%88/lesson/1271954/%ED%8F%AC%EC%9D%B8%ED%84%B0%EB%9E%80
    // ! "선언, *" 
    int *p; // ? int형 포인터 변수(pointer to int) 
    // p = 0; -> 에러! // ! 포인터는 NULL 로 초기화 해야 한다! 
    p = NULL;
    int num = 20;

    // ! (포인터에 메모리"주소" 할당 할 때는, "*" 붙이지 "않는다")
    p = &num; // ? num 의 "메모리주소(address of num)"가 포인터 p에 담긴다. 
    // ! "역참조, dereference *"
    printf("최초 포인터 p가 가리키는 값: %d\n\n", *p); // ! 포인터가 가리키는 값 (지정 값) 사용(접근)시에는 *p

    printf("변수 num의 주소 값: %d\n", &num); // ? "포인터"와 "메모리주소"는 같은 의미이다.
    printf("포인터 p의 값: %d\n", p);
    printf("포인터 p가 가리키는 값: %d\n\n", *p); // ? 포인터가 가리키고 있는 주소에 "접근"하여 값을 가져온다. 

    *p += 5;
    printf("포인터 p의 값: %d\n", p);
    printf("포인터 p가 가리키는 값: %d\n\n", *p);
    
    (*p)++;
    printf("포인터 p의 값: %d\n", p);
    printf("포인터 p가 가리키는 값: %d\n\n", *p);

    *p++; //! 주의!!! 증감연산자(++, --)는 dereference 연산자 * 보다 우선된다.
    printf("포인터 p의 값: %d\n", p);
    printf("포인터 p가 가리키는 값: %d\n\n", *p);


    //* 이중 포인터 (포인터의 포인터. 포인터의 메모리주소를 담을 수 있는 변수이다) 
    // https://dojang.io/mod/page/view.php?id=276 , https://dojang.io/mod/page/view.php?id=279
    int *numPtr1; // ? 단일 포인터 선언
    int **numPtr2; // ? 이중 포인터(포인터의 포인터) 선언
    int num1 = 10;

    numPtr1 = &num1; //? num1 의 메모리주소를 포인터변수 numPtr1 에 저장.
    numPtr2 = &numPtr1; //? 포인터변수 numPtr1 의 메모리주소를 이중포인터변수 numPtr2 에 저장.
    printf("%d\n", **numPtr2); // ? 포인터를 두 번 derefer 하여 num1의 메모리주소 접근
    printf("%d\n", *numPtr2); // ? 이러면 걍 numPtr2 메모리주소 접근

    // ? 포인터도 실제로는 변수이기 때문에 메모리 주소를 구할 수 있습니다. 
    // ! 하지만 포인터의 메모리 주소는 일반 포인터에 저장할 수 없고, 
    // ! int **numPtr2;처럼 이중 포인터에 저장해야 합니다. 
    // ? int **numPtr2;를 영어로 읽으면 pointer to pointer to int가 됩니다(numPtr2 → numPtr1 → num1).

    // ?  여기서 이중 포인터 numPtr2를 끝까지 따라가서 실제 값을 가져오려면 
    // ?  **numPtr2처럼 변수 앞에 역참조 연산자를 두 번 사용하면 됩니다. 
    // ? 즉, 역참조를 두 번 하므로 numPtr2 ← numPtr1 ← num1과 같은 모양이 되고 
    // ? num1의 값을 가져올 수 있습니다.
}