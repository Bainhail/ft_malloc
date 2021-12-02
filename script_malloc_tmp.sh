#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script_malloc_tmp.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabihali <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 13:12:10 by nabihali          #+#    #+#              #
#    Updated: 2021/12/01 15:40:19 by nabihali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc_macbook-pro-de-nabih.home.so
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
