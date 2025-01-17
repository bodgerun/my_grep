# `my_grep`

My own implementation of the standard Unix utility `grep`.

Syntax:
`$ my_grep [OPTIONS] [PATTERN] FILE ...`

The following options are supported:
- `-c` - print only the count of matched lines;
- `-e PATTERN` - specify a pattern;
- `-f FILE` - read patterns from a file;
- `-h` - hide filenames;
- `-i` - ignore case;
- `-l` - print only filenames, not lines;
- `-n` - precede each printed line with a number;
- `-o` - print only matched parts of lines;
- `-s` - silent mode (no error messages);
- `-v` - invert match.

(Integration tests are provided).
