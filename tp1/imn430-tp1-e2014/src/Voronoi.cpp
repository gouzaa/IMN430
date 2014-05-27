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
#include <limits>
#include <cmath>

//FIXME to remove
#include <iostream>

#include "Voronoi.h"
#include "DCEL.h"


//---------------SiteEvent---------------
VoronoiDiagram::SiteEvent::SiteEvent(DCEL::Vertex* pt)
    : VoronoiDiagram::VoronoiEvent(pt){
}
bool VoronoiDiagram::SiteEvent::isSiteEvent()const{
    return true;
}

//---------------CircleEvent---------------
VoronoiDiagram::CircleEvent::CircleEvent(DCEL::Vertex* triggerPoint, DCEL::Vertex center)
    : VoronoiDiagram::VoronoiEvent(triggerPoint)
    , mCenter(center)
{
}
bool VoronoiDiagram::CircleEvent::isSiteEvent()const{
    return false;
}
bool VoronoiDiagram::CircleEvent::isValid()const{
    return valid;
}
void VoronoiDiagram::CircleEvent::setValid(const bool isValid){
    valid = isValid;
}

//---------------VoronoiDiagram---------------
//void VoronoiDiagram::fortuneAlgorithm(const std::set<DCEL::Vertex*, DCEL::Vertex::Compare>& sites){
void VoronoiDiagram::fortuneAlgorithm(){
    if(sites.empty()){
        return;
    }

    std::vector<DCEL::Edge> edges;
    
    //Step1
    for(auto iter = sites.begin(); iter != sites.end(); iter++){
        mEventQueue.push(new SiteEvent(*iter));
    }
    
    //Step2
    VoronoiEvent* event = nullptr;
    while(!mEventQueue.empty()){
        event = mEventQueue.top();
        mEventQueue.pop();
        
        if(event->valid)
        {
            //Update fortune's line
            line = event->point->y;
        
            //Handle event
            if(event->isSiteEvent()){
                handleSiteEvent(event->point);
            }
            else{
                handleCircleEvent(reinterpret_cast<CircleEvent*>(event));
            }
        }
        delete event;
    }
    
    //Step3
    //finishEdge();
    
    //return edges;
}

double VoronoiDiagram::getIntersection(VoronoiDiagram::tree_type* par, const double y)const{
    /*VoronoiDiagram::tree_type* left = VParabola::GetLeftChild(par);
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
    return ((p->y < r->y) ? std::max(x1, x2) : std::min(x1, x2));*/
    return 0;
}

//FIXME: I guess we must handle the case were we have 2 points verticals and one to the side.
bool VoronoiDiagram::computeCircle(DCEL::Vertex v1, DCEL::Vertex v2,
                                   DCEL::Vertex v3, DCEL::Vertex& center,
                                   double& radius)
{
//    c->center.w = 1.0;
//    vertex *v1 = (vertex *)c->c.p1;
//    vertex *v2 = (vertex *)c->c.p2;
//    vertex *v3 = (vertex *)c->c.p3;
//    float bx = v1->xw; float by = v1->yw;
//    float cx = v2->xw; float cy = v2->yw;
//    float dx = v3->xw; float dy = v3->yw;
//    float temp = cx*cx+cy*cy;
//    float bc = (bx*bx + by*by - temp)/2.0;
//    float cd = (temp - dx*dx - dy*dy)/2.0;
//    float det = (bx-cx)*(cy-dy)-(cx-dx)*(by-cy);
//    if (fabs(det) < 1.0e-6) {
//        c->center.xw = c->center.yw = 1.0;
//        c->center.w = 0.0;
//        c->v1 = *v1;
//        c->v2 = *v2;
//        c->v3 = *v3;
//        return;
//    }
//    det = 1/det;
//    c->center.xw = (bc*(cy-dy)-cd*(by-cy))*det;
//    c->center.yw = ((bx-cx)*cd-(cx-dx)*bc)*det;
//    cx = c->center.xw; cy = c->center.yw;
//    c->radius = sqrt((cx-bx)*(cx-bx)+(cy-by)*(cy-by));
    
    //c->center.w = 1.0;
    bool valid = true;
    float bx = v1.x; float by = v1.y;
    float cx = v2.x; float cy = v2.y;
    float dx = v3.x; float dy = v3.y;
    float temp = cx*cx+cy*cy;
    float bc = (bx*bx + by*by - temp)/2.0;
    float cd = (temp - dx*dx - dy*dy)/2.0;
    float det = (bx-cx)*(cy-dy)-(cx-dx)*(by-cy);
    
    if (fabs(det) < 1.0e-6) {
        center.x = center.y = 1.0;
        valid = false;
    }
    else
    {
        det = 1/det;
        center.x = (bc*(cy-dy)-cd*(by-cy))*det;
        center.y = ((bx-cx)*cd-(cx-dx)*bc)*det;
        cx = center.x; cy = center.y;
        radius = sqrt((cx-bx)*(cx-bx)+(cy-by)*(cy-by));
    }
    return valid;
}

void VoronoiDiagram::addCircleEvent(VoronoiDiagram::status_type::iterator iter, bool isLeft)
{
    double radius = -1;
    DCEL::Vertex center;
    DCEL::Vertex first(iter->X(), iter->Y());
    
    //moving to the next  point
    isLeft ? iter-- : iter++;
    if (iter == mStatusTree.end()) //FIXME: to remove if it work
        return;
    
    DCEL::Vertex mid(iter->X(), iter->Y());
    
    isLeft ? iter-- : iter++;
    if (iter == mStatusTree.end()) //FIXME: to remove if it work
        return;
    
    DCEL::Vertex last(iter->X(), iter->Y());
    
    //TODO: compute the circle.
    if(computeCircle(first, mid, last, center, radius))
    {
        //TODO: add the circle event to the event queue and add the event to the tree
        std::cout << "center: " << center.x << " " << center.y << " " << " " << radius << " " <<  center.y + radius << std::endl;
    }
}

