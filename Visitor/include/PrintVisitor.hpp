#ifndef SD6_VISITOR_PRINT_VISITOR_HPP
#define SD6_VISITOR_PRINT_VISITOR_HPP

#include <stack>
#include <vector>

#include "TokenVisitor.hpp"

class PrintVisitor : public TokenVisitor {
 public:
  void visit(std::shared_ptr<BraceToken> token) override;
  void visit(std::shared_ptr<NumberToken> token) override;
  void visit(std::shared_ptr<OperationToken> token) override;
};

#endif
