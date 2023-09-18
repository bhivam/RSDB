#ifndef _TOKENIZER_H
#define _TOKENIZER_H

// TODO Fill in all token types: keywords, operators etc
typedef enum TokenType
{
  LITERAL,
  WHERE,
} TokenType;

typedef struct Token
{
  int line;
  char *lexeme;
  void *literal;
  TokenType token_type;
} Token;

TokenType *tokenize(char *source);

#endif
