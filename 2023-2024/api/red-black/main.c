#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEFT child[0]
#define RIGHT child[1]

#define BLACK 0
#define RED 1

// @todo space optimizations (or maybe not: how memory is aligned?)
//   - color in child[0] last bit
//   - delete parent field (recursive calls)

typedef struct _RB {
    int key;
    uint8_t color;
    struct _RB *child[2];
    struct _RB *parent;
} RB;

RB null_leaf = {.key = 0, .color = 0, /* .child = {&null_leaf, &null_leaf}, .parent = &null_leaf */};

RB *rb_new();
RB *rb_successor(RB *node);
RB *rb_min(RB *node);
void rb_insert(RB **root, int val);
void rb_delete(RB **root, RB *node);
RB *rb_find(RB *root, int val);
void rb_free(RB *root);
void rb_free_node(RB *node);
void rb_print(RB *root);
void rb_fix_insertion(RB **root, RB *node);
RB *_rb_fix_insertion_inner(RB **root, RB *node, int dir);
int rb_black_height(RB *root);
void rb_fix_deletion(RB **root, RB *node);
int _rb_fix_deletion_inner(RB **root, RB *parent, int dir);

/* void test() {
    RB *root = rb_new();
    rb_insert(&root, 8);
    rb_print(root);
    printf("------------\n");
    rb_insert(&root, 37);
    rb_print(root);
    printf("------------\n");
    rb_delete(&root, rb_find(root, 8));
    rb_print(root);
    printf("------------\n");
    rb_free(root);
} */

void test() {
    int n, m, max;
    scanf("%d %d %d", &n, &m, &max);
    int *nums = malloc(sizeof(int) * m);
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        RB *root = rb_new();
        int size = 0;
        for (int j = 0; j < m; j++) {
            if (size == 0 || rand() % 4 >= 1) {
                int x = rand() % max + 1;
                rb_insert(&root, x);
                nums[size++] = x;
            } else {
                int y = rand() % size;
                rb_delete(&root, rb_find(root, nums[y]));
                nums[y] = nums[--size];
            }
            assert(rb_black_height(root));
        }
        printf("\rTest %d of %d passed", i + 1, n);
        fflush(stdout);
        rb_free(root);
    }
    free(nums);
}

void from_input() {
    int n, x;
    scanf("%d", &n);
    RB *root = rb_new();
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        rb_insert(&root, x);
        assert(rb_black_height(root));
    }

    printf("Black height = %d (0 <=> not balanced)\n", rb_black_height(root));

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        RB *to_delete = rb_find(root, x);
        if (to_delete != &null_leaf) rb_delete(&root, to_delete);
        assert(rb_black_height(root));
    }

    printf("Black height = %d (0 <=> not balanced)\n", rb_black_height(root));
    rb_print(root);
    rb_free(root);
}

int main(void) {
    stdin = fopen("input.txt", "r");
    test();
    // from_input();
    return 0;
}

RB *rb_new() {
    return &null_leaf;
}

void rb_insert(RB **root, int val) {
    assert(root != NULL && *root != NULL);
    RB *x = malloc(sizeof(RB));
    x->parent = x->RIGHT = x->LEFT = &null_leaf;
    x->color = RED;
    x->key = val;

    RB *p = &null_leaf, *c = *root;
    while (c != &null_leaf) {
        p = c;
        if (x->key < c->key) c = c->LEFT;
        else c = c->RIGHT;
    }

    x->parent = p;
    if (p == &null_leaf) *root = x;
    else if (x->key < p->key) p->LEFT = x;
    else p->RIGHT = x;

    rb_fix_insertion(root, x);
}

RB *rb_successor(RB *node) {
    assert(node != &null_leaf);
    if (node->RIGHT != &null_leaf) return rb_min(node->RIGHT);
    RB *p = node->parent;
    while (p != &null_leaf && p->RIGHT == node) {
        node = p;
        p = node->parent;
    }
    return p;
}

RB *rb_min(RB *root) {
    RB *node = root;
    while (node->LEFT != &null_leaf) {
        node = node->LEFT;
    }
    return node;
}

void rb_print(RB *node) {
    if (node == &null_leaf) return;
    printf("%2d (%5s) ", node->key, node->color == BLACK ? "black" : "red");
    printf("[%2d, %2d] [%2d]\n", node->LEFT ? node->LEFT->key : -1,
           node->RIGHT ? node->RIGHT->key : -1, node->parent ? node->parent->key : -1);
    rb_print(node->LEFT);
    rb_print(node->RIGHT);
}

