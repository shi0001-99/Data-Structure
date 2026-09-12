输入样例
4
1 0
2 1
1 0
2
3
3
输出
2 4 1


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100010 


typedef struct Node {
    int id;
    struct Node* prev;
    struct Node* next;
} Node;

Node node_arr[MAXN]; 
bool deleted[MAXN];  

int main() {
    int N;
    scanf("%d", &N);

    
    node_arr[1].id = 1;
    node_arr[1].prev = NULL;
    node_arr[1].next = NULL;
    deleted[1] = false;

    
    for (int i = 2; i <= N; i++) {
        int k, p;
        scanf("%d %d", &k, &p);
        node_arr[i].id = i;
        deleted[i] = false;

        if (p == 0) {
            
            Node* k_node = &node_arr[k];
            node_arr[i].prev = k_node->prev;
            node_arr[i].next = k_node;
            if (k_node->prev != NULL) {
                k_node->prev->next = &node_arr[i];
            }
            k_node->prev = &node_arr[i];
        }
        else {
       
            Node* k_node = &node_arr[k];
            node_arr[i].next = k_node->next;
            node_arr[i].prev = k_node;
            if (k_node->next != NULL) {
                k_node->next->prev = &node_arr[i];
            }
            k_node->next = &node_arr[i];
        }
    }

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        int x;
        scanf("%d", &x);
        if (deleted[x]) continue; 
        Node* del_node = &node_arr[x];
        deleted[x] = true;

        if (del_node->prev != NULL) {
            del_node->prev->next = del_node->next;
        }
        if (del_node->next != NULL) {
            del_node->next->prev = del_node->prev;
        }
    }

    Node* head = &node_arr[1];
    while (head->prev != NULL) {
        head = head->prev;
    }

    bool first = true;
    while (head != NULL) {
        if (!deleted[head->id]) {
            if (!first) printf(" ");
            printf("%d", head->id);
            first = false;
        }
        head = head->next;
    }
    printf("\n");

    return 0;
}

