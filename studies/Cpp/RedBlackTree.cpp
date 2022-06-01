#include<iostream>

typedef struct Node {
	int key;
	struct Node* lson, * rson, * father;
	char* color;
}Node;

void InsertNode(Node** root, int new_key);
void PrintTree(Node* root, int k);
void SearchNode(Node* root, int key);
void DeleteNode(Node** root, int key);

// liczby wygenerowane: 9994, 134, 1614, 6136, 1198, 6615, 8334, 9217, 6913, 6945, 5327, 4502, 8342, 6955, 7508, 6680, 3813, 817, 3581, 8760
int main() {
    Node* root = new Node;
    InsertNode(&root, 9994);
    InsertNode(&root, 134);
    InsertNode(&root, 1614);
    InsertNode(&root, 6136);
    InsertNode(&root, 1198);
    InsertNode(&root, 6615);
    InsertNode(&root, 8334);
    InsertNode(&root, 9217);
    InsertNode(&root, 6913);
    InsertNode(&root, 6945);
    InsertNode(&root, 5327);
    InsertNode(&root, 4502);
    InsertNode(&root, 8342);
    InsertNode(&root, 6955);
    InsertNode(&root, 7508);
    InsertNode(&root, 6680);
    InsertNode(&root, 3813);
    InsertNode(&root, 817);
    InsertNode(&root, 3581);
    InsertNode(&root, 8760);

}

void InsertNode(Node** root, int new_key) {
    Node* element = new Node;
    element->key = new_key;
    element->lson = NULL;
    element->rson = NULL;
    element->father = NULL;

    if ((*root) == NULL) {
        (*root) = element;
    }
    else {
        Node* x = (*root);
        Node* y = NULL;
        while (x != NULL) {
            if (x->key == new_key) {
                printf("taki klucz juz istnieje: %d\n", new_key);
                return;
            }
            y = x;
            if (x->key > new_key) {
                x = x->lson;
            }
            else {
                x = x->rson;
            }
        }
        element->father = y;
        if (y->key > new_key) {
            y->lson = element;
        }
        else {
            y->rson = element;
        }
    }
}

// Pokazanie drzewa
void PrintTree(Node* root, int k) {
    if (root == NULL) {
        printf("Puste drzewo\n");
        return;
    }
    if (root != NULL) {
        if (root->lson != NULL)
            PrintTree(root->lson, k + 1);
        for (int i = 0; i < k; i++) {
            if (i == k - 1)
                printf("|");
            else
                printf(" ");
        }
        printf("%d \n", root->key);
        if (root->rson != NULL)
            PrintTree(root->rson, k + 1);
    }
}

// Szukanie wezla
void SearchNode(Node* root, int search_key) {
    Node* x = root;
    while (x != NULL) {
        if (x->key == search_key) {
            printf("znaleziono klucz\n");
            return;
        }
        else {
            if (x->key > search_key) {
                x = x->lson;
            }
            else {
                x = x->rson;
            }
        }
    }
    printf("nie znaleziono takiego klucza\n");
}

// Usuwanie wezla
void DeleteNode(Node** root, int delete_key) {

    if ((*root) == NULL)
        printf("Puste drzewo\n");
    else {
        Node* x = (*root);
        while (x != NULL) {
            if (x->key == delete_key) {
                break;
            }
            else {
                if (x->key > delete_key)
                    x = x->lson;
                else
                    x = x->rson;
            }
        }
        if (x == NULL)
            printf("Nie znaleziono takiego klucza\n");
        else {
            if (x == (*root)) {
                if ((*root)->lson == NULL && (*root)->rson == NULL) {
                    free((*root));
                    *root = NULL;
                    return;
                }
                else if ((*root)->lson == NULL && (*root)->rson != NULL) {
                    (*root) = (*root)->rson;
                    (*root)->father = NULL;
                    free(x);
                    return;
                }
                else if ((*root)->lson != NULL && (*root)->rson == NULL) {
                    (*root) = (*root)->lson;
                    (*root)->father = NULL;
                    free(x);
                    return;
                }
                else {
                    Node* y = x->rson;
                    while (y->lson != NULL) {
                        y = y->lson;
                    }
                    (*root)->key = y->key;
                    if (y->rson != NULL) {
                        y->rson->father = y->father;
                        y->father->lson = y->rson;
                        free(y);
                    }
                    else {
                        y->father->lson = NULL;
                        free(y);
                    }
                }
            }
            else {
                Node* y;
                if (x->lson == NULL && x->rson == NULL) {
                    if (x->father->key > x->key)
                        x->father->lson = NULL;
                    else
                        x->father->rson = NULL;
                    free(x);
                }
                else if (x->lson == NULL && x->rson != NULL) {
                    y = x->rson;
                    y->father = x->father;
                    if (x->father->key > x->key)
                        x->father->lson = y;
                    else
                        x->father->rson = y;
                }
                else if (x->lson != NULL && x->rson == NULL) {
                    y = x->lson;
                    y->father = x->father;
                    if (x->father->key > x->key)
                        x->father->lson = y;
                    else
                        x->father->rson = y;
                }
                else {
                    Node* y = x->rson;
                    while (y->lson != NULL)
                        y = y->lson;
                    x->key = y->key;
                    if (y->rson != NULL) {
                        y->rson->father = y->father;
                        y->father->lson = y->rson;
                        free(y);
                    }
                    else {
                        y->father->lson = NULL;
                        free(y);
                    }

                }
            }
        }
    }
}