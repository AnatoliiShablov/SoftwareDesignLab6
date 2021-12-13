#include "CalcVisitor.hpp"

void CalcVisitor::visit(std::shared_ptr<BraceToken> token) {
  throw std::runtime_error("CalcVisitor cannot accept braces");
}

void CalcVisitor::visit(std::shared_ptr<NumberToken> token) {
  _numbers.push(token->value());
}

void CalcVisitor::visit(std::shared_ptr<OperationToken> token) {
  if (_numbers.size() < 2) {
    throw std::runtime_error("Not enough args to proceed operation");
  }
  auto right = _numbers.top();
  _numbers.pop();
  auto left = _numbers.top();
  _numbers.pop();

  switch (token->type()) {
    case OperationToken::Type::Addition:
      _numbers.push(left + right);
      break;
    case OperationToken::Type::Subtraction:
      _numbers.push(left - right);
      break;
    case OperationToken::Type::Multiplication:
      _numbers.push(left * right);
      break;
    case OperationToken::Type::Division:
      _numbers.push(left / right);
      break;
    default:
      throw std::runtime_error("Unknown OperationToken");
  }
}

int64_t CalcVisitor::result() const {
  if (_numbers.size() != 1) {
    throw std::runtime_error("Failed to calc");
  }
  return _numbers.top();
}
