#include "PrintVisitor.hpp"

#include <iostream>

void PrintVisitor::visit(std::shared_ptr<BraceToken> token) {
  throw std::runtime_error("PrintVisitor cannot accept braces");
}

void PrintVisitor::visit(std::shared_ptr<NumberToken> token) {
  std::cout << token->value() << ' ';
}

void PrintVisitor::visit(std::shared_ptr<OperationToken> token) {
  switch (token->type()) {
    case OperationToken::Type::Addition:
      std::cout << '+';
      break;
    case OperationToken::Type::Subtraction:
      std::cout << '-';
      break;
    case OperationToken::Type::Multiplication:
      std::cout << '*';
      break;
    case OperationToken::Type::Division:
      std::cout << '/';
      break;
    default:
      throw std::runtime_error("Unknown OperationToken");
  }
  std::cout << ' ';
}
