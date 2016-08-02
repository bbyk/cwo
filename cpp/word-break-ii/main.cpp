// https://leetcode.com/problems/word-break-ii/

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    using sit = string::iterator;
    // in "cat sand dog", "cats and dog", the dog part is common and can be cached
    // reducing traversal in the backtracking
    unordered_map<char*, vector<string>> cache;
    unordered_set<string> *wordDict;

    vector<string>& wordBreak(sit begin, sit end) {
        auto cit = cache.find(&(*begin));
        if (cit == cache.end()) {
            cit = cache.insert({&(*begin), {}}).first;
            string word;
            for (auto i = begin; i != end; ++i) {
                word.append(1, *i);
                if (wordDict->find(word) != wordDict->end()) {
                    for (auto& wordR : wordBreak(i + 1, end)) {
                        cit->second.push_back(word + ' ' + wordR);
                    }
                    
                    // the case the word was last in the string
                    if ((i + 1) == end) {
                        cit->second.push_back(word);
                    }
                }
            }
        }
        
        return cit->second;
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        this->wordDict = &wordDict;
        return wordBreak(s.begin(), s.end());
    }
};

int main() {
    Solution solution;
    unordered_set<string> wordDict = { "cat", "cats", "and", "sand", "dog" };
    for (auto& sentence : solution.wordBreak("catsanddog", wordDict)) {
        cout << sentence << endl;
    }
    return 0;
}
