import os.path

def get_file_list(dirName):
    # create a list of file and sub directories 
    # names in the given directory 
    list_of_files = os.listdir(dirName)
    all_files = list()
    # Iterate over all the entries
    for entry in list_of_files:
        # Create full path
        full_path = os.path.join(dirName, entry)
        # If entry is a directory then get the list of files in this directory 
        if os.path.isdir(full_path):
            all_files = all_files + get_file_list(full_path)
        else:
            all_files.append(full_path)
    return all_files

def file_selector():
    print("= Coding style checks " + 58*"=")
    style_errors = 0
    directory = os.path.dirname(os.path.abspath(__file__))
    all_files = get_file_list(directory)
    directory = directory.replace("/tests","/src")
    all_files = get_file_list(directory) + all_files
    for filename in all_files:
        if os.path.isfile(filename):
            if filename[len(filename)-2:len(filename)]==".c" or \
                filename[len(filename)-2:len(filename)]==".h":
                with open(filename, 'r') as file:
                    file = file.read()
                    keep = filename.find("42sh")
                    filename = filename[keep:]
                    style_errors += coding_styler(file, filename)
    print(str(style_errors) + " coding style error(s) found.")
    if style_errors:
        return 1
    else:
        return 0

def coding_styler(file, filename):
    """ takes a file in string format """
    line_number = 1
    style_errors = 0
    col_err = False
    for index in range(0, len(file)-1):
        if file[index] == ';' and index != len(file):
            style_errors += trailing_spaces(index, file, line_number, filename)
            style_errors += dead_code(index, file, line_number, filename)
        if not col_err:
            if eighty_columns(index, file, line_number, filename):
                style_errors+=1
                col_err = True
        if file[index] == '*':
            style_errors += sticky_star(index, file, line_number, filename)
        if file[index] == '+' or file[index] == '-' or file[index] == '*':
            style_errors += operation_spacing(index, file, line_number, filename)
        if file[index] == '{' or file[index] == '}':
            style_errors += solo_braces(index, file, line_number, filename)
        #if file[index] == '{':
        #    style_errors += indentation_check(index, file, line_number, filename)
        if file[index] == ',':
            style_errors += comma_space(index, file, line_number, filename)
        if file[index] == '\n':
            col_err = False
            line_number+=1
    
    return style_errors

def find_line(index, file):
    """ returns line in which an index is """
    line_start = file[0:index].rfind('\n')
    line_end = file[index:len(file)].find('\n')+index
    return [line_start, line_end]

def eighty_columns(index, file, line_number, filename):
    """ Checks if there are more than 80 characters in a single line """
    [line_start, line_end] = find_line(index, file)
    if index-line_start > 80:
        print("More than 80 columns at line " + str(line_number)
              + " in file " + filename)
        print(file[line_start+1:line_end])
        print(" "*(index-line_start-2)+"^")
        return 1
    return 0

def operation_spacing(index, file, line_number, filename):
    """ Checks if there are spaces around binary operators """
    [line_start, line_end] = find_line(index, file)
    if file[index-1].isnumeric() or file[index+1].isnumeric():
        print("Missing space around binary operator at line "+str(line_number)
              + " of file " + filename)
        print(file[line_start+1:line_end])
        print(" "*(index-line_start-1) + "^")
        return 1
    return 0

def indentation_check(index, file, line_number, filename):
    """ Checks if there is an indent after anopening brace """
    [line_start, line_end] = find_line(index, file)
    if "struct" in file[line_start:line_end]:
        return 0
    if '"' in file[index-20:index] and '"' in file[index:index+20]:
        return 0
    if "'" in file[index-2:index] and "'" in file[index:index+2]:
        return 0
    preceding_spaces = index-file[0:index].rfind('\n')-1
    succeeding_spaces = 0
    special_index = index+1
    while file[special_index+1] == ' ':
        succeeding_spaces += 1
        special_index += 1
    print("preceded: " + str(preceding_spaces) + " succeed: "+str(succeeding_spaces))
    
    if succeeding_spaces == preceding_spaces:
        print("Badly indented code at line "+str(line_number+1)
                + " of file " + filename)
        [line_start, line_end] = find_line(line_end+3, file)
        print(file[line_start+1:line_end+10])
        print(" "*(succeeding_spaces) + "^")
        return 1
    return 0
    

def dead_code(index, file, line_number, filename):
    """ Checks if there is dead code in the code """
    [line_start, line_end] = find_line(index, file)
    if "//" in file[line_start:index]:
        print("Dead code at line " +str(line_number)
            + " of file " + filename)
        print(file[line_start+1:line_end] + "\n")
        return 1
    return 0

def sticky_star(index, file, line_number, filename):
    """ Checks if pointers are spaced correctly """
    [line_start, line_end] = find_line(index, file)
    is_comment = False
    if not ';' in file[line_start:line_end]:
        is_comment = True
    if file[index+2].isalpha() and not is_comment:
        #print(file[index+2])
        if file[index+1] == " ":
            print("Potential pointer style error at line "+str(line_number)
              + " of file " + filename)
            print(file[line_start+1:line_end])
            print(" "*(index-line_start) + "^")
            return 1
    return 0

def trailing_spaces(index, file, line_number, filename):
    """ Checks if there are any trailing spaces at the end of a line """
    [line_start, line_end] = find_line(index, file)
    if file[line_start:line_end].find("for") != -1:
        return 0
    # check if line is comment
    if "//" in file[line_start:line_end]:
        return 0
    # check if line is a multiline statement 
    if '\\' in file[index:line_end]:
        return 0
    # check if space is part of string
    if '"' in file[index-20:index] and '"' in file[index:index + 20]:
        return 0
    if file[index + 1] == " ":
        print("Trailing space at line "+str(line_number)
              + " of file " + filename)
        print(file[line_start+1:line_end])
        print(" "*(index-line_start) + "^")
        return 1
    return 0

def comma_space(index, file, line_number, filename):
    """ Checks if there is a space after a comma """
    [line_start, line_end] = find_line(index, file)
    if file[index+1] == '\n':
        return 0
    if file[index+1] != ' ':
        print("Missing space after comma at line "+str(line_number)
              + " of file " + filename)
        print(file[line_start+1:line_end])
        print(" "*(index-line_start) + "^")
        return 1
    return 0

def solo_braces(index, file, line_number, filename):
    """ Checks that { and } are on their own line """
    [line_start, line_end] = find_line(index, file)
    if "struct" in file[line_start:line_end]:
        return 0
    if '"' in file[index-20:index] and '"' in file[index:index+20]:
        return 0
    if "'" in file[index-2:index] and "'" in file[index:index+2]:
        return 0
    for character in file[line_start:line_end]:
        if character.isalpha() or character == ")" or character == "(":
            print("Badly indented brace at line "+str(line_number)
                    + " of file " + filename)
            print(file[line_start+1:line_end])
            print(" "*(index-line_start-1) + "^")
            return 1
    return 0