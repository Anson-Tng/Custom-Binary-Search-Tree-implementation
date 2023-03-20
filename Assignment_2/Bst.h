// Bst.h

//------------------------------------------------------------------------------


#ifndef BST_H
#define BST_H

#include <iostream>

//------------------------------------------------------------------------------

/**
 * @class Bst
 * @brief A simple template binary search tree (BST) with following recursive
 *        operations : Insert, Delete, Search, inOrder traversal, preOrder traversal,
 *                     postOrder traversal.
 *
 *
 * @author Anson Ting
 * @version 01
 * @date 06/05/2022 Anson Ting, Started
 *
 * @author Anson Ting
 * @version 02
 * @date 06/05/2022 Anson Ting, added DeleteTree().
 *
 * @author Anson Ting
 * @version 03
 * @date 08/05/2022 Anson Ting, Change the int BST to a template BST.
 *
 * @author Anson Ting
 * @version 04
 * @date 11/05/2022 Anson Ting, Copy operator, destructor, parameters updated.
 *
 * @author Anson Ting
 * @version 05
 * @date 20/05/2022 Anson Ting, details about constant references, and the explanation of *& has updated.
 *
 * @author Anson Ting
 * @version 06
 * @date 25/05/2022 Anson Ting, function pointer traversal.
 *
 * @author Anson Ting
 * @version 07
 * @date 02/06/2022 Anson Ting, Added public version deleteTree function.
 *
 * @todo To ensure this class is able to handles all the data and all functions usable.
 *
 * @bug All bugs are fixed at the moment.
 *
 */

template <class T>
struct node         /// Node struct
{
    T data;         /// Node value
    node<T>* left;  /// Left child node
    node<T>* right; /// Right child node

    node<T>() {}    /// Default constructor

    node<T>(const T& d):data(d), left(NULL), right(NULL) {}   /// Constructor with parameter (Initialization)
};

template <class T>
class Bst
{
    typedef void (*funcType)(T &); /// Template function
public:
    Bst():root(NULL) {}
    ~Bst(); /// Destructor
    Bst(const Bst<T>& other);
    /**
     * @brief  Insert function (client version)
     *
     * Call out the private Insert function.
     *
     * @param  d - node value
     * @return void
     */
    void Insert(const T& d);

    /**
     * @brief  Delete function (client version)
     *
     * Call out the private Delete function.
     *
     * @param  d - const reference of node value
     * @return void
     */
    void Delete(const T& d);

    /**
     * @brief  Search function (client version)
     *
     * Call out the private Search function.
     *
     * @param  d - node value
     * @return bool
     */
    bool Search(const T& d);

    /**
     * @brief  display in order traversal function (client version)
     *
     * Call out the private inOrderTraversal function.
     *
     *
     * @return void
     */
    void inOrderTraversal(funcType ft);

    /**
     * @brief  display pre order traversal function (client version)
     *
     * Call out the private preOrderTraversal function.
     *
     *
     * @return void
     */
    void preOrderTraversal(funcType ft);

    /**
     * @brief  display post order traversal function (client version)
     *
     * Call out the private postOrderTraversal function.
     *
     *
     * @return void
     */
    void postOrderTraversal(funcType ft);

    /**
     * @brief  Public version DeleteTree
     *
     * Delete all the childs and keep the root empty
     *
     * @param
     * @return void
     */
    void DeleteTree();

    /**
     * @brief  Overloaded = operator
     *
     * Copy the Binary Search Tree.
     *
     * @param  other - rhs Bst<T> const &
     * @return void
     */
    Bst<T>& operator =(const Bst<T>& other);

private:

    node<T>* root;  /// node

    /**
     * @brief  Insert node into Binary Search Tree
     *
     * Insertion function, first to check if the tree exist, create one if it's not.
     * If the node value is smaller than the root, it will be assigned to the left
     * and run into recursive routine to find the suitable place.
     *
     * @param  nd - address of node, d - node value
     * @return Node<T>* - pointer to Node
     */
    node<T>* Insert(node<T>* nd, const T& d);

    /**
     * @brief  Find the smallest node from Binary Search Tree
     *
     * This function only uses in Delete(node<T>* nd, T d);
     *
     *
     * @param  nd - address of node
     * @return Node<T>* - pointer to Node
     */
    node<T>* findMin(node<T>* nd);

