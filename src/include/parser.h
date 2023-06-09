#pragma once

#include "ast.h"
#include "utils.h"

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
/// token the parser is looking at.  getNextToken reads another token from the
/// lexer and updates CurTok with its results.
extern int CurTok;
extern int getNextToken();

/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.
extern std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
int GetTokPrecedence(); 

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str); 

std::unique_ptr<PrototypeAST> LogErrorP(const char *Str); 

std::unique_ptr<ExprAST> ParseExpression();

/// numberexpr ::= number
std::unique_ptr<ExprAST> ParseNumberExpr();

/// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> ParseParenExpr();

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> ParseIdentifierExpr();

/// ifexpr ::= 'if' expression 'then' expression 'else' expression
std::unique_ptr<ExprAST> ParseIfExpr();

/// forexpr ::= 'for' identifier '=' expr ',' expr (',' expr)? 'in' expression
std::unique_ptr<ExprAST> ParseForExpr();

/// varexpr ::= 'var' identifier ('=' expression)?
//                    (',' identifier ('=' expression)?)* 'in' expression
std::unique_ptr<ExprAST> ParseVarExpr();

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
///   ::= ifexpr
///   ::= forexpr
///   ::= varexpr
std::unique_ptr<ExprAST> ParsePrimary();

/// unary
///   ::= primary
///   ::= '!' unary
std::unique_ptr<ExprAST> ParseUnary();

/// binoprhs
///   ::= ('+' unary)*
std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);

/// expression
///   ::= unary binoprhs
///
std::unique_ptr<ExprAST> ParseExpression();

/// prototype
///   ::= id '(' id* ')'
///   ::= binary LETTER number? (id, id)
///   ::= unary LETTER (id)
std::unique_ptr<PrototypeAST> ParsePrototype();

/// definition ::= 'def' prototype expression
std::unique_ptr<FunctionAST> ParseDefinition();

/// toplevelexpr ::= expression
std::unique_ptr<FunctionAST> ParseTopLevelExpr();

/// external ::= 'extern' prototype
std::unique_ptr<PrototypeAST> ParseExtern();
