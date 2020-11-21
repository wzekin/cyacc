#include <lr.h>

inline Token at(vector<Token> const &w, size_t index) {
  if (index >= w.size()) {
    return Token(Token::TokenType::Null);
  } else {
    return w[index];
  }
}

bool LR::test(vector<Token> const &w) {
  vector<pair<unsigned, V>> s;
  s.push_back(make_pair(0, 'S'));
  size_t ip = 0;
  while (1) {
    auto S = s[s.size() - 1];
    auto a = at(w, ip);
    auto todo = action[make_pair(S.first, a)];
    if (todo.type == Action::Type::S) {
      s.push_back(make_pair(todo.index, a));
      ip++;
      cout << fmt::format("[移进]{}", a) << endl;
    } else if (todo.type == Action::Type::R) {
      auto p = P[todo.index];
      for (size_t i = 0; i < p.second.size(); i++) {
        s.pop_back();
      }
      auto now = s[s.size() - 1];
      s.push_back(make_pair(goto_[make_pair(now.first, p.first)], p.first));
      cout << fmt::format("[规约]{}->{}", p.first, fmt::join(p.second, ""))
           << endl;
    } else if (todo.type == Action::Type::ACC) {
      return true;
    } else {
      return false;
    }
  }
}

map<pair<unsigned, Token>, Action>
make_action(vector<Token> tokens, vector<vector<const char *>> table) {
  map<pair<unsigned, Token>, Action> actions;
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < tokens.size(); j++) {
      if (table[i][j] != NULL) {
        actions[make_pair(i, tokens[j])] = table[i][j];
      }
    }
  }
  return actions;
}

map<pair<unsigned, char>, unsigned> make_goto(vector<char> chars,
                                              vector<vector<unsigned>> table) {
  map<pair<unsigned, char>, unsigned> gotos;
  for (size_t i = 0; i < table.size(); i++) {
    for (size_t j = 0; j < chars.size(); j++) {
      if (table[i][j] != UINT32_MAX) {
        gotos[make_pair(i, chars[j])] = table[i][j];
      }
    }
  }
  return gotos;
}