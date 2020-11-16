#ifndef LR_H
#define LR_H
#include <map>
#include <stack>
#include <table.h>
#include <type.h>
#include <utility>
#include <vector>

using namespace std;

class Action
{
public:
    enum class Type
    {
        S,
        R,
        ACC,
    };
    Action() {}
    Action(const char *t)
    {
        if (t[0] == 'a' && t[1] == 'c' && t[2] == 'c')
        {
            this->type = Type::ACC;
            return;
        }
        if (t[0] == 's')
        {
            this->type = Type::S;
        }
        else if (t[0] == 'r')
        {
            this->type = Type::R;
        }
        else
        {
            throw "type must be s or r";
        }
        this->index = std::stoi(t + 1);
    }
    Action(unsigned index, Type type) : index(index), type(type) {}

    unsigned index;
    Type type;
};

class LR
{
public:
    map<pair<unsigned, Token>, Action> action;
    map<pair<unsigned, char>, unsigned> goto_;
    vector<pair<char, vector<V>>> P; //产生式

    bool test(vector<Token> w);
};

map<pair<unsigned, Token>, Action> make_action(vector<Token> tokens, vector<vector<const char *>> table);

map<pair<unsigned, char>, unsigned> make_goto(vector<char> chars, vector<vector<unsigned>> table);
#endif