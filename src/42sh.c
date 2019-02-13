#include <parser/parser.h>
#include <execution/execute_ast.h>

int main(void)
{
    struct lexer *lexer = lexer_init();
    struct ast_node *ast = parse(lexer);
    execute_ast(ast);
}