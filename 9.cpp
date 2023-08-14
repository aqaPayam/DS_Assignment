#include <bits/stdc++.h>

using namespace std;

struct Node {
    int val;
    int weight, size, maximum;
    Node *left, *right;

    explicit Node(int i) : val(i), weight(rand() % (int(1e9) + 7)), maximum(val), size(1), left(nullptr), right(nullptr) {}
} *root;

typedef Node *pnode;

inline int maximum(pnode &treap) {
    if (!treap) return INT_MIN;
    return treap->maximum;
}

inline int size(Node *treap) {
    return treap ? treap->size : 0;
}

void updateMax(Node *&treap) {
    if (treap)
        treap->maximum = max(treap->val, max(maximum(treap->left), maximum(treap->right)));
}

void updateSize(Node *&treap) {
    if (treap)
        treap->size = 1 + size(treap->left) + size(treap->right);
}


void split(Node *treap, Node *&left, Node *&right, int val) {
    if (!treap) {
        left = right = nullptr;
        return;
    }

    if (size(treap->left) < val) {
        split(treap->right, treap->right, right, val - size(treap->left) - 1);
        left = treap;
    } else {
        split(treap->left, left, treap->left, val);
        right = treap;
    }
    updateSize(treap);
    updateMax(treap);
}

void merge(Node *&treap, Node *left, Node *right) {
    if (left == nullptr) {
        treap = right;
        return;
    }
    if (right == nullptr) {
        treap = left;
        return;
    }

    if (left->weight < right->weight) {
        merge(left->right, left->right, right);
        treap = left;
    } else {
        merge(right->left, left, right->left);
        treap = right;
    }
    updateSize(treap);
    updateMax(treap);
}

void cyclic_shift(Node *&treap, int qL, int qR, int k) {
    if (qL == qR) return;
    k %= (qR - qL + 1);

    pnode l, mid, mid1, mid2, r;
    split(treap, l, r, qL);
    split(r, mid, r, qR - qL + 1);
    split(mid, mid1, mid2, qR - qL - k + 1);
    merge(mid, mid2, mid1);
    merge(r, mid, r);
    merge(treap, l, r);
}

int maximum_query(Node *&treap, int l, int r) {
    pnode Left, Mid, Right;
    split(treap, Left, Mid, l);
    split(Mid, Mid, Right, r - l + 1);
    int mx = maximum(Mid);
    merge(treap, Left, Mid);
    merge(treap, treap, Right);
    return mx;
}


int main() {
    int n, tmp, q;
    char str[10];
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        merge(root, root, new Node(tmp));
    }
    cin >> q;
    int a, b, c;
    for (int i = 0; i < q; ++i) {
        cin >> str;
        if (!strcmp(str, "shift")) {
            cin >> a;
            cin >> b;
            cin >> c;
            cyclic_shift(root, a - 1, b - 2, c);
        }
        if (!strcmp(str, "max")) {
            cin >> a;
            cin >> b;
            c = maximum_query(root, a - 1, b - 2);
            cout << c << "\n";
        }
    }

}