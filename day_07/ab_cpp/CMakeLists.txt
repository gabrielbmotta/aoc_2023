cmake_minimum_required(VERSION 3.10)

project(CamelCardsWinner VERSION 1.0)

configure_file(main.h.in main.h)

add_library(Hand hand.cpp)
target_include_directories(Hand PUBLIC
    ${PROJECT_SOURCE_DIR}
)

add_library(CamelCards camel_cards.cpp)
target_link_libraries(CamelCards PUBLIC
    Hand
)
target_include_directories(CamelCards PUBLIC
    ${PROJECT_SOURCE_DIR}
)

add_executable(CamelCardsWinner main.cpp)
target_link_libraries(CamelCardsWinner PUBLIC
    CamelCards
)
target_include_directories(CamelCardsWinner PUBLIC
    ${PROJECT_BINARY_DIR}
)

enable_testing()

add_test(NAME Example COMMAND CamelCardsWinner ${PROJECT_SOURCE_DIR}/input_example)
set_tests_properties(Example
    PROPERTIES PASS_REGULAR_EXPRESSION "Total winnings: 6440"
)
