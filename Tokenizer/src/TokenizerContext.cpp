#include "TokenizerContext.hpp"

State::~State() = default;

void EmptyState::proceedCharacter(std::shared_ptr<TokenizerContext> context,
                                  int symbol) {
  if (symbol == EOF) {
    context->setState(EndStateV);
    return;
  }

  if (symbol >= '0' && symbol <= '9') {
    auto state = std::make_shared<NumberState>();
    context->setState(state);
    state->proceedCharacter(context, symbol);
    return;
  }

  if (static_cast<unsigned char>(symbol) != symbol) {
    context->setState(ErrorStateV);
    return;
  }

  if (std::isspace(static_cast<unsigned char>(symbol))) {
    return;
  }

  switch (symbol) {
    case '(':
      context->addToken(LBraceToken);
      break;
    case ')':
      context->addToken(RBraceToken);
      break;
    case '+':
      context->addToken(AdditionToken);
      break;
    case '-':
      context->addToken(SubtractionToken);
      break;
    case '*':
      context->addToken(MultiplicationToken);
      break;
    case '/':
      context->addToken(DivisionToken);
      break;
    default:
      context->setState(ErrorStateV);
      break;
  }
}

void ErrorState::proceedCharacter(std::shared_ptr<TokenizerContext> context,
                                  int symbol) {
  // Do nothing
}

void NumberState::proceedCharacter(std::shared_ptr<TokenizerContext> context,
                                   int symbol) {
  if (symbol >= '0' && symbol <= '9') {
    _value = _value * 10 + (symbol - '0');
    return;
  }

  context->addToken(std::make_shared<NumberToken>(_value));

  auto state = std::make_shared<EmptyState>();
  context->setState(state);
  state->proceedCharacter(context, symbol);
  return;
}

void EndState::proceedCharacter(std::shared_ptr<TokenizerContext> context,
                                int symbol) {
  context->setState(EndStateV);
}

TokenizerContext::TokenizerContext() : _currentState{EmptyStateV} {}

void TokenizerContext::proceedNextCharacter(int symbol) {
  _currentState->proceedCharacter(shared_from_this(), symbol);
}

void TokenizerContext::addToken(std::shared_ptr<Token> token) {
  _tokens.emplace_back(std::move(token));
}

namespace {
void throwIfFailed(std::shared_ptr<State> state) {
  if (!state || !dynamic_cast<EndState *>(state.get())) {
    throw std::runtime_error("Parsing failed");
  }
}
}  // namespace

const std::vector<std::shared_ptr<Token> > &TokenizerContext::tokens() const & {
  throwIfFailed(_currentState);
  return _tokens;
}

const std::vector<std::shared_ptr<Token> > &&TokenizerContext::tokens()
    const && {
  throwIfFailed(_currentState);
  return std::move(_tokens);
}
