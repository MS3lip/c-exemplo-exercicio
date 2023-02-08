#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLIVROS 1000

typedef struct
{
  int numAutores;
  char **autor_es;
} TAutores;

typedef struct
{
  int numAssunto; // quantidade de assuntos
  char **assunto; // fazer menu para perguntar se quer adicionar mais um
} TAssunto;

typedef struct
{
  char *titulo;
  TAutores autores;
  char *editora;
  int num_pags;
  int anoEdicao;
  char *idioma;
  TAssunto assuntos;
} TLivro;

TLivro *_Biblioteca; // variavel global
int _numLivro = 0;

void menuPrincipal();
void mensagemError(int codigoErro);
void recuperarDadosLivros();

int incluirLivro();
int editarLivro();
int listarLivro();
int alocarNovoLivroEmMemoria();
TLivro criaLivro();
TAutores addAutor(TLivro livro);
TAutores alocarNovoAutorEmMemoria(TAutores autores);
int addOutroAutor();
int validaNumero(int num_pags);
int addLivroPaginas(TLivro livro);
int addAno(TLivro livro);
int validaData(int anoEdicao);
TAssunto addAssunto(TLivro livro);
TAssunto alocarNovoAssuntoEmMemoria(TAssunto assuntos);
int addOutroAssunto();
void salvarLivro();
void imprimeLivro(TLivro livro);
void listarTodosLivros();
void listarUmLivro();
void imprimirLivroEscolhido(TLivro livro);
void menuEditarLivro(TLivro livro);

int main()
{
  //  Recuperar os livros salvos
  recuperarDadosLivros();

  // Menu Principal
  menuPrincipal();

  return 0;
}

void menuPrincipal()
{
  int op = 0;
  while (op != 5)
  {
    system("cls");
    printf("*****************************************************\n");
    printf("***               MENU PRINCIPAL                  ***\n");
    printf("*** - 1) Incluir Livro                            ***\n");
    printf("*** - 2) Editar Livro                             ***\n");
    printf("*** - 3) Excluir Livro                            ***\n");
    printf("*** - 4) Listar Livro                             ***\n");
    printf("*** - 5) Encerrar Programa                        ***\n");
    printf("*****************************************************\n");
    printf("\n");
    printf(" - Digite uma opcao: ");

    scanf("%d", &op);
    fflush(stdin);

    switch (op)
    {
    case 1:
      incluirLivro();
      break;
    case 2:
      editarLivro();
      break;
    case 3:
      break;
    case 4:
      listarLivro();
      break;
    case 5:
      break;
    default:
      mensagemError(0);
      break;
    }
  }
}

int listarLivro()
{
  int op = 0;
  while (op != 3)
  {
    system("cls"); // limpar a tela
    printf("*****************************************************\n");
    printf("***               LISTAR LIVRO(S)                 ***\n");
    printf("*** - (1) Listar Livro                            ***\n");
    printf("*** - (2) Listar Todos                            ***\n");
    printf("*** - (3) Voltar Opcao Anterior                   ***\n");
    printf("*****************************************************\n");
    printf("\n");
    printf(" - Digite uma opcao : ");

    scanf("%d", &op);
    fflush(stdin);

    switch (op)
    {
    case 1:
      listarUmLivro();
      break;
    case 2:
      listarTodosLivros();
      break;
    case 3:
      break;
    default:
      mensagemError(0);
      break;
    }
  }
  return 1;
}

int editarLivro()
{
  //  Recuperar os livros salvos
  _numLivro = 0;
  recuperarDadosLivros();

  if (_numLivro == 0)
  {
    mensagemError(-2);
    system("pause");
  }
  else
  {
    int i, op;

    while (op != 0)
    {
      //  HEADER
      system("cls");
      printf("*****************************************************\n");
      printf("***        LISTA DE LIVRO - PARA EDICAO           ***\n\n");

      //  CARREGAR A LISTA
      for (i = 0; i < _numLivro; i++)
        printf("*** LIVRO %d: %s \n", (i + 1), _Biblioteca[i].titulo);

      //  ESCOLHA UM LIVRO
      printf("\n");
      printf("....Para voltar ao Menu anterior digite 0 \n");
      printf("\n");
      printf("Selecione um Livro da lista: ");

      scanf("%d", &op);
      fflush(stdin);

      //  VALIDAR SE É UM LIVRO VÁLIDO
      if (op > 0 && op < _numLivro)
      {
        menuEditarLivro(_Biblioteca[(op - 1)]);
        break;
      }
      else
      {
        //  Código de retorno ao menu anterior
        if (op == 0)
          break;

        mensagemError(0);
        system("pause");
      }
    }
  }
  return 1;
}

