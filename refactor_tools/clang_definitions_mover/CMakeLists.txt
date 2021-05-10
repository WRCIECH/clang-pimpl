add_library(definitions-mover-lib
  definitions_mover_action.cc
  definitions_mover_refactor_adapter.cc
)

target_link_libraries(definitions-mover-lib PRIVATE clangTooling)
