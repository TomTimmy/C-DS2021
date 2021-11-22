#include <stdio.h>
#include <string.h>  // strcpy 함수가 선언된 헤더 파일
#define _CRT_SECURE_NO_WARNINGS    // strcpy 보안 경고로 인한 컴파일 에러 방지

// * 구조체 
// ? 구조체는 관련 자료형을 하나의 의미로 묶을 때 사용한다.
// ? 구조체는 보통 main 함수 바깥에 정의합니다. 만약 함수 안에 구조체를 정의하면 해당 함수 안에서만 구조체를 사용할 수 있습니다.
struct Person { // ? 자료구조 data structure 의 약어로 "struct" 키워드 사용.
    char name[20];
    int age;
    char address[100];
};

// ? "}" 와 ";" 사이에 변수를 지정해주면, "구조체를 정의하는 동시에 변수를 선언"할 수 있습니다.
// * 구조체 정의
struct Movie {
    char title[10];
    int runningTime;
} Movie; // * 구조체 선언!


int main () {
    // ? 구조체 자체도 배열로 선언 할 수 있다! 
    struct Person people[100]; // ? 선언 방법: struct 구조체이름 변수이름;
    struct Person p1;

    // ? 일반 변수로 선언한 구조체의 멤버에 접근할 때는 .(점)을 사용합니다.
    strcpy(p1.name, "최수민"); // p1.name 등의 문자열 멤버는 = 로 저장할 수 없으므로 strcpy 함수를 사용했다.
    p1.age = 24; 
    strcpy(p1.address, "경기도 하남시");

    Movie.runningTime = 90;

    // ? . 으로 구조체 멤버에 접근하여 값 출력
    printf("이름: %s\n", p1.name);       
    printf("나이: %d\n", p1.age);        
    printf("주소: %s\n\n", p1.address);    

    printf("Movie runningTime: %d\n", Movie.runningTime);  

    // * 선언과 동시에 할당하기.
    // ? name에는 "홍길동", age에는 30, address에는 "한남동"
    struct Person p2 = { .name = "홍길동", .age = 30, .address = "한남동" };

    printf("이름: %s\n", p2.name);       // 이름: 홍길동
    printf("나이: %d\n", p2.age);        // 나이: 30
    printf("주소: %s\n", p2.address);    // 주소: 한남동

    // ? name에는 "고길동", age에는 40, address에는 "반포동"
    struct Person p3 = { "고길동", 40, "반포동" }; // ! 이때는 순서에 맞춰서 할당해야 한다.

    printf("이름: %s\n", p3.name);       // 이름: 고길동
    printf("나이: %d\n", p3.age);        // 나이: 40
    printf("주소: %s\n", p3.address);    // 주소: 반포동
}