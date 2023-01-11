#include "tseitinTransformer.h"
#include <iostream>
#include "treeNode.h"
using namespace std;
TseitinTransformer::TseitinTransformer(TreeNode *root)
{
  formulaRoot=root;
}


int TseitinTransformer::transSubformula(TreeNode* subRoot) {
// your code starts here
   if (subRoot != NULL) {
      string root_content=subRoot->content;

         if(root_content=="*")
         {
            addAndEq(subRoot->value, subRoot->leftChild->value, subRoot->rightChild->value);
            transSubformula(subRoot->leftChild);
            transSubformula(subRoot->rightChild);
        } 
          

        if(root_content=="-")
        {
            addNegEq(subRoot->value, subRoot->leftChild->value);
            transSubformula(subRoot->leftChild);
        }

        if(root_content=="+")
        {
            addOrEq(subRoot->value, subRoot->leftChild->value, subRoot->rightChild->value);
            transSubformula(subRoot->leftChild);
            transSubformula(subRoot->rightChild);
        }
        
        
      }     
  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  vector<int> v1={-1*curID,-1*childID};
  cnf.push_back(v1);
  v1={curID,childID};
  cnf.push_back(v1);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  vector<int> v1={-1*curID, leftID, rightID};
  cnf.push_back(v1);
  v1={-1*leftID, curID};
  cnf.push_back(v1);
  v1={-1*rightID, curID};
  cnf.push_back(v1);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  vector<int> v1;
  v1={-1*curID, leftID};
  cnf.push_back(v1);
  v1={-1*curID, rightID};
  cnf.push_back(v1);
  v1={-1*leftID, -1*rightID,curID};
  cnf.push_back(v1);
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  //varIdCounter=1;
  transSubformula(formulaRoot);
  cnf.push_back({1});
  return cnf;
}
// std::string TseitinTransformer::cnfString() const {
//   std::string result = "";
//  for(auto i = cnf.begin() ; i<cnf.end() ; i++)
//   {
//      for(auto j = i->begin() ; j< i->end() ; j++)
//         cout << *j <<" ";
//      cout <<"\n"; 
//      cout<<j.size();
//      cout<<"\n"; 
     
//   }
//   return result;
// }
// std::string TseitinTransformer::cnfString() const {
//   std::string result = "";
//  for(unsigned int i = 0 ; i< cnf.size() ; i++)
//   {
//      for(unsigned int j = 0 ; j< cnf[i].size() ; j++)
//         cout << cnf[i][j] <<" ";
//      cout <<"\n"; 
//      cout<<"size"<<cnf[i].size();
//      cout<<"\n"; 
     
//   }
//   return result;
// }

/*unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  //
  return 0;
}*/
