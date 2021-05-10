add_clang_library(definitions-mover-lib
  definitions_mover_action.cc
  definitions_mover_refactor_adapter.cc
)

clang_target_link_libraries(definitions-mover-lib PRIVATE clangTooling)
