project(battleships_buggy LANGUAGES CXX)

add_library(battleships_buggy_core
    src/core/Board.cpp
    src/core/Game.cpp
    src/core/Ship.cpp
)
target_include_directories(battleships_buggy_core PUBLIC src)
target_compile_features(battleships_buggy_core PUBLIC cxx_std_20)

# Intentionally less strict
if (MSVC)
  target_compile_options(battleships_buggy_core PRIVATE /W3)
else()
  target_compile_options(battleships_buggy_core PRIVATE -Wall -Wextra)
endif()

add_executable(battleships_buggy_cli
    apps/battleships_cli/main.cpp
    src/cli/ConsoleRenderer.cpp
    src/cli/Input.cpp
)
target_link_libraries(battleships_buggy_cli PRIVATE battleships_buggy_core)
target_include_directories(battleships_buggy_cli PRIVATE src)

enable_testing()
add_executable(battleships_buggy_tests tests/core_tests.cpp)
target_link_libraries(battleships_buggy_tests PRIVATE battleships_buggy_core)
add_test(NAME battleships_buggy_tests COMMAND battleships_buggy_tests)