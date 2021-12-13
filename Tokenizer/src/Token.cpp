#include "Token.hpp"

#include "TokenVisitor.hpp"

Token::~Token() = default;

void BraceToken::accept(std::shared_ptr<TokenVisitor> visitor) {
  visitor->visit(shared_from_base<std::remove_pointer_t<decltype(this)>>());
}

void NumberToken::accept(std::shared_ptr<TokenVisitor> visitor) {
  visitor->visit(shared_from_base<std::remove_pointer_t<decltype(this)>>());
}

void OperationToken::accept(std::shared_ptr<TokenVisitor> visitor) {
  visitor->visit(shared_from_base<std::remove_pointer_t<decltype(this)>>());
}
