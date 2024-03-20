#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de nó para a lista ligada
typedef struct Node {
    int pid;
    int end_time;
    struct Node* next;
} Node;

// Função para atualizar o tempo de fim de um processo
void update_terminated_process(Node* head, int pid, int end_time) {
    Node* current = head;

    // Percorre a lista até encontrar o processo com o pid especificado
    while (current != NULL) {
        if (current->pid == pid) {
            // Atualiza o tempo de fim do processo
            current->end_time = end_time;
            return;
        }
        current = current->next;
    }

    // Se o processo com o pid especificado não for encontrado
    printf("Processo com PID %d não encontrado.\n", pid);
}

// Função para imprimir a lista de processos
void print_list(Node* head) {
    Node* current = head;
    printf("Lista de processos:\n");
    while (current != NULL) {
        printf("PID: %d, Tempo de fim: %d\n", current->pid, current->end_time);
        current = current->next;
    }
}

// Função principal
int main() {
    // Exemplo de lista de processos
    Node* head = malloc(sizeof(Node));
    Node* second = malloc(sizeof(Node));
    Node* third = malloc(sizeof(Node));

    head->pid = 101;
    head->end_time = 50;
    head->next = second;

    second->pid = 202;
    second->end_time = 60;
    second->next = third;

    third->pid = 303;
    third->end_time = 70;
    third->next = NULL;

    // Antes da atualização
    printf("Antes da atualização:\n");
    print_list(head);

    // Atualizando o tempo de fim do processo com PID 202
    update_terminated_process(head, 202, 80);

    // Após a atualização
    printf("\nApós a atualização:\n");
    print_list(head);

    // Liberando memória alocada
    free(head);
    free(second);
    free(third);

    return 0;
}
