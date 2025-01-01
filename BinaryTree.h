//
//  BinaryTree.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 06/11/2024.
//

#pragma once
template <typename T>
class BinaryTree
{
    private :
    int _depth;
    std::vector<std::vector<T>> _tree;
    public :
    // constructor
    //BinaryTree() : _depth(0) {};
    void setDepth(int depth){
        _depth = depth;
        _tree.resize(_depth+1);
        for ( int i=0 ;i <_depth+1; i++ )
        {
            _tree[i].resize(i+1);
        }
    };
    
    void setNode(int level, int pos , T value)
    {
        _tree[level][pos] = value;
    };
    
    T getNode( int level, int pos)
    {
        return _tree[level][pos];
    };
    void display()
    {
        for ( int i= 0 ; i<=_depth; i++)
        {
            for (int  j= 0 ; j< i+1; j++)
            {
                std::cout << _tree[i][j] << " " ;
            }
            std::cout<< std::endl;
        }
        
    };
};
