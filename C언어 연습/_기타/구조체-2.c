#include <stdio.h>
#include <string.h>  // strcpy 함수가 선언된 헤더 파일
#define _CRT_SECURE_NO_WARNINGS    // strcpy 보안 경고로 인한 컴파일 에러 방지

// * typedef 로 구조체 만들기
// ? 구조체 변수를 선언할 때 일일이 struct 키워드를 붙이려니 좀 귀찮습니다. struct키워드를 생략하는 방법은 없을까요? 
// ? 이럴때는 typedef로 구조체를 정의하면서 별칭(alias)을 지정해주면 됩니다.

typedef struct Person { // ? 구조체 "이름"은 Person
    char name[20];
    int age;
    char address[100];
} Person; // ? typedef 를 사용하여 구조체의 "별칭"을 Person 으로 정의

// * typedef는 자료형의 별칭을 만드는 기능입니다. 따라서 구조체뿐만 아니라 모든 자료형의 별칭을 만들 수 있습니다.
    // typedef 자료형 별칭
    // typedef 자료형* 별칭

typedef int MYINT;      // int를 별칭 MYINT로 정의
typedef int* PMYINT;    // int 포인터를 별칭 PMYINT로 정의
//! 결론: typedef 는 allias 를 만드는 키워드이다.


// * 구조체 태그(= 이름)
// ? struct 뒤에 붙는 구조체 이름은 원래 구조체 태그(tag)라 부릅니다(나중에 배울 공용체, 열거형도 마찬가지로 공용체 태그, 열거형 태그라 부릅니다). 
// ? 그리고 typedef로 정의한 구조체 별칭은 사용자 정의 타입의 이름이라 할 수 있습니다.

struct 태그 {
    // 자료형 멤버이름;
};

typedef struct 태그 {
    // 자료형 멤버이름;
} 타입이름;

// * C 언어는 나온지가 오래되다 보니 여러 가지 관습이 남아 있는데 구조체 태그와 타입 이름을 구분하기 위해 
// ? 관례상 태그 앞에 _, tag_, tag를 붙이고 있습니다. 코드에 따라서 태그 뒤에 _t를 붙이기도 합니다.
    // 예) _Person, tag_Person, tagPerson, Person_t
// ? 구조체 태그와 타입 이름은 사실상 같은 구조체를 지칭하므로 이름을 완전히 다르게 지을 필요는 없습니다. 
// ? 요즘은 구조체 태그와 타입 이름을 똑같이 만들기도 합니다.

typedef struct Person {    // 구조체 이름은 Person
    char name[20];
    int age;
    char address[100];
} Person;                  // typedef로 정의한 타입 이름도 Person
// ! 이때는 구조체 변수를 struct Person p1;과 같이 선언해도 되고, Person p1;과 같이 선언해도 됩니다.


int main () {
    Person p1; // ! 구조체 별칭 Person으로 변수를 선언했기 때문에 struct 키워드가 필요하지 않다!
    p1.age = 30;
    printf("나이: %d\n", p1.age);        

    // ? 만약 구조체 별칭을 사용하지 않고 구조체 이름으로 변수를 선언하고 싶다면 어떻게 해야 할까요? 
    // ? 다음과 같이 struct 키워드에 구조체 이름으로 변수를 선언하면 됩니다.

    struct Person p2; // 구조체 이름으로 변수 선언
    // !즉, 여기서 struct Person p2;과 Person p2;은 완전히 같습니다.
}