//
//  Voronoi.h
//  IMN430-TP1
//
//  Created by François Bélanger on 2014-05-13.
//  Copyright (c) 2014 François Bélanger 94 245 437. All rights reserved.
//

#ifndef __IMN430_TP1__Voronoi__
#define __IMN430_TP1__Voronoi__

#include <set>
#include <queue>

#include "utils.h"
#include "DCEL.h"
#include "Tree.h"

using std::vector;

class VoronoiDiagram{
private:
    class VoronoiEvent{
    protected:
        //---- Constructors
        VoronoiEvent(DCEL::Vertex* pt, const bool isValid=true)
            : point(pt), valid(isValid){
        }
    public:
        //---- Desctructors
        virtual ~VoronoiEvent(){
            delete point;
        }
        
        //---- Accessors
        double getX()const{
            return point->x;
        }
        double getY()const{
            return point->y;
        }
        
        //---- Virtual Methods
        virtual bool isSiteEvent()const = 0;
        
        //---- Coparator Object
        struct EventCompare : public std::binary_function<VoronoiEvent*, VoronoiEvent*, bool>{
            bool operator()(const VoronoiEvent* e1, const VoronoiEvent* e2){
                return e1->point < e2->point;
            }
        };
        
        //---- Members
        DCEL::Vertex* point;//Point where the event occurs
        bool valid;//Define if this event is valid (Circle Event can be invalid)
    };
    
    class SiteEvent : public VoronoiEvent{
    public:
        SiteEvent(DCEL::Vertex* pt);
        bool isSiteEvent()const;
        
    };

    class CircleEvent : public VoronoiEvent{
    public:
        CircleEvent(DCEL::Vertex* pt);
        bool isSiteEvent()const;
        bool isValid()const;
        void setValid(const bool isValid);
        TreeNode<DCEL::Edge, DCEL::Vertex, CircleEvent>* node;
    };
    
public:
    //---- Typedefs
    typedef TreeNode<DCEL::Edge, DCEL::Vertex, CircleEvent> tree_type;
    
    //---- Constructors
    VoronoiDiagram(const double owidth = 500, const double oheigth = 500)
        : line(0), root(nullptr), width(owidth), height(oheigth){
    }
    
    //---- Public Methods
    /*
        This is the base of the algo.
        Call this method to generate the diagram using the fortune's algo
     */
    void fortuneAlgorithm(const std::set<DCEL::Vertex*, DCEL::Vertex::Compare>& sites);
    
private:
    //---- Private Methods
    tree_type* getLeftLeaf(const double site_x)const;
    double getIntersection(tree_type* par, const double y)const;
    void checkCircle(tree_type* node, DCEL::Vertex* point);
    DCEL::Vertex* circle(DCEL::Vertex* p1, DCEL::Vertex* p2, DCEL::Vertex* p3, double* y_inter);
    
    //---- Event handlers
    void handleSiteEvent(DCEL::Vertex* point);
    void handleCircleEvent(VoronoiDiagram::CircleEvent* event);
    
    //---- Members
    std::priority_queue<VoronoiEvent*> mEventQueue;//Handle events base on it's y coord
    tree_type* root;//To maintain the topology of the beach line
    vector<DCEL::Vertex*> vertices;//Keep track of the constructed VD
    double line;//sweep line
    
    double width;//Bouding width of the VD
    double height;//Bounding Heigth of the VD
};
#endif /* defined(__IMN430_TP1__Voronoi__) */
