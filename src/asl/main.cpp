#include "asl.h"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        asl_context* context = asl_context_create();
        {
            asl_context_execute(context, argv[1]);
        }
        asl_context_destroy(context);
    }

    return (0);
}
