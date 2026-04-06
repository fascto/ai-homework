//
// Created by tdela on 6/4/2026.
//

#ifndef IAHOMEWORK_BINARYTREE_H
#define IAHOMEWORK_BINARYTREE_H

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class BinaryTree {
private:
    struct BinaryTreeNode {
        T data;
        BinaryTreeNode* left{nullptr};
        BinaryTreeNode* right{nullptr};

        explicit BinaryTreeNode(const T data) : data(data) {}
    };

    BinaryTreeNode* root{nullptr};

    BinaryTreeNode* insertRec(BinaryTreeNode* node, const T& value) {
        if (node == nullptr) {
            return new BinaryTreeNode(value);
        }
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    BinaryTreeNode* removeRec(BinaryTreeNode* node, const T& data) {
        if (node == nullptr) return nullptr;

        if (data < node->data) {
            node->left = removeRec(node->left, data);
        } else if (data > node->data) {
            node->right = removeRec(node->right, data);
        } else {
            if (node->left == nullptr) {
                BinaryTreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BinaryTreeNode* temp = node->left;
                delete node;
                return temp;
            }

            BinaryTreeNode* temp = node->right;
            while (temp && temp->left != nullptr) {
                temp = temp->left;
            }
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    bool binarySearchRec(BinaryTreeNode* node, const T& data) const {
        if (node == nullptr) return false;

        if (data < node->data) return binarySearchRec(node->left, data);
        if (data > node->data) return binarySearchRec(node->right, data);

        return true;
    }

    void inOrderRec(BinaryTreeNode* node, std::vector<T>& v) const {
        if (node == nullptr) return;

        inOrderRec(node->left, v);
        v.push_back(node->data);
        inOrderRec(node->right, v);
    }

    void destroyTree(BinaryTreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void dfsPreOrderRec(BinaryTreeNode* node) const {
        if (node == nullptr) return;

        std::cout << node->data << " ";
        dfsPreOrderRec(node->left);
        dfsPreOrderRec(node->right);
    }

public:

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void insert(const T& value) {
        root = insertRec(root, value);
    }

    void remove(const T& data) {
        root = removeRec(root, data);
    }

    bool contains(const T& data) const {
        return binarySearchRec(root, data);
    }

    std::vector<T> getInOrder() const {
        std::vector<T> v;
        inOrderRec(root, v);
        return v;
    }

    void printBFS() const {

        if (root == nullptr) return;

        std::queue<BinaryTreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            BinaryTreeNode* node = q.front();
            q.pop();

            std::cout << node->data << " ";

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        std::cout << std::endl;
    }

    void printDFS_PreOrder() const {
        dfsPreOrderRec(root);
        std::cout << std::endl;
    }

};

#endif //IAHOMEWORK_BINARYTREE_H