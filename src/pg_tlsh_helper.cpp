#define _XOPEN_SOURCE
#include "tlsh.h"
#include "pg_tlsh_helper.h"

extern "C" {
    int tlsh_similarity(char *hash1, char *hash2) {
        Tlsh TlshA, TlshB;
        TlshA.fromTlshStr(hash1);
        TlshB.fromTlshStr(hash2);
        return TlshA.totalDiff(&TlshB);
    }
}