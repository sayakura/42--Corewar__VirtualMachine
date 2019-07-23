#include "../include/test.h"
#include "helper.h"

char buffer[1024];

void    before(void)
{ 
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buffer);
}

void    after(void)
{ 
    freopen("/dev/tty", "a", stdout);
}

void    test_h_rev_bytes()
{
    static unsigned int tests[] = {
        0x0A0B0C0D, 
        0x0,
        0x0D0A0000,
        0x00000001
    };

    h_rev_bytes(&tests[0], sizeof(tests[0]));
    CU_ASSERT_EQUAL(tests[0], 0x0D0C0B0A);
    h_rev_bytes(&tests[1], sizeof(tests[1]));
    CU_ASSERT_EQUAL(tests[1], 0);
    h_rev_bytes(&tests[2], sizeof(tests[2]));
    CU_ASSERT_EQUAL(tests[2], 0x00000A0D);
    h_rev_bytes(&tests[3], sizeof(tests[3]));
    CU_ASSERT_EQUAL(tests[3], 0x01000000);
}

void    test_helper(CU_pSuite *suite)
{
    CU_add_test(*suite, "test if test_h_rev_bytes flips the bytes", test_h_rev_bytes);
}