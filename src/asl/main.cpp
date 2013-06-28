#include "asl.h"

int main(int argc, char** argv)
{
    asl_context* context = asl_context_create();
    {
        asl_context_execute(context, "test.asl");
    }
    asl_context_destroy(context);

    return (0);
}