    /**
     * @brief  delete node from Binary Search Tree
     *
     * Find the assigned node location and do the deletion with the suitable method.
     * It has 3 scenario of deletion
     * 1. Leaf node (0 children)
     * 2. Node with 1 Child
     * 3. Node with 2 Child
     *
     *
     * @param  nd - address of node, d - node value
     * @return Node<T>* - pointer to Node
     */
    node<T>* Delete(node<T>* nd, const T& d);

    /**
     * @brief  Find if the node value exist in the Binary Search Tree
     *
     * Check through all sub trees.
     *
     *
     * @param  nd - address of node, d - node value
     * @return Boolean
     */
    bool Search(node<T>* nd, const T& d);

    /**
     * @brief  In order traversal Binary Search Tree display
     *
     * In order traversal starts from Left to Root to Right
     *
     *
     * @param  nd - address of node
     * @return Void
     */
    void inOrderTraversal(node<T>* nd, funcType ft);

    /**
     * @brief  Pre order traversal Binary Search Tree display
     *
     * In order traversal starts from Root to Left to Right
     *
     *
     * @param  nd - address of node
     * @return Void
     */
    void preOrderTraversal(node<T>* nd, funcType ft);

    /**
     * @brief  Post order traversal Binary Search Tree display
     *
     * In order traversal starts from Left to Right to Root
     *
     *
     * @param  nd - address of node
     * @return Void
     */
    void postOrderTraversal(node<T>* nd, funcType ft);

    /**
     * @brief  Copy the entire Binary Search Tree.
     *
     * this function is used in overloading = operator
     *
     * Reason of why using *& is to get the access of exactly that node
     * to do the modification (duplicate).
     *
     * Caller's pointer can be modified by using it.
     *
     * @param  thisNd - pointer passed by reference, other - The coying node
     * @return Void
     */
    void copyTree(node<T>*& thisNd, const node<T>* other);


    /**
    * @brief  Delete all the nodes from Binary Search Tree
    *
    * Delete nodes from left to right, and least set the root
    * to NULL.
    *
    * Reason of why using *& is to get the access of exactly that node
    * to do the modification (deletion).
    *
    * @param  nd - pointer passed by reference
    * @return Void
    */
    void DeleteTree(node<T>* nd);

};

template <class T>
Bst<T>::~Bst()
{
    /// Delete all the child node.
    DeleteTree(root);
}

template <class T>
Bst<T>::Bst(const Bst<T>& other)
{
    if(other.root == NULL)
    {
        root = NULL;
    }
    else
    {
        copyTree(this -> root,other.root);
    }

}

template <class T>
void Bst<T>::Insert(const T& d)
{
    root = Insert(root, d);
}

template <class T>
node<T>* Bst<T>::Insert(node<T>* nd, const T& d)
{

    /// If that memory of node is empty, assign Template d as new node to the memory.
    /// The first call of this function will assign the Template d as the root.
    if(nd == NULL)
    {
        return new node<T>(d);
    }
    else
    {
        /// Check if Template d is already exist in the Binary Search Tree
        if(!Search(this->root, d))
        {
            /// If smaller, assign to the left node
            if(d < nd -> data)
            {
                nd -> left = Insert(nd -> left, d);
            }
            /// If larger, assign to the right node
            else
            {
                nd -> right = Insert(nd -> right, d);
            }
        }
    }
    return nd;
}

template <class T>
node<T>* Bst<T>::findMin(node<T>* nd)
{
    /// Reaching to the end of left = smallest
    while(nd -> left != NULL)
    {
        nd = nd -> left;
    }
    return nd;
}

template <class T>
void Bst<T>::Delete(const T& d)
{
    root = Delete(root, d);
}

template <class T>
node<T>* Bst<T>::Delete(node<T>* nd, const T& d)
{
    node<T>* temp = new node<T>;
    /// Finding the node wanted to delete
    if(nd == NULL)
    {
        return nd;
    }
    /// if its smaller than current node value, go left child node
    else if(d < nd -> data)
    {
        nd -> left = Delete(nd -> left, d);

    }
    /// if its larger than current node value, go right child node
    else if(d > nd -> data)
    {
        nd -> right = Delete(nd -> right, d);

    }
    /// Now the node memory has found, deletion started
    else
    {
        /// CASE 1 : NO Child ( Leaf node)
        if(nd -> left == NULL && nd -> right == NULL)
        {
            delete nd;
            nd = NULL;
        }
        /// CASE 2 : One child
        else if(nd -> left == NULL)
        {
            /// put unwanted value to temp, then it's right node shift up
            /// to it's memory, finally delete the temp.
            temp = nd;
            nd = nd -> right;
            delete temp;
        }
        else if(nd -> right == NULL)
        {
            /// put unwanted value to temp, then it's left node shift up
            /// to it's memory, finally delete the temp.
            temp = nd;
            nd = nd -> left;
            delete temp;
        }
        /// CASE 3 : Two Child
        else
        {
            /// Take the smallest node from left sub tree to replace deleted node
            /// and shift up the other nodes.
            temp = findMin(nd -> right);
            nd -> data = temp ->data;
            nd -> right = Delete(nd -> right, temp -> data);
        }
    }
    return nd;
}

