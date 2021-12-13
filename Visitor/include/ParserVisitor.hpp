#ifndef SD6_VISITOR_PARSER_VISITOR_HPP
#define SD6_VISITOR_PARSER_VISITOR_HPP

#include <stack>
#include <vector>

#include "TokenVisitor.hpp"

class ParserVisitor : public TokenVisitor {
 public:
  void visit(std::shared_ptr<BraceToken> token) override;
  void visit(std::shared_ptr<NumberToken> token) override;
  void visit(std::shared_ptr<OperationToken> token) override;

  std::vector<std::shared_ptr<Token>> const& tokens() &;
  std::vector<std::shared_ptr<Token>> const&& tokens() &&;

 private:
  template <typename T>
  T* getTopOrNull() {
    return _tmpTokens.empty() ? nullptr
                              : dynamic_cast<T*>(_tmpTokens.top().get());
  }

  void finalize();

  std::stack<std::shared_ptr<Token>> _tmpTokens;
  std::vector<std::shared_ptr<Token>> _tokens;
};

#endif
