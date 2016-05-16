#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

void showDeltaTable(std::vector<std::map<char, int>>& deltaTable, std::vector<char>& alphabet) {
  std::cout << "state\t";
  for (size_t j = 0; j < alphabet.size(); j++)
    std::cout << alphabet[j] << "\t";
  std::cout << std::endl;


  for (size_t i = 0; i < deltaTable.size(); i++){
    std::cout << i << "\t";
    for (size_t j = 0; j < alphabet.size(); j++) {
      if (deltaTable[i].find(alphabet[j]) == deltaTable[i].end())
        std::cout << "0" << "\t";
      else
        std::cout << deltaTable[i][alphabet[j]] << "\t";
    }
    std::cout << std::endl;
  }
}