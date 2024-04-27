#ifndef ARTISTAS_H
#define ARTISTAS_H

typedef struct {
    char nome[100];
    char genero[100];
    char nacionalidade[100];
    char albuns[1000];
} Artista;

void inserirNovoArtista(Artista artistas[], int *contagem_artistas);
void removerArtista(Artista artistas[], int *contagem_artistas);
void editarArtista(Artista artistas[], int contagem_artistas);
void buscarArtistaPorNome(Artista artistas[], int contagem_artistas);
void buscarAlbum(Artista artistas[], int contagem_artistas);

#endif 
