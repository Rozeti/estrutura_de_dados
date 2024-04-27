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

void converterIniciaisParaMaiusculo(char *string) {
    int tamanho = strlen(string);
    for (int i = 0; i < tamanho; i++) {
        if (i == 0 || string[i - 1] == ' ') {
            string[i] = toupper(string[i]);
        } else {
            string[i] = tolower(string[i]);
        }
    }
}

void removerArtista(Artista artistas[], int *contagem_artistas) {
    char buscaNome[100];
    printf("Digite o nome do artista que deseja remover: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    int indiceEncontrado = -1;
    for (int i = 0; i < *contagem_artistas; i++) {
        if (strcmp(artistas[i].nome, buscaNome) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("Artista nao encontrado.\n");
        return;
    }

    printf("Artista encontrado:\n");
    printf("->Nome: %s\n", artistas[indiceEncontrado].nome);
    printf("->Genero: %s\n", artistas[indiceEncontrado].genero);
    printf("->Nacionalidade: %s\n", artistas[indiceEncontrado].nacionalidade);
    printf("->Albuns:\n%s\n", artistas[indiceEncontrado].albuns);

    char escolha;
    printf("Deseja remover este artista? (s/n): ");
    scanf(" %c", &escolha);

    if (escolha == 's' || escolha == 'S') {
        for (int i = indiceEncontrado; i < *contagem_artistas - 1; i++) {
            strcpy(artistas[i].nome, artistas[i + 1].nome);
            strcpy(artistas[i].genero, artistas[i + 1].genero);
            strcpy(artistas[i].nacionalidade, artistas[i + 1].nacionalidade);
            strcpy(artistas[i].albuns, artistas[i + 1].albuns);
        }
        (*contagem_artistas)--;
        printf("Artista removido com sucesso.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
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
                removerArtista(artistas, &contagem_artistas);
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
