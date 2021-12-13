project(Tokenizer LANGUAGES CXX)

add_library(${PROJECT_NAME}
            include/Token.hpp   src/Token.cpp
            include/TokenizerContext.hpp src/TokenizerContext.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} INTERFACE include)

target_link_libraries(${PROJECT_NAME} PRIVATE Visitor)
