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
#include <cmath>

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
    : line(0), root(nullptr){
}

void VoronoiDiagram::fortuneAlgorithm(const std::set<DCEL::Vertex*, DCEL::Vertex::Compare>& sites)
{
    //Step0
    if(root){//TODO FAIRE UNE DESTRUCTEUR
        delete root;
    }
    for(auto v = vertices.begin(); v != vertices.end(); ++v){
        delete *v;
    }
    vertices.clear();
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        delete *e;
    }
    edges.clear();
    for(auto p = points.begin(); p != points.end(); ++p){
        delete  *p;
    }
    points.clear();
    
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
            insert(event->point);//HandleSite and STUFF
        }
        else{
           remove(event);
        }
        
        delete event;
    }
    
    //return edges;
}

double VoronoiDiagram::getIntersection(VoronoiDiagram::tree_type* par, const double y)const{
    VoronoiDiagram::tree_type* left = VParabola::GetLeftChild(par);
    VoronoiDiagram::tree_type* right= VParabola::GetRightChild(par);
 
    DCEL::Vertex* p = left->site;
    DCEL::Vertex* r = right->site;
 
    //Get parabola distance
    double dp = 2.0 * (p->y - y);
    const double a1 = 1.0 / dp;
    const double b1 = -2.0 * p->x / dp;
    const double c1 = y + dp / 4 + p->x * p->x / dp;
 
    //Get parabola distance
    dp = 2.0 * (r->y - y);
    const double a2 = 1.0 / dp;
    const double b2 = -2.0 * r->x/dp;
    const double c2 = y + dp / 4 + r->x * r->x / dp;
 
    //Compare Equation
    const double a = a1 - a2;
    const double b = b1 - b2;
    const double c = c1 - c2;
 
    //Compute discriminant
    const double disc = b*b - 4 * a * c;
    const double _2_A = 2*a;
    const double sqrt_disct = std::sqrt(disc);
    
    //Get point value
    const double x1 = (-b + sqrt_disct) / _2_A;
    const double x2 = (-b - sqrt_disct) / _2_A;
 
    //Getthe closest
    return ((p->y < r->y) ? std::max(x1, x2) : std::min(x1, x2));
}

VoronoiDiagram::tree_type* VoronoiDiagram::getLeftLeaf(const double site_x)const{
    tree_type* par = root;
    double x = 0.0;
    
    while(!par->isLeaf){
        x = getIntersection(par, line);
        par = ((x > site_x) ? par->left : par->right);
    }
    return par;
}

void VoronoiDiagram::insert(DCEL::Vertex* point){
    if(!root){
        root = new tree_type(point);
        return;
    }
    
    if(root->isLeaf){//TODO
        root->isLeaf = false;
        root->left = new tree_type(root->site);
        root->right = new tree_type(point);
    }
    
    //Get left arc
    getLeftLeaf();
}

void VoronoiDiagram::remove(VoronoiDiagram::VoronoiEvent* event){
    
}








