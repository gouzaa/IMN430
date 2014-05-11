//
//  DCEL.h
//  IMN430-TP1
//
//  Created by Steven Aubertin on 2014-05-11.
//  Copyright (c) 2014 VISU_TEAM. All rights reserved.
//

#ifndef IMN430_TP1_DCEL_h
#define IMN430_TP1_DCEL_h

//---- Namespace to avoid name clash
namespace DCEL{
    /*
        Edges are oriented counterclockwise inside each face
        Because an edge may border two faces an edge is replace by two half edge
     */
    
    
    //---- Foward Declaration
    class edge;
    
    //---- An edge is a half edge
    typedef edge half_edge;
    
    class vertex{
    public:
        //---- Members
        half_edge* rep;
    };
    
    class face{
    public:
        half_edge* rep;
    };
    
    class edge{
    public:
        //---- Constructors
        edge(half_edge* oprev = nullptr, half_edge* onext = nullptr) :
            prev(oprev), next(onext){
        }
        
        //---- Members
        half_edge* prev;
        half_edge* next;
        half_edge* twin;
        vertex* tail;
        face* left;
    };
}


#endif
