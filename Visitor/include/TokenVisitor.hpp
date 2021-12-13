#ifndef SD6_VISITOR_TOKEN_VISITOR_HPP
#define SD6_VISITOR_TOKEN_VISITOR_HPP

#include <memory>

#include "Token.hpp"

class TokenVisitor : public std::enable_shared_from_this<TokenVisitor> {
 public:
  virtual void visit(std::shared_ptr<BraceToken> token) = 0;
  virtual void visit(std::shared_ptr<NumberToken> token) = 0;
  virtual void visit(std::shared_ptr<OperationToken> token) = 0;

  virtual ~TokenVisitor();
};

#endif
