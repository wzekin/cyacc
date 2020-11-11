#include <table.h>

map<char, set<Token>> getFirst(G &g) {
  map<char, set<Token>> first;
  for (auto &vn : g.V_n) {
    first.insert(make_pair(vn, set<Token>()));
  }
  int count = g.V_t.size();
  while (true) {
    for (auto &p : g.P) {
      if (p.second.size() == 0) {
        first[p.first].insert(Token(NULL, Token::TokenType::Null));
        continue;
      }
      if (p.second[0].is_t()) {
        first[p.first].insert(p.second[0].as_t());
      } else {
        size_t i = 0;
        bool has_theta = true;
        while (has_theta) {
          has_theta = false;
          if (i >= p.second.size()) {
            first[p.first].insert(Token(NULL, Token::TokenType::Null));
            break;
          }
          for (auto &c : first[p.second[i].as_n()]) {
            if (c.is_null()) {
              has_theta = true;
            } else {
              first[p.first].insert(c);
            }
          }
          i++;
        }
      }
    }
    int count_ = 0;
    for (auto &f : first) {
      count_ += f.second.size();
    }
    if (count_ == count) {
      break;
    }
    count = count_;
  }
  return first;
}

map<char, set<Token>> getFollow(G &g, map<char, set<Token>> &first) {
  map<char, set<Token>> follow;
  for (auto &vn : g.V_n) {
    follow.insert(make_pair(vn, set<Token>()));
  }
  follow[g.start].insert(Token(NULL, Token::TokenType::Null));
  int count = 1;
  while (true) {
    for (auto &p : g.P) {
      for (auto v = p.second.begin(); v != p.second.end(); v++) {
        if (v->is_t()) {
          continue;
        }
        size_t i = 1;
        bool has_theta = true;
        while (has_theta) {
          has_theta = false;
          if (v + i == p.second.end()) {
            for (auto &i : follow[p.first]) {
              follow[v->as_n()].insert(i);
            }
            break;
          }
          if ((v + i)->is_t()) {
            follow[v->as_n()].insert((v + i)->as_t());
          } else {
            for (auto &c : first[(v + i)->as_n()]) {
              if (c.is_null()) {
                has_theta = true;
              } else {
                follow[v->as_n()].insert(c);
              }
            }
          }
          i++;
        }
      }
    }
    int count_ = 0;
    for (auto &f : follow) {
      count_ += f.second.size();
    }
    if (count_ == count) {
      break;
    }
    count = count_;
  }
  return follow;
}

map<pair<char, Token>, vector<V>> buildTable(G &g, map<char, set<Token>> &first,
                                             map<char, set<Token>> &follow) {
  map<pair<char, Token>, vector<V>> table;
  for (auto &p : g.P) {
    size_t i = 0;
    bool has_theta = true;
    while (has_theta) {
      has_theta = false;
      if (i >= p.second.size()) {
        for (auto &f : follow[p.first]) {
          table[make_pair(p.first, f)] = p.second;
        }
        break;
      }
      if (p.second[i].is_t()) {
        table[make_pair(p.first, p.second[i].as_t())] = p.second;
      } else {
        for (auto &c : first[p.second[i].as_n()]) {
          if (c.is_null()) {
            has_theta = true;
          } else {
            table[make_pair(p.first, c)] = p.second;
          }
        }
      }
      i++;
    }
  }
  return table;
}