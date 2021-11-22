#include <stdio.h>
#include <stdlib.h> // ? malloc, free 함수 사용을 위한 헤더 파일

// * 동적 할당 영역을 배열처럼 쓰기
// 형태가 같은 변수가 많이 필요할 때 하나씩 동적 할당하는 것은 비효율적입니다. 할당한 저장 공간의 수만큼 포인터가 필요하기 때문입니다. 
// 따라서 많은 저장 공간을 한꺼번에 동적 할당하여 배열처럼 사용합니다. 
// 이때 할당한 저장 공간의 시작 위치만 포인터에 저장하면 포인터를 배열처럼 쓸 수 있습니다. 

// ? 한 번에 저장 공간을 동적 할당하여 배열처럼 사용할수 있다
int main(void) {
    // ? 동적 할당 영역을 연결할 포인터
    int *pi; 
    int i, sum = 0;

    pi = (int *)malloc(5 * sizeof(int)); // 20바이트 저장공간 할당.

    printf("pi: %d\n", pi);
    printf("*pi: %d\n", *pi);
    printf("&pi: %d\n", &pi);

    // NULL 포인터 처리
    if (pi == NULL) {
        exit(1);  
    }

    printf("다섯 명의 나이를 입력하세요: ");
    for (i=0; i<5; i++) {
        scanf("%d", &pi[i]); // ? 배열 요소에 입력
        sum += pi[i];
    }
    printf("다섯 명의 평균 나이: %.1lf\n", (sum/5.0));
    free(pi);

    return 0;
}