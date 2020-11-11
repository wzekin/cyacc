// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <table.h>
#include <type.h>

#include "example.h"
#include "exampleConfig.h"

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main() {
  G g =
      G(set<Token>({
            Token(OpType::ADD),
            Token(OpType::ASTERISK),
            Token(OpType::L_PAREN),
            Token(OpType::R_PAREN),
            Token(NULL, Token::TokenType::Ident),
        }),
        set<char>({'E', 'e', 'T', 't', 'F'}), 'E',
        vector<pair<char, vector<V>>>({
            make_pair('E', vector<V>({V('T'), V('e')})),
            make_pair('e', vector<V>({V(Token(OpType::ADD)), V('T'), V('e')})),
            make_pair('e', vector<V>()),
            make_pair('T', vector<V>({V('F'), V('t')})),
            make_pair('t',
                      vector<V>({V(Token(OpType::ASTERISK)), V('F'), V('t')})),
            make_pair('t', vector<V>()),
            make_pair('F', vector<V>({
                               V(Token(OpType::L_PAREN)),
                               V('E'),
                               V(Token(OpType::R_PAREN)),
                           })),
            make_pair('F', vector<V>({
                               V(Token(NULL, Token::TokenType::Ident)),
                           })),
        }));
  auto first = getFirst(g);
  for (auto &k : first) {
    std ::cout << k.first << k.second.size() << std::endl;
  }
  auto follow = getFollow(g, first);
  for (auto &k : follow) {
    std ::cout << k.first << k.second.size() << std::endl;
    // for (auto &i : k.second) {
    //   std::cout << i << std::endl;
    // }
  }
  auto table = buildTable(g, first, follow);
  for (auto &c : g.V_n) {
    for (auto &p : g.V_t) {
      auto v = table.find(make_pair(c, p));
      if (v != table.end()) {
        cout << "1\t";
      } else {
        cout << "0\t";
      }
    }
    auto v = table.find(make_pair(c, Token(NULL,Token::TokenType::Null)));
    if (v != table.end()) {
      cout << "1\t";
    } else {
      cout << "0\t";
    }
    cout << endl;
  }
}
