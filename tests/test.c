/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 20:52:52 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/17 20:09:16 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int maxi(int i1, int i2)
{
    return (i1 > i2) ? i1 : i2;
}

void test_maxi(void)
{
    CU_ASSERT(maxi(0,2) == 2);
}

void    run_unit_tesing()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("suit name", 0, 0);

    CU_add_test(suite, "test if maxi function return the correct value", test_maxi);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}

int main() {
    printf("-----------------------------------------------------------\n");
    run_unit_tesing();
    printf("-----------------------------------------------------------\n");
    return 0;
}