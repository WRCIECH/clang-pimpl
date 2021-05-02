add_executable(clang-order-fields 
    clang_order_fields.cc
)

target_link_libraries(clang-order-fields refactor-adapter-lib order-fields-lib)