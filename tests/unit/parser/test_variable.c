#include "test_parser.h"

static void check_variables(char *expected)
{
    char *str = calloc(sizeof(char), 512);

    char buff_str[128];
    struct key_value *buff = variables;
    while (buff)
    {
        sprintf(buff_str, "%s=%s;", buff->key, buff->value);
        strcat(str, buff_str);
        buff = buff->next;
    }

    assert(strcmp(str, expected) == 0);
    free(str);
}

static void test_variables_add(void)
{
    variables_init();

    variables_add(strdup("i"), strdup("0"));
    check_variables("i=0;");

    variables_add(strdup("k"), strdup("15"));
    check_variables("i=0;k=15;");

    variables_add("i", strdup("45"));
    check_variables("i=45;k=15;");

    variables_add("k", strdup("55"));
    check_variables("i=45;k=55;");

    variables_add(strdup("docker"), strdup("compose"));
    check_variables("i=45;k=55;docker=compose;");

    variables_add("docker", strdup("swarm"));
    check_variables("i=45;k=55;docker=swarm;");

    variables_add(strdup("google"), strdup("search"));
    check_variables("i=45;k=55;docker=swarm;google=search;");

    variables_free();
}
void test_variable_delete(void)
{
    variables_init();

    variables_add(strdup("i"), strdup("0"));
    check_variables("i=0;");

    variables_add(strdup("k"), strdup("15"));
    check_variables("i=0;k=15;");

    variables_add("i", strdup("45"));
    check_variables("i=45;k=15;");

    variables_add("k", strdup("55"));
    check_variables("i=45;k=55;");

    variables_add(strdup("docker"), strdup("compose"));
    check_variables("i=45;k=55;docker=compose;");

    variables_add("docker", strdup("swarm"));
    check_variables("i=45;k=55;docker=swarm;");

    variables_add(strdup("google"), strdup("search"));
    check_variables("i=45;k=55;docker=swarm;google=search;");

    variables_delete("google");
    check_variables("i=45;k=55;docker=swarm;");

    variables_delete("k");
    check_variables("i=45;docker=swarm;");

    variables_delete("i");
    check_variables("docker=swarm;");

    variables_delete("docker");
    check_variables("");

    variables_add(strdup("docker"), strdup("kubernetes"));
    check_variables("docker=kubernetes;");

    variables_delete("docker");
    check_variables("");

    variables_free();
}

void test_variable(void)
{
    test_variables_add();
    test_variable_delete();
}