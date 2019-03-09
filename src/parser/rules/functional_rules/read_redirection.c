#include <parser/rules/rules.h>

bool read_redirection_1(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readchar(p, '>')
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, word, NULL);
        ast_set_in_parser(p, ast);
        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_2(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readchar(p, '<')
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, word, NULL);
        ast_set_in_parser(p, ast);

        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_3(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, ">>")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, word, NULL);
        ast_set_in_parser(p, ast);

        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_4(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, "<<")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "heredoc")
        && read_heredoc(p))
    {
        char *redirect = parser_get_capture(p, "redirect");
        struct ast_node *ast_heredoc = ast_get_from_parser(p, AST_HEREDOC);
        char *heredoc = strdup(ast_heredoc->data);
        ast_free(ast_heredoc);
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, NULL, heredoc);
        ast_set_in_parser(p, ast);
        return true;
    }
    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "heredoc");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_5(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, "<<-")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "heredoc")
        && read_heredoc(p))
    {
        char *redirect = parser_get_capture(p, "redirect");
        struct ast_node *ast_heredoc = ast_get_from_parser(p, AST_HEREDOC);
        char *heredoc = strdup(ast_heredoc->data);
        ast_free(ast_heredoc);
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, NULL, heredoc);
        ast_set_in_parser(p, ast);
        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "heredoc");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_6(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, ">&")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber, redirect, word, NULL);
        ast_set_in_parser(p, ast);

        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_7(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, "<&")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber, redirect, word, NULL);
        ast_set_in_parser(p, ast);

        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_8(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, ">|")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, word, NULL);
        ast_set_in_parser(p, ast);

        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}

bool read_redirection_9(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *ionumber = NULL;
    parser_begin_capture(p, "ionumber");
    bool status = read_ionumber(p);

    if (status)
    {
        parser_end_capture(p, "ionumber");
        ionumber = parser_get_capture(p, "ionumber");
    }

    if (parser_begin_capture(p, "redirect")
        && parser_readtext(p, "<>")
        && parser_end_capture(p, "redirect")
        && parser_begin_capture(p, "word")
        && read_word(p)
        && parser_end_capture(p, "word"))
    {
        char *redirect = parser_get_capture(p, "redirect");
        char *word = parser_get_capture(p, "word");
        struct ast_node *ast = ast_redirection_init(ionumber,
            redirect, word, NULL);
        ast_set_in_parser(p, ast);

        return true;
    }

    parser_remove_capture_by_tag(p, "ionumber");
    parser_remove_capture_by_tag(p, "redirect");
    parser_remove_capture_by_tag(p, "word");
    free(ionumber);
    p->cursor = tmp;
    return false;
}


bool read_redirection(struct parser *p)
{
    read_spaces(p);
    return (read_redirection_1(p)
            || read_redirection_2(p)
            || read_redirection_3(p)
            || read_redirection_4(p)
            || read_redirection_5(p)
            || read_redirection_6(p)
            || read_redirection_7(p)
            || read_redirection_8(p)
            || read_redirection_9(p));
}

void ast_redirection_free(void *data)
{
    struct ast_redirection *ast_redirection = data;
    free(ast_redirection->ionumber);
    free(ast_redirection->redirect);
    free(ast_redirection->word);
    free(ast_redirection->heredoc);
    free(data);
}

char *ast_redirection_to_string(struct ast_node *ast)
{
    struct ast_redirection *data = ast->data;
    char *ionumber = data->ionumber ? data->ionumber : "0";
    char *word = data->word ? data->word : data->heredoc;
    char *base = ast_node_default_to_string(ast);
    size_t size = strlen(base) + strlen("___") + strlen(ionumber)
        + strlen(data->redirect) + strlen(word) + 1;

    char *output = malloc(size);
    sprintf(output, "%s_%s_%s_%s", base, ionumber, data->redirect, word);
    free(base);
    return output;
}

struct ast_node *ast_redirection_init(char *ionumber,
    char *redirect, char *word, char *heredoc)
{
    struct ast_redirection *data = malloc(sizeof(struct ast_redirection));
    data->ionumber = ionumber;
    data->redirect = redirect;
    data->word = word;
    data->heredoc = heredoc;
    struct ast_node *ast = ast_init(AST_REDIRECTION, data);
    ast->free = ast_redirection_free;
    ast->to_string = ast_redirection_to_string;

    return ast;
}