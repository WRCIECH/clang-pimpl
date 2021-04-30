add_library(order-fields-lib
    clang_order_fields_master.cc
    order_fields_action.cc
)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs option core support irreader)

# Link against LLVM libraries
target_link_libraries(order-fields-lib
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
