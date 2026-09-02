/*输入：输入的第一行给出了初始两列的人数 m、n
接下来的两行（如果均存在）分别给出两列中每个小蓝鲸的身高 h
输出：输出合并后的数组，一共 1行，共 𝑚+𝑛个数字，数字用空格分隔开
输入：3 3
1 2 3
2 5 6
输出：6 5 3 2 2 1
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

Node* readList(int len)//创建两个链表，时间复杂度O(n)
{
    if(len <= 0)
        return NULL;
    Node* head = NULL;
    Node* tail = NULL;
    int x;
    for(int i = 0; i < len; i++)
    {
        scanf("%d",&x);
        Node* newNode = createNode(x);
        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

Node* orderedlistmerge(Node* la, Node* lb)
{
    Node dummy;
    dummy.next = NULL;
    Node* tail = &dummy;

    while(la != NULL && lb != NULL)
    {
        if(la->data < lb->data)
        {
            tail->next = la;
            la = la->next;
            tail = tail->next;
        }
        else
        {
            tail->next = lb;
            lb = lb->next;
            tail = tail->next;
        }
    }
    if(la != NULL)
        tail->next = la;
    if(lb != NULL)
        tail->next = lb;

    return dummy.next;
}

Node* reverselist(Node* head)
{
    Node* pre = NULL;
    Node* cur = head;
    Node* next;

    while (cur != NULL)
    {
        next= cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}


void printlist(Node* head) {
    Node* p = head;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    Node* la = readList(m);
    Node* lb = readList(n);

    Node* lc;
    lc = reverselist(orderedlistmerge(la, lb));
    printlist(lc);
    return 0;
}