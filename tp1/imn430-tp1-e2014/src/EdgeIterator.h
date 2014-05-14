//
//  EdgeIterator.h
//  IMN430_tp1
//
//  Created by Steven Aubertin on 2014-05-13.
//  Copyright (c) 2014 Steven Aubertin. All rights reserved.
//

#ifndef IMN430_tp1_EdgeIterator_h
#define IMN430_tp1_EdgeIterator_h

namespace DCEL {
    template<class T, class EdgeT>
    class EdgeIterator{
    public:
        //---- Typedefs
        typedef EdgeT edge_type;
        typedef T value_type;
        typedef EdgeIterator<edge_type, value_type> iterator_type;
        
        //---- Predicates
        inline bool hasNext()const{
            return next != nullptr;
        }
        inline bool isStart(const edge_type* const edge)const{
            return edge == start;
        }
        
        //---- Virtual Methods
        inline virtual edge_type* getNext() = 0;
        
        //---- Operators
        iterator_type& operator ++(){
            this->getNext();
            return *this;
        }
        iterator_type operator ++(int){
            iterator_type itt(*this);
            this->getNext();
            return itt;
        }
        const bool operator ==(const iterator_type& ie)const{
            return &ie == this;
        }
        bool operator ==(const iterator_type& ie){
            return &ie == this;
        }
        const bool operator !=(const iterator_type& ie)const{
            return !(operator==(ie));
        }
        bool operator !=(const iterator_type& ie){
            return !(operator==(ie));
        }
        
    protected:
        //---- Constructors
        /*
         Desactivate constructions for not childs
         */
        EdgeIterator(edge_type* startEdge = nullptr)
            : start(startEdge), next(startEdge){
        }
        EdgeIterator(const EdgeIterator& ei)
            : start(ei.start), next(ei.next){
        }
        
        //---- Members
        edge_type* start;
        edge_type* next;
    };
}

#endif
