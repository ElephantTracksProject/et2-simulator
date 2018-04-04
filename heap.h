
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class CCNode;
class HeapObject;

typedef map<int, HeapObject *> HeapMap;

class HeapObject
{
private:

  int id;
  string type;
  int bytes;
  bool live;

  int alloc_time;
  CCNode * alloc_cc;
  
  int death_time;
  CCNode * death_cc;
  
  // -- union/find stuff
  HeapObject * parent;
  int rank;
  HeapObject * pointsTo;

  int size;
  int num_dead;

public:  

  static HeapMap theHeap;

public:

  HeapObject(int i /*, const string & ty, int sz, int a_time*/ )
    : id(i),
      type("UNKNOWN"),
      bytes(-1),
      live(true),
      alloc_time(-1),
      alloc_cc(0),
      death_time(-1),
      death_cc(0),
      parent(0), 
      rank(0),
      pointsTo(0),
      size(1),
      num_dead(0)
  {}

  int getId() const { return id; }
  
  const string & getType() const { return type; }

  void setAlloc(int a_time, int sz, const string & ty) {
    alloc_time = a_time;
    bytes = sz;
    type = ty;
  }
  
  void setDead(int d_time) { 
    live = false;
    death_time = d_time;
  }

  bool isDead() const { return live; }

  int getAllocTime() const { return alloc_time; }
  int getDeathTime() const { return death_time; }

  CCNode * getAllocCC() const { return alloc_cc; }
  void setAllocCC(CCNode * cc) { alloc_cc = cc; }
  
  CCNode * getDeathCC() const { return death_cc; }
  void setDeathCC(CCNode * cc) { death_cc = cc; }
  
  void incRank() { rank++; }
  int getRank() const { return rank; }

  void setParent(HeapObject * new_parent) {
    parent = new_parent;
  }

  HeapObject * getParent() const { return parent; }
  bool isRoot() const { return parent == 0; }

  HeapObject * getPointsTo() const { return pointsTo; }

  void setSize(int new_size) { size = new_size; }
  int getSize() const { return size; }

  void setNumDead(int nd) { num_dead = nd; }
  void incNumDead() { num_dead++; }
  int getNumDead() const { return num_dead; }

  // -- Global heap
  
  static HeapObject * DemandHeapObject(int object_id);
  
  // -- Disjoint sets operations

  static HeapObject * Find(HeapObject * obj);
  static HeapObject * Union(HeapObject * one, HeapObject * two);
  static HeapObject * RecUnion(HeapObject * one, HeapObject * two);
  
  void setPointsTo(HeapObject * target);
  

};

#endif
