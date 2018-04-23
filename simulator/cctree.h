#ifndef ET2_SIMULATOR_SIMULATOR_CCTREE_H_
#define ET2_SIMULATOR_SIMULATOR_CCTREE_H_

#include "simulator/ccnode.h"
#include "simulator/heap.h"

namespace et_simulator {
// Context tree.
class CCTree {
 private:
  CCNode * root;
  std::map<int, int> thread_id_map;

  //  Multi-threaded stack
  typedef std::map<int, CCNode *> StackMap;
  StackMap stack;
  //  Map from thread objects to the context in which start() was called
  StackMap thread_starts;

  //  Global counters
  int64_t total_alloc_size = 0;
  int64_t no_alloc = 0;

  int thread_start_method_id = 0;
  int last_method_id = 0;

  int64_t thread_number = 0;


  int depth = 0;
  int64_t time = 0;
  bool in_death_records = false;
  int64_t last_thread_id = 0;
  int64_t record = 0;

  void LogStack(CCNode * node);
 public:
  CCTree() {
    root = new CCNode(0, 0, 0, 0);
    last_thread_id = 0;
    stack[0] = root;
    thread_starts[0] = root;
  }

  int get_depth() { return depth; }
  int get_time() { return time; }
  int64_t get_thread_number() { return thread_number; }
  int64_t get_last_thread_id() { return last_thread_id; }

  void HandleObjectAllocation(int object_id, int size,
                              std::string type, int thread_id);
  void HandleObjectDeath(int object_id);
  void HandleObjectUpdate(int old_target, int object_id,
                          int new_target, int target_id);
  void HandleMethodEntry(int method_id, int object_id, int thread_id);
  void HandleMethodExit(int method_id, int object_id, int thread_id);

  //  Output methods

  void PrintTree(CCNode * node, int depth);
  void EmitPath(CCNode * node, std::ofstream & out);
  void EmitTreeMapTM3(CCNode * node, std::ofstream & out);
  void EmitTreeMapTM3(std::ofstream & out);

  //  treeml output
  void EmitTreeML(CCNode * node, std::ofstream & out, int depth);
  void emitTreeML(std::ofstream & out);

  //  JSON output
  void EmitTreeJSON(CCNode * node, std::ofstream & out, int depth);
  void EmitTreeJSON(std::ofstream & out);
};
}  // namespace et_simulator
#endif  // ET2_SIMULATOR_SIMULATOR_CCTREE_H
