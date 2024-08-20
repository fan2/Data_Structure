
struct tree /* 树的结构宣告       */
{
    int data;           /* 节点数据           */
    struct tree *left;  /* 指向左子树的指标   */
    struct tree *right; /* 指向右子树的指标   */
};
typedef struct tree treenode; /* 树的结构新型态     */
typedef treenode *btree;      /* 宣告树节点指标型态 */
