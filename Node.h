/* 
 * File:   Node.h
 * Author: john
 *
 * Created on April 13, 2010, 1:07 PM
 */

#ifndef _NODE_H
#define	_NODE_H
typedef int DADO;

struct Node{
    Node *proximo;
    DADO data;
    int peso;
};

#endif	/* _NODE_H */

