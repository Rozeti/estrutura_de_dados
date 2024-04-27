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

void buscarArtistaPorNome(Artista artistas[], int contagem_artistas) {
    char buscaNome[100];
    printf("Digite o nome do artista que deseja buscar: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    char buscaNomeLowerCase[100];
    strcpy(buscaNomeLowerCase, buscaNome);
    for (int i = 0; i < strlen(buscaNomeLowerCase); i++) {
        buscaNomeLowerCase[i] = tolower(buscaNomeLowerCase[i]);
    }

    int encontrado = 0; 

    int baixo = 0, alto = contagem_artistas - 1, meio;
    while (baixo <= alto) {
        meio = (baixo + alto) / 2;
        char nomeArtista[100];

        strcpy(nomeArtista, artistas[meio].nome);
        for (int i = 0; i < strlen(nomeArtista); i++) {
            nomeArtista[i] = tolower(nomeArtista[i]);
        }

        char *tokenBusca = strtok(buscaNomeLowerCase, " ");
        int encontradoPartes = 1;
        while (tokenBusca != NULL) {
            if (strstr(nomeArtista, tokenBusca) == NULL) {
                encontradoPartes = 0;
                break;
            }
            tokenBusca = strtok(NULL, " ");
        }

        if (encontradoPartes) {
            printf("\nArtista encontrado:\n");
            printf("->Nome: %s\n", artistas[meio].nome);
            printf("->Genero: %s\n", artistas[meio].genero);
            printf("->Nacionalidade: %s\n", artistas[meio].nacionalidade);
            printf("->Albuns:\n%s\n", artistas[meio].albuns);
            encontrado = 1; 
            break; 
        } else if (strcmp(nomeArtista, buscaNomeLowerCase) < 0) {
            baixo = meio + 1;
        } else {
            alto = meio - 1;
        }
    }
    if (!encontrado) {
        printf("\nArtista não encontrado.\n");
    }
}

void buscarAlbum(Artista artistas[], int contagem_artistas) {
    char buscaAlbum[100];
    printf("Digite o nome do album que deseja buscar: ");
    fgets(buscaAlbum, sizeof(buscaAlbum), stdin);
    buscaAlbum[strcspn(buscaAlbum, "\n")] = 0;

    for (int i = 0; i < strlen(buscaAlbum); i++) {
        buscaAlbum[i] = tolower(buscaAlbum[i]);
    }

    int encontrado = 0; 
    for (int i = 0; i < contagem_artistas; i++) {
        char albunsLowerCase[1000]; 
        strcpy(albunsLowerCase, artistas[i].albuns);
        
        for (int j = 0; j < strlen(albunsLowerCase); j++) {
            albunsLowerCase[j] = tolower(albunsLowerCase[j]);
        }

        if (strstr(albunsLowerCase, buscaAlbum) != NULL) {
            printf("\nResultado:\n");
            printf("->Nome: %s\n", artistas[i].nome);
            printf("->Genero: %s\n", artistas[i].genero);
            printf("->Nacionalidade: %s\n", artistas[i].nacionalidade);
            printf("->Albuns:\n%s\n", artistas[i].albuns);
            encontrado = 1; 
        }
    }

    if (!encontrado) {
        printf("\nNenhum resultado encontrado para '%s'.\n", buscaAlbum);
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
                buscarArtistaPorNome(artistas, contagem_artistas);
                break;
            case 5:
                buscarAlbum(artistas, contagem_artistas);
                break;
            case 0:
                break;
            default:
        }
    } while (escolha != 0);

    return 0;
}
