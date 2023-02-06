#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLIVROS 1000

typedef struct
{
  char *titulo;
  char **autor_es; // fazer menu para perguntar se quer adicionar mais um
  int numAutores;  // quantidade de autores
  char *editora;
  int num_pags;
  int anoEdicao;
  char *idioma;
  char **assunto; // fazer menu para perguntar se quer adicionar mais um
  int numAssunto; // quantidade de assuntos
} TLivro;

TLivro *_Biblioteca; // variavel global
int _numLivro = 0;

// funcoes
void menu();                        // mostrar a opcao do menu
TLivro criaLivro();                 // cria livro digitado pelo usuario
void imprimeLivro();                // imprime o livro
void opcao_menu(int op);            // disparar a funcionalidade escolhida
void mensagemError(int codigoErro); // mensagens de erro
int inclusao();                     // dispara funcao para incluir livro
int alteracao();                    // dispara funcaoo alterar livro
int validaNumero(int num_pags);     // validar o numero de paginas
int validaData(int anoEdicao);      // validar a data do ano de da edição do livro
void salvarArquivo();
void recuperarDados();
void menu_listar();                              // lista sub menu listar
void opcao_listar_menu(int opS);                 // dispara uma das funcoes de listar
int listarBiblioteca(int pause);                 // listar todos os livros
int alterarLivro(int livro);                     // funcionalidade de alterar um livro
int menuAlterarLivro();                          // menu de opcao para alterar um item do livro
void disparaTpAlteracaoAutor(int op, int livro); // dispara tipo de alteracao para autor
void adicionarAutor(int livro);                  // adicionar um novo autor
void alterarAutor(int livro);                    // alterar um autor
void imprimeAutorLivro(TLivro l);                // imprimee os autores de um livro
void excluirAutor(int livro);                    // exclui o autor de um livro
int menuAlterarEscolha();
void menuAlterarOpcoes(char *str);

int main()
{

  int op = 1;
  // int opS = 1;
  recuperarDados();

  while (op != 5)
  {
    menu();
    scanf("%d", &op);
    fflush(stdin);
    system("cls");
    opcao_menu(op);
  }
  return 0;
}

void menu()
{

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
}

void opcao_menu(int op)
{
  int erro;
  int opS = 1;

  if (op < 1 || op > 5)
  {
    mensagemError(0);
  }
  else if (op < 5)
  {
    if (op == 1)
    { // incluir
      erro = inclusao();
    }

    else if (op == 2)
    {
      // if (_Biblioteca)  {

      //}

      erro = alteracao();
    }
    else if (op == 4)
    { // listar
      if (_numLivro <= 0)
      {
        erro = -2; // lista vazia
        opS = 3;   // opções de submenu
      }
      while (opS != 3)
      {
        if (_numLivro > 1)
        {
          menu_listar();
          scanf("%d", &opS);
          fflush(stdin);
          opcao_listar_menu(opS);
        }
        else
        {
          opS = 3; // opcao de sair, vai quebrar o laço
          opcao_listar_menu(2);
        }
      }
    }
    if (erro < 0)
    {
      mensagemError(erro); // em caso de erro de alguma operação. mostrar o erro na tela
    }
  }
  else
  {

    if (_numLivro > 0)
    { // condicional para sair
      salvarArquivo();
    }
  }
}

int inclusao()
{
  if (_numLivro >= MAXLIVROS)
  {
    return -1;
  }

  if (_numLivro == 0)
  {                                                     // se a lista de livros estiver vazia
    _Biblioteca = (TLivro *)malloc(1 * sizeof(TLivro)); // malloc aloca um espaço de memoria para um livro
  }

  else
  {
    _Biblioteca = (TLivro *)realloc(_Biblioteca, (_numLivro + 1) * sizeof(TLivro)); // realloc garante que mais um livro seja alocado preservando a biblioteca do jeito que ela ta
  }

  if (!_Biblioteca)
  {
    return -10;
  }

  _Biblioteca[_numLivro] = criaLivro();
  system("cls"); // limpar a tela
  salvarArquivo();
  imprimeLivro(_Biblioteca[_numLivro]);
  system("pause");
  return 1;
}

