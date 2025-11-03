/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:09:00 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/03 17:44:49 by dvemba           ###   ########.fr       */
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
		~Validate();
		Validate &operator=(const Validate &);

		void	validatePortNumber(const std::string &port);
	
	private:
		
};

#endif // !VALIDATE_HPP
