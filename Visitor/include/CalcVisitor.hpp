#ifndef SD6_VISITOR_CALC_VISITOR_HPP
#define SD6_VISITOR_CALC_VISITOR_HPP

#include <stack>
#include <vector>

#include "TokenVisitor.hpp"

class CalcVisitor : public TokenVisitor {
 public:
  void visit(std::shared_ptr<BraceToken> token) override;
  void visit(std::shared_ptr<NumberToken> token) override;
  void visit(std::shared_ptr<OperationToken> token) override;

  int64_t result() const;

 private:
  std::stack<int64_t> _numbers;
};

#endif
