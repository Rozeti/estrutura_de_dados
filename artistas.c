#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[100];
    char genero[100];
    char nacionalidade[100];
    char albuns[1000];
} Artista;

int comparar(const void *a, const void *b) {
    const Artista *artistaA = (const Artista *)a;
    const Artista *artistaB = (const Artista *)b;
    return strcmp(artistaA->nome, artistaB->nome);
}

int main() {
    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char buffer[1000];
    Artista artistas[100];

    int contagem_artistas = 0;
    while (fgets(buffer, sizeof(buffer), arquivo)) {
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            continue;
        }

        if (strcmp(buffer, "==========") == 0) {
            strcat(artistas[contagem_artistas].albuns, "==========\n");
            contagem_artistas++;
        } else if (strlen(artistas[contagem_artistas].nome) == 0) {
            strcpy(artistas[contagem_artistas].nome, buffer);
        } else if (strlen(artistas[contagem_artistas].genero) == 0) {
            strcpy(artistas[contagem_artistas].genero, buffer);
        } else if (strlen(artistas[contagem_artistas].nacionalidade) == 0) {
            strcpy(artistas[contagem_artistas].nacionalidade, buffer);
        } else {
            strcat(artistas[contagem_artistas].albuns, buffer);
            strcat(artistas[contagem_artistas].albuns, "\n");
        }
    }

    fclose(arquivo);

    qsort(artistas, contagem_artistas, sizeof(Artista), comparar);

    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir novo artista\n");
        printf("2. Remover artista\n");
        printf("3. Editar artista\n");
        printf("4. Buscar artista pelo nome\n");
        printf("5. Buscar album\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                break;
            default:
        }
    } while (escolha != 0);

    return 0;
}
