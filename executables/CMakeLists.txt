add_executable(clang-order-fields 
    clang_reorder_fields.cc
)

target_link_libraries(clang-order-fields refactor-adapter-lib reorder-fields-lib)