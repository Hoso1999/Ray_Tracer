# Libft

Implementation of libc some functions in c99 standard

## List of funtions
All functions have ft_ prefix


| Functions|  Part 1  | Part 2      | Bonus         |
| ---------|----------|-------------|---------------|
| isalpha  | strlcpy  | substr      | lstnew        |
| isdigit  | toupper  | strjoin     | lstadd_front  |
| isalnum  | tolower  | strtrim     | lstsize       |
| isascii  | strchr   | split       | lstlast       |
| isprint  | strrchr  | itoa        | lstadd_back   |
| strlen   | strncmp  | strmapi     | lstdelone     |   
| memset   | memchr   | striteri    | lstclear      |
| bzero    | memcmp   | putchar_fd  | lstiter       |
| memcpy   | strnstr  | putstr_fd   | lstmap        |
| memmove  | atoi     | putendl_fd  | push_back     |
| calloc   | strdup   | putnbr_fd   | getline       |


# Usage

Use CMake to generate Makefile and set PATH_OF_BUILD
```bash
CMake -B PATH_OF_BUILD
```
Run make to build lib
```bash
make
```
Add to compiler options
```bash
-IPATH_OF_LIBRARY/include -LPATH_OF_BUILD -lft
```


# Examples
main.c
```C
#include "libft.h"

int main()
{
  int num = ft_atoi("150");
  ft_putnbr_fd(num, 1);
  return 0;
}
```


```C
#include "libft.h"

int main()
{
  list_t* lst = NULL;
  char* content = ft_strdup("example");
  ft_lstadd_back(&lst, ft_lstnew(content));
  ft_putstr_fd((char*)lst->content, 1);
  ft_lstclear(lst, free);
  return 0;
}
```

```C
#include "libft.h"

int main()
{
  int fd = open("file.txt");
  char* line;
  
  while(ft_getline(fd, &line) > 0)
  {
    ft_putendl_fd(line, 1);
    free(line);
  }
  
  return 0;
}
```

```C
#include "libft.h"

void iter(unsigned int i, char* str)
{
  ft_putchar_fd(ft_tolower(str[i]), 1);
}

int main()
{
  char* str = "example 1 oF usIng iterate ";
  ft_striteri(str, iter);
  return 0;
}
```


















