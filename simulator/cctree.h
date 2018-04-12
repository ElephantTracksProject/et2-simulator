
#ifndef CCTREE_H_
#define CCTREE_H_

#include "ccnode.h"
#include "heap.h"


// Context tree.
class CCTree {
 private:
  CCNode * root;
  std::map<int, int> threadIdNumbering;

  // Multi-threaded stack
  typedef std::map<int, CCNode *> StackMap;
  StackMap theStack;
  // Map from thread objects to the context in which start() was called
  StackMap threadStarts;

  // Global counters
  int64_t total_alloc_size = 0;
  int64_t no_alloc = 0;

  int thread_start_method_id = 0;
  int thread_number = 0;


  int depth = 0;
  int64_t time = 0;
  bool in_death_records = false;
  int64_t last_thread_id = 0;
  int64_t record = 0;

 public:
  CCTree() {
    root = new CCNode(0, 0, 0, 0);
    last_thread_id = 0;
    theStack[0] = root;
    threadStarts[0] = root;
  }

  void handle_object_allocation(int object_id, int size, std::string type,
                                int thread_id, int method_id);
  void handle_object_death(int object_id);
  void handle_object_update(int old_target, int object_id,
                            int new_target, int target_id);
  void handle_method_entry(int method_id, int object_id, int thread_id);
  void handle_method_exit(int method_id, int object_id, int thread_id);

  // Output methods

  void printTree(CCNode * node, int depth);
  void printStack(CCNode * node);

  void emitPath(CCNode * node, std::ofstream & out);
  void emitTreeMapTM3Rec(CCNode * node, std::ofstream & out);
  void emitTreeMapTM3(std::ofstream & out);

  //     treeml output
  void emitTreeMLRec(CCNode * node, std::ofstream & out, int depth);
  void emitTreeML(std::ofstream & out);

  //     JSON output
  void emitTreeJSONRec(CCNode * node, std::ofstream & out, int depth);
  void emitTreeJSON(std::ofstream & out);
};

#endif
