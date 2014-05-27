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
            //FIXME: we don't delete the point here because it belong to the
            //          main...
            //delete point;
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
        bool isValid()const { return true; };
        //---- Comparator Object
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
        CircleEvent(DCEL::Vertex* pt, DCEL::Vertex center);
        bool isSiteEvent()const;
        bool isValid()const;
        void setValid(const bool isValid);
        TreeNode<DCEL::Edge, DCEL::Vertex, CircleEvent>* node;
        DCEL::Vertex mCenter;
    };
    
public:
    //---- Typedefs
    typedef TreeNode<DCEL::Edge, DCEL::Vertex, CircleEvent> tree_type;
    typedef std::set<tree_type, tree_type::Compare> status_type;
    
    //---- Constructors
    VoronoiDiagram(const double owidth = 500, const double oheigth = 500)
        : line(0), root(nullptr), width(owidth), height(oheigth) {
    }
    
    //---- Public Methods
    /*
        This is the base of the algo.
        Call this method to generate the diagram using the fortune's algo
     */
    //FIXME: to delete if it work
    //void fortuneAlgorithm(const std::set<DCEL::Vertex*, DCEL::Vertex::Compare>& sites);
    void fortuneAlgorithm();
    void addSite(DCEL::Vertex vertex) {sites.insert(new DCEL::Vertex(vertex));}
    
private:
    //---- Private Methods
    //FIXME to remove
    double getIntersection(tree_type* par, const double y)const;
    //FIXME to remove
    void checkCircle(tree_type* node, DCEL::Vertex* point);
    bool circle(DCEL::Vertex p1, DCEL::Vertex p2, DCEL::Vertex p3, double *radius, DCEL::Vertex *center);
    bool computeCircle(DCEL::Vertex v1, DCEL::Vertex v2,
                       DCEL::Vertex v3, DCEL::Vertex& center,
                       double& radius);
    void addCircleEvent(status_type::iterator iter, bool isLeft);
    
    //---- Event handlers
    void handleSiteEvent(DCEL::Vertex* point);
    void handleCircleEvent(VoronoiDiagram::CircleEvent* event);
    void checkCircleEvent(status_type::iterator site, double x);
    
    //---- Members
    std::priority_queue<VoronoiEvent*> mEventQueue;//Handle events base on it's y coord

    tree_type* root;//To maintain the topology of the beach line
    status_type mStatusTree;
    vector<DCEL::Vertex*> vertices;//Keep track of the constructed VD
    double line;//sweep line
    
    double width;//Bouding width of the VD
    double height;//Bounding Heigth of the VD
    std::set<DCEL::Vertex*, tree_type::Compare> sites;
};
#endif /* defined(__IMN430_TP1__Voronoi__) */
