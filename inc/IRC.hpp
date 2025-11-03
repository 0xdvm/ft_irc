/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:06:24 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/03 17:44:54 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include "Validate.hpp"
#include <string>

class IRC {

	public:
		
		IRC(void);
		IRC(const std::string &port, const std::string &password);
		IRC(const IRC &other);
		~IRC();
		IRC &operator=(const IRC &other);

		void		run(void);
	
	private:
		
		Validate	_validation;
		unsigned short		_port;
		std::string	_password;

};

#endif // !IRC_HPP
