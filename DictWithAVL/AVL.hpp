typedef double TC; 
typedef float TV;

struct Noh { 
    TC chave; 
    TV valor; 
    Noh *esq, *dir, *pai; 
    int h; 
};

// Nulo quando árvore vazia.
struct DicAVL { 
    Noh *raiz; 
}; 

// Inicializa D como uma árvore vazia.
void inicializar (DicAVL &D);

// Retorna um ponteiro para o novo nó ou nulo se erro de alocação
Noh* inserir (DicAVL &D, TC c, TV v);

// Retorna um ponteiro para o nó da chave procurada, ou nulo se a chave não estiver em D.
Noh* procurar (DicAVL &D, TC c); 

// n aponta para o nó a ser removido
void remover (DicAVL &D, Noh *n);

// Desaloca os nós da árvore.
void terminar (DicAVL &D);