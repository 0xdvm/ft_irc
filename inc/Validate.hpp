/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:09:00 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/03 15:26:48 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_HPP
# define VALIDATE_HPP

# include <string>
# include <iostream>
# include <cctype>

class Validate {

	public:

		Validate();
		Validate(const Validate &);
		Validate &operator=(const Validate &);
		~Validate();

		bool	isAllNums(const std::string &nums);
		void	validatePortNumber(const std::string &port);
	
	private:
		
};

#endif // !VALIDATE_HPP
