add_clang_library(reorder-fields-lib
  reorder_fields_action.cc
  reorder_fields_options_adapter.cc
  reorder_fields_refactor_adapter.cc
)

clang_target_link_libraries(reorder-fields-lib PRIVATE clangTooling)
