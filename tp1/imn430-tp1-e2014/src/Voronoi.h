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

class VoronoiDiagram
{
public:
    //FIXME: stub
    class Dobacaracol
    {
    };
private:
    //////////Private classes +
    class VoronoiEvent
    {
    public:
        virtual bool isSiteEvent() = 0;
    }; //class VoronoiEvent
    
    class SiteEvent : public VoronoiEvent
    {
    public:
        SiteEvent( UTILS::Site aPoint);
        ~SiteEvent();
        
        bool isSiteEvent();
        
    protected:
    private:
        std::shared_ptr<UTILS::Site> mSite;
        
    }; // class SiteEvent
    
    class CircleEvent : VoronoiEvent
    {
    public:
        //TODO: a implanter quand on sera c'est quoi la leaf
        CircleEvent(noeudAVL<Dobacaracol>* aLeaf);
        ~CircleEvent();
        
        bool isSiteEvent();
        
    protected:
    private:
        noeudAVL<Dobacaracol>* mLeaf;
        
    }; // class CircleEvent
    //////////Private classes -
    
public:
    VoronoiDiagram(std::set<UTILS::Site, compareSite> site);
    
    void fortuneAlgorithm();
    
protected:
    void initEventQueue( std::set<UTILS::Site, compareSite> site );
    
private:
    std::queue <std::shared_ptr<VoronoiEvent> > mEventQueue;
    AVL<Dobacaracol> mTree;
    
    //TODO: add the DCEL here
    //DCEL mEdgeList;
};
#endif /* defined(__IMN430_TP1__Voronoi__) */
