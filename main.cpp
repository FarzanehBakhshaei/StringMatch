#include <vector>
#include <array>
#include <string>
#include <map>

#include <assert.h>

#include "helper.h"

bool AreEqual(std::string T, size_t start, size_t end, size_t match_start, size_t match_end, char c) {
  assert(end - start == match_end - match_start + 1);
  
  bool equal = true;
  for (size_t i = start, j = 0; i < end-1; i++, j++) {
    if (T[i] != T[match_start + j]) {
      equal = false;
      break;
    }
  }

  if (equal && T[end - 1] != c)
    return false;

  return equal;
}

std::vector<std::map<char, int>> makeDeltaTable(std::string T, std::vector<char> alphabet) {
  std::vector<std::map<char, int>> delta(T.size()+1);
  for (size_t i = 0; i < T.size()+1; i++) {
    for (size_t j = 0; j < alphabet.size(); j++)
      delta[i][alphabet[j]] = 0;
  }

  delta[0][T[0]] = 1;

  for (size_t j = 0; j < T.size()+1; j++) {
    for (auto c : alphabet) {
      size_t k = (std::min)(T.size(), j + 1);
      delta[j][c] = 0;
      while (k > 0) {
        if (AreEqual(T, 0, k, j - k + 1, j, c)) {
          delta[j][c] = k;
          break;
        }

        k--;
      }
    }
  }

  return delta;
}

void matchString(std::string S, std::string T, std::vector<char> alphabet, std::vector<std::map<char, int>> deltaTable) {
  int state = 0;   // Starting state
  for (size_t i = 0; i < S.size(); i++) {
    state = deltaTable[state][S[i]];
    if (state == T.size()) {
      std::cout << std::string(S.begin(), S.begin() + i + 1) << std::endl;
    }
  }
}

void main() {
  std::string S = "abggxaxabgxb";
  std::string T = "gxa";
  std::string alphabet_str = "gxab";

  std::vector<char> alphabet;
  for (auto a : alphabet_str)
    alphabet.push_back(a);

  std::vector<std::map<char, int>> deltaTable = makeDeltaTable(T, alphabet);

  std::cout << "string: " << S << ", matching pattern: " << T << std::endl;
  std::cout << "alphabet: { ";
  for (size_t i = 0; i < alphabet.size(); i++) {
    std::cout << alphabet[i];
    if (i == alphabet.size() - 1)
      std::cout << " }\n";
    else
      std::cout << ", ";
  }
  std::cout << "=====================================================\n";
  std::cout << "Delta Table: \n";
  std::cout << "=====================================================\n";

  showDeltaTable(deltaTable, alphabet);

  std::cout << "\n\n=====================================================\n";
  std::cout << "Matching: \n";
  std::cout << "=====================================================\n";
  matchString(S, T, alphabet, deltaTable);
}