template <class T>
bool Bst<T>::Search(const T& d)
{
    return Search(this -> root, d);
}

template <class T>
bool Bst<T>::Search(node<T>* nd, const T& d)
{
    /// If node not exist, return false;
    if(nd == NULL)
    {
        return false;
    }
    /// If node found, return true;
    else if(nd -> data == d)
    {
        return true;
    }
    /// If It's smaller than current node, go left sub tree node
    else if(d < nd -> data)
    {
        return Search(nd-> left, d);
    }
    /// If it's larger than current node, go right sub tree node
    else
    {
        return Search(nd -> right, d);
    }
}

template <class T>
void Bst<T>::inOrderTraversal(funcType ft)
{
    inOrderTraversal(this->root, ft);
}

template <class T>
void Bst<T>::inOrderTraversal(node<T>* nd, funcType ft)
{
    /// Display nodes with in order traversal
    if(nd == NULL)
    {
        return;
    }
    /// Left then Root then Right
    inOrderTraversal(nd -> left, ft);
    ft(nd -> data);
    inOrderTraversal(nd -> right, ft);
}

template <class T>
void Bst<T>::preOrderTraversal(funcType ft)
{
    preOrderTraversal(this->root, ft);
}

template <class T>
void Bst<T>::preOrderTraversal(node<T>* nd, funcType ft)
{
    /// Display Nodes with pre order traversal
    if(nd == NULL)
    {
        return;
    }
    /// Root then Left then Right
    ft(nd -> data);
    preOrderTraversal(nd -> left, ft);
    preOrderTraversal(nd -> right, ft);
}

template <class T>
void Bst<T>::postOrderTraversal(funcType ft)
{
    postOrderTraversal(this->root, ft);
}

template <class T>
void Bst<T>::postOrderTraversal(node<T>* nd, funcType ft)
{
    /// Display nodes with post order traversal
    if(nd == NULL)
    {
        return;
    }
    /// Left then Right then root
    postOrderTraversal(nd -> left, ft);
    postOrderTraversal(nd -> right, ft);
    ft(nd -> data);
}

template <class T>
void Bst<T>::DeleteTree()
{
    DeleteTree(root);
    /// keep the root null, to prevent crash.
    root = NULL;
}

template <class T>
void Bst<T>::DeleteTree(node<T>* nd)
{
    /// * used for getting pointer(*) of the data,
    /// then run the function on that exact data, and be able to
    /// make the changes (Deletion).

    /// If node is not empty
    if(nd != NULL)
    {
        /// Run recursive helper to left and right
        /// of the node.
        DeleteTree(nd -> left);
        DeleteTree(nd -> right);
        /// Delete node.
        delete nd;
        /// Finally delete the root itself.
        nd = nullptr;
    }

}

template <class T>
void Bst<T>::copyTree(node<T>*& thisNd, const node<T>* other)
{
    /// *& used for getting pointer(*) of the referred(&) data,
    /// so that the function allows to modify the data,
    /// client are able to receive the modified data.

    /// "thisNd" copy the "other"
    /// If other is exists, go in if statement.
    if(other)
    {
        thisNd = new node<T>;
        /// copy the current node data, then go run the function recursively for left and right.
        thisNd -> data = other -> data;
        copyTree(thisNd -> left, other -> left);
        copyTree(thisNd -> right, other -> right);
    }
    else
    {
        /// If the other is null, then stop copying and put as NULL.
        thisNd = NULL;
    }
}

template <class T>
Bst<T>& Bst<T>::operator =(const Bst<T>& other)
{
    /// If current root already exist, delete the nodes and root.
    if(root)
    {
        DeleteTree(root);
        root = NULL;
    }
    /// calling copy function
    copyTree(root,other.root);

    return *this;
}

#endif // BST_H