void VoronoiDiagram::handleSiteEvent(DCEL::Vertex* site){
    if(mStatusTree.empty())
    {
        mStatusTree.insert(site);
        return;
    }
    
    double minYInter = std::numeric_limits<double>::max();
    double yIntersec = minYInter;
    
//Step 2 check intersection with parabolas directly above pi
    status_type::iterator intersectedParabola = mStatusTree.begin();
    for(status_type::iterator i = mStatusTree.begin(); i != mStatusTree.end(); ++i){
        const double xDiff = i->X() - site->x;
        const double yDiff = i->Y() - site->y;
        yIntersec = ((xDiff*xDiff)+ (i->Y()*i->Y()) - (site->y*site->y));
        yIntersec /= (2*yDiff);
        if(minYInter > yIntersec)
        {
            minYInter = yIntersec;
            intersectedParabola = status_type::iterator(i);
        }
    }
    if(intersectedParabola->event != nullptr)
    {
        intersectedParabola->event->setValid(false);
    }
    
//Step 3 insert the new site in the tree
    mStatusTree.insert(site);
    //maybe there<s shit missing here
    
//Step 4 edges
    //TODO: step 4 edges
    
//Step 5 Create circles
    checkCircleEvent(intersectedParabola, site->x );
    checkCircleEvent(prev(intersectedParabola), site->x );
    checkCircleEvent(next(intersectedParabola), site->x );
    
}

//code very lightly modifed from http://www.cs.hmc.edu/~mbrubeck/voronoi.html
bool VoronoiDiagram::circle(DCEL::Vertex p1, DCEL::Vertex p2, DCEL::Vertex p3, double *radius, DCEL::Vertex *center)
{
    // Check that bc is a "right turn" from ab.
    if ((p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y) > 0)
        return false;
    
    // Algorithm from O'Rourke 2ed p. 189.
    double A = p2.x - p1.x,  B = p2.y - p1.y,
    C = p3.x - p1.x,  D = p3.y - p1.y,
    E = A*(p1.x+p2.x) + B*(p1.y+p2.y),
    F = C*(p1.x+p3.x) + D*(p1.y+p3.y),
    G = 2*(A*(p3.y-p2.y) - B*(p3.x-p2.x));
    
    if (G == 0) return false;  // Points are co-linear.
    
    // Compute the center of the circle.
    center->x = (D*E-B*F)/G;
    center->y = (A*F-C*E)/G;
    
    // o.x plus radius equals max x coordinate.
    *radius = center->y + sqrt( pow(p1.x - center->x, 2) + pow(p1.y - center->y, 2) );
    return true;
}

void VoronoiDiagram::checkCircleEvent(status_type::iterator parabola, double x)
{
    //If there's no site before or after, do not compute...
    if ((parabola == mStatusTree.begin()) || (parabola == std::prev(mStatusTree.end())))
        return;
    
    status_type::iterator tmp = prev(parabola);
    DCEL::Vertex a(tmp->X(), tmp->Y());
    DCEL::Vertex b(parabola->X(), parabola->Y());
    tmp = next(parabola);
    DCEL::Vertex c(tmp->X(), tmp->Y());
    
    DCEL::Vertex circleCenter;
    double circleRadius;
    
    if (circle(a, b, c, &circleRadius, &circleCenter) && (circleRadius > x)) {
        //Create a pointer to a new circle event
        CircleEvent* newEvent = new CircleEvent(new DCEL::Vertex(circleCenter.x, circleCenter.y - circleRadius), circleCenter/*???, parabola*/);
//        parabola->event = newEvent;
        parabola->setEvent(newEvent);
        //Add the event in the event queue
        mEventQueue.push(parabola->event);
    }
    
    
}

void VoronoiDiagram::handleCircleEvent(VoronoiDiagram::CircleEvent* event){
//    assert(event->node);
//    
//    if(event->isValid()){
//        assert(event->point);
//        DCEL::Vertex* pt = event->point;
//        
//        //Start a new segment
//        DCEL::Edge* segment = new DCEL::Edge();
//        
//        //Get arcs from the beachline
//        tree_type* node = event->node;
//        tree_type* left = node->getLeft();
//        tree_type* right = node->getRight();
//        
//        //Remove node from the beachline
//        if(left){
//            left->setRight(right);
//            checkCircle(left, pt);
//        }
//        if(right){
//            right->setLeft(left);
//            checkCircle(left, pt);
//        }
//    }
}

void VoronoiDiagram::checkCircle(tree_type* node, DCEL::Vertex* point){
//    assert(node && point);
//    
//    CircleEvent* event = node->event;
//    tree_type* left = node->getLeft();
//    tree_type* right = node->getRight();
//    
//    if(event && point != event->point){
//        event->setValid(false);
//    }
//    event = nullptr;
//    
//    if(left && right){
//        double y;
//        DCEL::Vertex* intersection = circle(
//            left->site,
//            node->site,
//            right->site,
//            &y
//        );
//        
//        if(intersection){
//            //node->event = new CircleEvent();
//        }
//    }
}

//DCEL::Vertex* VoronoiDiagram::circle(DCEL::Vertex* left, DCEL::Vertex* midlle, DCEL::Vertex* right, double* y_inter){
//    
//    //if(){}
//    
//    return nullptr;
//}
//
//






