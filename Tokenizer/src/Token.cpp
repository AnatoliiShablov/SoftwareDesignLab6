#include "Token.hpp"

Token::~Token() = default;

constexpr BraceToken::BraceToken(Type type) noexcept : _type{type} {}

void BraceToken::accept(std::shared_ptr<TokenVisitor> visitor) {
  visitor->visit(shared_from_base<std::remove_pointer_t<decltype(this)>>());
}

constexpr NumberToken::NumberToken(uint64_t value) noexcept : _value{value} {}

void NumberToken::accept(std::shared_ptr<TokenVisitor> visitor) {
  visitor->visit(shared_from_base<std::remove_pointer_t<decltype(this)>>());
}

constexpr OperationToken::OperationToken(Type type) noexcept : _type{type} {}

void OperationToken::accept(std::shared_ptr<TokenVisitor> visitor) {
  visitor->visit(shared_from_base<std::remove_pointer_t<decltype(this)>>());
}

TokenVisitor::~TokenVisitor() = default;
