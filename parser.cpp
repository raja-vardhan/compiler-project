#include "lexer.h"
#include<map>
#include<utility>
#include<stack>
#include<queue>

using namespace std;

map< pair<int, string> , string> parseTable;
stack<string> stk;
vector< pair<string, int> > rules;
queue<struct token> nextToken;

void initParser(char* filename){
    if(initFile(filename) == 0){
        cout << "Failed to open file" << endl;
    }

    rules.push_back({"program", 1});
    rules.push_back({"funclist", 2});
    rules.push_back({"funclist", 0});
    rules.push_back({"type", 1});
    rules.push_back({"type", 1});
    rules.push_back({"func", 8});
    rules.push_back({"argument_list", 2});
    rules.push_back({"argument_list", 4});
    rules.push_back({"argument_list", 0});
    rules.push_back({"name", 1});
    rules.push_back({"statements", 2});
    rules.push_back({"statements", 2});
    rules.push_back({"statements", 2});
    rules.push_back({"statements", 2});
    rules.push_back({"statements", 0});
    rules.push_back({"declaration_statement", 3});
    rules.push_back({"variable_list", 1});
    rules.push_back({"variable_list", 3});
    rules.push_back({"assignment_statement", 4});
    rules.push_back({"conditional_statement", 7});
    rules.push_back({"conditional_statement", 11});
    rules.push_back({"iteration_statement", 1});
    rules.push_back({"iteration_statement", 1});
    rules.push_back({"for_loop", 10});
    rules.push_back({"while_loop", 7});
    rules.push_back({"expression", 1});
    rules.push_back({"expression", 1});
    rules.push_back({"arithmetic_expression", 3});
    rules.push_back({"arithmetic_expression", 3});
    rules.push_back({"arithmetic_expression", 3});
    rules.push_back({"arithmetic_expression", 3});
    rules.push_back({"arithmetic_expression", 1});
    rules.push_back({"arithmetic_expression", 1});
    rules.push_back({"conditional_expression", 3});
    rules.push_back({"compare", 1});
    rules.push_back({"compare", 1});
    rules.push_back({"compare", 1});
    rules.push_back({"compare", 1});
    rules.push_back({"compare", 1});
    rules.push_back({"variable", 1});


    parseTable[{0,"int"}] = "s4";
    parseTable[{0,"float"}] = "s5";
    parseTable[{0,"$"}] = "r2";
    parseTable[{0,"funclist"}] = "1.0";
    parseTable[{0,"type"}] = "3.0";
    parseTable[{0,"func"}] = "2.0";
    parseTable[{1,"$"}] = "acc";
    parseTable[{2,"int"}] = "s4";
    parseTable[{2,"float"}] = "s5";
    parseTable[{2,"$"}] = "r2";
    parseTable[{2,"funclist"}] = "6.0";
    parseTable[{2,"type"}] = "3.0";
    parseTable[{2,"func"}] = "2.0";
    parseTable[{3,"IDENTIFIER"}] = "s8";
    parseTable[{3,"name"}] = "7.0";
    parseTable[{4,"IDENTIFIER"}] = "r3";
    parseTable[{5,"IDENTIFIER"}] = "r4";
    parseTable[{6,"$"}] = "r1";
    parseTable[{7,"("}] = "s9";
    parseTable[{8,"("}] = "r9";
    parseTable[{8,")"}] = "r9";
    parseTable[{8,","}] = "r9";
    parseTable[{9,"int"}] = "s4";
    parseTable[{9,"float"}] = "s5";
    parseTable[{9,")"}] = "r8";
    parseTable[{9,"type"}] = "11.0";
    parseTable[{9,"argument_list"}] = "10.0";
    parseTable[{10,")"}] = "s12";
    parseTable[{11,"IDENTIFIER"}] = "s8";
    parseTable[{11,"name"}] = "13.0";
    parseTable[{12,"{"}] = "s14";
    parseTable[{13,")"}] = "r6";
    parseTable[{13,","}] = "s15";
    parseTable[{14,"int"}] = "s4";
    parseTable[{14,"float"}] = "s5";
    parseTable[{14,"}"}] = "r14";
    parseTable[{14,"IDENTIFIER"}] = "s26";
    parseTable[{14,"if"}] = "s23";
    parseTable[{14,"for"}] = "s27";
    parseTable[{14,"while"}] = "s28";
    parseTable[{14,"type"}] = "21.0";
    parseTable[{14,"statements"}] = "16.0";
    parseTable[{14,"declaration_statement"}] = "17.0";
    parseTable[{14,"assignment_statement"}] = "18.0";
    parseTable[{14,"conditional_statement"}] = "19.0";
    parseTable[{14,"iteration_statement"}] = "20.0";
    parseTable[{14,"for_loop"}] = "24.0";
    parseTable[{14,"while_loop"}] = "25.0";
    parseTable[{14,"variable"}] = "22.0";
    parseTable[{15,"int"}] = "s4";
    parseTable[{15,"float"}] = "s5";
    parseTable[{15,")"}] = "r8";
    parseTable[{15,"type"}] = "11.0";
    parseTable[{15,"argument_list"}] = "29.0";
    parseTable[{16,"}"}] = "s30";
    parseTable[{17,"int"}] = "s4";
    parseTable[{17,"float"}] = "s5";
    parseTable[{17,"}"}] = "r14";
    parseTable[{17,"IDENTIFIER"}] = "s26";
    parseTable[{17,"if"}] = "s23";
    parseTable[{17,"for"}] = "s27";
    parseTable[{17,"while"}] = "s28";
    parseTable[{17,"type"}] = "21.0";
    parseTable[{17,"statements"}] = "31.0";
    parseTable[{17,"declaration_statement"}] = "17.0";
    parseTable[{17,"assignment_statement"}] = "18.0";
    parseTable[{17,"conditional_statement"}] = "19.0";
    parseTable[{17,"iteration_statement"}] = "20.0";
    parseTable[{17,"for_loop"}] = "24.0";
    parseTable[{17,"while_loop"}] = "25.0";
    parseTable[{17,"variable"}] = "22.0";
    parseTable[{18,"int"}] = "s4";
    parseTable[{18,"float"}] = "s5";
    parseTable[{18,"}"}] = "r14";
    parseTable[{18,"IDENTIFIER"}] = "s26";
    parseTable[{18,"if"}] = "s23";
    parseTable[{18,"for"}] = "s27";
    parseTable[{18,"while"}] = "s28";
    parseTable[{18,"type"}] = "21.0";
    parseTable[{18,"statements"}] = "32.0";
    parseTable[{18,"declaration_statement"}] = "17.0";
    parseTable[{18,"assignment_statement"}] = "18.0";
    parseTable[{18,"conditional_statement"}] = "19.0";
    parseTable[{18,"iteration_statement"}] = "20.0";
    parseTable[{18,"for_loop"}] = "24.0";
    parseTable[{18,"while_loop"}] = "25.0";
    parseTable[{18,"variable"}] = "22.0";
    parseTable[{19,"int"}] = "s4";
    parseTable[{19,"float"}] = "s5";
    parseTable[{19,"}"}] = "r14";
    parseTable[{19,"IDENTIFIER"}] = "s26";
    parseTable[{19,"if"}] = "s23";
    parseTable[{19,"for"}] = "s27";
    parseTable[{19,"while"}] = "s28";
    parseTable[{19,"type"}] = "21.0";
    parseTable[{19,"statements"}] = "33.0";
    parseTable[{19,"declaration_statement"}] = "17.0";
    parseTable[{19,"assignment_statement"}] = "18.0";
    parseTable[{19,"conditional_statement"}] = "19.0";
    parseTable[{19,"iteration_statement"}] = "20.0";
    parseTable[{19,"for_loop"}] = "24.0";
    parseTable[{19,"while_loop"}] = "25.0";
    parseTable[{19,"variable"}] = "22.0";
    parseTable[{20,"int"}] = "s4";
    parseTable[{20,"float"}] = "s5";
    parseTable[{20,"}"}] = "r14";
    parseTable[{20,"IDENTIFIER"}] = "s26";
    parseTable[{20,"if"}] = "s23";
    parseTable[{20,"for"}] = "s27";
    parseTable[{20,"while"}] = "s28";
    parseTable[{20,"type"}] = "21.0";
    parseTable[{20,"statements"}] = "34.0";
    parseTable[{20,"declaration_statement"}] = "17.0";
    parseTable[{20,"assignment_statement"}] = "18.0";
    parseTable[{20,"conditional_statement"}] = "19.0";
    parseTable[{20,"iteration_statement"}] = "20.0";
    parseTable[{20,"for_loop"}] = "24.0";
    parseTable[{20,"while_loop"}] = "25.0";
    parseTable[{20,"variable"}] = "22.0";
    parseTable[{21,"IDENTIFIER"}] = "s26";
    parseTable[{21,"variable_list"}] = "35.0";
    parseTable[{21,"variable"}] = "36.0";
    parseTable[{22,":="}] = "s37";
    parseTable[{23,"("}] = "s38";
    parseTable[{24,"int"}] = "r21";
    parseTable[{24,"float"}] = "r21";
    parseTable[{24,"}"}] = "r21";
    parseTable[{24,"IDENTIFIER"}] = "r21";
    parseTable[{24,"if"}] = "r21";
    parseTable[{24,"for"}] = "r21";
    parseTable[{24,"while"}] = "r21";
    parseTable[{25,"int"}] = "r22";
    parseTable[{25,"float"}] = "r22";
    parseTable[{25,"}"}] = "r22";
    parseTable[{25,"IDENTIFIER"}] = "r22";
    parseTable[{25,"if"}] = "r22";
    parseTable[{25,"for"}] = "r22";
    parseTable[{25,"while"}] = "r22";
    parseTable[{26,","}] = "r39";
    parseTable[{26,";"}] = "r39";
    parseTable[{26,":="}] = "r39";
    parseTable[{27,"("}] = "s39";
    parseTable[{28,"("}] = "s40";
    parseTable[{29,")"}] = "r7";
    parseTable[{30,"int"}] = "r5";
    parseTable[{30,"float"}] = "r5";
    parseTable[{30,"$"}] = "r5";
    parseTable[{31,"}"}] = "r10";
    parseTable[{32,"}"}] = "r11";
    parseTable[{33,"}"}] = "r12";
    parseTable[{34,"}"}] = "r13";
    parseTable[{35,";"}] = "s41";
    parseTable[{36,","}] = "s42";
    parseTable[{36,";"}] = "r16";
    parseTable[{37,"IDENTIFIER"}] = "s44";
    parseTable[{37,"CONSTANT"}] = "s45";
    parseTable[{37,"arithmetic_expression"}] = "43.0";
    parseTable[{38,"IDENTIFIER"}] = "s44";
    parseTable[{38,"CONSTANT"}] = "s45";
    parseTable[{38,"arithmetic_expression"}] = "47.0";
    parseTable[{38,"conditional_expression"}] = "46.0";
    parseTable[{39,"int"}] = "s4";
    parseTable[{39,"float"}] = "s5";
    parseTable[{39,"type"}] = "21.0";
    parseTable[{39,"declaration_statement"}] = "48.0";
    parseTable[{40,"IDENTIFIER"}] = "s44";
    parseTable[{40,"CONSTANT"}] = "s45";
    parseTable[{40,"arithmetic_expression"}] = "47.0";
    parseTable[{40,"conditional_expression"}] = "49.0";
    parseTable[{41,"int"}] = "r15";
    parseTable[{41,"float"}] = "r15";
    parseTable[{41,"}"}] = "r15";
    parseTable[{41,"IDENTIFIER"}] = "r15";
    parseTable[{41,"if"}] = "r15";
    parseTable[{41,"for"}] = "r15";
    parseTable[{41,"Unnamed: 14"}] = "r15";
    parseTable[{41,"while"}] = "r15";
    parseTable[{42,"IDENTIFIER"}] = "s26";
    parseTable[{42,"variable_list"}] = "50.0";
    parseTable[{42,"variable"}] = "36.0";
    parseTable[{43,";"}] = "s51";
    parseTable[{43,"+"}] = "s52";
    parseTable[{43,"-"}] = "s53";
    parseTable[{43,"*"}] = "s54";
    parseTable[{43,"/"}] = "s55";
    parseTable[{44,")"}] = "r31";
    parseTable[{44,";"}] = "r31";
    parseTable[{44,"+"}] = "r31";
    parseTable[{44,"-"}] = "r31";
    parseTable[{44,"*"}] = "r31";
    parseTable[{44,"/"}] = "r31";
    parseTable[{44,">"}] = "r31";
    parseTable[{44,">="}] = "r31";
    parseTable[{44,"="}] = "r31";
    parseTable[{44,"<"}] = "r31";
    parseTable[{44,"<="}] = "r31";
    parseTable[{45,")"}] = "r32";
    parseTable[{45,";"}] = "r32";
    parseTable[{45,"+"}] = "r32";
    parseTable[{45,"-"}] = "r32";
    parseTable[{45,"*"}] = "r32";
    parseTable[{45,"/"}] = "r32";
    parseTable[{45,">"}] = "r32";
    parseTable[{45,">="}] = "r32";
    parseTable[{45,"="}] = "r32";
    parseTable[{45,"<"}] = "r32";
    parseTable[{45,"<="}] = "r32";
    parseTable[{46,")"}] = "s56";
    parseTable[{47,"+"}] = "s52";
    parseTable[{47,"-"}] = "s53";
    parseTable[{47,"*"}] = "s54";
    parseTable[{47,"/"}] = "s55";
    parseTable[{47,">"}] = "s58";
    parseTable[{47,">="}] = "s59";
    parseTable[{47,"="}] = "s60";
    parseTable[{47,"<"}] = "s61";
    parseTable[{47,"<="}] = "s62";
    parseTable[{47,"compare"}] = "57.0";
    parseTable[{48,"Unnamed: 14"}] = "s63";
    parseTable[{49,")"}] = "s64";
    parseTable[{50,";"}] = "r17";
    parseTable[{51,"int"}] = "r18";
    parseTable[{51,"float"}] = "r18";
    parseTable[{51,")"}] = "r18";
    parseTable[{51,"}"}] = "r18";
    parseTable[{51,"IDENTIFIER"}] = "r18";
    parseTable[{51,"if"}] = "r18";
    parseTable[{51,"for"}] = "r18";
    parseTable[{51,"while"}] = "r18";
    parseTable[{52,"IDENTIFIER"}] = "s44";
    parseTable[{52,"CONSTANT"}] = "s45";
    parseTable[{52,"arithmetic_expression"}] = "65.0";
    parseTable[{53,"IDENTIFIER"}] = "s44";
    parseTable[{53,"CONSTANT"}] = "s45";
    parseTable[{53,"arithmetic_expression"}] = "66.0";
    parseTable[{54,"IDENTIFIER"}] = "s44";
    parseTable[{54,"CONSTANT"}] = "s45";
    parseTable[{54,"arithmetic_expression"}] = "67.0";
    parseTable[{55,"IDENTIFIER"}] = "s44";
    parseTable[{55,"CONSTANT"}] = "s45";
    parseTable[{55,"arithmetic_expression"}] = "68.0";
    parseTable[{56,"{"}] = "s69";
    parseTable[{57,"IDENTIFIER"}] = "s44";
    parseTable[{57,"CONSTANT"}] = "s45";
    parseTable[{57,"arithmetic_expression"}] = "70.0";
    parseTable[{58,"IDENTIFIER"}] = "r34";
    parseTable[{58,"CONSTANT"}] = "r34";
    parseTable[{59,"IDENTIFIER"}] = "r35";
    parseTable[{59,"CONSTANT"}] = "r35";
    parseTable[{60,"IDENTIFIER"}] = "r36";
    parseTable[{60,"CONSTANT"}] = "r36";
    parseTable[{61,"IDENTIFIER"}] = "r37";
    parseTable[{61,"CONSTANT"}] = "r37";
    parseTable[{62,"IDENTIFIER"}] = "r38";
    parseTable[{62,"CONSTANT"}] = "r38";
    parseTable[{63,"IDENTIFIER"}] = "s44";
    parseTable[{63,"CONSTANT"}] = "s45";
    parseTable[{63,"arithmetic_expression"}] = "47.0";
    parseTable[{63,"conditional_expression"}] = "71.0";
    parseTable[{64,"{"}] = "s72";
    parseTable[{65,")"}] = "r27";
    parseTable[{65,";"}] = "r27";
    parseTable[{65,"+"}] = "s52 ";
    parseTable[{65,"-"}] = "s53";
    parseTable[{65,"*"}] = "s54";
    parseTable[{65,"/"}] = "s55";
    parseTable[{65,">"}] = "r27";
    parseTable[{65,">="}] = "r27";
    parseTable[{65,"="}] = "r27";
    parseTable[{65,"<"}] = "r27";
    parseTable[{65,"<="}] = "r27";
    parseTable[{66,")"}] = "r28";
    parseTable[{66,";"}] = "r28";
    parseTable[{66,"+"}] = "s52";
    parseTable[{66,"-"}] = "s53";
    parseTable[{66,"*"}] = "s54";
    parseTable[{66,"/"}] = "s55";
    parseTable[{66,">"}] = "r28";
    parseTable[{66,">="}] = "r28";
    parseTable[{66,"="}] = "r28";
    parseTable[{66,"<"}] = "r28";
    parseTable[{66,"<="}] = "r28";
    parseTable[{67,")"}] = "r29";
    parseTable[{67,";"}] = "r29";
    parseTable[{67,"+"}] = "s52";
    parseTable[{67,"-"}] = "s53";
    parseTable[{67,"*"}] = "s54";
    parseTable[{67,"/"}] = "s55";
    parseTable[{67,">"}] = "r29";
    parseTable[{67,">="}] = "r29";
    parseTable[{67,"="}] = "r29";
    parseTable[{67,"<"}] = "r29";
    parseTable[{67,"<="}] = "r29";
    parseTable[{68,")"}] = "r30";
    parseTable[{68,";"}] = "r30";
    parseTable[{68,"+"}] = "s52";
    parseTable[{68,"-"}] = "s53";
    parseTable[{68,"*"}] = "s54";
    parseTable[{68,"/"}] = "s55";
    parseTable[{68,">"}] = "r30";
    parseTable[{68,">="}] = "r30";
    parseTable[{68,"="}] = "r30";
    parseTable[{68,"<"}] = "r30";
    parseTable[{68,"<="}] = "r30";
    parseTable[{69,"int"}] = "s4";
    parseTable[{69,"float"}] = "s5";
    parseTable[{69,"}"}] = "r14";
    parseTable[{69,"IDENTIFIER"}] = "s26";
    parseTable[{69,"if"}] = "s23";
    parseTable[{69,"for"}] = "s27";
    parseTable[{69,"while"}] = "s28";
    parseTable[{69,"type"}] = "21.0";
    parseTable[{69,"statements"}] = "73.0";
    parseTable[{69,"declaration_statement"}] = "17.0";
    parseTable[{69,"assignment_statement"}] = "18.0";
    parseTable[{69,"conditional_statement"}] = "19.0";
    parseTable[{69,"iteration_statement"}] = "20.0";
    parseTable[{69,"for_loop"}] = "24.0";
    parseTable[{69,"while_loop"}] = "25.0";
    parseTable[{69,"variable"}] = "22.0";
    parseTable[{70,")"}] = "r33";
    parseTable[{70,";"}] = "r33";
    parseTable[{70,"+"}] = "s52";
    parseTable[{70,"-"}] = "s53";
    parseTable[{70,"*"}] = "s54";
    parseTable[{70,"/"}] = "s55";
    parseTable[{71,";"}] = "s74";
    parseTable[{72,"int"}] = "s4";
    parseTable[{72,"float"}] = "s5";
    parseTable[{72,"}"}] = "r14";
    parseTable[{72,"IDENTIFIER"}] = "s26";
    parseTable[{72,"if"}] = "s23";
    parseTable[{72,"for"}] = "s27";
    parseTable[{72,"while"}] = "s28";
    parseTable[{72,"type"}] = "21.0";
    parseTable[{72,"statements"}] = "75.0";
    parseTable[{72,"declaration_statement"}] = "17.0";
    parseTable[{72,"assignment_statement"}] = "18.0";
    parseTable[{72,"conditional_statement"}] = "19.0";
    parseTable[{72,"iteration_statement"}] = "20.0";
    parseTable[{72,"for_loop"}] = "24.0";
    parseTable[{72,"while_loop"}] = "25.0";
    parseTable[{72,"variable"}] = "22.0";
    parseTable[{73,"}"}] = "s76";
    parseTable[{74,"IDENTIFIER"}] = "s26";
    parseTable[{74,"assignment_statement"}] = "77.0";
    parseTable[{74,"variable"}] = "22.0";
    parseTable[{75,"}"}] = "s78";
    parseTable[{76,"int"}] = "r19";
    parseTable[{76,"float"}] = "r19";
    parseTable[{76,"}"}] = "r19";
    parseTable[{76,"IDENTIFIER"}] = "r19";
    parseTable[{76,"if"}] = "r19";
    parseTable[{76,"else"}] = "s79";
    parseTable[{76,"for"}] = "r19";
    parseTable[{76,"while"}] = "r19";
    parseTable[{77,")"}] = "s80";
    parseTable[{78,"int"}] = "r24";
    parseTable[{78,"float"}] = "r24";
    parseTable[{78,"}"}] = "r24";
    parseTable[{78,"IDENTIFIER"}] = "r24";
    parseTable[{78,"if"}] = "r24";
    parseTable[{78,"for"}] = "r24";
    parseTable[{78,"while"}] = "r24";
    parseTable[{79,"{"}] = "s81";
    parseTable[{80,"{"}] = "s82";
    parseTable[{81,"int"}] = "s4";
    parseTable[{81,"float"}] = "s5";
    parseTable[{81,"}"}] = "r14";
    parseTable[{81,"IDENTIFIER"}] = "s26";
    parseTable[{81,"if"}] = "s23";
    parseTable[{81,"for"}] = "s27";
    parseTable[{81,"while"}] = "s28";
    parseTable[{81,"type"}] = "21.0";
    parseTable[{81,"statements"}] = "83.0";
    parseTable[{81,"declaration_statement"}] = "17.0";
    parseTable[{81,"assignment_statement"}] = "18.0";
    parseTable[{81,"conditional_statement"}] = "19.0";
    parseTable[{81,"iteration_statement"}] = "20.0";
    parseTable[{81,"for_loop"}] = "24.0";
    parseTable[{81,"while_loop"}] = "25.0";
    parseTable[{81,"variable"}] = "22.0";
    parseTable[{82,"int"}] = "s4";
    parseTable[{82,"float"}] = "s5";
    parseTable[{82,"}"}] = "r14";
    parseTable[{82,"IDENTIFIER"}] = "s26";
    parseTable[{82,"if"}] = "s23";
    parseTable[{82,"for"}] = "s27";
    parseTable[{82,"while"}] = "s28";
    parseTable[{82,"type"}] = "21.0";
    parseTable[{82,"statements"}] = "84.0";
    parseTable[{82,"declaration_statement"}] = "17.0";
    parseTable[{82,"assignment_statement"}] = "18.0";
    parseTable[{82,"conditional_statement"}] = "19.0";
    parseTable[{82,"iteration_statement"}] = "20.0";
    parseTable[{82,"for_loop"}] = "24.0";
    parseTable[{82,"while_loop"}] = "25.0";
    parseTable[{82,"variable"}] = "22.0";
    parseTable[{83,"}"}] = "s85";
    parseTable[{84,"}"}] = "s86";
    parseTable[{85,"int"}] = "r20";
    parseTable[{85,"float"}] = "r20";
    parseTable[{85,"}"}] = "r20";
    parseTable[{85,"IDENTIFIER"}] = "r20";
    parseTable[{85,"if"}] = "r20";
    parseTable[{85,"for"}] = "r20";
    parseTable[{85,"while"}] = "r20";
    parseTable[{86,"int"}] = "r23";
    parseTable[{86,"float"}] = "r23";
    parseTable[{86,"}"}] = "r23";
    parseTable[{86,"IDENTIFIER"}] = "r23";
    parseTable[{86,"if"}] = "r23";
    parseTable[{86,"for"}] = "r23";
    parseTable[{86,"while"}] = "r23";

}

