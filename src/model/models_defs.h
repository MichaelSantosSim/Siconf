/*
 * models_defs.h
 *
 *  Created on: Jun 27, 2015
 *      Author: michael
 */

#ifndef MODEL_MODELS_DEFS_H_
#define MODEL_MODELS_DEFS_H_

#include <Wt/Dbo/weak_ptr>
#include <Wt/Dbo/collection>
#include <Wt/Dbo/Field>
#include <Wt/WDate>
#include <Wt/WDateTime>
#include <Wt/WDate>
#include <Wt/WTime>
#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Dbo>

#include "../utils/SessionSetupHelper.hpp"


namespace SiconfModel{
	class Usuario;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Usuario> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Endereco;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Endereco> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Aluno;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Aluno> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Professor;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Professor> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Turma;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Turma> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Disciplina;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Disciplina> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Nota;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Nota> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Frequencia;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Frequencia> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Aula;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Aula> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

namespace SiconfModel{
	class Avaliacao;
}

namespace Wt {
    namespace Dbo {
	    template<>
	        struct dbo_traits<SiconfModel::Avaliacao> : public dbo_default_traits {
	    	    /**
	    	     * Inibe a criacao do campo version.
	    	     */
	            static const char* versionField()     { return 0; }
	        };
    }
}

// usuario

namespace SiconfModel{
	class Usuario{
	public:
		friend class Wt::Dbo::Session;
		enum TipoUsuario{_Invalido, _Aluno, _Professor, _Administrador};
		Usuario() :
			_tipoUsuario(_Invalido){}

		/* setters */
		inline void definirNome(std::string novoNome)						{_nome = novoNome;}
		inline void definirSobrenome(std::string sobrenome)					{_sobrenome = sobrenome;}
		inline void definirEmail(std::string novoEmail)						{_email = novoEmail;}
		inline void definirEndereco(Wt::Dbo::ptr<Endereco> endereco)		{_endereco = endereco;}
		inline void definirDataNascimento(Wt::WDate novaDataNascimento)		{_dataNascimento = novaDataNascimento;}
		inline void definirFotoPerfil(std::string fileName)					{_foto = fileName;}
		inline void definirSenha(std::string senha)							{_senha = senha;}
		inline void definirLogin(std::string login)							{_login = login;}
		inline void definirTipoUsuario(TipoUsuario tipo)					{_tipoUsuario = tipo;}

		/* getters */

		inline std::string nome () 						const {return _nome;}
		inline std::string sobrenome()					const {return _sobrenome;}
		inline std::string email () 					const {return _email;}
		inline Wt::Dbo::ptr<Endereco> endereco () 		const {return _endereco;}
		inline Wt::WDate dataNascimento() 				const {return _dataNascimento;}
		inline std::string fotoPerfil()					const {return _foto;}
		inline std::string login()						const {return _login;}
		std::string senha()								const {return _senha;};
		TipoUsuario tipoUsuario()						const {return _tipoUsuario;}

		template <class Action>
		void persist(Action& a){
			Wt::Dbo::field(a, _nome, "nome");
			Wt::Dbo::field(a, _sobrenome, "sobrenome");
			Wt::Dbo::field(a, _email, "email");
			Wt::Dbo::belongsTo(a, _endereco);
			Wt::Dbo::field(a, _dataNascimento, "data_nascimento");
			Wt::Dbo::hasOne(a, _aluno);
			Wt::Dbo::hasOne(a, _professor);
			Wt::Dbo::field(a, _login, "login");
			Wt::Dbo::field(a, _senha, "senha");
			Wt::Dbo::field(a, _tipoUsuario, "tipo_usuario");
		}
	private:
		Wt::Dbo::weak_ptr<Aluno> _aluno;
		Wt::Dbo::weak_ptr<Professor> _professor;
		std::string _nome;
		std::string _sobrenome;
		std::string _email;
		Wt::Dbo::ptr<Endereco> _endereco;
		std::string _foto;
		Wt::WDate _dataNascimento;
		TipoUsuario _tipoUsuario;
		std::string _login;
		std::string _senha;
	};
}

// endereco

namespace SiconfModel{
	class Endereco{
		friend class Wt::Dbo::Session;
	public:

