/*
 * Exceptions.h
 *
 *  Created on: Jul 4, 2015
 *      Author: michael
 */

#ifndef EXCEPTIONS_EXCEPTIONS_H_
#define EXCEPTIONS_EXCEPTIONS_H_

#include <exception>

namespace SiconfException{

	namespace UsuarioException{
		class invalidUserData : public std::exception{
		public:
			virtual const char* what() const throw(){
				return "Erro, os campos de usuario nao foram validados";
			}
		}UsuarioInvalido;
	}

	namespace EnderecoException{
		class invalidEnderecoData : public std::exception{
		public:
			virtual const char* what() const throw(){
				return "Erro, os campos de endereco nao foram validados";
			}
		}EnderecoInvalido;
	}

}


#endif /* EXCEPTIONS_EXCEPTIONS_H_ */