void menuEditarLivro(TLivro livro)
{
  int op = 0;

  while (op != 8)
  {
    system("cls");
    printf("*****************************************************\n");
    printf("***      Digite a opcao que deseja alterar        ***\n");
    printf("*** - (1) Titulo                                  ***\n");
    printf("*** - (2) Autor (es)                              ***\n");
    printf("*** - (3) Editora                                 ***\n");
    printf("*** - (4) Numero de paginas                       ***\n");
    printf("*** - (5) Ano de Edicao                           ***\n");
    printf("*** - (6) Idioma                                  ***\n");
    printf("*** - (7) Assunto(s)                              ***\n");
    printf("*** - (8) Voltar p/ menu anterior                 ***\n");
    printf("*****************************************************\n");

    printf("- Digite sua opcao que deseja alterar: ");

    scanf("%d", &op);
    fflush(stdin);

    switch (op)
    {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    default:
      mensagemError(0);
      break;
    }
  }
}

int incluirLivro()
{
  //  Validar tamanho máximo de livros na biblioteca
  if (_numLivro >= MAXLIVROS)
  {
    mensagemError(-1);
    return 0; // retornar menu Principal
  }

  //  Se o Alocar livro em memoria for negativo  voltar ao menu Principal
  if (alocarNovoLivroEmMemoria() == 0)
    return 0; // retorna menu Principal

  _Biblioteca[_numLivro] = criaLivro();
  salvarLivro();
  imprimeLivro(_Biblioteca[_numLivro]);

  return 1;
}

TLivro criaLivro()
{
  TLivro livro;
  char stringAux[100], op; // a stringAux vai facilitar a alocação dinamica das strings

  //  HEADER
  system("cls");
  printf("*****************************************************\n");
  printf("***               NOVO LIVRO                      ***\n");
  printf("\n");

  // TITULO
  printf(" Titulo: ");
  gets(stringAux);                                                       // strlen retorna a quantidade de caracteres de uma string  - strcpy copia pra um destino oq vem da origem
  livro.titulo = (char *)malloc((strlen(stringAux) + 1) * sizeof(char)); // malloc = criação       sizeof pega o tamanho que o char ocupada na memoria e vai multiplicar  pela quantidade que precisamos( que é oq o usuario digitou) OTIMIZAÇÃO DE MEMORIA
  strcpy(livro.titulo, stringAux);                                       // pegamos oq o usuario digitou e jogamos no l.titulo cujo espaço de memoria reservamos na linha acima
  fflush(stdin);

  // AUTOR(ES)
  livro.autores = addAutor(livro);

  // EDITORA
  printf(" Editora: ");
  gets(stringAux);
  livro.editora = (char *)malloc((strlen(stringAux) + 1) * sizeof(char));
  strcpy(livro.editora, stringAux);
  fflush(stdin);

  // NUMERO DE PAGINAS
  livro.num_pags = addLivroPaginas(livro);

  // ANO
  livro.anoEdicao = addAno(livro);

  // IDIOMA
  printf(" Idioma: ");
  gets(stringAux);
  livro.idioma = (char *)malloc((strlen(stringAux) + 1) * sizeof(char));
  strcpy(livro.idioma, stringAux);
  fflush(stdin);

  // ASSUNTO
  livro.assuntos = addAssunto(livro);

  return livro;
}

