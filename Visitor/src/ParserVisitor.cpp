#include "ParserVisitor.hpp"

void ParserVisitor::visit(std::shared_ptr<BraceToken> token) {
  switch (token->type()) {
    case BraceToken::Type::Left:
      _tmpTokens.emplace(std::move(token));
      return;
    case BraceToken::Type::Right:
      while (!_tmpTokens.empty() && !getTopOrNull<BraceToken>()) {
        _tokens.emplace_back(_tmpTokens.top());
        _tmpTokens.pop();
      }
      if (auto ptr = getTopOrNull<BraceToken>();
          ptr && ptr->type() == BraceToken::Type::Left) {
        _tmpTokens.pop();
      } else {
        throw std::runtime_error("Left brace not found");
      }
      return;
  }
  throw std::runtime_error("Incorrect type");
}

void ParserVisitor::visit(std::shared_ptr<NumberToken> token) {
  _tokens.emplace_back(std::move(token));
}

void ParserVisitor::visit(std::shared_ptr<OperationToken> token) {
  for (auto ptr = getTopOrNull<OperationToken>();
       ptr && ptr->priority() <= token->priority();
       ptr = getTopOrNull<OperationToken>()) {
    _tokens.emplace_back(_tmpTokens.top());
    _tmpTokens.pop();
  }
  _tmpTokens.emplace(std::move(token));
}

const std::vector<std::shared_ptr<Token> > &ParserVisitor::tokens() & {
  finalize();
  return _tokens;
}

const std::vector<std::shared_ptr<Token> > &&ParserVisitor::tokens() && {
  finalize();
  return std::move(_tokens);
}

void ParserVisitor::finalize() {
  while (!_tmpTokens.empty()) {
    if (getTopOrNull<BraceToken>()) {
      throw std::runtime_error("Not closed brace found");
    }
    _tokens.emplace_back(std::move(_tmpTokens.top()));
    _tmpTokens.pop();
  }
}
