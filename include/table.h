#ifndef TABLE_H
#define TABLE_H
#include <fmt/core.h>
#include <map>
#include <set>
#include <stack>
#include <type.h>
#include <utility>
#include <vector>

using namespace std;

#define THETA 0
#define END 1

class V {
public:
  V(char n) : type(Type::N) { this->value.n = n; }
  V(Token t) : type(Type::T) { this->value.t = t; }
  V(Token::TokenType t) : type(Type::T) { this->value.t = t; }
  V(OpType o) : type(Type::T) { this->value.t = o; }

  union Value {
    char n;  //非终结符数据
    Token t; //终结符数据

    Value() : n(0) {}
  };

  enum class Type {
    N, //非终结符
    T  //终结符
  };

  inline bool is_n() const { return this->type == Type::N; }
  inline bool is_t() const { return this->type == Type::T; }

  inline char as_n() const { return this->value.n; }
  inline Token as_t() const { return this->value.t; }
  inline bool operator==(const V &other) const {
    if (this->is_t() && other.is_t()) {
      return this->as_t() == other.as_t();
    } else if (this->is_n() && other.is_n()) {
      return this->as_n() == other.as_n();
    } else {
      return false;
    }
  }

private:
  Value value;
  Type type;
};

// 文法
class G {
public:
  G(set<Token> V_t, set<char> V_n, char start, vector<pair<char, vector<V>>> P)
      : V_t(V_t), V_n(V_n), start(start), P(P){};

  set<Token> V_t; //终结符
  set<char> V_n;  //非终结符

  char start;

  vector<pair<char, vector<V>>> P; //产生式
};

typedef map<pair<char, Token>, vector<V>> Table;

map<char, set<Token>> getFirst(G &g);
map<char, set<Token>> getFollow(G &g, map<char, set<Token>> &first);
Table buildTable(G &g, map<char, set<Token>> &first,
                 map<char, set<Token>> &follow);

bool test(Table &M, char start, vector<Token> const &w);

template <> struct fmt::formatter<V> : formatter<string_view> {
  template <typename FormatContext>
  auto format(const V &v, FormatContext &ctx) {
    string_view s = "unknown";
    if (v.is_n()) {
      string ss;
      ss.push_back(v.as_n());
      s = ss;
    } else if (v.is_t()) {
      return format_to(ctx.out(), "{}", v.as_t());
    }
    return formatter<string_view>::format(s, ctx);
  }
};

#endif