int alteracao()
{
  int livro = -1, resp;
  if (_numLivro <= 0)
  {
    return -2;
  }
  while (livro < 0 || livro >= _numLivro)
  {
    listarBiblioteca(0);
    if (_numLivro > 1)
    {
      printf("Digite o livro que deseja alterar [%d - %d]: ", 1, _numLivro); // 1 é o limite
      scanf("%d", &livro);
      fflush(stdin);
      printf("\n");
    }
    else
    {
      livro = 1; // quebrar o laco
    }
    livro--; // pq estamos pedindo p usuario digitar uma pagina entre 1 e o limite max
    if (livro < 0 || livro >= _numLivro)
    {
      mensagemError(-8);
    }
    else
    {
      resp = alterarLivro(livro); // 1
    }
  }
  system("cls");
  if (resp > 0)
  {
    imprimeLivro(_Biblioteca[livro]);
  }
  system("PAUSE");
}

int alterarLivro(int livro)
{
  int escolha = 1, erro = -1, opTpAlteracao; // opcao de escolha q o usuario quer alterar
  char op;

  while (escolha > 0)
  {
    escolha = menuAlterarEscolha();
    switch (escolha)
    {
    case 1:
      printf("*** Dados do Livro\n");
      imprimeLivro(_Biblioteca[livro]);
      printf("Digite o novo titulo do livro: ");
      gets(_Biblioteca[livro].titulo);
      fflush(stdin);
      break;
    case 2:
      op = opTpAlteracao = -1;
      while (1)
      {
        menuAlterarOpcoes("Autor(es): ");
        scanf("%d", &opTpAlteracao);
        disparaTpAlteracaoAutor(opTpAlteracao, livro);
        if (opTpAlteracao == 8)
        {
          break;
        }
      }
      system("cls");
      printf("*** Dados do Livro\n");
      imprimeLivro(_Biblioteca[livro]);
      fflush(stdin);
      break;
    case 3:
      printf("*** Dados do Livro\n");
      imprimeLivro(_Biblioteca[livro]);
      printf("Digite a nova editora: ");
      gets(_Biblioteca[livro].editora);
      fflush(stdin);
      break;
    case 4:
      printf("*** Dados do Livro\n");
      imprimeLivro(_Biblioteca[livro]);
      while (erro < 0)
      {
        printf("Digite o novo numero de paginas: ");
        scanf("%d", &_Biblioteca[livro].num_pags);
        fflush(stdin);
        erro = validaNumero(_Biblioteca[livro].num_pags);
        if (erro < 0)
        {
          mensagemError(erro);
        }
      }
      break;
    case 5:
      printf("*** Dados do Livro\n");
      imprimeLivro(_Biblioteca[livro]);
      while (erro < 0)
      {
        printf("Digite o novo ano de edicao: ");
        scanf("%d", &_Biblioteca[livro].anoEdicao);
        fflush(stdin);
        erro = validaData(_Biblioteca[livro].anoEdicao);
        if (erro < 0)
        {
          mensagemError(erro);
        }
      }
      break;
    case 6:
      printf("*** Dados do Livro\n");
      imprimeLivro(_Biblioteca[livro]);
      printf("Digite o novo idioma: ");
      gets(_Biblioteca[livro].idioma);
      fflush(stdin);
      break;
    case 8:
      return -1;
      break;
    }

    op = 'x';
    while (op != 's' && op != 'n')
    {
      printf("Deseja alterar mais algum item (s/n)? ");
      scanf("%c", &op);
      fflush(stdin);
      op = tolower(op);
      if (op != 's' && op != 'n')
      {
        mensagemError(0);
      }
    }

    if (op == 'n')
    {
      escolha = -1;
    }
  }
  return 1;
}

int menuAlterarEscolha()
{
  int op = -1;
  while (op < 1 || op > 8)
  {
    system("cls");
    printf("****** Digite a opcao que deseja alterar\n ******");
    printf("- (1) Titulo\n");
    printf("- (2) Autor (es)\n");
    printf("- (3) Editora\n");
    printf("- (4) Numero de paginas\n");
    printf("- (5) Ano de Edicao\n");
    printf("- (6) Idioma\n");
    printf("- (7) Assunto(s)\n");
    printf("- (8) Voltar p/ menu anterior\n");
    printf("*******************************\n");
    printf("- Digite sua opcao que deseja alterar: ");
    scanf("%d", &op);
    fflush(stdin);
    if (op < 1 || op > 8)
    {
      mensagemError(0);
    }
    else
    {
      return op;
    }
  }
}

