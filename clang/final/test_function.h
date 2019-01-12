#ifndef __TESTPARSEFUNC__H__
#define __TESTPARSEFUNC__H__
enum instruction { NO_INST, DO_LT, DO_FD, DO_RT};
typedef enum instruction instruct;
bool test_start (Prog *s);
bool test_end(Prog *s);
void test_statement(Prog *p);
bool test_load_varnum(Prog *p);
void test_for_loop(Prog *p);
void test_instruction(Prog *p);
void test_code(Prog *p);
bool test_start_num (Prog *p);
void test_set_var(Prog *p);
bool test_assign_value(Prog *p);
bool test_end_num (Prog *p);
void test_all(Prog *s);
#endif
