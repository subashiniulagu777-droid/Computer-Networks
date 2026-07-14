typedef struct TrieNode {
    struct TrieNode *child[2];
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->child[0] = NULL;
    node->child[1] = NULL;
    return node;
}

void insert(TrieNode* root, int num) {
    TrieNode* curr = root;

    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;

        if (!curr->child[bit])
            curr->child[bit] = createNode();

        curr = curr->child[bit];
    }
}

int findMax(TrieNode* root, int num) {
    TrieNode* curr = root;
    int maxXor = 0;

    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int opposite = 1 - bit;

        if (curr->child[opposite]) {
            maxXor |= (1 << i);
            curr = curr->child[opposite];
        } else {
            curr = curr->child[bit];
        }
    }

    return maxXor;
}

int findMaximumXOR(int* nums, int numsSize) {
    TrieNode* root = createNode();

    for (int i = 0; i < numsSize; i++) {
        insert(root, nums[i]);
    }

    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        int curr = findMax(root, nums[i]);
        if (curr > ans)
            ans = curr;
    }

    return ans;
}