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

using namespace std;
using namespace UTILS;

//---------------SiteEvent---------------

VoronoiDiagram::SiteEvent::SiteEvent( UTILS::Site aPoint)
{
    mSite = std::shared_ptr<UTILS::Site> (new UTILS::Site(aPoint));
}
    
VoronoiDiagram::SiteEvent::~SiteEvent()
{
}
    
bool VoronoiDiagram::SiteEvent::isSiteEvent()
{
    return true;
}

//---------------CircleEvent---------------

//TODO: a implanter quand on sera c'est quoi la leaf
VoronoiDiagram::CircleEvent::CircleEvent(noeudAVL<Dobacaracol> *aLeaf)
{
    mLeaf = aLeaf;
}
    
VoronoiDiagram::CircleEvent::~CircleEvent()
{
}
    
bool VoronoiDiagram::CircleEvent::isSiteEvent()
{
    return false;
}

//---------------VoronoiDiagram---------------
VoronoiDiagram::VoronoiDiagram( set<Site, compareSite> site )
{
    //Step1
    for(auto iter = site.begin(); iter != site.end(); iter++)
    {
        shared_ptr<SiteEvent> event(new SiteEvent(*iter));
        mEventQueue.push(event);
    }
}

void VoronoiDiagram::fortuneAlgorithm()
{
    //TODO: a implanter de la sorte
    while(!mEventQueue.empty())
    {
        //FIXME la condition est a revoir
//        if(mEventQueue.back().isSiteEvent())
//        {
//            //handleSiteEvent
//            //qqc genre pop
//        }
//        else
//        {
//            //handleCircleEvent
//            //qqc genre pop
//        }
    }
}