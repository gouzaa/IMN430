//
//  DCEL.h
//  IMN430-TP1
//
//  Created by Steven Aubertin on 2014-05-11.
//  Copyright (c) 2014 VISU_TEAM. All rights reserved.
//

#ifndef IMN430_TP1_DCEL_h
#define IMN430_TP1_DCEL_h

#include <cassert>

//---- Namespace to avoid name clash
namespace DCEL{
    /*
        Edges are oriented counterclockwise inside each face
        Because an edge may border two faces an edge is replace by two half edge
     */
    
    
    //---- Foward Declaration
    class Edge;
    
    //---- An edge is a half edge
    typedef Edge HalfEdge;
    
    class Vertex{
    public:
        //---- Constructors
        Vertex(HalfEdge* oedge = nullptr) :
            edge(oedge){
        }
        
        //---- Members
        HalfEdge* edge;
    };
    
    class Face{
    public:
        //---- Constructors
        Face(HalfEdge* obound = nullptr) :
            bound(obound){
        }
        
        //---- Members
        HalfEdge* bound;
    };
    
    class Edge{
    public:
        //---- Constructors
        Edge(HalfEdge* oprev = nullptr, HalfEdge* onext = nullptr) :
            prev(oprev), next(onext), twin(nullptr), tail(nullptr), left(nullptr){
        }
        
        //---- Mutators
        inline void setTwin(HalfEdge* twin){
            assert(twin);
            
            this->twin = twin;
            twin->twin = this;
        }
        inline void setNext(HalfEdge* next){
            assert(next);
            
            this->next = next;
            next->prev = this;
        }
        inline void setPrev(HalfEdge* prev){
            assert(prev);
            
            this->prev = prev;
            prev->next = this;
        }
        
        //---- Members
        HalfEdge* prev;
        HalfEdge* next;
        HalfEdge* twin;
        Vertex*   tail;//Or origin
        Face* left;
    };
}


#endif
