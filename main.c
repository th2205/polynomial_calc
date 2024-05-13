#include <stdio.h>
#include <stdlib.h>

/*
다항식을 구현하기 위한 노드 구조체 정의
연결리스트를 이용하여 구현할 예정
*/
typedef struct Node
{
    /*
    다항식의 차수
    */
    int expo;
    /*
    다항식의 계수
    */
    int coef;
    /*
    다음 항(노드)를 가리키는 포인터
    */
    struct Node *next;
} Node;

/*
차수와 계수를 인자로 받아 항(노드)를 생성하는 함수
*/
Node *create_node(int expo, int coef)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->expo = expo;
    new_node->coef = coef;
    new_node->next = NULL;

    return new_node;
}

/*
다항식에 항(노드)를 추가하는 함수
poly 변수를 이중 포인터로 설정하는 이유:
 - main 함수에서 poly의 초기 값이 null인데 이를 그대로 파라미터로 전달하면 null값 자체가 들어가게되어서
   poly의 값이 변하지 않는다. 따라서 이중 포인터로 설정하여 주소값을 전달하고 이를 변경하여 값을 변경할 수 있도록 한다.
*/
void insert_node(Node **poly, int expo, int coef)
{
    Node *new_node = create_node(expo, coef);

    /*
    다항식이 비어있을 경우 새로운 노드를 추가한다.
    */
    if (*poly == NULL)
    {
        *poly = new_node;
    }
    else
    {
        /*
        다항식이 비어있지 않을 경우 마지막 노드를 찾아서 새로운 노드를 추가한다.
        */

        Node *temp = *poly;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_node;
    }
}

/*
만들어진 다항식을 출력하기 위한 함수
*/
void print_poly(Node *poly)
{
    Node *temp = poly;

    while (temp != NULL)
    {
        printf("%dx^%d", temp->coef, temp->expo);
        if (temp->next != NULL)
        {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

/*
다항식을 받아서 두 다항식을 더하는 함수
*/
Node add_polynomial(Node *poly1, Node *poly2)
{
    Node *result = NULL;
    Node *p1 = poly1;
    Node *p2 = poly2;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->expo > p2->expo)
        {
            insert_node(&result, p1->coef, p1->expo);
            p1 = p1->next;
        }
        else if (p1->expo < p2->expo)
        {
            insert_node(&result, p2->coef, p2->expo);
            p2 = p2->next;
        }
        else
        { // 같은 차수의 항을 더함
            int summedCoeff = p1->coef + p2->coef;
            if (summedCoeff != 0)
            {
                insert_node(&result, summedCoeff, p1->expo);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    // 남은 항들 추가
    while (p1 != NULL)
    {
        insert_node(&result, p1->coef, p1->expo);
        p1 = p1->next;
    }
    while (p2 != NULL)
    {
        insert_node(&result, p2->coef, p2->expo);
        p2 = p2->next;
    }

    return *result;
}

int main()
{
    printf("Hello, World!\n");
    Node *poly1 = NULL;
    Node *poly2 = NULL;

    insert_node(&poly1, 1, 3);
    insert_node(&poly1, 2, 2);
    insert_node(&poly1, 5, 4);
    insert_node(&poly1, 3, 3);

    insert_node(&poly2, 1, 1);
    insert_node(&poly2, 2, 2);
    insert_node(&poly2, 4, 2);
    insert_node(&poly2, 3, 3);

    print_poly(poly1);
    print_poly(poly2);

    Node result = add_polynomial(poly1, poly2);

    print_poly(&result);

    printf("\n");
    return 0;
}