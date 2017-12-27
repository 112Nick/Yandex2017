#include <cctype>
#include <cstdio>
#include <iostream>

enum State {
  SENTENCE_END,
  SENTENCE_BEGIN,
  WORD_INSIDE,
  SENTENCE_SPACE,
  WORD_END,
  FAIL
};

bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main() {
    State currentState = SENTENCE_SPACE;
    char cur;
    std::string output;
    while ((cur = std::getchar()) != EOF) {
        if (isAlpha(cur)) {
            if (currentState == SENTENCE_SPACE) {
                output.push_back(std::toupper(cur));
                currentState = SENTENCE_BEGIN;
            } 
            else if (currentState == SENTENCE_END) {
                output.push_back(' ');
                output.push_back(std::toupper(cur));
                currentState = SENTENCE_BEGIN;
            } 
            else if (currentState == SENTENCE_BEGIN ||
                currentState == WORD_INSIDE || currentState == WORD_END) {
                output.push_back(std::tolower(cur));
                currentState = WORD_INSIDE;
            } 
            else {
                currentState = FAIL;
                break;
            }
        } 
        else if (cur == '.') {
            if (currentState == WORD_INSIDE || currentState == SENTENCE_BEGIN) {
                output.push_back('.');
                currentState = SENTENCE_END;
            } 
            else if (currentState == WORD_END) {
                output[output.size() - 1] = '.';
                currentState = SENTENCE_END;
            } 
            else {
                currentState = FAIL;
               break;
            }
        } 
        else if (cur == ' ') {
            if (currentState == SENTENCE_END) {
                output.push_back(' ');
                currentState = SENTENCE_SPACE;
            } 
            else if (currentState == WORD_INSIDE ||
                currentState == SENTENCE_BEGIN) {
                output.push_back(' ');
                currentState = WORD_END;
            }
            else if (currentState == SENTENCE_SPACE || currentState == WORD_END) {
                continue;
            }
             
            else {
                currentState = FAIL;
                break;
            }
        }
    }

    if (currentState == SENTENCE_SPACE && output[output.size() - 1] == ' ') {
        output.resize(output.size() - 1);
        currentState = SENTENCE_END;
    }
    if (currentState == SENTENCE_END) {
        std::cout << output << std::endl;
    } 
    else {
        std::cout << -1 << std::endl;
    }
    return 0;
}