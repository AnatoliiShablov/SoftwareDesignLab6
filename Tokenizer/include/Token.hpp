#ifndef SD6_TOKENIZER_TOKEN_HPP
#define SD6_TOKENIZER_TOKEN_HPP

#include <memory>

class TokenVisitor;

class Token : public std::enable_shared_from_this<Token> {
 public:
  virtual void accept(std::shared_ptr<TokenVisitor> visitor) = 0;
  virtual ~Token();

 protected:
  template <typename Derived>
  std::shared_ptr<Derived> shared_from_base() {
    return std::static_pointer_cast<Derived>(shared_from_this());
  }

  template <typename Derived>
  std::shared_ptr<std::add_const_t<Derived>> shared_from_base() const {
    return std::static_pointer_cast<Derived>(shared_from_this());
  }
};

class BraceToken : public Token {
 public:
  enum class Type { Left, Right };
  constexpr BraceToken(Type type) noexcept : _type{type} {}
  constexpr Type type() const noexcept { return _type; }
  void accept(std::shared_ptr<TokenVisitor> visitor) override;

 private:
  Type _type;
};

static std::shared_ptr<Token> LBraceToken =
    std::make_shared<BraceToken>(BraceToken::Type::Left);
static std::shared_ptr<Token> RBraceToken =
    std::make_shared<BraceToken>(BraceToken::Type::Right);

class NumberToken : public Token {
 public:
  constexpr NumberToken(uint64_t value) noexcept : _value{value} {}
  void accept(std::shared_ptr<TokenVisitor> visitor) override;

 private:
  uint64_t _value;
};

class OperationToken : public Token {
 public:
  enum class Type { Addition, Subtraction, Multiplication, Division };
  constexpr OperationToken(Type type, uint32_t priority) noexcept
      : _type{type}, _priority{priority} {}
  constexpr Type type() const noexcept { return _type; }
  constexpr uint32_t priority() const noexcept { return _priority; }
  void accept(std::shared_ptr<TokenVisitor> visitor) override;

 private:
  Type _type;
  uint32_t _priority;
};

static std::shared_ptr<Token> AdditionToken =
    std::make_shared<OperationToken>(OperationToken::Type::Addition, 5);
static std::shared_ptr<Token> SubtractionToken =
    std::make_shared<OperationToken>(OperationToken::Type::Subtraction, 5);
static std::shared_ptr<Token> MultiplicationToken =
    std::make_shared<OperationToken>(OperationToken::Type::Multiplication, 4);
static std::shared_ptr<Token> DivisionToken =
    std::make_shared<OperationToken>(OperationToken::Type::Division, 4);

#endif
