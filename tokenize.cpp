#include "tokenize.hpp"
#include <cctype>

#include <iostream>

TokenSequenceType tokenize(std::istream &seq)
{
  TokenSequenceType tokens; // a deque of string type tokens

  std::string str;

  bool comment = false;

  while (std::getline(seq, str, ' ')) // find each string delimited by a space and tokenize it
  {
    int size = str.length();

    std::string token; // start with an empty token

    if (comment) // truncates everything before the newline character in a commented part of the string
    {
      CommentLine(str, comment);
    }

    size = str.length();

    tokenizing(token, tokens, str, comment);

    if (comment) // skip the loop for each token in that commented line (until a newline character is encountered)
    {
      continue;
    }

    // if there exists a token to be pushed/queued, then push it. // Ex: when a number or group of characters follow ( like in "(begin"
    // Then, "begin" must be added as a token once all the characters of the string have been completely parsed
    if (!token.empty())
    {
      tokens.push_back(token);
    }
  }

  return tokens;
}

void CommentLine(std::string &str, bool &comment)
{
  int size = str.length();

  for (int i = 0; i < size; i++)
  {
    if (str[i] == '\n' || str[i] == 13) // if a new line or CRF character is encountered, the new string truncates this character
    {
      int x = i + 1;

      // skip cascading newlines or carriage returns (i.e. CRF).
      while (str[x] == '\n' || str[x] == 13)
      {
        x++;
      }

      str = str.substr(x, size - (x));

      // also, the previously encountered comment character ; is no longer in effect as \n was encountered
      // Because anything after \n is treated as a completely different expression altogether.
      comment = false;
      break;
    }
  }
}

void tokenizing(std::string &token, TokenSequenceType &tokens, std::string &str, bool &comment)
{
  int size = str.length();

  for (int i = 0; i < size; i++)
  {
    if (comment) // break out of this loop if a comment is in effect
    {
      break;
    }

    if (str[i] == COMMENT) //if a ';' is encountered, then everything after it is a comment.
    {
      if (!token.empty() && token != ";") //if a token has already built up before encountering this comment and doesn't just contain a ';'
      {
        tokens.push_back(token); //then it's pushed back as a token (queued), and made empty
        token = "";
      }

      comment = true;

      break;
    }

    if (str[i] == '\n' || str[i] == 13) // skip tokenizing the end of line character or carriage return
    {
      continue;
    }

    if (str[i] == OPEN || str[i] == CLOSE) //if a character is either '(' or ')'
    {
      if (!token.empty()) //if a token has already been built up before these characters,
      {
        tokens.push_back(token); //then it's pushed back as a token (queued), and made empty
        token = "";
      }
      tokens.push_back(str.substr(i, 1)); //the parentheses character is pushed as a token
    }
    else
    {
      token += str[i]; // else, build up the token character by character
    }
  }
}