add_library(reorder-fields-lib
  reorder_fields_action.cc
  reorder_fields_refactor_adapter.cc
)

target_link_libraries(reorder-fields-lib PRIVATE clangTooling)
