#include <fstream>
#include <iostream>
#include <string_view>

#include "CalcVisitor.hpp"
#include "ParserVisitor.hpp"
#include "PrintVisitor.hpp"
#include "TokenizerContext.hpp"

void readFromStdin(std::shared_ptr<TokenizerContext> ctx) {
  while (!std::feof(stdin)) {
    ctx->proceedNextCharacter(std::getc(stdin));
  }
}

void readFromFile(std::shared_ptr<TokenizerContext> ctx,
                  std::string_view fileName) {
  std::ifstream file(fileName.data());
  while (!file.eof()) {
    ctx->proceedNextCharacter(file.get());
  }
}

int main(int argc, char* argv[]) {
  try {
    auto tokenizer = std::make_shared<TokenizerContext>();

    if (argc == 2 && std::string_view(argv[1]) != "-") {
      readFromFile(tokenizer, argv[1]);
    } else {
      readFromStdin(tokenizer);
    }

    auto const& fileTokens = tokenizer->tokens();

    auto parser = std::make_shared<ParserVisitor>();
    std::for_each(fileTokens.begin(), fileTokens.end(),
                  [&parser](auto token) { token->accept(parser); });

    auto const& parserTokens = parser->tokens();

    auto printer = std::make_shared<PrintVisitor>();
    std::for_each(parserTokens.begin(), parserTokens.end(),
                  [&printer](auto token) { token->accept(printer); });

    auto calculator = std::make_shared<CalcVisitor>();
    std::for_each(parserTokens.begin(), parserTokens.end(),
                  [&calculator](auto token) { token->accept(calculator); });

    std::cout << std::endl << calculator->result() << std::endl;

  } catch (std::runtime_error const& err) {
    std::cout << err.what();
    return -1;
  }
  return 0;
}
