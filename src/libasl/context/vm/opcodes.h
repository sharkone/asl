#pragma once

namespace asl
{
    class vm;

    struct opcode
    {
        enum id
        {
            OP_NOP = 0,
           
            OP_PUSH_BOOL,
            OP_PUSH_UINT,
            OP_POP,
            
            OP_EQUAL,
            OP_NOT_EQUAL,
            OP_GREATER,
            OP_GREATER_EQUAL,
            OP_LESSER,
            OP_LESSER_EQUAL,
            
            OP_ADD,
            OP_SUB,
            OP_MUL,
            OP_DIV,

            OP_JMP,

            OP_DUMP_STACK,

            OP_MAX
        };
        
        typedef int (*function_type)(vm& vm, void* data);

        opcode();
        opcode(function_type function, std::size_t data_size);

        function_type   m_function;
        std::size_t     m_data_size;
    };

    int opcode_nop(vm& vm, void* data);
    int opcode_push_bool(vm& vm, void* data);
    int opcode_push_uint(vm& vm, void* data);
    int opcode_pop(vm& vm, void* data);
    
#define BINARY_OP(name)                     \
    int opcode_##name(vm& vm, void* data)
    BINARY_OP(equal);
    BINARY_OP(not_equal);
    BINARY_OP(greater);
    BINARY_OP(greater_equal);
    BINARY_OP(lesser);
    BINARY_OP(lesser_equal);
    BINARY_OP(add);
    BINARY_OP(sub);
    BINARY_OP(mul);
    BINARY_OP(div);
#undef BINARY_OP

    int opcode_jmp(vm& vm, void* data);
    int opcode_dump_stack(vm& vm, void* data);
}
