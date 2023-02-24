#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 11

void imprimir_contato(void *pBuffer, int index) {
    char *pNome = pBuffer + index * (MAX_NOME + sizeof(int) * 2);
    int *pIdade = (int*) (pNome + MAX_NOME);
    int *pTelefone = (int*) (pIdade + 1);

    printf("%s, %d anos, telefone %d\n", pNome, *pIdade, *pTelefone);
}

int buscar_contato(void *pBuffer, int n, char *nome) {
    int i;
    for (i = 0; i < n; i++) {
        char *pNome = pBuffer + i * (MAX_NOME + sizeof(int) * 2);
        if (strncmp(pNome, nome, MAX_NOME) == 0) {
            return i;
        }
    }
    return -1;
}

void deletar_contato(void *pBuffer, int *n, int index) {
    char *pContato = pBuffer + index * (MAX_NOME + sizeof(int) * 2);
    char *pProximoContato = pBuffer + (index + 1) * (MAX_NOME + sizeof(int) * 2);

    memmove(pContato, pProximoContato, (*n - index - 1) * (MAX_NOME + sizeof(int) * 2));

    *n = *n - 1;
    pBuffer = realloc(pBuffer, *n * (MAX_NOME + sizeof(int) * 2));
}

int main() {
    void *pBuffer;
    int n = 0;
    int opcao;
    int i;

    while (1) {
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato\n");
        printf("4 - Deletar contato\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                n++;
                pBuffer = realloc(pBuffer, n * (MAX_NOME + sizeof(int) * 2));

                char nome[MAX_NOME];
                int idade;
                int telefone;

                printf("Digite o nome (max 10 caracteres): ");
                scanf("%s", nome);

                printf("Digite a idade: ");
                scanf("%d", &idade);

                printf("Digite o telefone: ");
                scanf("%d", &telefone);

                char *pNome = pBuffer + (n - 1) * (MAX_NOME + sizeof(int) * 2);
                int *pIdade = (int*) (pNome + MAX_NOME);
                int *pTelefone = (int*) (pIdade + 1);

                strncpy(pNome, nome, MAX_NOME);
                *pIdade = idade;
                *pTelefone = telefone;
                break;

            case 2:

                printf("Contatos:\n");
                for (i = 0; i < n; i++) {
                    printf("%d - ", i + 1);
                    imprimir_contato(pBuffer, i);
                }
                break;

            case 3:

                printf("Digite o nome do contato: ");
                scanf("%s", nome);

                int index = buscar_contato(pBuffer, n, nome);
                if (index == -1) {
                    printf("Contato nao encontrado\n");
                } else {
                    printf("Contato encontrado: ");
                    imprimir_contato(pBuffer, index);
                }
                break;

                case 4:
            printf("Digite o nome do contato a ser deletado: ");
            scanf("%s", nome);

            int indexDeletar = buscar_contato(pBuffer, n, nome);

                if (indexDeletar == -1) {
            printf("Contato nao encontrado\n");
        } else {
        deletar_contato(pBuffer, &n, indexDeletar);
        printf("Contato deletado\n");
    }
    break;

            case 5:

                free(pBuffer);
                return 0;
                default:
                printf("Opcao invalida\n");

        }
    }
}