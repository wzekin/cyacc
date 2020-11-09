#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

#define THETA 0
#define END 1 

// 文法
class G {
public:
  set<char> V_t; //终结符
  set<char> V_n; //非终结符

  map<char, string> P; //产生式
};

map<char, set<char>> getFirst(G g);
map<char, set<char>> getFollow(G g);
map<pair<char, char>, string> buildTable(map<char, set<char>> first,
                                         map<char, set<char>> follow);