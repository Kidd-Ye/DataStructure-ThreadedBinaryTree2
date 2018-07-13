//
//  BinaryTree.h
//  ThreadedBinaryTree2
//
//  Created by kidd on 2018/7/13.
//  Copyright © 2018年 Kidd. All rights reserved.
//

#ifndef BinaryTree_h
#define BinaryTree_h
using namespace std;

enum PointerTag{
    Thread, //0 线索
    Link    //1 指针
};

template<typename T>
struct BinaryTreeThrNode {
    BinaryTreeThrNode(const T& x=T())
            :_data(x)
            ,_left(NULL)
            ,_right(NULL)
            ,_leftTag(Link)
            ,_rightTag(Link)
    {}
    T _data;
    BinaryTreeThrNode<T> *_left;
    BinaryTreeThrNode<T> *_right;
    PointerTag _leftTag;
    PointerTag _rightTag;
};

template<typename T>
class BinaryTreeThd{
    typedef BinaryTreeThrNode<T> Node;
    
public:
    BinaryTreeThd(const T *a, size_t size, const T& invalid)
    :_root(NULL)
    ,_prev(NULL)
    {
        size_t index=0;
        _root = _CreateTreeThd(a, size, index, invalid);
    }
public:
    void PrevOrderThread() // 前序线索化二叉树
    {
        _PrevOrderThread(_root);
    }
    void PrevOrder()         //前序遍历二叉树
    {
        _PrevOrder(_root);
        cout<<endl;
    }
    void InOrderThread()    //中序线索化二叉树
    {
        _InOrderThread(_root);
    }
    void InOrder()          //中序遍历二叉树
    {
        _InOrder(_root);
        cout<<endl;
    }
    void PostOrderThread()  //后序线索化二叉树
    {
        _PostOrderThread(_root);
    }
    void PostOrder()
    {
        _PostOrder(_root);
        cout<<endl;
    }
    
protected:
    Node *_CreateTreeThd(const T *a, size_t size, size_t& index, const T& invalid){
        assert(a);
        Node *root = NULL;
        if (index < size && a[index] != invalid) {
            root = new Node(a[index]);
            root->_left = _CreateTreeThd(a, size, ++index, invalid);
            root->_right = _CreateTreeThd(a, size, ++index, invalid);
        }
        return root;
    }
    

protected:
    void _PrevOrderThread(Node *root){
        if (root == NULL) {
            return;
        }
        if (root->_left == NULL) {
            root->_leftTag = Thread;
            root->_left = _prev;
        }
        if (_prev && _prev->_right == NULL) {
            _prev->_rightTag = Thread;
            _prev->_right = root;
        }
        _prev = root;
        
        if (root->_leftTag == Link) { //防止栈溢出
            _PrevOrderThread(root->_left);
        }
        if (root->_rightTag == Link) {
            _PrevOrderThread(root->_right);
        }
    }
    void _InOrderThread(Node *root){
        if (root == NULL) {
            return;
        }
        _InOrderThread(root->_left);
        
        if (root->_left == NULL) {
            root->_leftTag = Thread;
            root->_left = _prev;
        }
        if (_prev && _prev->_right == NULL) {
            _prev->_rightTag = Thread;
            _prev->_right = root;
        }
        _prev = root;
        
        _InOrderThread(root->_right);
    }
    
    void _PostOrderThread(Node *root){
        if (root == NULL) {
            return;
        }
        _PostOrderThread(root->_left);
        _PostOrderThread(root->_right);
        
        if (root->_left == NULL) {
            root->_leftTag = Thread;
            root->_left = _prev;
        }
        if (_prev && _prev->_right == NULL) {
            _prev->_rightTag = Thread;
            _prev->_right = root;
        }
        _prev = root;
        
    }
    
    //接下来是各种遍历方法
    void _PrevOrder(Node *root){
        if (root == NULL) {
            return;
        }
        Node *cur = root;
        while (cur) {
            while (cur && cur->_leftTag == Link) {
                cout << cur->_data << " ";
                cur = cur->_left;
            }
            cout << cur->_data << " ";
            cur = cur->_right;
        }
    }
    
    void _InOrder(Node *root){
        if (root == NULL) {
            return;
        }
        Node *cur = root;
        while (cur) {
            while (cur && cur->_leftTag == Link) {
                cur = cur->_left;
            }
            cout << cur->_data << " ";
            while (cur && cur->_rightTag == Thread) {
                cur = cur->_right;
                cout << cur->_data << " ";
            }
            cur = cur->_right;
        }
    }
    //倒着遍历后序线索二叉树
    //根-右-左
    void _PostOrder(Node *root){
        if (root == NULL) {
            return;
        }
        Node *cur = root;
        
        while (cur) {
            while (cur && cur->_rightTag == Link) {
                cout << cur->_data << " ";
                cur = cur->_right;
            }
            cout << cur->_data << " ";
            while (cur->_left && cur->_leftTag == Thread) {
                cur = cur->_left;
                cout << cur->_data << " ";
            }
            cur = cur->_left;
        }
    }
    
    Node *_root;
    Node *_prev;
};

















#endif /* BinaryTree_h */
