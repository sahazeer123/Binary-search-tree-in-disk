struct node
{
	int key;
	int left_offset;
	int right_offset;
};
typedef struct node node_t;

struct tree
{
	int free_head;
	int root;
};
typedef struct tree tree_t;

FILE* init_tree(tree_t*, const char* name);

void close_tree(tree_t *, FILE *fp);

void display_inorder(const tree_t *ptr_tree, FILE *fp);

void display_preorder(const tree_t *ptr_tree, FILE *fp);

void insert_key(tree_t *ptr_tree, int key, FILE *fp);

void delete_key(tree_t *ptr_tree, int key, FILE *fp);