		Endereco(){}

		inline std::string cidade()			const {return _cidade;}
		inline std::string bairro()			const {return _bairro;}
		inline std::string rua()			const {return _rua;}
		inline int		   numero()			const {return _numero;}
		inline std::string complemento()	const {return _complemento;}

		inline void definirCidade(std::string nome){_cidade = nome;}
		inline void definirBairro(std::string nome){_bairro = nome;}
		inline void definirRua	 (std::string nome){_rua = nome;}
		inline void definirNumero(int numero)	   {_numero = numero;}
		inline void definirComplemento(std::string complemento){_complemento = complemento;}


		template<class Action>
		void persist(Action& a){

			Wt::Dbo::field(a, _cidade, "cidade");
			Wt::Dbo::field(a, _bairro, "bairro");
			Wt::Dbo::field(a, _rua, "rua");
			Wt::Dbo::field(a, _numero, "numero");
			Wt::Dbo::field(a, _complemento, "complemento");

			Wt::Dbo::hasOne(a, _usuario);
		}

	private:

		std::string _cidade;
		std::string _bairro;
		std::string _rua;
		int			_numero;
		std::string _complemento;

		Wt::Dbo::weak_ptr<Usuario> _usuario;
	};
}

// TODO frequencia

namespace SiconfModel{
	class Frequencia{
	public:
		friend class Wt::Dbo::Session;

		Frequencia(){}
		Frequencia(Wt::Dbo::ptr<Aula> aula, Wt::Dbo::ptr<Aluno> aluno, bool presenca)
			: _aula(aula), _aluno(aluno), _data(Wt::WDate::currentDate()), _presenca(presenca){

		}

		inline Wt::Dbo::ptr<Aula> aula()	const {return _aula;}
		inline Wt::Dbo::ptr<Aluno> aluno()	const {return _aluno;}
		inline bool presenca()				const {return _presenca;}
		inline Wt::WDate data()				const {return _data;}


		inline void definirPresenca(bool presenca){_presenca = presenca;}

		template<class Action>
		void persist(Action& a){
			Wt::Dbo::belongsTo(a, _aula, "frequencias_aula");
			Wt::Dbo::belongsTo(a, _aluno, "frequencias_aluno");
			Wt::Dbo::field(a, _presenca, "presenca");
			Wt::Dbo::field(a, _data, "data");
		}

	private:

		Wt::Dbo::ptr<Aula> 	_aula;
		Wt::Dbo::ptr<Aluno> _aluno;
		Wt::WDate 			_data;
		bool _presenca;

	};
}

// TODO aluno

namespace SiconfModel{
	class Aluno{
	public:
		friend class Wt::Dbo::Session;

		Aluno() {};

		Aluno(Wt::Dbo::ptr<Usuario> usuario) :
			_usuario(usuario){

			//TODO na hora de cadastrar o Aluno novo, devemos informar o login do usuario
			//	   chamando o método definirLogin;
		}

		inline int 												matricula()		const {return _matricula;}
		inline Wt::Dbo::ptr<Usuario> 							usuario()		const {return _usuario;}
		inline Wt::Dbo::ptr<Turma> 	 							turma()			const {return _turma;};
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Nota>>			notas()			const {return _notas;}
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Frequencia>>	frequencia()	const {return _frequencia;}

		void definirMatricula(int matricula){_matricula = matricula;}

		void definirTurma(Wt::Dbo::ptr<Turma> turma){_turma = std::move(turma);}
		void adicionarNota(Wt::Dbo::ptr<Nota> nota){_notas.insert(nota);}
		void adicionarFrequencia(Wt::Dbo::ptr<Frequencia> frequencia){_frequencia.insert(frequencia);}

