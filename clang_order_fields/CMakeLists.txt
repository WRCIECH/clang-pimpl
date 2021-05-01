llvm_map_components_to_libnames(llvm_libs option core support irreader)
add_clang_library(order-fields-lib
  clang_order_fields_master.cc
  order_fields_action.cc
)

clang_target_link_libraries(order-fields-lib
  PRIVATE
${llvm_libs}
clangAST
clangASTMatchers
clangBasic
clangIndex
clangLex
clangSerialization
clangToolingCore
clangBasic
clangFrontend
clangRewrite
clangSerialization
clangTooling
  )
