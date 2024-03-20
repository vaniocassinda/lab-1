#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

// Definição da estrutura para uma tarefa
typedef struct {
    char id[20]; // ID da tarefa
    int priority; // Prioridade da tarefa (0 a 5)
} Task;

// Definição da estrutura para um nó da lista ligada de tarefas
typedef struct Node {
    Task task;
    struct Node* next;
} Node;

// Função para criar um novo nó da lista
Node* createNode(Task task) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->task = task;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir uma nova tarefa na lista, ordenada por prioridade
void insertTask(Node** head, Task task) {
    Node* newNode = createNode(task);
    if (*head == NULL || (*head)->task.priority < task.priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->task.priority >= task.priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Função para listar todas as tarefas com prioridade indicada ou superior
void listTasks(Node* head, int priority) {
    printf("Lista de tarefas com prioridade %d ou superior:\n", priority);
    while (head != NULL && head->task.priority >= priority) {
        printf("Tarefa: %s, Prioridade: %d\n", head->task.id, head->task.priority);
        head = head->next;
    }
}

// Função para completar uma tarefa
void completeTask(Node** head, char* taskId) {
    Node* temp = *head;
    Node* prev = NULL;

    // Percorre a lista procurando pela tarefa com o ID especificado
    while (temp != NULL && strcmp(temp->task.id, taskId) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Se a tarefa for encontrada, remove-a da lista
    if (temp != NULL) {
        if (prev == NULL) {
            *head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Tarefa \"%s\" concluída com sucesso.\n", taskId);
    } else {
        printf("TAREFA INEXISTENTE\n");
    }
}

int main() {
    Node* taskLists[6] = {NULL}; // Array de listas ligadas para cada nível de prioridade

    while (1) {
        char command[20], taskId[20];
        int priority;

        printf("Comando: ");
        scanf("%s", command);

        if (strcmp(command, "new") == 0) {
            scanf("%d %s", &priority, taskId);
            if (priority < 0 || priority > 5) {
                printf("Prioridade inválida. Deve ser um número entre 0 e 5.\n");
                continue;
            }
            Task newTask;
            strcpy(newTask.id, taskId);
            newTask.priority = priority;
            insertTask(&taskLists[priority], newTask);
            printf("Tarefa \"%s\" adicionada com prioridade %d.\n", taskId, priority);
        } else if (strcmp(command, "list") == 0) {
            scanf("%d", &priority);
            if (priority < 0 || priority > 5) {
                printf("Prioridade inválida. Deve ser um número entre 0 e 5.\n");
                continue;
            }
            listTasks(taskLists[priority], priority);
        } else if (strcmp(command, "complete") == 0) {
            scanf("%s", taskId);
            completeTask(&taskLists[0], taskId); // Procura a tarefa em todas as listas
        } else {
            printf("Comando inválido.\n");
        }
    }

    return 0;
}