		void removerNota(Wt::Dbo::ptr<Nota> nota){_notas.erase(nota);}
		void removerFrequencia(Wt::Dbo::ptr<Frequencia> frequencia){_frequencia.erase(frequencia);}

		float frequenciaTotal() const {

			double presenca = 0;
			double total = _frequencia.size();

			if(total == 0.0){
				return 0.0;
			}

			for(auto f : _frequencia){
				if(f->presenca()){
					presenca += 1.0;
				}
			}

			return ((presenca/total) * 100);
		}


		template<class Action>
		void persist(Action& a){

			Wt::Dbo::field(a, _matricula, "matricula");

			Wt::Dbo::belongsTo(a, _usuario, "usuario");
			Wt::Dbo::belongsTo(a, _turma, "turma_alunos");
			Wt::Dbo::hasMany(a, _notas, Wt::Dbo::ManyToOne, "notas_aluno");
			Wt::Dbo::hasMany(a, _frequencia, Wt::Dbo::ManyToOne, "frequencias_aluno");
		}



	private:
		int 											_matricula;

		Wt::Dbo::ptr<Usuario> 							_usuario;
		Wt::Dbo::ptr<Turma> 							_turma;
		Wt::Dbo::collection<Wt::Dbo::ptr<Nota>>			_notas;
		Wt::Dbo::collection<Wt::Dbo::ptr<Frequencia>>	_frequencia;
	};
}

// TODO turma

namespace SiconfModel {
	class Turma{
	public:
		friend class Wt::Dbo::Session;
		enum Turno{	Manha,
					Tarde,
					Noite
			};

		Turma(){}

		Turma(Turno turno, int serie, std::string classe)
		: _turno(turno), _serie(serie), _classe(classe){

		}

		inline void adicionarAluno(Wt::Dbo::ptr<Aluno> aluno)				{_alunos.insert(aluno);}
		inline void adicionarDisciplina(Wt::Dbo::ptr<Disciplina> disciplina){_disciplinas.insert(disciplina);}

		inline void removerAluno(Wt::Dbo::ptr<Aluno> aluno)					{_alunos.erase(aluno);}
		inline void removerDisciplina(Wt::Dbo::ptr<Disciplina> disciplina)	{_disciplinas.erase(disciplina);}

		inline Wt::Dbo::collection<Wt::Dbo::ptr<Aluno>> alunos()			const	{return _alunos;}
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Disciplina>> disciplinas()	const	{return _disciplinas;}
		inline int serie()													const	{return _serie;}
		inline Turno turno()												const	{return _turno;}
		inline std::string classe()											const	{return _classe;}

		std::string nome()	const {return std::to_string(_serie) + " Serie, " + _classe;}

		template<class Action>
		void persist(Action& a){

			Wt::Dbo::hasMany(a, _alunos, Wt::Dbo::ManyToOne, "turma_alunos");
			Wt::Dbo::hasMany(a, _disciplinas, Wt::Dbo::ManyToOne, "turma_disciplinas");

			Wt::Dbo::field(a, _turno, "turno");
			Wt::Dbo::field(a, _serie, "serie");
			Wt::Dbo::field(a, _classe, "classe");

		}

	private:

		Wt::Dbo::collection<Wt::Dbo::ptr<Aluno>> 		_alunos;
		Wt::Dbo::collection<Wt::Dbo::ptr<Disciplina>>	_disciplinas;

		Turno _turno;
		int _serie;
		std::string _classe;
	};
}

// TODO disciplina

namespace SiconfModel{
	class Disciplina{
	public:
		friend class Wt::Dbo::Session;

		Disciplina(){}
		Disciplina(std::string nome, std::string descricao, Wt::Dbo::ptr<Turma> turma)
				: _nome(nome), _descricao(descricao), _turma(turma){
		}


