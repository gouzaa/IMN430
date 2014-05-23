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
    
    //---- Accessors
    TreeNode* getLeft()const{
        return left;
    }
    TreeNode* getRight()const{
        return right;
    }
    
    //---- Predicates
    bool isValidEvent()const{
        return event->valid;
    }
    
    //---- Mutators
    void setLeft(TreeNode* oleft){
        left = oleft;
    }
    void setRight(TreeNode* oright){
        right = oright;
    }
    void setIsValid(const bool isValid){
        event->valid = isValid;
    }
    
    //---- Members
    bool      isLeaf;
	PoinT*	  site;
	EdgeT*	  edge;//TODO: should we really put that here ????
	EventT*	  event;
	TreeNode* parent;
    
    //TODO: private ?
    TreeNode* left;
    TreeNode* right;
};

#endif
