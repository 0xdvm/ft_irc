/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:22:04 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/11 11:22:06 by dvemba           ###   ########.fr       */
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
