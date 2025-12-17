/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:22:04 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:15:40 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_HPP
# define VALIDATE_HPP

# include <string>
# include <iostream>
# include <cctype>

class Validate {
	public:	
		void			validatePortNumber(const std::string &port);	
};

#endif // !VALIDATE_HPP