void menuAlterarOpcoes(char *str)
{ // string que passamos em menuAlterarOpcoes
  system("cls");
  printf(" - (1) Incluir %s\n", str);
  printf(" - (2) Alterar %s\n", str);
  printf(" - (3) Excluir %s\n", str);
  printf(" - (4) Voltar ao menu anterior \n\n");
  printf("** Digite a opcao: ");
}

void disparaTpAlteracaoAutor(int op, int livro)
{
  int erro = 1, opS = -1;
  if (op < 1 || op > 4)
  {
    mensagemError(0);
  }
  else if (op < 4)
  {
    if (op == 1)
    {
      // incluir autor
      adicionarAutor(livro);
      printf("\n ****** AUTOR ADICIONADO!!!!*****\n");
      system("PAUSE");
    }
    else if (op == 2)
    {
      alterarAutor(livro);
      system("PAUSE");
    }
    else if (op == 3)
    {
      if (_Biblioteca[livro].numAutores == 1)
      {
        erro = -9;
      }
      else
      {
        excluirAutor(livro);
        system("PAUSE");
      }
    }
  }
  if (erro <= 0)
  {
    mensagemError(erro);
  }
}

void excluirAutor(int livro)
{
  int opAutor = 1, i;
  char op_sn;
  while (1)
  {
    system("cls");
    imprimeAutorLivro(_Biblioteca[livro]);
    printf("\n Escolha o Autor que deseja excluir: ");
    scanf("%d", &opAutor);
    fflush(stdin);

    if (opAutor < 1 || opAutor > (_Biblioteca[livro].numAutores))
    {
      mensagemError(0);
      continue;
    }
    else
    {
      op_sn = 'n';
      while (1)
      {
        printf("Deseja mesmo excluir o Autor [ %d ] (s / n)? ");
        scanf("%c", &op_sn);
        fflush(stdin);
        op_sn = tolower(op_sn);

        if ((op_sn != 'n') && (op_sn != 's'))
        {
          mensagemError(0);
          continue;
        }
        break; // quebra o laço
      }
      if (op_sn == 's')
      {
        if (_Biblioteca[livro].numAutores == opAutor)
        {                                                 // se ele escolher o ultimo autor
          free(_Biblioteca[livro].autor_es[opAutor - 1]); /// free libera espaço de memória
          _Biblioteca[livro].numAutores--;
        }
        else
        {
          for (i = opAutor - 1; i < (_Biblioteca[livro].numAutores - 1); i++)
          { // se ele escolher um autor do meio, a lista será reorganizada
            _Biblioteca[livro].autor_es[i] = _Biblioteca[livro].autor_es[i + 1];
          }
          _Biblioteca[livro].numAutores--; // Aqui exclui o artista
        }
        printf("\n **AUTOR EXCLUIDO COM SUCESSO !! **\n");
      }
      break;
    }
  }
}

void adicionarAutor(int livro)
{
  char strAux[100];
  printf("Novo Autor: ");
  gets(strAux);
  _Biblioteca[livro].autor_es = (char **)realloc(_Biblioteca[livro].autor_es, (_Biblioteca[livro].numAutores + 1) * sizeof(char *)); // mantem os autores que existe, e add mais um

  if (!_Biblioteca[livro].autor_es)
  {
    printf("Erro ao adicionar um novo Autor (1)!!!\n");
    exit(1);
  }

  _Biblioteca[livro].autor_es[_Biblioteca[livro].numAutores] = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

  if (!_Biblioteca[livro].autor_es[_Biblioteca[livro].numAutores])
  {
    printf("Erro ao adicionar um novo Autor (2)!!!\n");
    exit(1);
  }

  strcpy(_Biblioteca[livro].autor_es[_Biblioteca[livro].numAutores], strAux);
  _Biblioteca[livro].autor_es++;
}

