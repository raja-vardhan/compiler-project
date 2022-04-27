#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

/*
    Helper macros
*/
#define isNum(c) (c >= '0' && c <= '9')
#define isPosNum(c) (c > '0' && c <= '9')
#define isDelim(c) (c == ' ' || c == '\n' || c == '\t')
#define isLetter(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define isAlpha(c) (isNum(c) || isLetter(c) || c == '_')

using namespace std;

fstream file;
string FILENAME;
string BUFFER;
int LINENUM = 1;
int CURRIDX = 0;
vector<string> keywords{"int", "float", "boolean", "for", "while", "until", "if", "else", "true", "false"};

/* 
    Token names
*/
enum TOKEN
{
    INT,
    FLOAT,
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    ASSIGN,
    COLON,
    EQ,
    LE,
    LT,
    GE,
    GT,
    NEQ,
    NOT,
    AND,
    OR,
    COND,
    COMMA,
    SEMICOLON,
    LCB,
    RCB,
    LRB,
    RRB,
    LSB,
    RSB,
    ID,
    STR,
    USELESS,
    ERR,
    KEYWORD,
    TEMP
};

struct token
{
    enum TOKEN tokenName;
    string tokenStr;
    int offset;
};

/*
    Check if the identifier is a keyword
*/
bool in_array(string &s, vector<string> &keywords)
{
    return find(keywords.begin(), keywords.end(), s) != keywords.end();
}

/*
    Rollback action
*/
void retract(string &s)
{
    if (s.back() == '\n')
        LINENUM--;
    s.pop_back();
    CURRIDX--;
}

/*
    Retrieve next character.
    Returns -1 in case of end of file
*/
int getNextChar(string &s)
{
    if (CURRIDX >= (int)BUFFER.size())
    {
        return -1;
    }
    int c = BUFFER[CURRIDX++];
    if (c == '\n')
        LINENUM++;
    s.push_back(c);
    return c;
}

/*
    Implementation of DFA.
    Returns next token.
*/
struct token getNextToken()
{