		template<class Action>
		void persist(Action& a){

			Wt::Dbo::field(a, _nome, "nome");
			Wt::Dbo::field(a, _descricao, "descricao");
			Wt::Dbo::belongsTo(a, _professor, "professor_disciplinas");
			Wt::Dbo::hasMany(a, _avaliacoes, Wt::Dbo::ManyToOne, "avaliacoes_disciplina");
			Wt::Dbo::hasMany(a, _aulas, Wt::Dbo::ManyToOne, "aulas_disciplina");
			Wt::Dbo::belongsTo(a, _turma, "turma_disciplinas");
		}

		inline std::string nome()											const {return _nome;}
		inline std::string descricao()										const {return _descricao;}
		inline Wt::Dbo::ptr<Professor> professor()							const {return _professor;}
		inline Wt::Dbo::ptr<Turma> turma()									const {return _turma;}
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Avaliacao>> avaliacoes()	const {return _avaliacoes;}
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Aula>> aulas()				const {return _aulas;}

		inline void definirNome(std::string nome){_nome = nome;}
		inline void definirDescricao(std::string descricao){_descricao = descricao;}
		inline void definirProfessor(Wt::Dbo::ptr<Professor> professor){_professor =  std::move(professor);}

		inline void adicionarAvaliacao(Wt::Dbo::ptr<Avaliacao> avaliacao){ _avaliacoes.insert(avaliacao);}
		inline void adicionarAula(Wt::Dbo::ptr<Aula> aula){ _aulas.insert(aula);}

		inline void removerAvaliacao(Wt::Dbo::ptr<Avaliacao> avaliacao){ _avaliacoes.erase(avaliacao);}
		inline void removerAula(Wt::Dbo::ptr<Aula> aula){ _aulas.erase(aula);}

	private:

		std::string _nome;
		std::string _descricao;

		Wt::Dbo::ptr<Professor> _professor;
		Wt::Dbo::ptr<Turma> 	_turma;
		Wt::Dbo::collection<Wt::Dbo::ptr<Avaliacao>>	_avaliacoes;
		Wt::Dbo::collection<Wt::Dbo::ptr<Aula>> 		_aulas;
	};
}

// TODO professor

namespace SiconfModel{
	class Professor{
	public:
		friend class Wt::Dbo::Session;

		Professor(){}
		Professor(Wt::Dbo::ptr<Usuario> usuario, int matricula)
			: _usuario(usuario), _matricula(matricula){};

		inline Wt::Dbo::ptr<Usuario> usuario() 								const {return _usuario;}
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Disciplina>> disciplinas() 	const {return _disciplinas;}
		inline int matricula()												const {return _matricula;}

		inline void adicionarDisciplina(Wt::Dbo::ptr<Disciplina> disciplina){_disciplinas.insert(disciplina);}
		inline void removerDisciplina(Wt::Dbo::ptr<Disciplina> disciplina){_disciplinas.erase(disciplina);}

		template<class Action>
		void persist(Action& a){
			Wt::Dbo::belongsTo(a, _usuario);
			Wt::Dbo::field(a, _matricula, "matricula");
			Wt::Dbo::hasMany(a, _disciplinas, Wt::Dbo::ManyToOne, "professor_disciplinas");
		}

	private:

		Wt::Dbo::ptr<Usuario> _usuario;
		Wt::Dbo::collection<Wt::Dbo::ptr<Disciplina>> _disciplinas;

		int  _matricula;
	};

} /* Professor */

// TODO avaliacao

namespace SiconfModel{
	class Avaliacao{
	public:
		friend class Wt::Dbo::Session;
		enum Tipo{ 	Prova,
					Trabalho,
					Exercicio,
					Recuperacao};
		Avaliacao(){}
		Avaliacao(std::string nome, Wt::Dbo::ptr<Disciplina> disciplina, float peso)
			: _disciplina(disciplina), _nome(nome), _peso(peso), _data(Wt::WDate::currentDate()){

		}