void alterarAutor(int livro)
{
  int opAutor;
  char op_sn, strAux[100];
  while (1)
  {
    system("cls");
    imprimeAutorLivro(_Biblioteca[livro]);
    if (_Biblioteca[livro].numAutores > 1)
    {
      printf("\nEscolha qual autor deseja alterar: ");
      scanf("%d", &opAutor);
      fflush(stdin);
    }
    else
    {
      opAutor = 1;
    }

    if ((opAutor < 1) || (opAutor > _Biblioteca[livro].numAutores))
    {
      mensagemError(0);
    }
    else
    {
      op_sn = 'n';
      while (1)
      {
        printf("\nAlteracao autor [%d]: ", opAutor);
        gets(strAux);
        fflush(stdin);

        printf("Voce confirma essa alteracao [%d]? (s/n): ", opAutor);
        scanf("%c", &op_sn);
        fflush(stdin);
        op_sn = tolower(op_sn);
        if (op_sn != 'n' || op_sn != 's')
        {
          mensagemError(0);
          continue;
        }
        break;
      }
      if (op_sn == 's')
      {
        _Biblioteca[livro].autor_es[opAutor - 1] = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

        if (!_Biblioteca[livro].autor_es[opAutor - 1])
        {
          printf("Erro na alteracao de um autor!!!\n");
          exit(1);
        }
        strcpy(_Biblioteca[livro].autor_es[opAutor - 1], strAux);
        printf("\n\n**** AUTOR ALTERADO!!!!");
      }
      break;
    }
  }
}

void imprimeAutorLivro(TLivro l)
{
  int i;
  for (i = 0; i < l.autor_es; i++)
  {
    printf("[ %d ] - %s\n", i + 1, l.autor_es[i]);
  }
}

void mensagemError(int codigoErro)
{ // mensagens de erro
  switch (codigoErro)
  {
  case 0:
    printf("\nERRO: Opcao Invalida. Selecione outra!\n");
    break;
  case -1:
    printf("\nERRO: A biblioteca ja esta cheia!\n");
    break;
  case -2:
    printf("A Lista esta vazia!!!\n");
    break;
    break;
  case -10:
    printf("\nERRO: Erro de Alocacao de Memoria!\n");
    break;

  case -5:
    printf("\nERRO: O numero de paginas nao pode ser negativo. Nao avacalha!!!!\n");
    break;

  case -6:
    printf("Caramba, voce achou um livro de antes de Cristo?\n");
    printf("Por favor, coloque o ano dessa edicao!\n");
    break;

  case -7:
    printf("Erro: Voce precisa colocar um ano valido!!!!\n");
    break;
  case -9:
    printf("Erro: Exclusao de Autor nao permitido!!");
    break;

  case -8:
    printf("Livro invalido!!!!\n");
    break;

  default:
    printf("ERRO!\n");
    break;
  }
  system("pause");
  system("cls"); // limpar a tela
}

