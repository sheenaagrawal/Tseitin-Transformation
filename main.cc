#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "parser.h"
#include "treeNode.h"
#include "tseitinTransformer.h"
#include "memory"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

using namespace std;

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr) {
  int scPos = line.find(";");
  if (scPos != -1) throw "Error: invalid input";
  else {
    formulaStr =  line;
    //assignmentStr = line.substr(scPos+1, std::string::npos);
  }
}


void print2DUtil(TreeNode *root, int space)
{
  // Base case
  if (root == NULL)
    return;

  // Increase distance between levels
  space += 4;

  // Process right child first
  print2DUtil(root->rightChild, space);

  // Print current node after space
  // count
  cout << endl;
  for (int i = 4; i < space; i++)
    cout << " ";
  cout << root->value << "\n";

  // Process left child
  print2DUtil(root->leftChild, space);
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver()); //creating new solver
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    //std::string assignmentStr; // store the assignment string
    std::getline(std::cin, line);
    if (std::cin.eof()) break; // terminate gracefully encountering eof
    try {
      parseLine(line, formulaStr);
    } catch (const char *e) {
      std::cout << e << std::endl;
      continue;
    }
    // std::cout << "formula: " << formulaStr << "; assignment: " << assignmentStr << std::endl;
    FormulaParser fParser{formulaStr};
    //AssignmentParser aParser{assignmentStr};
    TreeNode *treeRoot = nullptr;
    try {
      treeRoot = fParser.getTreeRoot();
      //std::cout<<"1"<<std::endl;
      //td::map<int,std::string> VarTable;
      
      fParser.getVarTable(treeRoot);

      int varCount = fParser.counter -1;
      vector <Minisat::Lit> L;
      for(int i =0;i< varCount;i++)
        L.push_back(Minisat::mkLit(solver->newVar()));

      TseitinTransformer *t=new TseitinTransformer(treeRoot);
      t->transform();
      auto cnf = t->cnf;
      //printing............................................................
  //      for(unsigned int i = 0 ; i< cnf.size() ; i++)
  // {
  //    for(unsigned int j = 0 ; j< cnf[i].size() ; j++)
  //       cout << cnf[i][j] <<" ";
  //    cout <<"\n"; 

     
  // }
      //printing...........................................................

      //adding clauses......................
    for(unsigned int i = 0 ; i< cnf.size() ; i++)
  {
     if(cnf[i].size() == 1)
      {
        if(cnf[i][0] < 0)
          solver->addClause(~L[abs(cnf[i][0])-1]);
        else
          solver->addClause(L[abs(cnf[i][0])-1]);
      }
      else if(cnf[i].size() == 2)
      {
        if(cnf[i][0] < 0)
          {
            if(cnf[i][1] < 0)
              solver->addClause(~L[abs(cnf[i][0])-1],~L[abs(cnf[i][1])-1]);
            else
              solver->addClause(~L[abs(cnf[i][0])-1],L[abs(cnf[i][1])-1]);
          }
          if(cnf[i][0] > 0)
            {
            if(cnf[i][1] < 0)
              solver->addClause(L[abs(cnf[i][0])-1],~L[abs(cnf[i][1])-1]);
            else
              solver->addClause(L[abs(cnf[i][0])-1],L[abs(cnf[i][1])-1]);
            }
      }
      else if(cnf[i].size() == 3)
      {
        if(cnf[i][0] < 0)
        {
          if(cnf[i][1] < 0)
          {
            if(cnf[i][2] < 0)
              solver->addClause(~L[abs(cnf[i][0])-1],~L[abs(cnf[i][1])-1],~L[abs(cnf[i][2])-1]);
            else
              solver->addClause(~L[abs(cnf[i][0])-1],~L[abs(cnf[i][1])-1],L[abs(cnf[i][2])-1]);
          }
          else
          {
            if(cnf[i][2] < 0)
              solver->addClause(~L[abs(cnf[i][0])-1],L[abs(cnf[i][1])-1],~L[abs(cnf[i][2])-1]);
            else
              solver->addClause(~L[abs(cnf[i][0])-1],L[abs(cnf[i][1])-1],L[abs(cnf[i][2])-1]);
          }
            
        }
        if(cnf[i][0] > 0)
        {
           if(cnf[i][1] < 0)
          {
            if(cnf[i][2] < 0)
              solver->addClause(L[abs(cnf[i][0])-1],~L[abs(cnf[i][1])-1],~L[abs(cnf[i][2])-1]);
            else
              solver->addClause(L[abs(cnf[i][0])-1],~L[abs(cnf[i][1])-1],L[abs(cnf[i][2])-1]);
          }
          else
          {
            if(cnf[i][2] < 0)
              solver->addClause(L[abs(cnf[i][0])-1],L[abs(cnf[i][1])-1],~L[abs(cnf[i][2])-1]);
            else
              solver->addClause(L[abs(cnf[i][0])-1],L[abs(cnf[i][1])-1],L[abs(cnf[i][2])-1]);
          }
        }
      }
      

     
  }
      //adding clauses......................
     // t->cnfString();
    //   Minisat::Lit l1, l2, l3, l4;

    // // create 4 positive literals over 4 new variables
    // l1 = Minisat::mkLit(solver->newVar());
    // l2 = Minisat::mkLit(solver->newVar());
    // l3 = Minisat::mkLit(solver->newVar());
    // l4 = Minisat::mkLit(solver->newVar());

    // // create 3 positive literals over 3 new variables
    // Minisat::Lit b0, b1, b2;
    // b0 = Minisat::mkLit(solver->newVar());
    // b1 = Minisat::mkLit(solver->newVar());
    // b2 = Minisat::mkLit(solver->newVar());

    // // (l1 || b0)
    // solver->addClause(l1, b0);
    // // (!b0 || l2 || b1)
    // solver->addClause(~b0, l2, b1);
    // // (!b1 || l3 || b2)
    // solver->addClause(~b1, l3, b2);
    // // (!b2|| l4)
    // solver->addClause(~b2, l4);

    bool res = solver->solve();
  //  std::cout << "The result is: " << res << "\n";
  if(res == 1)
    cout<<"sat"<<'\n';
  else
    cout<<"unsat"<<'\n';

solver.reset (new Minisat::Solver());
    } catch (const char *e) {
      delete treeRoot;
      std::cout << e << std::endl;
      continue;
    }
    delete treeRoot;
  }
}
