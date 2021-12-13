#include <fstream>
#include <iostream>

#include "CalcVisitor.hpp"
#include "ParserVisitor.hpp"
#include "PrintVisitor.hpp"
#include "TokenizerContext.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage:\n\tSD6 INPUT_FILE" << std::endl;
    return -1;
  }

  auto tokenizer = std::make_shared<TokenizerContext>();
  {
    std::ifstream file(argv[1]);
    while (!file.eof()) {
      tokenizer->proceedNextCharacter(file.get());
    }
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

  return 0;
}