TLivro criaLivro()
{
  TLivro l;
  char stringAux[100], op; // a stringAux vai facilitar a alocação dinamica das strings
  int adicionar;

  // TITULO

  printf("Titulo: ");
  gets(stringAux);                                                   // strlen retorna a quantidade de caracteres de uma string  - strcpy copia pra um destino oq vem da origem
  l.titulo = (char *)malloc((strlen(stringAux) + 1) * sizeof(char)); // malloc = criação       sizeof pega o tamanho que o char ocupada na memoria e vai multiplicar  pela quantidade que precisamos( que é oq o usuario digitou) OTIMIZAÇÃO DE MEMORIA
  strcpy(l.titulo, stringAux);                                       // pegamos oq o usuario digitou e jogamos no l.titulo cujo espaço de memoria reservamos na linha acima
  fflush(stdin);

  // AUTORES //
  adicionar = 1;
  l.numAutores = 0;
  while (adicionar)
  {
    printf("Autor(es) [%d]: ", l.numAutores + 1);
    gets(stringAux);

    if (l.numAutores == 0)
    {
      l.autor_es = (char **)malloc(1 * sizeof(char));
    }
    else
    {
      l.autor_es = (char **)realloc(l.autor_es, (l.numAutores + 1) * sizeof(char));
    }

    if (!l.autor_es)
    {
      printf("ERRO na criacao do vetor Autores! \n");
      exit(1);
    }

    l.autor_es[l.numAutores] = (char *)malloc((strlen(stringAux) + 1) * sizeof(char)); // aqui reservamos a quantidade de caracteres necessarias pro numAutores

    if (!l.autor_es[l.numAutores])
    {
      printf("ERRO na Criacao da String para o Autor [%d] !\n", l.numAutores);
      exit(1);
    }

    strcpy(l.autor_es[l.numAutores++], stringAux); // copiar oq o usuario escreveu e adiciona +1 no numero de autores
    fflush(stdin);

    op = 'x';
    while (op != 's' && op != 'n') // forçando a digitar s ou n
    {
      printf("Deseja adicionar outro Autor? (S/N)");
      scanf("%c", &op);
      fflush(stdin);
      op = tolower(op); // tolower = pegar o que o usuario digitou e converter para minusculo, caso digite em maiusculo
      if (op == 's' || op == 'n')
      { // se escolher opcao certa, quebra o laço
        break;
      }
      mensagemError(0);
    }

    if (op == 'n')
    {
      adicionar = 0;
    }
  }

  // EDITORA

  printf("Editora: ");
  gets(stringAux);
  l.editora = (char *)malloc((strlen(stringAux) + 1) * sizeof(char));
  strcpy(l.editora, stringAux);
  fflush(stdin);

  // NUMERO DE PAGINAS
  int erro = -1;
  while (erro < 0)
  {
    printf("Numero de Paginas: ");
    scanf("%d", &l.num_pags);
    fflush(stdin);
    erro = validaNumero(l.num_pags);
    if (erro < 0)
    {
      mensagemError(erro);
    }
    else
    {
    }
  }

  // Ano de edição
  erro = -1;
  while (erro < 0)
  {
    printf("Ano de Edicao: ");
    scanf("%d", &l.anoEdicao);
    fflush(stdin);
    erro = validaData(l.anoEdicao);

    if (erro < 0)
    {
      mensagemError(erro);
    }
    else
    {
    }
  }

  // IDIOMA
  printf("Idioma: ");
  gets(stringAux);
  l.idioma = (char *)malloc((strlen(stringAux) + 1) * sizeof(char));
  strcpy(l.idioma, stringAux);
  fflush(stdin);

  // ASSUNTO

  adicionar = 1;
  l.numAssunto = 0;
  while (adicionar)
  {
    printf("Assunto [%d]:", l.numAssunto + 1);
    gets(stringAux);

    if (l.numAssunto == 0)
    {
      l.assunto = (char **)malloc(1 * sizeof(char));
    }
    else
    {
      l.assunto = (char **)realloc(l.assunto, (l.numAssunto + 1) * sizeof(char));
    }

    if (!l.assunto)
    {
      printf("ERRO na criacao do vetor Assunto! \n");
      exit(1);
    }

    l.assunto[l.numAssunto] = (char *)malloc((strlen(stringAux) + 1) * sizeof(char)); // aqui reservamos a quantidade de caracteres necessarias pro numAssunto

    if (!l.assunto[l.numAssunto])
    {
      printf("ERRO na Criacao da String para o Assunto [%d] !\n", l.numAssunto);
      exit(1);
    }

    strcpy(l.assunto[l.numAssunto++], stringAux); // copiar oq o usuario escreveu e adiciona +1 no numero de assuntos
    op = 'x';

    while (op != 's' && op != 'n') // forçando a digitar s ou n
    {
      printf("Deseja adicionar outro Assunto ao Livro? (S/N)");
      scanf("%c", &op);
      fflush(stdin);
      op = tolower(op); // tolower = pegar o que o usuario digitou e converter para minusculo, caso digite em maiusculo
      if (op == 's' || op == 'n')
      { // se escolher opcao certa, quebra o laço
        break;
      }
      mensagemError(0);
    }

    if (op == 'n')
    {
      adicionar = 0;
    }
  }
  return l;
}

void imprimeLivro(TLivro l)
{
  int i;
  printf("Titulo: %s\n", l.titulo);

  printf("Autor: ");
  for (i = 0; i < l.numAutores; i++) // imprimir todos os autores
  {
    printf("%s, ", l.autor_es[i]);
  }

  printf("\n");

  printf("Editora: %s\n", l.editora);

  printf("Numero de Paginas: %d\n", l.num_pags);

  printf("Ano de Edicao: %d\n", l.anoEdicao);

  printf("Idioma: %s\n", l.idioma);

  printf("Assunto: ");
  for (i = 0; i < l.numAssunto; i++) // imprimir todos os assuntos
  {
    printf("%s,", l.assunto[i]);
  }
  printf("\n");
}

int validaNumero(int num_pags)
{
  if (num_pags <= 0)
  {
    return -5;
  }

  else if (num_pags >= 10000)
  {
    return -8;
  }

  else
  {
    return 1;
  }
}

