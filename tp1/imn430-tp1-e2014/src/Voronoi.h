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

#include "abr.h"
#include "utils.h"
#include "DCEL.h"

class VoronoiDiagram
{
public:
private:
    //////////Private classes +
    class VoronoiEvent
    {
    protected:
        VoronoiEvent(DCEL::Vertex* pt = nullptr)
            : point(pt){
        }
    public:
        virtual ~VoronoiEvent(){
            if(point){
                delete point;
                point = nullptr;
            }
        }
        
        virtual bool isSiteEvent() = 0;
        
        struct EventCompare : public std::binary_function<VoronoiEvent*, VoronoiEvent*, bool>{
            bool operator()(const VoronoiEvent* e1, const VoronoiEvent* e2){
                return e1->point < e2->point;
            }
        };
        
        DCEL::Vertex* point;//Point where the event occurs
    }; //class VoronoiEvent
    
    class SiteEvent : public VoronoiEvent
    {
    public:
        SiteEvent(DCEL::Vertex* pt);
        
        bool isSiteEvent();
        
    }; // class SiteEvent
    
    class CircleEvent : VoronoiEvent
    {
    public:
        //TODO: a implanter quand on sera c'est quoi la leaf
        CircleEvent(DCEL::Vertex* pt);
        
        bool isSiteEvent();
        
    }; // class CircleEvent
    //////////Private classes -
    
public:
    VoronoiDiagram();
    
    void fortuneAlgorithm(const std::set<DCEL::Vertex*, DCEL::Vertex::Compare>& sites);
    
private:
    std::priority_queue<VoronoiEvent*> mEventQueue;
    double line;
    vector<DCEL::Vertex*> vertices;
    vector<DCEL::Edge*> edges;
    abr<DCEL::Vertex*> root;//Parabolassss
};
#endif /* defined(__IMN430_TP1__Voronoi__) */
