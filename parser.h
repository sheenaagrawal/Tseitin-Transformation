#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    public:
    Tokenizer *tknzr;
    int counter=1;
    TreeNode *parseFormula(); // parse non-terminal Formula in the grammar
    std::map<int,std::string> variableTable;
    TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // parse non-terminal Term in the grammar
    void getVarTable(TreeNode* node);
    bool findVal(std::string K);
    int findValue(std::map<int,std::string> &Map, std::string V);
  
    FormulaParser(std::string ln);
    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser();
};

// Parser for the Assignment
/*class AssignmentParser {
    public:
    Tokenizer *tknzr;
  
    AssignmentParser(std::string ln);
    std::map<std::string, bool> parseAssignment();
    ~AssignmentParser();
};*/

#endif
