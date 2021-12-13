#ifndef SD6_TOKENIZER_STATE_HPP
#define SD6_TOKENIZER_STATE_HPP

#include <memory>
#include <vector>

#include "Token.hpp"

class TokenizerContext;

class State : std::enable_shared_from_this<State> {
 public:
  virtual void proceedCharacter(std::shared_ptr<TokenizerContext> context,
                                int symbol) = 0;
  virtual ~State();
};

class EmptyState : public State {
 public:
  void proceedCharacter(std::shared_ptr<TokenizerContext> context,
                        int symbol) override;
};

class ErrorState : public State {
 public:
  void proceedCharacter(std::shared_ptr<TokenizerContext> context,
                        int symbol) override;
};

class NumberState : public State {
 public:
  void proceedCharacter(std::shared_ptr<TokenizerContext> context,
                        int symbol) override;

 private:
  uint64_t _value{0};
};

class EndState : public State {
 public:
  void proceedCharacter(std::shared_ptr<TokenizerContext> context,
                        int symbol) override;
};

static std::shared_ptr<State> EmptyStateV = std::make_shared<EmptyState>();
static std::shared_ptr<State> ErrorStateV = std::make_shared<ErrorState>();
static std::shared_ptr<State> EndStateV = std::make_shared<EndState>();

class TokenizerContext : std::enable_shared_from_this<TokenizerContext> {
 public:
  TokenizerContext();

  void proceedNextCharacter(int symbol);

  void setState(std::shared_ptr<State> state);
  void addToken(std::shared_ptr<Token> token);

  std::vector<std::shared_ptr<Token>> const& tokens() const&;
  std::vector<std::shared_ptr<Token>> const&& tokens() const&&;

 private:
  std::shared_ptr<State> _currentState;
  std::vector<std::shared_ptr<Token>> _tokens;
};

#endif