int validaData(int anoEdicao)
{
  if (anoEdicao < 0)
  {
    return -7;
  }
  else if (anoEdicao > 2023)
  {
    return -6;
  }

  else
  {
    return 1;
  }
}

void menu_listar()
{
  system("cls"); // limpar a tela
  printf("*********** LISTAR LIVRO(S) ************\n");
  printf(" - (1) Listar Livro.\n");
  printf(" - (2) Listar Todos os Livros.\n");
  printf(" - (3) Voltar Opcao Anterior.\n\n");
  printf(" - Digite a opcao que deseja alterar: ");
}

void opcao_listar_menu(int opS)
{
  int erro, livro;
  if (opS < 1 || opS > 3)
  {
    mensagemError(0);
  }
  else if (opS < 3)
  {
    system("cls");
    if (opS == 1)
    {
      if (_numLivro == 1)
      {                               // listar um livro especifico
        imprimeLivro(_Biblioteca[0]); // essa funcao recebe por parametro um livro
        system("PAUSE");
        return;
      }
      livro = -1;
      while (livro < 1 || livro > _numLivro)
      {
        printf("Digite o n. do livro! [%d - %d]", 1, _numLivro);
        scanf("%d", &livro);
        if (livro < 1 || livro > _numLivro)
        {
          mensagemError(-8);
          continue;
        }
        imprimeLivro(_Biblioteca[livro - 1]);
        system("PAUSE");
      }
    }
    else if (opS == 2)
    { // listar todos os livros
      erro = listarBiblioteca(1);
    }
    if (erro < 0)
    {
      mensagemError(erro);
    }
  }
}

int listarBiblioteca(int pause)
{
  int i; // indexador para percorrer a lista
  if (_numLivro <= 0)
  {
    return -2; // lista vazia
  }

  system("cls");

  for (i = 0; i < _numLivro; i++)
  {
    printf("****** LIVRO[%d] *****\n", i + 1);
    imprimeLivro(_Biblioteca[i]);
  }

  if (pause)
  {
    system("PAUSE");
  }

  return 1;
}
void salvarArquivo()
{
  int i, j;
  FILE *Larq; // pra salvar em arquivo precisa declarar uma variavel do tipo file

  // abrir o arquivo
  Larq = fopen("ArqLivros.txt", "a"); // um dos modos de abrir o arquivo é com w de write onde ele escreve os dados. o W apaga os dados e sobrescreve

  if (Larq == NULL)
  {
    printf("ERRO: Nao foi possivel criar o Livro. Aconteceu alguma coisa!");
    exit(0);
  }

  for (i = 0; i <= _numLivro; i++)
  {                                              // o fprintf diz em qual arquivo eu vou salvar
    fprintf(Larq, "%s;", _Biblioteca[i].titulo); // cada musica vai ficar numa linha. dados serão separados por ; @ e #.
    fprintf(Larq, "%s;", _Biblioteca[i].editora);
    fprintf(Larq, "%d;", _Biblioteca[i].num_pags);
    fprintf(Larq, "%d;", _Biblioteca[i].anoEdicao);
    fprintf(Larq, "%s;", _Biblioteca[i].idioma);

    for (j = 0; j < _Biblioteca[i].numAutores; j++)
    {
      fprintf(Larq, "%s@", _Biblioteca[i].autor_es[j]); // os autores serão separados por @
    }

    for (j = 0; j < _Biblioteca[i].numAssunto; j++)
    {
      fprintf(Larq, "%s#", _Biblioteca[i].assunto[j]);
    }

    fprintf(Larq, "%c", '\n'); // cada livro vai ficar numa linha
  }

  fclose(Larq);
}

