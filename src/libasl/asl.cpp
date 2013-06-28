#include "precomp/precomp.h"

#include "asl.h"

#include "context/context.h"

// Context
asl_context* asl_context_create()
{
    return ((asl_context*)new asl::context());
}

void asl_context_destroy(asl_context* context)
{
    delete ((asl::context*)context);
}

void asl_context_execute(asl_context* context, const char* file_path)
{
    std::vector<unsigned int> program;
    ((asl::context*)context)->get_vm().load(file_path, program);
    ((asl::context*)context)->get_vm().execute(program);
}
