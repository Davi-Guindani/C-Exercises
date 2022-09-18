#ifndef Fila_h
#define Fila_h

typedef struct fila *Fila;
int Enfileira (Fila F, int x);
int Desenfileira (Fila f, int *x);
void Imprimir (Fila f);
Fila Inicializar ();
Fila Destruir (Fila f);

#endif
