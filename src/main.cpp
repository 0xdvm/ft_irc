/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:28:42 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/04 20:30:45 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/IRC.hpp"
// #include <cstdlib>
// #include <iostream>
// #include <stdexcept>

// int	main(int ac, char **av) {
//     /**/
//     if (ac != 3){
//         std::cout << "Wrong args\nRun: ./ircserv <port> <password>\n";
//         return (1);
//     }    
// 	try {
// 		IRC irc(av[1], av[2]);
//         irc.run();
// 	} catch (const std::exception &e) {
//         std::cerr << "Error: " << e.what() << "\n";
//         return 1;
//     }
// }

#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include <netinet/in.h>

int main(void){
    //Cria um canal para comunicao entre dispositivos
    //O tipo se socket criado foi o do tipo tcp e o endereco e o IPV4
    int server_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (server_tcp == -1){
        std::cout << "Error: Couln'd create socket for communicate.\n"; 
        return (1);
    }
    struct sockaddr_in address;
    
    address.sin_family = AF_INET; // ---> Permite usar o endereco IPV4.
    address.sin_port = htons(8080); // ----> reserva a porta 8080 para endereco.
    address.sin_addr.s_addr = INADDR_ANY; // -----> Permite que esse endereco seja acesso por qualquer maquina.

    //Associa uma endereco ip e porta ao socket criado(Fazendo assim o servidor escutar num endereco).
    if (bind(server_tcp, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind");
    }
    
    //Permite que o socket que foi anexado a uma porta possa receber conexcoes.
    //O numero de conexoes que ele colocar em espera antes de ser aceitar com o (accept) é 10.
    if (listen(server_tcp, 10) < 0){
        perror("listen");
    }
    int addrlen = sizeof(address);
    int new_socket = accept(server_tcp, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0){
        perror("New Socket");
    }

    char buffer[5000];
    read(new_socket, buffer, 5000);
    std::cout << buffer << std::endl;
    
    close(new_socket);
    close(server_tcp);
}