void recuperarDados()
{
  int i, separador, j;
  char str[100], c;
  FILE *Larq; // abre o arquivo

  Larq = fopen("ArqLivros.txt", "ar");
  if (Larq)
  {
    i = 0;         // usado para indexar a string
    separador = 0; // usado para contar os separadores ~> ; # &

    while (!feof(Larq)) // o feof(end of file) com o Larq aponta para o final do arquivo. Quando o caracter do Larq for igual ao final, o laço quebra.
    {
      c = fgetc(Larq); // fgetch pega caracter e posiciona o proximo para leitura até chegar no final.
      if ((c != '\n') && (c != ';') && (c != '@') && (c != '#') && (c != EOF))
      {
        str[i++] = c;
      }
      else if ((c == ';') || (c == '@') || (c == '#') || (c == '\n'))
      {
        str[i] = '\0'; // colocando o \0 forçadamente e tratando final de string
        i = 0;         // i = 0 porque o proximo caractere tem que ir pra primeira posição de novo, sobescrevendo o anterior.
        if (c == ';')
        {
          if (separador == 0)
          { // se for = 0 o titulo é o primeiro q vai mostrar
            if (_numLivro == 0)
            {
              _Biblioteca = (TLivro *)malloc(1 * sizeof(TLivro)); // reserva 1 espaco para o ponteiro TLivro
            }
            else
            {
              _Biblioteca = (TLivro *)realloc(_Biblioteca, (_numLivro + 1) * sizeof(_numLivro)); // vai add varios
            }

            _Biblioteca[_numLivro].titulo = (char *)malloc(strlen(str) + 1 * sizeof(char)); // reserva espaco do tipo char em função da quantidade de caracteres que vai ter em st
            strcpy(_Biblioteca[_numLivro].titulo, str);                                     // joga o q esta em titulo para str (que pegamos no arq)
            _Biblioteca[_numLivro].numAutores = 0;                                          // inicializa em 0, pois n sabemos qnt autores tem
            _Biblioteca[_numLivro].numAssunto = 0;                                          // inicializa em 0, pois n sabemos qnt assunto tem
            separador++;
          }
          else if (separador == 1)
          {
            _Biblioteca[_numLivro].editora = (char *)malloc(strlen(str) + 1 * sizeof(char)); // reserva espaco do tipo char em função da quantidade de caracteres que vai ter em str
            strcpy(_Biblioteca[_numLivro].editora, str);
            separador++;
          }
          else if (separador == 2)
          {
            _Biblioteca[_numLivro].num_pags = atoi(str); // atoi transforma um int em char
            separador++;
          }

          else if (separador == 3)
          {
            _Biblioteca[_numLivro].anoEdicao = atoi(str); // atoi transforma um int em char
            separador++;
          }
          else if (separador == 4)
          {
            _Biblioteca[_numLivro].idioma = (char *)malloc(strlen(str) + 1 * sizeof(char)); // reserva espaco do tipo char em função da quantidade de caracteres que vai ter em str
            strcpy(_Biblioteca[_numLivro].idioma, str);
            separador = 0;
          }

          else if (c == '@')
          {
            if (separador == 0)
            {
              _Biblioteca[_numLivro].autor_es = (char **)malloc(1 * sizeof(char *)); // reservando espaço para uma unica string
              j = _Biblioteca[_numLivro].numAutores;
              _Biblioteca[_numLivro].autor_es[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
              strcpy(_Biblioteca[_numLivro].autor_es[j], str);
              _Biblioteca[_numLivro].numAutores++;
            }
          }
          else
          {
            j = _Biblioteca[_numLivro].numAutores;
            _Biblioteca[_numLivro].autor_es = (char **)realloc(_Biblioteca[_numLivro].autor_es, (j + 1) * sizeof(char *));
            _Biblioteca[_numLivro].autor_es[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
            strcpy(_Biblioteca[_numLivro].autor_es[j], str);
            _Biblioteca[_numLivro].numAutores++;
          }
          separador = -1;
        }
        else if (c == '#')
        {
          if (separador == -1)
          {
            _Biblioteca[_numLivro].assunto = (char **)malloc(1 * sizeof(char *)); // reservando espaço para uma unica string
            j = _Biblioteca[_numLivro].numAssunto;
            _Biblioteca[_numLivro].assunto[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
            strcpy(_Biblioteca[_numLivro].assunto[j], str);
            _Biblioteca[_numLivro].numAssunto++;
          }
          else
          {
            j = _Biblioteca[_numLivro].numAssunto;
            _Biblioteca[_numLivro].assunto = (char **)realloc(_Biblioteca[_numLivro].assunto, (j + 1) * sizeof(char *));
            _Biblioteca[_numLivro].assunto[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
            strcpy(_Biblioteca[_numLivro].assunto[j], str);
            _Biblioteca[_numLivro].numAssunto++;
          }
          separador = -2;
        }
        else
        {
          separador = 0;
          _numLivro++;
        }
      }
    }
  }

  fclose(Larq);
}
