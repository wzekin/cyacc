#include <lr.h>

inline Token at(vector<Token> &w, size_t index)
{
    if (index >= w.size())
    {
        return Token(Token::TokenType::Null);
    }
    else
    {
        return w[index];
    }
}

bool LR::test(vector<Token> w)
{
    stack<pair<unsigned, V>> s;
    s.push(make_pair(0, 'S'));
    size_t ip = 0;
    while (1)
    {
        auto S = s.top();
        auto a = at(w, ip);
        auto todo = action[make_pair(S.first, a)];
        if (todo.type == Action::Type::S)
        {
            s.push(make_pair(todo.index, a));
            ip++;
        }
        else if (todo.type == Action::Type::R)
        {
            auto p = P[todo.index];
            for (size_t i = 0; i < p.second.size(); i++)
            {
                s.pop();
            }
            auto now = s.top();
            s.push(make_pair(goto_[make_pair(now.first, p.first)], p.first));
        }
        else if (todo.type == Action::Type::ACC)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

map<pair<unsigned, Token>, Action> make_action(vector<Token> tokens, vector<vector<const char *>> table)
{
    map<pair<unsigned, Token>, Action> actions;
    for (size_t i = 0; i < table.size(); i++)
    {
        for (size_t j = 0; j < tokens.size(); j++)
        {
            if (table[i][j] != NULL)
            {
                actions[make_pair(i, tokens[j])] = table[i][j];
            }
        }
    }
    return actions;
}

map<pair<unsigned, char>, unsigned> make_goto(vector<char> chars, vector<vector<unsigned>> table)
{
    map<pair<unsigned, char>, unsigned> gotos;
    for (size_t i = 0; i < table.size(); i++)
    {
        for (size_t j = 0; j < chars.size(); j++)
        {
            if (table[i][j] != UINT32_MAX)
            {
                gotos[make_pair(i, chars[j])] = table[i][j];
            }
        }
    }
    return gotos;
}