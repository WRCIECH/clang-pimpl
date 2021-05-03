llvm_map_components_to_libnames(llvm_libs option core support irreader)
add_clang_library(reorder-fields-lib
  reorder_fields_action.cc
)

clang_target_link_libraries(reorder-fields-lib
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
