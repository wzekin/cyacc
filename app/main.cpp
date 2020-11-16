// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

#include "lr.h"
#include "table.h"
#include <iostream>
#include <stdlib.h>
#include <type.h>

#include "example.h"
#include "exampleConfig.h"

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main() {
  G g = G(set<Token>({
              Token(OpType::ADD),
              Token(OpType::SUB),
              Token(OpType::ASTERISK),
              Token(OpType::DIV),
              Token(OpType::L_PAREN),
              Token(OpType::R_PAREN),
              Token(Token::TokenType::Number),
          }),
          set<char>({'E', 'A', 'B', 'T', 'C', 'D', 'F'}), 'E',
          vector<pair<char, vector<V>>>({
              make_pair('E', vector<V>({'T', 'A'})),
              make_pair('A', vector<V>({'B', 'A'})),
              make_pair('A', vector<V>()),
              make_pair('B', vector<V>({OpType::SUB, 'T'})),
              make_pair('B', vector<V>({OpType::ADD, 'T'})),

              make_pair('T', vector<V>({'F', 'C'})),
              make_pair('C', vector<V>({'D', 'C'})),
              make_pair('C', vector<V>()),
              make_pair('D', vector<V>({OpType::ASTERISK, 'F'})),
              make_pair('D', vector<V>({OpType::DIV, 'F'})),

              make_pair('F', vector<V>({
                                 OpType::L_PAREN,
                                 'E',
                                 OpType::R_PAREN,
                             })),
              make_pair('F', vector<V>({
                                 Token::TokenType::Number,
                             })),
          }));
  auto first = getFirst(g);
  auto follow = getFollow(g, first);
  auto table = buildTable(g, first, follow);

  auto t = vector<Token>({
      Token::TokenType::Number,
      OpType::ADD,
      Token::TokenType::Number,
      OpType::ASTERISK,
      Token::TokenType::Number,
  });
  cout << test(table, 'E', t) << endl;

  auto lr = LR();
  // lr.action = map<pair<unsigned, Token>, Action>({
  //     {{0, OpType::ADD}, "s6"},
  //     {{0, OpType::L_PAREN}, "s12"},
  //     {{1, OpType::ADD}, "s2"},
  //     {{1, OpType::SUB}, "s9"},
  //     {{1, Token::TokenType::Null}, "acc"},
  //     {{2, OpType::ADD}, "s6"},
  //     {{2, OpType::L_PAREN}, "s12"},
  //     {{3, OpType::ADD}, "r1"},
  //     {{3, OpType::SUB}, "r1"},
  //     {{3, OpType::ASTERISK}, "s4"},
  //     {{3, OpType::DIV}, "s11"},
  //     {{3, OpType::R_PAREN}, "r1"},
  //     {{4, OpType::L_PAREN}, "s6"},
  //     {{4, OpType::L_PAREN}, "s6"},
  // });
  lr.action = make_action(
      vector<Token>({OpType::ADD, OpType::SUB, OpType::ASTERISK, OpType::DIV,
                     OpType::L_PAREN, OpType::R_PAREN, Token::TokenType::Number,
                     Token::TokenType::Null}),
      vector<vector<const char *>>({
          {0, 0, 0, 0, "s6", 0, "s12", 0},
          {"s2", "s9", 0, 0, 0, 0, 0, "acc"},
          {0, 0, 0, 0, "s6", 0, "s12", 0},
          {"r1", "r1", "s4", "s11", 0, "r1", 0, "r1"},
          {0, 0, 0, 0, "s6", 0, "s12", 0},
          {"r4", "r4", "r4", "r4", 0, "r4", 0, "r4"},
          {0, 0, 0, 0, "s6", 0, "s12", 0},
          {"s2", "s9", 0, 0, 0, "s8", 0, 0},
          {"r7", "r7", "r7", "r7", 0, "r7", 0, "r7"},
          {0, 0, 0, 0, "s6", 0, "s12", 0},
          {"r3", "r3", 0, 0, 0, "r3", 0, 0},
          {0, 0, 0, 0, "s6", 0, "s12", 0},
          {"r8", "r8", "r8", "r8", 0, "r8", 0, "r8"},
          {"r5", "r5", "r5", "r5", 0, "r5", 0, "r5"},
          {"r6", "r6", "r6", "r6", 0, "r6", 0, "r6"},
          {"r2", "r2", "s4", "s11", 0, "r2", 0, "r2"},
      }));
  lr.goto_ = make_goto(vector<char>({'E', 'T', 'F'}),
                       vector<vector<unsigned>>{
                           {1, 10, 14},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, 3, 14},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, UINT32_MAX, 5},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {7, 10, 14},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, 15, 14},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, UINT32_MAX, 13},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                           {UINT32_MAX, UINT32_MAX, UINT32_MAX},
                       });
  lr.P = vector<pair<char, vector<V>>>({
      make_pair('S', vector<V>({'E'})),
      make_pair('E', vector<V>({'E', OpType::ADD, 'T'})),
      make_pair('E', vector<V>({'E', OpType::SUB, 'T'})),
      make_pair('E', vector<V>({'T'})),
      make_pair('T', vector<V>({'T', OpType::ASTERISK, 'F'})),
      make_pair('T', vector<V>({'T', OpType::DIV, 'F'})),
      make_pair('T', vector<V>({'F'})),
      make_pair('F', vector<V>({
                         OpType::L_PAREN,
                         'E',
                         OpType::R_PAREN,
                     })),
      make_pair('F', vector<V>({
                         Token::TokenType::Number,
                     })),
  });

  auto t1 = vector<Token>({
      Token::TokenType::Number,
      OpType::ADD,
      Token::TokenType::Number,
  });

  cout << lr.test(t1) << endl;
}