void salvarLivro()
{
  int i, j;
  FILE *Larq; // pra salvar em arquivo precisa declarar uma variavel do tipo file

  // abrir o arquivo
  Larq = fopen("ArqLivros.txt", "w"); // um dos modos de abrir o arquivo é com w de write onde ele escreve os dados. o W apaga os dados e sobrescreve

  if (Larq == NULL)
  {
    printf(" ERRO: Nao foi possivel criar o Livro. Aconteceu um erro ao salvar o livro!");
    system("pause");
  }

  for (i = 0; i <= _numLivro; i++)
  {                                              // o fprintf diz em qual arquivo eu vou salvar
    fprintf(Larq, "%s;", _Biblioteca[i].titulo); // cada musica vai ficar numa linha. dados serão separados por ; @ e #.
    fprintf(Larq, "%s;", _Biblioteca[i].editora);
    fprintf(Larq, "%d;", _Biblioteca[i].num_pags);
    fprintf(Larq, "%d;", _Biblioteca[i].anoEdicao);
    fprintf(Larq, "%s;", _Biblioteca[i].idioma);

    for (j = 0; j < _Biblioteca[i].autores.numAutores; j++)
    {
      fprintf(Larq, "%s@", _Biblioteca[i].autores.autor_es[j]); // os autores serão separados por @
    }

    for (j = 0; j < _Biblioteca[i].assuntos.numAssunto; j++)
    {
      fprintf(Larq, "%s#", _Biblioteca[i].assuntos.assunto[j]);
    }

    fprintf(Larq, "%c", '\n'); // cada livro vai ficar numa linha
  }

  fclose(Larq);

  printf("\n");
  printf(" Livro Salvo com sucesso!\n");
  system("pause");
}

void imprimeLivro(TLivro livro)
{
  int i;

  //  HEADER
  system("cls");
  printf("*****************************************************\n");
  printf("***               LIVRO SALVO                      ***\n");
  printf("\n");

  printf("Titulo    : %s\n", livro.titulo);

  printf("Autor     : ");
  for (i = 0; i < livro.autores.numAutores; i++) // imprimir todos os autores
    printf("%s, ", livro.autores.autor_es[i]);

  printf("\n");
  printf("Editora   : %s\n", livro.editora);
  printf("No Paginas: %d\n", livro.num_pags);
  printf("Ano da Edicao: %d\n", livro.anoEdicao);
  printf("Idioma    : %s\n", livro.idioma);

  printf("Assunto   : ");
  for (i = 0; i < livro.assuntos.numAssunto; i++) // imprimir todos os assuntos
    printf("%s, ", livro.assuntos.assunto[i]);

  printf("\n\n");
  system("pause");
}

TAssunto addAssunto(TLivro livro)
{
  TAssunto assuntos;
  int adicionar = 1;
  char stringAux[100]; // a stringAux vai facilitar a alocação dinamica das strings

  assuntos.numAssunto = 0;
  while (adicionar)
  {
    //  Alocar Em Memoria um novo Autor
    assuntos = alocarNovoAssuntoEmMemoria(assuntos);
    if (!assuntos.assunto)
      break;

    // AUTOR(ES)
    printf(" %do Assunto(s): ", assuntos.numAssunto + 1);
    gets(stringAux);
    assuntos.assunto[assuntos.numAssunto] = (char *)malloc((strlen(stringAux) + 1) * sizeof(char)); // aqui reservamos a quantidade de caracteres necessarias pro numAutores

    if (!assuntos.assunto[assuntos.numAssunto])
    {
      printf("ERRO na Criacao da String para o Assunto [%d] !\n", assuntos.numAssunto);
      system("pause");
      break;
    }

    strcpy(assuntos.assunto[assuntos.numAssunto++], stringAux); // copiar oq o usuario escreveu e adiciona +1 no numero de autores
    fflush(stdin);

    // ADICIONAR MAIS UM AUTO?????
    adicionar = addOutroAssunto();
  }

  return assuntos;
}

TAutores addAutor(TLivro livro)
{
  TAutores autores;
  int adicionar = 1;
  char stringAux[100]; // a stringAux vai facilitar a alocação dinamica das strings

  autores.numAutores = 0;
  while (adicionar)
  {
    //  Alocar Em Memoria um novo Autor
    autores = alocarNovoAutorEmMemoria(autores);
    if (!autores.autor_es)
      break;

    // AUTOR(ES)
    printf(" %do Autor(es): ", autores.numAutores + 1);
    gets(stringAux);
    autores.autor_es[autores.numAutores] = (char *)malloc((strlen(stringAux) + 1) * sizeof(char)); // aqui reservamos a quantidade de caracteres necessarias pro numAutores

    if (!autores.autor_es[autores.numAutores])
    {
      printf("ERRO na Criacao da String para o Autor [%d] !\n", autores.numAutores);
      system("pause");
      break;
    }

    strcpy(autores.autor_es[autores.numAutores++], stringAux); // copiar oq o usuario escreveu e adiciona +1 no numero de autores
    fflush(stdin);

    // ADICIONAR MAIS UM AUTO?????
    adicionar = addOutroAutor();
  }

  return autores;
}

