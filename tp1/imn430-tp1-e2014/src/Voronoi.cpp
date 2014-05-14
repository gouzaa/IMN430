//
//  Voronoi.cpp
//  IMN430-TP1
//
//  Created by François Bélanger on 2014-05-13.
//  Copyright (c) 2014 François Bélanger 94 245 437. All rights reserved.
//

//TODO: renommer les fichiers !!!

#include <set>
#include <queue>

#include "utils.h"
#include "Voronoi.h"
#include "DCEL.h"

using namespace std;
using namespace UTILS;

//---------------SiteEvent---------------

VoronoiDiagram::SiteEvent::SiteEvent(DCEL::Vertex* pt)
    : VoronoiDiagram::VoronoiEvent(pt){
}
    
bool VoronoiDiagram::SiteEvent::isSiteEvent()
{
    return true;
}

//---------------CircleEvent---------------

//TODO: a implanter quand on sera c'est quoi la leaf
VoronoiDiagram::CircleEvent::CircleEvent(DCEL::Vertex* pt)
    : VoronoiDiagram::VoronoiEvent(pt){
}
    
bool VoronoiDiagram::CircleEvent::isSiteEvent()
{
    return false;
}

//---------------VoronoiDiagram---------------
VoronoiDiagram::VoronoiDiagram()
    : line(0){
}

void VoronoiDiagram::fortuneAlgorithm(const std::set<DCEL::Vertex*, DCEL::Vertex::Compare>& sites)
{
    //Step0
    root.clear();
    for(auto v = vertices.begin(); v != vertices.end(); ++v){
        delete *v;
    }
    vertices.clear();
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        delete *e;
    }
    edges.clear();
    
    //Step1
    for(auto iter = sites.begin(); iter != sites.end(); iter++){
        mEventQueue.push(new SiteEvent(*iter));
    }
    
    //Step2
    VoronoiEvent* event = nullptr;
    while(!mEventQueue.empty()){
        event = mEventQueue.top();
        mEventQueue.pop();
        
        //Update fortune's line
        line = event->point->y;
        
        //Handle event
        if(event->isSiteEvent()){
            insert(event->point);
        }
        else{
           remove(event);
        }
        
        delete event;
    }
    
    //return edges;
}

void VoronoiDiagram::insert(DCEL::Vertex* point){
    if(root.empty()){
        root.insert(point);
        return;
    }
    
    //Determiner si root est une leaf...
}

void VoronoiDiagram::remove(VoronoiDiagram::VoronoiEvent* event){
    
}