int main(int argc, char* argv[]){
    initParser(argv[1]);

    stk.push("0");

    while(1){
        int currState = stoi(stk.top());

        if(CURRIDX < (int)BUFFER.size()){
            nextToken.push(getNextToken());
        }
        else{
            struct token dol = {TEMP, "$", -1};
            nextToken.push(dol);
        }

        struct token t = nextToken.front();

        if(t.tokenName == USELESS){
            nextToken.pop();
            continue;
        }

        // cout << t.tokenStr << endl;

        string oper = parseTable[{currState, t.tokenStr}];
        // cout << oper << endl;
        
        // Shift
        if(oper[0] == 's'){

            // cout << t.tokenStr << endl;
            // cout << oper.substr(1) << endl;

            stk.push(t.tokenStr);
            stk.push(oper.substr(1));
            nextToken.pop();

        }

        // Reduce
        else if(oper[0] == 'r'){
            int ruleNum = stoi(oper.substr(1));
            int numSym = rules[ruleNum].second;
            numSym *= 2;
            for(int i = 0; i < numSym; i++){
                // if(i & 1){
                //     cout << stk.top() << endl;
                // }
                stk.pop();
            }

            // Go to
            int useState = stoi(stk.top());
            stk.push(rules[ruleNum].first);

            cout << rules[ruleNum].first << endl;

            stk.push(to_string(stoi(parseTable[{useState, stk.top()}])));

        }

        else{
            cout << "program" << endl;
            cout << "Accepted" << endl;
            break;
        }
    }

}