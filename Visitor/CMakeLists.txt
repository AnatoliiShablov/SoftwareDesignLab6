project(Visitor LANGUAGES CXX)

add_library(${PROJECT_NAME}
    include/TokenVisitor.hpp   src/TokenVisitor.cpp
    include/ParserVisitor.hpp  src/ParserVisitor.cpp
    include/CalcVisitor.hpp    src/CalcVisitor.cpp
    include/PrintVisitor.hpp   src/PrintVisitor.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} INTERFACE include)

target_link_libraries(${PROJECT_NAME} PRIVATE Tokenizer)
