/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:30:29 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/13 00:30:35 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes.hpp"

bool is_number(const std::string& s);
std::string runUnixCommandAndCaptureOutput(std::string cmd);