int addOutroAutor()
{
  char op;

  printf(" Deseja adicionar outro Autor? (S/N) ");
  scanf(" %c", &op);
  fflush(stdin);

  op = tolower(op);

  if (op != 's' && op != 'n')
  {
    mensagemError(0);
    return 0;
  }

  if (op == 'n')
    return 0;

  return 1;
}

int addOutroAssunto()
{
  char op;

  printf(" Deseja adicionar outro Assunto? (S/N) ");
  scanf(" %c", &op);
  fflush(stdin);

  op = tolower(op);

  if (op != 's' && op != 'n')
  {
    mensagemError(0);
    return 0;
  }

  if (op == 'n')
    return 0;

  return 1;
}

int addLivroPaginas(TLivro livro)
{
  int erro = -1;
  while (erro < 0)
  {
    printf(" Numero de Paginas: ");
    scanf("%d", &livro.num_pags);
    fflush(stdin);
    erro = validaNumero(livro.num_pags);
    if (erro < 0)
      mensagemError(erro);
  }

  return livro.num_pags;
}

int validaNumero(int num_pags)
{
  if (num_pags <= 0)
    return -5;

  if (num_pags >= 10000)
    return -8;

  return 1;
}

int addAno(TLivro livro)
{
  int erro = -1;
  while (erro < 0)
  {
    printf(" Ano de Edicao: ");
    scanf("%d", &livro.anoEdicao);
    fflush(stdin);

    erro = validaData(livro.anoEdicao);
    if (erro < 0)
      mensagemError(erro);
  }
  return livro.anoEdicao;
}

int validaData(int anoEdicao)
{
  if (anoEdicao < 0)
    return -7;

  if (anoEdicao > 2023)
    return -6;

  return 1;
}

void mensagemError(int codigoErro)
{ // mensagens de erro
  switch (codigoErro)
  {
  case 0:
    printf("\nERRO: Opcao Invalida. Selecione outra!\n\n");
    break;
  case -1:
    printf("\nERRO: A biblioteca ja esta cheia!\n\n");
    break;
  case -2:
    printf("A Lista esta vazia!!!\n\n");
    break;
  case -10:
    printf("\nERRO: Erro de Alocacao de Memoria!\n\n");
    break;

  case -5:
    printf("\nERRO: O numero de paginas nao pode ser negativo. Nao avacalha!!!!\n\n");
    break;

  case -6:
  {
    printf("Caramba, voce achou um livro de antes de Cristo?\n");
    printf("Por favor, coloque o ano dessa edicao!\n\n");
  };
  break;

  case -7:
    printf("Erro: voce precisa colocar um ano valido!!!!\n\n");
    break;

  case -8:
    printf("ERRO: Numero de paginas invalido!!!!\n\n");
    break;

  default:
    printf("ERRO!\n\n");
    break;
  }
  system("pause");
}

int alocarNovoLivroEmMemoria()
{
  // se a lista de livros estiver vazia
  if (_numLivro == 0)
    _Biblioteca = (TLivro *)malloc(1 * sizeof(TLivro)); // malloc aloca um espaço de memoria para um livro
  else
    _Biblioteca = (TLivro *)realloc(_Biblioteca, (_numLivro + 1) * sizeof(TLivro)); // realloc garante que mais um livro seja alocado preservando a biblioteca do jeito que ela ta

  if (!_Biblioteca)
  {
    mensagemError(-10);
    return 0;
  }

  return 1;
}

TAutores alocarNovoAutorEmMemoria(TAutores autores)
{
  if (autores.numAutores == 0)
    autores.autor_es = (char **)malloc(1 * sizeof(char));
  else
    autores.autor_es = (char **)realloc(autores.autor_es, (autores.numAutores + 1) * sizeof(char));

  if (!autores.autor_es)
  {
    printf("\nERRO na criacao do vetor Autores! \n");
    system("pause");
  }

  return autores;
}

