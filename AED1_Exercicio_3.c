#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void IncluirNome ( void **pBuffer, int *count );
void DeletarNome ( void **pBuffer, int *count );
void BuscarNome ( void *pBuffer, int *count );
void ListarDados ( void *pBuffer, int count );
int Menu();

typedef struct {
    char nome[ 10 ];
    int idade;
    char telefone[ 15 ];
}Agenda_t;

void IncluirNome ( void **pBuffer, int *count ){
    *pBuffer = ( Agenda_t * )realloc( *pBuffer, ( *count + 1 ) * sizeof( Agenda_t ) );
    Agenda_t *info = *pBuffer;

    printf("\nDigite o nome: ");
    scanf("%s", info[ *count ].nome);
    printf("\nDigite a idade: ");
    scanf("%d", &info[ *count ].idade);
    printf("\nDigite o telefone: ");
    scanf("%s", info[ *count ].telefone);
    (*count)++;

}

void DeletarNome ( void **pBuffer, int *count ) {
    Agenda_t *info = ( Agenda_t * )*pBuffer;
    char nome[ 10 ];

    printf("\nDigite o nome a ser removido: ");
    scanf("%s", nome);

    int i;
    for ( i = 0; i < *count; i++ ) {
        if ( strcmp( info[ i ].nome, nome ) == 0) {
            int j;
            for ( j = i; j < *count - 1; j++ ) {
                info[ j ] = info[ j + 1 ];
            }
            ( *count )--;
            info = ( Agenda_t * )realloc( info, ( *count ) * sizeof( Agenda_t ) );
            *pBuffer = info;
        }
    }
    printf("Nome nao encontrado\n");
}
void BuscarNome ( void *pBuffer, int *count ) {

    Agenda_t *info = ( Agenda_t * )pBuffer;
    char nome[ 10 ];

    printf("Digite o nome a ser encontrado: ");
    scanf("%s", nome);

    int i;
    for (i = 0; i < *count; ++i) {
        if ( strcmp( info[ i ].nome, nome) == 0) {
            printf("Nome: %s\n", info[i].nome);
            printf("Idade: %d\n", info[i].idade);
            printf("Telefone: %s\n", info[i].telefone);
            break;
        }
        printf("Nome nao encontrado\n");

    }

}

void ListarDados ( void *pBuffer, int count ) {

    Agenda_t *info = ( Agenda_t * )pBuffer;
    int i;
    for ( i = 0; i < count; ++i ) {
        printf("Nome: %s\n", info[ i ].nome);
        printf("Idade: %d\n", info[ i ].idade);
        printf("Telefone: %s\n", info[ i ].telefone);
        printf("\n");

    }
}

int Menu() {

    int escolha = 0;
    printf("1. Adicionar contato\n");
    printf("2. Remover Contato\n");
    printf("3. Procurar contato\n");
    printf("4. Listar contatos\n");
    printf("5. Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    printf("\n");
    return escolha;
}

int main() {

    Agenda_t *info = NULL;
    int count = 0;
    int escolha = 0;
    for ( ; ; ) {
        escolha = Menu();
        switch ( escolha ) {

        case 1:
            IncluirNome( ( void ** ) &info, &count );
            break;

        case 2:
            DeletarNome( ( void ** ) &info, &count );
            break;

        case 3:
            BuscarNome( info, &count );
            break;

        case 4:
            ListarDados( info, count );
            break;

        case 5:
            exit( 0 );
            break;

        }
    
    }
    return 0;
}
