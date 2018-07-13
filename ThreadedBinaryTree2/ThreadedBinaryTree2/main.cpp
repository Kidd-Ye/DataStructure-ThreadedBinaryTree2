//
//  main.cpp
//  ThreadedBinaryTree2
//
//  Created by kidd on 2018/7/13.
//  Copyright © 2018年 Kidd. All rights reserved.
//

#include <iostream>
#include "BinaryTree.h"

int main(int argc, const char * argv[]) {
    int array[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
    size_t size=sizeof(array)/sizeof(array[0]);
    
    BinaryTreeThd<int> bt1(array,size,'#');
    cout<<"线索化中序遍历>";
    bt1.InOrderThread();
    bt1.InOrder();        //3  2  1  5  6  7  4  8
    
    BinaryTreeThd<int> bt2(array,size,'#');
    cout<<"线索化前序遍历>";
    bt2.PrevOrderThread();
    bt2.PrevOrder();      //1  2  3  4  5  6  7  8
    
    BinaryTreeThd<int> bt3(array,size,'#');
    cout<<"线索化后序遍历>";
    bt3.PostOrderThread();
    bt3.PostOrder();      //1  4  8  5  6  7  2  3

    return 0;
}
