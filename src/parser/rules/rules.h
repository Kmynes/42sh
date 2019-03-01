#include <parser/parser.h>


bool read_ini_file(struct parser *p);

bool read_sections(struct parser *p);

bool read_key_value(struct parser *p);

bool read_value(struct parser *p);

bool read_identifier(struct parser *p);

bool read_spaces(struct parser *p);

bool read_end_of_line(struct parser *p);

bool read_spacing(struct parser *p);

bool parser_readassign(struct parser *p);