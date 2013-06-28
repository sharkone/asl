#pragma once

// Context
struct asl_context;

asl_context*    asl_context_create();
void            asl_context_destroy(asl_context* context);

void            asl_context_execute(asl_context* context, const char* file_path);
