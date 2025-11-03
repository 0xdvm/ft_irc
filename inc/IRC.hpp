/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:06:24 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/03 15:48:37 by marcsilv         ###   ########.fr       */
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
		IRC &operator=(const IRC &other);
		~IRC();

		void		run(void);
	
	private:
		
		Validate	_validation;
		short		_port;
		std::string	_password;

};

#endif // !IRC_HPP