void rb_free_node(RB *node) {
    free(node);
}

void rb_free(RB *node) {
    if (node == &null_leaf) return;
    rb_free(node->RIGHT);
    rb_free(node->LEFT);
    rb_free_node(node);
}

// 0 left, 1 right
void rb_rotate(RB **root, RB *x, int dir) {
    RB *y = x->child[1 - dir];
    x->child[1 - dir] = y->child[dir];
    if (x->child[1 - dir] != &null_leaf) x->child[1 - dir]->parent = x;
    y->child[dir] = x;
    y->parent = x->parent;
    if (y->parent == &null_leaf) *root = y;
    else if (y->parent->child[dir] == x) y->parent->child[dir] = y;
    else y->parent->child[1 - dir] = y;
    x->parent = y;
}

void rb_fix_insertion(RB **root, RB *node) {
    RB *p = node->parent;
    while (p->color == RED) {
        node = _rb_fix_insertion_inner(root, node, p == p->parent->child[1]);
        p = node->parent;
    }
    (*root)->color = BLACK;
}

RB *_rb_fix_insertion_inner(RB **root, RB *z, int dir) {
    RB *y = z->parent->parent->child[1 - dir];
    if (y->color == RED) {  // case 1
        z->parent->color = BLACK;
        y->parent->color = RED;
        y->color = BLACK;
        return y->parent;
    } else {
        if (z == z->parent->child[1 - dir]) {  // case 2
            z = z->parent;
            rb_rotate(root, z, dir);
        }
        z->parent->color = BLACK;  // case 3
        z->parent->parent->color = RED;
        rb_rotate(root, z->parent->parent, 1 - dir);
        return z;
    }
}

// returns 0 if it is not balanced
int rb_black_height(RB *node) {
    // assert(((unsigned long long)node & 1ull) == 0);
    if (node == &null_leaf) return 1;
    if (node->color == RED && (node->LEFT->color == RED || node->RIGHT->color == RED)) return 0;
    int left = rb_black_height(node->LEFT);
    int right = rb_black_height(node->RIGHT);
    if (left == 0 || right == 0 || left != right) return 0;
    return left + (node->color == BLACK);
}

RB *rb_find(RB *root, int val) {
    RB *node = root;
    while (node != &null_leaf) {
        if (val < node->key) node = node->LEFT;
        else if (val > node->key) node = node->RIGHT;
        else return node;
    }
    return &null_leaf;
}

void rb_delete(RB **root, RB *x) {
    assert(x != &null_leaf);
    RB *to_delete = x;
    if (x->LEFT != &null_leaf && x->RIGHT != &null_leaf) {
        to_delete = rb_successor(x);
        x->key = to_delete->key;
    }
    RB *to_append = to_delete->LEFT, *p = to_delete->parent;
    if (to_append == &null_leaf) to_append = to_delete->RIGHT;
    to_append->parent = p; // null_leaf can now have a parent
    int dir = to_delete == p->child[1];
    if (p == &null_leaf) *root = to_append;
    else if (dir) p->RIGHT = to_append;
    else p->LEFT = to_append;

    if (to_delete->color == BLACK) rb_fix_deletion(root, to_append);
    rb_free_node(to_delete);
}

void rb_fix_deletion(RB **root, RB *x) {
    RB *p = x->parent;
    int loop = 1;
    while (p != &null_leaf && x->color != RED && loop) {
        loop = _rb_fix_deletion_inner(root, p, p->child[1] == x);
        x = p;
        p = p->parent;
    }
    x->color = BLACK;  // case 0
}

// returns 1 if the function has to be called again, 0 otherwise
int _rb_fix_deletion_inner(RB **root, RB *p, int dir) {
    // RB *x = p->child[dir];
    RB *w = p->child[1 - dir];
    if (w->color == RED) {  // case 1
        w->color = BLACK;
        p->color = RED;
        rb_rotate(root, p, dir);
        w = p->child[1 - dir];
    }
    if (w->color == BLACK && w->LEFT->color == BLACK && w->RIGHT->color == BLACK) {  // case 2
        w->color = RED;
        return 1;
    }
    if (w->child[1 - dir]->color == BLACK) {  // case 3
        w->color = RED;
        w->child[dir]->color = BLACK;
        rb_rotate(root, w, 1 - dir);
        w = p->child[1 - dir];
    }  // case 4
    w->color = p->color;
    w->child[1 - dir]->color = BLACK;
    rb_rotate(root, p, dir);
    return 0;
}
