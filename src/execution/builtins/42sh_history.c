#include "42sh_history.h"

/**
** \file 42sh_history.c
** \brief This function writes in the history file any input in the shell
** \param input: the input of the user
*/
void put_in_history(char *input)
{
    add_history(input);
}

/**
** \brief This function checks for 'history' command
** \param input: the input of the user
*/
bool read_builtin_history(char *input)
{
    struct parser *p = parser_new_from_string(input);

    if (read_spaces(p) && parser_readtext(p, "history") && read_spaces(p))
    {
        parser_free(p);
        return true;
    }

    parser_free(p);
    return false;
}

/**
** \brief This function prints the results of the 'history' command
*/
int my_read_history(char **voidarg)
{
    voidarg++;
    HISTORY_STATE *historytoprint = history_get_history_state();
    HIST_ENTRY **listhistory = history_list();

    for (int i = 0; i < historytoprint->length; i++)
    {
        printf("%d %s %s\n",i , listhistory[i]->line, listhistory[i]->timestamp);
        free_history_entry(listhistory[i]);
    }

    free(historytoprint);
    free(listhistory);

    return 0;
}