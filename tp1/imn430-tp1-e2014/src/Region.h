//
//  Region.h
//  IMN430_tp1
//
//  Created by Steven Aubertin on 2014-05-13.
//  Copyright (c) 2014 Steven Aubertin. All rights reserved.
//

#ifndef IMN430_tp1_Region_h
#define IMN430_tp1_Region_h

#include "EdgeIterator.h"

namespace DCEL {
    class Region{
    public:
        //---- Typedefs
        
        
        //---- Constructors
        Region(HalfEdge* obound = nullptr) :
            bound(obound){
        }
        
        //---- Accessors
        inline HalfEdge* getBound() const{
            return this->bound;
        }
        
        //---- Mutators
        inline void setBound(HalfEdge* bound){
            assert(bound);
            
            this->bound = bound;
        }
        
        //---- Iterators
    private:
        template<class EdgeT>
        class RegionIterator : public EdgeIterator<Region, EdgeT>{
        public:
            //---- typedefs
            typedef EdgeIterator<Region, EdgeT> base_iterator;
            typedef typename base_iterator::edge_type edge_type;
            typedef typename base_iterator::value_type value_type;
            
            //---- Constructors
            RegionIterator(const Region* region)
                : base_iterator(region->getBound()){
            }
            
            //---- Overriden Methods
            inline edge_type* getNext(){
                edge_type* n = this->next;
                
                //--- If not the end we go foward
                if(this->hasNext()){
                    this->next = this->next->getNext();
                }
                
                //--- If we are at the begining then it's the end
                if(this->isStart(this->next)){
                    this->next = nullptr;
                }
                
                return n;
            }
        };
    public:
        typedef RegionIterator<HalfEdge> iterator_type;
        iterator_type begin(){
            return iterator_type(this);
        }
        iterator_type end(){
            return iterator_type(nullptr);
        }
        
    private:
        //---- Members
        HalfEdge* bound;
        
        //TODO: If we need to add hole to a region it will be here
        //std::List<HalfEdge*> holes; ou quelque chose comme ca
        
        //friend class EdgeIterator<HalfEdge*>;
    };
}

#endif
