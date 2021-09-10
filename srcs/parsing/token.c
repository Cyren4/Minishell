
int	check_type(char *elem)
{
	if (ft_strcmp(elem, "|"))
		return (PIPE);
	else if (ft_strcmp(elem, "<"))
		return (LT);
	else if (ft_strcmp(elem, "<<"))
		return (LT2);
	else if (ft_strcmp(elem, ">"))
		return (GT);
	else if (ft_strcmp(elem, ">>"))
		return (GT2);
}