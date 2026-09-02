/*输入：3 3   m行输入，每次选倒数第n个
1 2 3 4 5 #
6 7 #
1 #
输出
1 2 4 5 #
1 2 4 6 7 #
1 2 4 7 1 #
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
    int data;
    struct Node* next;
}Node;

Node* createNode(int a) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = a;
    newNode->next = NULL;
    return newNode;
}

void tailadd(Node** head, int a) {
    Node* newNode = createNode(a);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
}//时间复杂度为O(n)

void deletelastn(Node** head, int n) {//快慢指针法
    Node* fast = *head;
    Node* slow = *head;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    if (fast == NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = temp->next;
    free(temp);
}

void printlist(Node* head) {
    Node* p = head;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("#\n");
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    Node* head = NULL;
    int num;
    char ch;
    for (int i = 0; i < m; i++) {
        while (scanf("%d", &num) == 1) {//遇到#，读取整数失败返回0
            tailadd(&head, num);
        }
        scanf("%c", &ch);//读取掉缓冲区的#
        deletelastn(&head, n);
        printlist(head);
    }
    return 0;
}