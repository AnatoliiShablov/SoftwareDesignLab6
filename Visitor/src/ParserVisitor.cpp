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
  if (!_isFinalized) {
    while (!_tmpTokens.empty()) {
      if (getTopOrNull<BraceToken>()) {
        throw std::runtime_error("Not closed brace found");
      }
      _tokens.emplace_back(std::move(_tmpTokens.top()));
      _tmpTokens.pop();
    }

    size_t counter = 0;

    for (auto const &t : _tokens) {
      if (dynamic_cast<NumberToken *>(t.get())) {
        ++counter;
      }
      if (dynamic_cast<OperationToken *>(t.get())) {
        if (counter == 0) {
          throw std::runtime_error("Not enough args for operation");
        }
        --counter;
      }
    }

    if (counter != 1) {
      throw std::runtime_error("Too many args");
    }

    _isFinalized = true;
  }
}
