project(battleships_good LANGUAGES CXX)

add_library(battleships_good_core
    src/core/Board.cpp
    src/core/Game.cpp
    src/core/Ship.cpp
)
target_include_directories(battleships_good_core PUBLIC src)
target_compile_features(battleships_good_core PUBLIC cxx_std_20)

# Strict warnings in the good version
if (MSVC)
  target_compile_options(battleships_good_core PRIVATE /W4 /WX)
else()
  target_compile_options(battleships_good_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(battleships_good_cli
    apps/battleships_cli/main.cpp
    src/cli/ConsoleRenderer.cpp
    src/cli/Input.cpp
)
target_link_libraries(battleships_good_cli PRIVATE battleships_good_core)
target_include_directories(battleships_good_cli PRIVATE src)

enable_testing()
add_executable(battleships_good_tests tests/core_tests.cpp)
target_link_libraries(battleships_good_tests PRIVATE battleships_good_core)
add_test(NAME battleships_good_tests COMMAND battleships_good_tests)