		template<class Action>
		void persist(Action& a){

			Wt::Dbo::belongsTo(a, _disciplina, "avaliacoes_disciplina");
			Wt::Dbo::hasMany(a, _notas, Wt::Dbo::ManyToOne, "notas_avaliacao");

			Wt::Dbo::field(a, _data, "data");
			Wt::Dbo::field(a, _nome, "nome");
			Wt::Dbo::field(a, _peso, "peso");

		}

		inline Wt::Dbo::ptr<Disciplina> disciplina()			const {return _disciplina;}
		inline Wt::Dbo::collection<Wt::Dbo::ptr<Nota>> notas()	const {return _notas;}
		inline std::string nome()								const {return _nome;}
		inline float peso()										const {return _peso;}

		inline void adicionarNota(Wt::Dbo::ptr<Nota> nota){_notas.insert(nota);}
		inline void removerNota(Wt::Dbo::ptr<Nota> nota){_notas.erase(nota);}
		inline void definirPeso(float peso){ _peso = peso;}

	private:

		Wt::Dbo::ptr<Disciplina> _disciplina;
		Wt::Dbo::collection<Wt::Dbo::ptr<Nota>> _notas;

		std::string _nome;
		float _peso;
		Wt::WDate _data;


	};
}

// TODO aula

namespace SiconfModel{
	class Aula{
	public:
		friend class Wt::Dbo::Session;

		Aula(){}
		Aula(Wt::Dbo::ptr<Disciplina> disciplina)
			: _disciplina(disciplina), _data(Wt::WDate::currentDate()){

		}

		template<class Action>
		void persist(Action& a){

			Wt::Dbo::hasMany(a, _frequencias, Wt::Dbo::ManyToOne, "frequencias_aula");
			Wt::Dbo::belongsTo(a, _disciplina, "aulas_disciplina");
			Wt::Dbo::field(a, _data, "data");
		}

		inline Wt::Dbo::collection<Wt::Dbo::ptr<Frequencia>> frequencias()	const {return _frequencias;}
		inline Wt::Dbo::ptr<Disciplina> disciplina()						const {return _disciplina;}
		inline Wt::WDate data()												const {return _data;}

		inline void adicionarFrequencia(Wt::Dbo::ptr<Frequencia> frequencia){_frequencias.insert(frequencia);}
		inline void removerFrequencia(Wt::Dbo::ptr<Frequencia> frequencia){_frequencias.erase(frequencia);}


	private:

		Wt::Dbo::ptr<Disciplina> _disciplina;
		Wt::Dbo::collection<Wt::Dbo::ptr<Frequencia>> _frequencias;
		Wt::WDate _data;

	};
}

// TODO nota

namespace SiconfModel{
	class Nota{
	public:
		friend class Wt::Dbo::Session;

		Nota(){}
		Nota(Wt::Dbo::ptr<Avaliacao> avaliacao, Wt::Dbo::ptr<Aluno> aluno, float nota)
			: _avaliacao(avaliacao), _aluno(aluno), _nota(nota) {

		}

		inline Wt::Dbo::ptr<Avaliacao> avaliacao()	const {return _avaliacao;}
		inline Wt::Dbo::ptr<Aluno> aluno()			const {return _aluno;}
		inline float nota()							const {return _nota;}

		inline void definirNota(float nota){_nota = nota;}

		template<class Action>
		void persist(Action& a){
			Wt::Dbo::belongsTo(a, _avaliacao, "notas_avaliacao");
			Wt::Dbo::belongsTo(a, _aluno, "notas_aluno");
			Wt::Dbo::field(a, _nota, "nota");
		}

	private:

		Wt::Dbo::ptr<Avaliacao> _avaliacao;
		Wt::Dbo::ptr<Aluno> 	_aluno;

		float _nota;
	};
}

#endif /* MODEL_MODELS_DEFS_H_ */
