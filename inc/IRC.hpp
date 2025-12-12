/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:21:55 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/11 11:21:57 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include "Validate.hpp"
#include <string>

class IRC {

	private:
		
		Validate		_validation;
		std::string	_port;
		std::string		_password;
		
	public:
		
		IRC(void);
		IRC(const std::string &port, const std::string &password);
		IRC(const IRC &other);
		~IRC();
		IRC &operator=(const IRC &other);

		void		run(void);
	
};

#endif // !IRC_HPP
