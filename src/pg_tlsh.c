#define _XOPEN_SOURCE
// PostgreSQL includes
#include <postgres.h>
#include <fmgr.h>
#include <utils/builtins.h> // for text_to_cstring()

// Project includes
#include "pg_tlsh_helper.h"

PG_MODULE_MAGIC;

// Final step: Make the code available to SQL by loading the library.
// CREATE OR REPLACE FUNCTION tlsh_compare(TEXT, TEXT) RETURNS INTEGER AS 'tlsh_psql.so', 'pg_tlsh_compare' LANGUAGE 'c';

PG_FUNCTION_INFO_V1(pg_tlsh_compare);
Datum pg_tlsh_compare(PG_FUNCTION_ARGS) {
    if (PG_ARGISNULL(0) || PG_ARGISNULL(1)) {
        PG_RETURN_INT32(0);
    }
    text *arg1 = PG_GETARG_TEXT_P(0);
    text *arg2 = PG_GETARG_TEXT_P(1);
    char* hash1 = text_to_cstring(arg1);
    char* hash2 = text_to_cstring(arg2);

    int score = tlsh_similarity(hash1, hash2);

    pfree(hash1);
    pfree(hash2);

    PG_RETURN_INT32(score);
}

