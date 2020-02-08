/**
 * Description: 1D range update, range query
 * Source: USACO Counting Haybales
 * Verification: SPOJ Horrible
 */

template<int SZ> struct lazysumtree {
    node* root;
    lazysumtree() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node(0, ub-1);
    }
    void propagate(node* n) {
        if(n->l != n->r) {
            int mid = ((n->l) + (n->r))/2;
            if(n->left == nullptr) n->left = new node(n->l, mid);
            if(n->right == nullptr) n->right = new node(mid+1, n->r);
        }
        if(n->lazy != 0) {
            n->val += ((n->r) - (n->l) + 1) * n->lazy;
            if(n->l != n->r) {
                n->left->lazy += n->lazy;
                n->right->lazy += n->lazy;
            }
            n->lazy = 0;
        }
    }
    void addN(node* n, int i1, int i2, int val) {
        propagate(n);
        if(i2 < n->l || i1 > n->r) return;
        if(n->l == n->r) {
            n->val += val;
            return;
        }
        if(i1 <= n->l && i2 >= n->r) {
            n->val += ((n->r) - (n->l) + 1)*val;
            n->left->lazy += val;
            n->right->lazy += val;
            return;
        }
        
        addN(n->left, i1, i2, val);
        addN(n->right, i1, i2, val);
        n->val = n->left->val + n->right->val;
    }
    void add(int i1, int i2, int val) {
        addN(root, i1, i2, val);
    }
    int queryN(node* n, int i1, int i2) {
        propagate(n);
        if(i2 < n->l || i1 > n->r) return 0;
        if(n->l == n->r) {
            return n->val;
        }
        if(i1 <= n->l && i2 >= n->r) {
            return n->val;
        }
        
        return queryN(n->left, i1, i2) + queryN(n->right, i1, i2);
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};
