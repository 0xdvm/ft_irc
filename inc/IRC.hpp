/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:21:55 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:04:45 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include "Validate.hpp"
#include <string>

class IRC {

	private:
		
		Validate				_validation;
		std::string				_port;
		std::string				_password;
		
	public:
		void					run(void);
		IRC(const std::string&, const std::string&);
};

#endif // !IRC_HPP
