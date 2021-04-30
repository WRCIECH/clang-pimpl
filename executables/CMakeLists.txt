add_executable(clang-order-fields 
    clang_order_fields.cc
    command_line_files_keeper.cc
)

target_link_libraries(clang-order-fields order-fields-lib)