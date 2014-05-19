//
//  Tree.h
//  IMN430_tp1
//
//  Created by Steven Aubertin on 2014-05-19.
//

#ifndef IMN430_tp1_Tree_h
#define IMN430_tp1_Tree_h

template<class EdgeT, class PoinT, class EventT>
class TreeNode{
public:
    //----Consrtructors
    TreeNode()
        : isLeaf(false), site(nullptr), parent(nullptr), edge(nullptr), event(nullptr){
    }
    TreeNode(PoinT* pt)
        : isLeaf(true), site(pt), parent(nullptr), edge(nullptr), event(nullptr){
    }
    
    //---- Public Methods
    TreeNode* getLeft()const{
        return left;
    }
    TreeNode* getright()const{
        return right;
    }
    
    //---- Members
    bool      isLeaf;
	PoinT*	  site;
	EdgeT*	  edge;
	EventT*	  event;
	TreeNode* parent;
    
    //TODO private ?
    TreeNode* left;
    TreeNode* right;
};

#endif
