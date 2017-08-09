#define ALPHABET_SIZE 27
#define TAM_VETOR 100
#define BACKSPACE 8
#define ESC 27

struct trieNode
{
    struct trieNode *children[ALPHABET_SIZE];
    struct trieNode *parent;
    bool finalWord;
};

typedef struct trieNode td_trieNode;

td_trieNode* CreateTrieNode     ();
void         menu               ();
void         printAllChildrens  (td_trieNode *node);
void         InsertNewWord      (td_trieNode *node, char *word);
void         PrintAllTree       (td_trieNode *node, char *word, int atualPos);
void         PrintAllTree       (td_trieNode *node, char *word, int atualPos);
void         findWordWith       (td_trieNode *node, char *cfind);
int          verifyRemotion     (td_trieNode *node, char *word, FILE* arq);
int          SearchWord         (td_trieNode *node, char *word);
int          removeWord         (td_trieNode *node, char *word, int atualPos, int lengthWord);
int          GetIndex           (char value);
int          GetChar            (int index);





