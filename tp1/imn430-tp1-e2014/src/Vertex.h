//
//  Vertex.h
//  IMN430_tp1
//
//  Created by Steven Aubertin on 2014-05-13.
//  Copyright (c) 2014 Steven Aubertin. All rights reserved.
//

#ifndef IMN430_tp1_Vertex_h
#define IMN430_tp1_Vertex_h

#include "EdgeIterator.h"

namespace DCEL {
    class Vertex{
    public:
        //---- Constructors
        Vertex(HalfEdge* oedge = nullptr) :
        edge(oedge)
        ,   x(0)
        ,   y(0)
        ,   z(0)
        {
        }
        
        Vertex(int xPos, int yPos, HalfEdge* oedge = nullptr, int zPos = 0) :
        edge(oedge)
        ,   x(xPos)
        ,   y(yPos)
        ,   z(zPos)
        {
        }
        
        //---- Accessors
        inline HalfEdge* getEdge()const{
            return this->edge;
        }
        
        //---- Iterators
    private:
        template<class EdgeT>
        class VertexIterator : public EdgeIterator<Vertex, EdgeT>{
        public:
            //---- typedefs
            typedef EdgeIterator<Vertex, EdgeT> base_iterator;
            typedef typename base_iterator::edge_type edge_type;
            typedef typename base_iterator::value_type value_type;
            
            //---- Constructors
            VertexIterator(const Vertex* vertex)
                : base_iterator(vertex->getEdge()){
            }
            
            //---- Overriden Methods
            inline edge_type* getNext(){
                edge_type* n = this->next;
                
                if(this->hasNext()){
                    edge_type* twin = this->next->getTwin();
                    this->next = twin->getNext();
                }
                
                if(this->isStart(this->next)){
                    this->next = nullptr;
                }
                
                return n;
            }
        };
    public:
        typedef VertexIterator<HalfEdge> iterator_type;
        iterator_type begin(){
            return iterator_type(this);
        }
        iterator_type end(){
            return iterator_type(nullptr);
        }
        
        //---- Members
        HalfEdge* edge;
        
        int x;
        int y;
        int z;
    };
}

#endif
