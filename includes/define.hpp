#pragma once

/* ************************************************************************** */
/* ********************************* Color ********************************** */
/* ************************************************************************** */

#define DEBUG		true
#define RED			"\033[0;31m"
#define RED_ERR		"\033[1;41m"
#define GREEN		"\033[1;32m"
#define YELLOW		"\033[1;33m"
#define YELLOW_BK	"\033[1;43m"
#define BLUE		"\033[1;34m"
#define BLUE_BK		"\033[1;44m"
#define NC			"\033[0m"

/* ************************************************************************** */
/* ********************************* Server ********************************* */
/* ************************************************************************** */

//Commande size max can be receive
#define MAX_CMD_LEN 512

#ifndef FT_TCP_PROTOCOL
// Protocol number of tcp protocol (less /etc/protocols)
# define FT_TCP_PROTOCOL 6
#endif

#ifndef FT_SOCK_BACKLOG
// Max of demand waiting on socket
# define FT_SOCK_BACKLOG 100
#endif

#ifndef FT_INET_ADDR
// ip match
# define FT_INET_ADDR "0.0.0.0"
#endif