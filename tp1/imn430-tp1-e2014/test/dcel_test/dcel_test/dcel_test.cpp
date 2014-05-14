//
//  dcel_test.cpp
//  dcel_test
//
//  Created by Steven Aubertin on 2014-05-13.
//  Copyright (c) 2014 Steven Aubertin. All rights reserved.
//

#include "dcel_test.h"
#include "../../../src/DCEL.h"
#include <vector>
#include <memory>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;
using namespace DCEL;

HalfEdge* edge_factory(Vertex* v1, Vertex* v2){
    auto e11 = new HalfEdge();
    auto e12 = new HalfEdge();//twin
    
    e11->setOrigin(v1);
    e12->setOrigin(v2);
    
    v1->edge = e11;
    v2->edge = e12;
    e11->setTwin(e12);
    
    return e11;
}

shared_ptr<Region> triangle_factory(Vertex* v1, Vertex* v2, Vertex* v3){
    auto e11 = edge_factory(v1, v2);
    auto e21 = edge_factory(v2, v3);
    auto e31 = edge_factory(v3, v1);
    
    auto triangle = shared_ptr<Region>(new Region(e11));
    e11->setNext(e21);
    e21->setNext(e31);
    e31->setNext(e11);
    
    return triangle;
}


int main(){
    //Building a triangle for tests
    auto v1 = new Vertex(10, 0);
    auto v2 = new Vertex(20, 20);
    auto v3 = new Vertex(0, 10);
    
    auto triangle = triangle_factory(v1, v2, v3);
    
    int i = 0;
    for(auto edge = triangle->begin(); edge.hasNext(); ++edge){
        cout << "edge "<< i++ <<" " << (*edge)->getOrigin()<< ", " << (*edge)->getTwin()->getOrigin() << endl;
    }
    cout << endl;
    
    
    //Adding a vertex in a region
    auto v4 = new Vertex(10, 10, 0);
    auto e41 = new HalfEdge();
    auto e42 = new HalfEdge();

    v4->edge = e41;

    e41->setOrigin(v4);
//    e41->setNext(e11->getNext());
//    e41->setPrev(e42.get());
//    e41->setRegion(triangle.get());
//    
//    e42->setOrigin(e11->getOrigin());
//    e42->setNext(e41.get());
//    e42->setPrev(e11->getPrev());
//    e42->setRegion(triangle.get());
//    
//    e11->getPrev()->setNext(e42.get());
//    e11->getNext()->setPrev(e41.get());
//    
//    auto e41t = shared_ptr<HalfEdge>(new HalfEdge());
//    
//    e41->setTwin(e41t.get());
    //delete e11
    
    delete v1;
    delete v2;
    delete v3;
    
    for (auto i = triangle->begin(); i.hasNext(); ++i) {
        if((*i)->getTwin()){
            delete (*i)->getTwin();
        }
        delete *i;
    }
    
    return 0;
}










