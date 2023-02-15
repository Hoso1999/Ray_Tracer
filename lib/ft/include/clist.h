#ifndef CLIST_H
#define CLIST_H


# include <stdlib.h>
# include <unistd.h>


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					list_t;

list_t				*ft_lstnew(void *content);

void				ft_lstadd_front(list_t **alst, list_t *new_lst);

int					ft_lstsize(list_t *lst);

list_t				*ft_lstlast(list_t *lst);

void				ft_lstadd_back(list_t **alst, list_t *new_lst);

void				ft_lstdelone(list_t *lst, void (*del)(void *));

void				ft_lstclear(list_t **lst, void (*del)(void *));

void				ft_lstiter(list_t *lst, void (*f)(void *));

void				ft_push_back(list_t **lst, void *content);

list_t				*ft_lstmap(list_t *lst, void *(*f)(void *), void (*del)(void *));


#endif

