/*
 * AVL_Tree.h
 *
 *  Created on: 11 May 2020
 *      Author: User
 */

#ifndef MYAVLTREE_H_
#define MYAVLTREE_H_

struct DATA {
	int key;
	string info;
};

class MyAVLTree: public AvlTree<DATA, int> {
	/* Define AvlTree protected function here */
	NODE<DATA>* _retrieve(int key, NODE<DATA> *root);

public:
	/* Define function to override AvlTree here */
	template<class KTYPE, class TYPE>
	void AVL_Modify(KTYPE, TYPE);
};

template<class KTYPE, class TYPE>
void MyAVLTree::AVL_Modify(KTYPE key, TYPE data) {
	NODE<TYPE> *node = _retrieve(key, tree);
	node->data = data;
}

#endif /* MYAVLTREE_H_ */
