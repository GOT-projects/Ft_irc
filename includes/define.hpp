#pragma once

/**
 * @brief 
 * 
 */

/* ************************************************************************** */
/* ********************************* Color ********************************** */
/* ************************************************************************** */

#define DEBUG		true
//RED COLOR
#define RED			"\033[0;31m"
// RED BACKGROUND COLOR
#define RED_ERR		"\033[1;41m"
// GREEN COLOR
#define GREEN		"\033[1;32m"
// YELLOW COLOR
#define YELLOW		"\033[1;33m"
// YELLOW BACKGROUND COLOR
#define YELLOW_BK	"\033[1;43m"
// BLUE COLOR
#define BLUE		"\033[1;34m"
// BLUE BACKGROUND COLOR
#define BLUE_BK		"\033[1;44m"
// NO COLOR COLOR
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

/* ************************************************************************** */
/* ******************************** Compare ********************************* */
/* ************************************************************************** */

// if exist in (the same instance)
#define EXIST_IN		0b01
// if exist in (not the same insatance)
#define EXIST_IN_COPY	0b10