    int state = 0;
    int final = 0;
    int error = 0;
    string s = "";
    int c = -1;
    struct token t = {USELESS, "" ,-1};
    while ((!final) && (CURRIDX <= (int)BUFFER.size()))
    {

        switch (state)
        {
        case 0:
            c = getNextChar(s);
            if (c == '+')
                state = 1;
            else if (c == '-')
                state = 2;
            else if (c == '*')
                state = 3;
            else if (c == '/')
                state = 4;
            else if (c == '%')
                state = 11;
            else if (c == ':')
                state = 12;
            else if (c == '=')
                state = 15;
            else if (c == '<')
                state = 17;
            else if (c == '>')
                state = 20;
            else if (c == '!')
                state = 23;
            else if (c == '&')
                state = 26;
            else if (c == '|')
                state = 28;
            else if (c == '?')
                state = 30;
            else if (isPosNum(c))
                state = 31;
            else if (c == '0')
                state = 36;
            else if (c == ',')
                state = 38;
            else if (c == ';')
                state = 39;
            else if (c == '{')
                state = 40;
            else if (c == '}')
                state = 41;
            else if (c == '(')
                state = 42;
            else if (c == ')')
                state = 43;
            else if (c == '[')
                state = 44;
            else if (c == ']')
                state = 45;
            else if (isDelim(c))
                state = 46;
            else if (isLetter(c))
                state = 48;
            else if (c == '"')
                state = 50;
            else
            {
                final = 1;
                error = 1;
                t.tokenName = ERR;
                t.tokenStr = "Error";
            }
            break;
        case 1:
            final = 1;
            t.tokenName = PLUS;
            t.tokenStr = "+";
            break;
        case 2:
            final = 1;
            t.tokenName = MINUS;
            t.tokenStr = "-";
            break;
        case 3:
            final = 1;
            t.tokenName = MUL;
            t.tokenStr = "*";
            break;
        case 4:
            c = getNextChar(s);
            if (c == '/')
                state = 5;
            else if (c == '*')
                state = 7;
            else
                state = 10;
            break;
        case 5:
            c = getNextChar(s);
            if (c == '\n' || c == -1)
                state = 6;
            break;
        case 6:
            final = 1;
            break;
        case 7:
            c = getNextChar(s);
            if (c == '*')
                state = 8;
            break;
        case 8:
            c = getNextChar(s);
            if (c == '/')
                state = 9;
            break;
        case 9:
            final = 1;
            break;
        case 10:
            final = 1;
            t.tokenName = DIV;
            t.tokenStr = "/";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 11:
            final = 1;
            t.tokenName = MOD;
            break;
        case 12:
            c = getNextChar(s);
            if (c == '=')
                state = 13;
            else
                state = 14;
            break;
        case 13:
            final = 1;
            t.tokenName = ASSIGN;
            t.tokenStr = ":=";
            break;
        case 14:
            final = 1;
            t.tokenName = COLON;
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 15:
            c = getNextChar(s);
            if (c == '=')
                state = 16;
            else
            {
                final = 1;
                error = 1;
                t.tokenName = ERR;
                if (CURRIDX < (int)BUFFER.size())
                    retract(s);
            }
            break;
        case 16:
            final = 1;
            t.tokenName = EQ;
            t.tokenStr = "=";
            break;
        case 17:
            c = getNextChar(s);
            if (c == '=')
                state = 18;
            else
                state = 19;
            break;
        case 18:
            final = 1;
            t.tokenName = LE;
            t.tokenStr = "<=";
            break;
        case 19:
            final = 1;
            t.tokenName = LT;
            t.tokenStr = "<";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 20:
            c = getNextChar(s);
            if (c == '=')
                state = 21;
            else
                state = 22;
            break;
        case 21:
            final = 1;
            t.tokenName = GE;
            t.tokenStr = ">=";
            break;
        case 22:
            final = 1;
            t.tokenName = GT;
            t.tokenStr = ">";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 23:
            c = getNextChar(s);
            if (c == '=')
                state = 24;
            else
                state = 25;
            break;
        case 24:
            final = 1;
            t.tokenName = NEQ;
            break;
        case 25:
            final = 1;
            t.tokenName = NOT;
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 26:
            c = getNextChar(s);
            if (c == '&')
                state = 27;
            else
            {
                final = 1;
                error = 1;
                t.tokenName = ERR;
                if (CURRIDX < (int)BUFFER.size())
                    retract(s);
            }
            break;
        case 27:
            final = 1;
            t.tokenName = AND;
            break;
        case 28:
            c = getNextChar(s);
            if (c == '|')
                state = 29;
            else
            {
                final = 1;
                error = 1;
                t.tokenName = ERR;
                t.tokenStr = "Error";
                if (CURRIDX < (int)BUFFER.size())
                    retract(s);
            }
            break;
        case 29:
            final = 1;
            t.tokenName = OR;
            break;
        case 30:
            final = 1;
            t.tokenName = COND;
            break;
        case 31:
            c = getNextChar(s);
            if (isNum(c))
                ;
            else if (c == '.')
                state = 32;
            else
                state = 35;
            break;
        case 32:
            c = getNextChar(s);
            if (isNum(c))
                state = 33;
            else
            {
                final = 1;
                error = 1;
                t.tokenName = ERR;
                if (CURRIDX < (int)BUFFER.size())
                    retract(s);
            }
            break;
        case 33:
            c = getNextChar(s);
            if (isNum(c))
                ;
            else
                state = 34;
            break;
        case 34:
            final = 1;
            t.tokenName = FLOAT;
            t.tokenStr = "CONSTANT";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 35:
            final = 1;
            t.tokenName = INT;
            t.tokenStr = "CONSTANT";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 36:
            c = getNextChar(s);
            if (c == '.')
                state = 32;
            else
                state = 37;
            break;
        case 37:
            final = 1;
            t.tokenName = INT;
            t.tokenStr = "CONSTANT";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 38:
            final = 1;
            t.tokenName = COMMA;
            t.tokenStr = ",";
            break;
        case 39:
            final = 1;
            t.tokenName = SEMICOLON;
            t.tokenStr = ";";
            break;
        case 40:
            final = 1;
            t.tokenName = LCB;
            t.tokenStr = "{";
            break;
        case 41:
            final = 1;
            t.tokenName = RCB;
            t.tokenStr = "}";
            break;
        case 42:
            final = 1;
            t.tokenName = LRB;
            t.tokenStr = "(";
            break;
        case 43:
            final = 1;
            t.tokenName = RRB;
            t.tokenStr = ")";
            break;
        case 44:
            final = 1;
            t.tokenName = LSB;
            break;
        case 45:
            final = 1;
            t.tokenName = RSB;
            break;
        case 46:
            c = getNextChar(s);
            if (isDelim(c))
                ;
            else
                state = 47;
            break;
        case 47:
            final = 1;
            t.tokenName = USELESS;
            if (CURRIDX <= (int)BUFFER.size())
                retract(s);
            break;
        case 48:
            c = getNextChar(s);
            if (isAlpha(c))
                ;
            else
                state = 49;
            break;
        case 49:
            final = 1;
            t.tokenName = ID;
            t.tokenStr = "IDENTIFIER";
            if (CURRIDX < (int)BUFFER.size())
                retract(s);
            break;
        case 50:
            c = getNextChar(s);
            if (c == '"')
                state = 51;
            break;
        case 51:
            final = 1;
            t.tokenName = STR;
            break;
        }
    }

    /*
        Error on recognising invalid token.
    */
    if (error)
    {

        cout << "\x1b[1;31m"
             << "Lexical error"
             << ", string "
             << "\u001b[34m" << s << "\u001b[33m"
             << ", line number " << LINENUM << endl;
        return t;
    }

    
    if ( t.tokenName == ID && in_array(s, keywords))
    {
        t.tokenName = KEYWORD;
        t.tokenStr = s;
    }

    /*
        Skip whitespaces, tabspaces, newlines.
    */
    // if (t.tokenName != USELESS)
    // {
    //     cout << "Token " << t.tokenName << ", string "
    //          << "\u001b[34m" << s << "\u001b[33m"
    //          << ", line number " << LINENUM << endl;
    // }

    return t;
}

/*
    Open file and store its contents in the string BUFFER.
    Returns 1 on SUCCESS, 0 otherwise
*/
int initFile(char* filename)
{
    FILENAME = filename;
    file.open(FILENAME);
    if(!file.is_open()){
        return 0;
    }
    string line;
    while (getline(file, line))
    {
        BUFFER += line;
        BUFFER += '\n';
    }
    BUFFER.pop_back();
    return 1;
}

// int main(int argc, char *argv[])
// {

//     if(argc < 2){
//         cout << "Provide file as argument" << endl;
//         return 0;
//     }
//     else if(argc > 2){
//         cout << "Too many arguments" << endl;
//         return 0;
//     }

//     FILENAME = argv[1];
    
//     if(!initFile()){
//         cout << "Couldn't open file" << endl;
//         return 0;
//     }

//     struct token t;

//     /*
//         Main scanner loop.
//     */
//     while (1)
//     {
//         t = getNextToken();

//         if (CURRIDX >= (int)BUFFER.size())
//             break;
//     }

//     file.close();

//     return 0;
// }