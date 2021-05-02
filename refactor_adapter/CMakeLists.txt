llvm_map_components_to_libnames(llvm_libs option core support irreader)
add_clang_library(refactor-adapter-lib
  refactor_adapter.cc
  command_line_files_keeper.cc
)

clang_target_link_libraries(refactor-adapter-lib
  PRIVATE
${llvm_libs}
# all needed?
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
