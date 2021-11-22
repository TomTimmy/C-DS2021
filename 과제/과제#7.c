#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1

// ! 2018040155 최수민
// ! C 언어 사용이 미숙하여, main 함수를 별도로 작성하여 출력하였습니다.
// ! 스크린샷을 참조해주세요.

typedef char element;

typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

void init (StackType* s) {
    s->top = -1;
}

int is_empty (StackType* s) {
    return (s->top == -1);
}

int is_full (StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// ? check full
void push (StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "Stack is Full\n");
        return;
    }
    else s->stack[++(s->top)] = item;
}

element pop (StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    else return s->stack[(s->top)--];
}

element peek (StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    else return s->stack[s->top];
}


// * 후위표기수식(postfix) 계산 함수
element eval(char exp[]) {
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    init(&s);
    for (i=0; i<len; i++) {
        ch = exp[i];
        // ? Operator 가 아니라, operhand 이면 
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/' ) {
            value = ch - '0'; // ? 이렇게 하면 ch 의 아스키코드값이 나옴. 
            push(&s, value);
        }
        // ? Operator 이면, operhand 를 스택에서 제거.
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
    }
    return pop(&s);
}


// * 연산자, Operator 의 우선순위 반환
int prec (char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}


// * 중위표기수식(infix) -> 후위표기수식(postfix) 변환함수
void infix_to_postfix (char exp[]) {
    int i = 0;
    char ch, top_op;
    int len =strlen(exp);

    StackType s;
    init(&s);

    for (i=0; i<len; i++) {
        ch = exp[i];
        switch (ch) {
        // ? 연산자 이면,
        case '+': case '-': case '*': case '/':
            // ? 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
                printf("%c", pop(&s));
            }
            push(&s, ch);
            break;

        // ? 왼쪽 괄호 이면,
        case '(': 
            push(&s, ch);
            break;

        // ? 오른쪽 괄호 이면,
        case ')': 
            top_op = pop(&s);
            // ? 왼쪽 괄호를 만날때까지 출력
            while (top_op != '(') {
                printf("%c", top_op);
                top_op = pop(&s);
            }
            break;

        // ? 피연산자 operhand 이면,
        default: 
            printf("%c", ch);
            break;
        }
    }
    // ? 스택에 저장된 연산자 Operator 들 출력.
    while (!is_empty(&s)) {
        printf("%c", pop(&s));
    }
}



// * infix -> postfix 변환값 출력
int main(void) {
  char infix[100];

  printf("input infix: ");
  scanf("%s", infix);

  infix_to_postfix(infix);

  return 0;
}

// // * postfix 계산 결과값 출력
// int main(void) {
//   int result; 
//   char postfix[100];

//   printf("postfix input: ");
//   scanf("%s", postfix);

//   result = eval(postfix);
//   printf("result is %d\n", result);

//   return 0;
// }