TAssunto alocarNovoAssuntoEmMemoria(TAssunto assuntos)
{
  if (assuntos.numAssunto == 0)
    assuntos.assunto = (char **)malloc(1 * sizeof(char));
  else
    assuntos.assunto = (char **)realloc(assuntos.assunto, (assuntos.numAssunto + 1) * sizeof(char));

  if (!assuntos.assunto)
  {
    printf("\nERRO na criacao do vetor Assuntos! \n");
    system("pause");
  }

  return assuntos;
}

void recuperarDadosLivros()
{

  int i, separador, j;
  int t = 0;
  char str[100], c;
  FILE *Larq; // abre o arquivo

  Larq = fopen("ArqLivros.txt", "r");
  if (Larq)
  {
    i = 0;         // usado para indexar a string
    separador = 0; // usado para contar os separadores ~> ; # &

    while (!feof(Larq)) // o feof(end of file) com o Larq aponta para o final do arquivo. Quando o caracter do Larq for igual ao final, o laço quebra.
    {
      c = fgetc(Larq); // fgetch pega caracter e posiciona o proximo para leitura até chegar no final.
      if ((c != '\n') && (c != ';') && (c != '@') && (c != '#') && (c != EOF))
        str[i++] = c;

      if ((c == ';') || (c == '@') || (c == '#') || (c == '\n'))
      {
        str[i] = '\0'; // colocando o \0 forçadamente e tratando final de string
        i = 0;         // i = 0 porque o proximo caractere tem que ir pra primeira posição de novo, sobescrevendo o anterior.

        if (c == ';')
        {
          //  TITULO
          if (separador == 0)
          {
            if (_numLivro == 0)
              _Biblioteca = (TLivro *)malloc(1 * sizeof(TLivro)); // reserva 1 espaco para o ponteiro TLivro
            else
              _Biblioteca = (TLivro *)realloc(_Biblioteca, (_numLivro + 1) * sizeof(TLivro)); // vai add varios

            _Biblioteca[_numLivro].titulo = (char *)malloc((strlen(str) + 1) * sizeof(char *)); // reserva espaco do tipo char em função da quantidade de caracteres que vai ter em st
            strcpy(_Biblioteca[_numLivro].titulo, str);                                         // joga o q esta em titulo para str (que pegamos no arq)
            _Biblioteca[_numLivro].autores.numAutores = 0;                                      // inicializa em 0, pois n sabemos qnt autores tem
            _Biblioteca[_numLivro].assuntos.numAssunto = 0;                                     // inicializa em 0, pois n sabemos qnt assunto tem
            separador++;
          }

          // EDITORA
          else if (separador == 1)
          {
            _Biblioteca[_numLivro].editora = (char *)malloc((strlen(str) + 1) * sizeof(char)); // reserva espaco do tipo char em função da quantidade de caracteres que vai ter em str
            strcpy(_Biblioteca[_numLivro].editora, str);
            separador++;
          }

          // NUM PAGINAS
          else if (separador == 2)
          {
            _Biblioteca[_numLivro].num_pags = atoi(str); // atoi transforma um int em char
            separador++;
          }

          // ANO EDIÇÃO
          else if (separador == 3)
          {
            _Biblioteca[_numLivro].anoEdicao = atoi(str); // atoi transforma um int em char
            separador++;
          }

          //  IDIOMA
          else if (separador == 4)
          {
            _Biblioteca[_numLivro].idioma = (char *)malloc((strlen(str) + 1) * sizeof(char)); // reserva espaco do tipo char em função da quantidade de caracteres que vai ter em str
            strcpy(_Biblioteca[_numLivro].idioma, str);
            separador = 0;
          }
        }

        // AUTOR(ES)
        else if (c == '@')
        {
          j = _Biblioteca[_numLivro].autores.numAutores;

          if (j == 0)
            _Biblioteca[_numLivro].autores.autor_es = (char **)malloc(1 * sizeof(char));

          _Biblioteca[_numLivro].autores.autor_es[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
          strcpy(_Biblioteca[_numLivro].autores.autor_es[j], str);
          _Biblioteca[_numLivro].autores.numAutores++;
        }

        //  ASSUNTO(S)
        else if (c == '#')
        {
          t = _Biblioteca[_numLivro].assuntos.numAssunto;

          if (t == 0)
            _Biblioteca[_numLivro].assuntos.assunto = (char **)malloc(1 * sizeof(char));

          _Biblioteca[_numLivro].assuntos.assunto[t] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
          strcpy(_Biblioteca[_numLivro].assuntos.assunto[t], str);
          _Biblioteca[_numLivro].assuntos.numAssunto++;
        }

        else if (c == '\n')
        {
          separador = 0;
          // memset(str, 0, sizeof(str));
          _numLivro++;
        }
      }
    }
  }

  fclose(Larq);
}

void listarTodosLivros()
{
  //  Recuperar os livros salvos
  _numLivro = 0;
  recuperarDadosLivros();

  if (_numLivro == 0)
    printf("\n ATENCAO!!!!!!  A Biblioteca esta vazia.....\n\n");

  else
  {
    //  HEADER
    system("cls");
    printf("*****************************************************\n");
    printf("***            LISTAR TODOS OS LIVROS             ***\n");

    int i, l;

    for (i = 0; i < _numLivro; i++)
    {
      //  HEADER
      printf("*****************************************************\n");
      printf("LIVRO %d \n", (i + 1));

      printf("Titulo    : %s \n", _Biblioteca[i].titulo);

      printf("Autor     : ");
      for (l = 0; l < _Biblioteca[i].autores.numAutores; l++) // imprimir todos os autores
        printf("%s, ", _Biblioteca[i].autores.autor_es[l]);

      printf("\n");
      printf("Editora   : %s \n", _Biblioteca[i].editora);
      printf("No Paginas: %d \n", _Biblioteca[i].num_pags);
      printf("Ano da Edicao: %d \n", _Biblioteca[i].anoEdicao);
      printf("Idioma    : %s \n", _Biblioteca[i].idioma);

      printf("Assunto   : ");
      for (l = 0; l < _Biblioteca[i].assuntos.numAssunto; l++) // imprimir todos os assuntos
        printf("%s, ", _Biblioteca[i].assuntos.assunto[l]);

      printf("\n\n");
    }
  }
  system("pause");
}

void listarUmLivro()
{
  //  Recuperar os livros salvos
  _numLivro = 0;
  recuperarDadosLivros();

  if (_numLivro == 0)
  {
    mensagemError(-2);
    system("pause");
  }
  else
  {
    int i, op;

    while (op != 0)
    {

      //  HEADER
      system("cls");
      printf("*****************************************************\n");
      printf("***          SELECIONE UM LIVRO DA LISTA          ***\n\n");

      //  CARREGAR A LISTA
      for (i = 0; i < _numLivro; i++)
        printf("*** LIVRO %d: %s \n", (i + 1), _Biblioteca[i].titulo);

      //  ESCOLHA UM LIVRO
      printf("\n");
      printf("....Para voltar ao Menu anterior digite 0 \n");
      printf("\n");
      printf("Selecione um Livro da lista: ");

      scanf("%d", &op);
      fflush(stdin);

      //  VALIDAR SE É UM LIVRO VÁLIDO
      if (op > 0 && op < _numLivro)
        imprimirLivroEscolhido(_Biblioteca[(op - 1)]);

      else
      {
        //  Código de retorno ao menu anterior
        if (op == 0)
          break;

        mensagemError(0);
      }
      system("pause");
    }
  }
}

void imprimirLivroEscolhido(TLivro livro)
{
  int i;

  //  HEADER
  system("cls");
  printf("*****************************************************\n");
  printf("***               LIVRO ESCOLHIDO                 ***\n");
  printf("\n");

  printf("Titulo    : %s\n", livro.titulo);

  printf("Autor     : ");
  for (i = 0; i < livro.autores.numAutores; i++) // imprimir todos os autores
    printf("%s, ", livro.autores.autor_es[i]);

  printf("\n");
  printf("Editora   : %s\n", livro.editora);
  printf("No Paginas: %d\n", livro.num_pags);
  printf("Ano da Edicao: %d\n", livro.anoEdicao);
  printf("Idioma    : %s\n", livro.idioma);

  printf("Assunto   : ");
  for (i = 0; i < livro.assuntos.numAssunto; i++) // imprimir todos os assuntos
    printf("%s, ", livro.assuntos.assunto[i]);

  printf("\n\n");
}