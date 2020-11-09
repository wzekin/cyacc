#include <table.h>

map<char, set<char>> getFirst(G g) {
  map<char, set<char>> first;
  for (auto &vt : g.V_t) {
    first.insert(make_pair(vt, set<char>({vt})));
  }
  for (auto &vn : g.V_n) {
    first.insert(make_pair(vn, set<char>()));
  }
  int count = g.V_t.size();
  while (true) {
    for (auto &p : g.P) {
      if (p.second.length() == 0) {
        first[p.first].insert(THETA);
        continue;
      }
      auto v_t = g.V_t.find(p.second[0]);
      if (v_t != g.V_t.end()) {
        first[p.first].insert(p.second[0]);
        continue;
      }
    }
    int count_ = 0;
    for (auto &f : first) {
      count_ += f.second.size();
    }
    if (count_ == count) {
      break;
    }
    count = count;
  }
}