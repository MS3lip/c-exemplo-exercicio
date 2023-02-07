#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLIVROS 1000

typedef struct
{
  int numAssunto; // quantidade de assuntos
  char **assunto; // fazer menu para perguntar se quer adicionar mais um
} TAssunto;

typedef struct
{
  char *titulo;
  int numAutores;
  char **autor_es;
  char *editora;
  int num_pags;
  int anoEdicao;
  char *idioma;
  TAssunto assuntos;
} TLivro;

TLivro *_Biblioteca; // variavel global
int _numLivro = 0;

int main()
{
  int i, separador, j;
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
            _Biblioteca[_numLivro].assuntos.numAssunto = 0;                                 // inicializa em 0, pois n sabemos qnt assunto tem
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

            if (j == 0)
            {
              _Biblioteca[_numLivro].autor_es = (char **)malloc(1 * sizeof(char));
            }
            else
            {
              _Biblioteca[_numLivro].autor_es = (char *)realloc(_Biblioteca[_numLivro].autor_es, (j + 1) * sizeof(j));
            }

            _Biblioteca[_numLivro].autor_es[j] = (char *)malloc(strlen(str) + 1 * sizeof(char));
            strcpy(_Biblioteca[_numLivro].autor_es[j], str);
            _Biblioteca[_numLivro].numAutores++;
          }
          separador = -1;
        }
        else if (c == '#')
        {
          if (separador == -1)
          {
            _Biblioteca[_numLivro].assuntos.assunto = (char **)malloc(1 * sizeof(char *)); // reservando espaço para uma unica string
            j = _Biblioteca[_numLivro].assuntos.numAssunto;
            _Biblioteca[_numLivro].assuntos.assunto[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
            strcpy(_Biblioteca[_numLivro].assuntos.assunto[j], str);
            _Biblioteca[_numLivro].assuntos.numAssunto++;
          }
          else
          {
            j = _Biblioteca[_numLivro].assuntos.numAssunto;
            //_Biblioteca[_numLivro].assuntos.assunto[j] = (char *)malloc((strlen(str) + 1) * sizeof(char *));
            //_Biblioteca[_numLivro].assuntos.assunto = (char **)realloc(_Biblioteca[_numLivro].assuntos.assunto, (j + 1) * sizeof(char *));
            strcpy(_Biblioteca[_numLivro].assuntos.assunto[j], str);
            _Biblioteca[_numLivro].assuntos.numAssunto++;
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

  printf("_numlivro: %d", _numLivro);

  system("pause");
}

/*
int i, separador,j;
    char str[100], c;
    FILE *Larq;          // abre o arquivo

    Larq = fopen ("ArqLivros.txt", "ar");
    if (Larq)
    {
        i = 0;          // usado para indexar a string
        separador = 0;  // usado para contar os separadores ~> ; # &

        while (!feof(Larq))      // o feof(end of file) com o Larq aponta para o final do arquivo. Quando o caracter do Larq for igual ao final, o laço quebra.
        {
            c = fgetc(Larq);          // fgetch pega caracter e posiciona o proximo para leitura até chegar no final.
            if((c != '\n') && (c != ';') && (c != '@') && (c!= '#') && (c != EOF)){
                str[i++] = c;

            } else if((c == ';') || (c == '@') || (c == '#') || (c == '\n')){
                str[i] = '\0';              //colocando o \0 forçadamente e tratando final de string
                i = 0;                      // i = 0 porque o proximo caractere tem que ir pra primeira posição de novo, sobescrevendo o anterior.
                if(c == ';'){
                    if(separador == 0){     //se for = 0 o titulo é o primeiro q vai mostrar
                        if(_numLivro == 0){
                            _Biblioteca = (TLivro *) malloc (1 * sizeof(TLivro)); //reserva 1 espaco para o ponteiro TLivro
                        }
                        else{
                            _Biblioteca = (TLivro *) realloc (_Biblioteca, (_numLivro + 1) * sizeof(_numLivro)); //vai add varios
                        }

                        _Biblioteca[_numLivro].titulo = (char *) malloc (strlen(str)+1 * sizeof (char)); //reserva espaco do tipo char em função da quantidade de caracteres que vai ter em st
                        strcpy(_Biblioteca[_numLivro].titulo, str); //joga o q esta em titulo para str (que pegamos no arq)
                        _Biblioteca[_numLivro].numAutores = 0; //inicializa em 0, pois n sabemos qnt autores tem
                        _Biblioteca[_numLivro].numAssunto = 0; //inicializa em 0, pois n sabemos qnt assunto tem
                        separador++;
                    }
                    else if(separador == 1){
                        _Biblioteca[_numLivro].editora = (char *) malloc (strlen(str)+1 * sizeof (char)); //reserva espaco do tipo char em função da quantidade de caracteres que vai ter em str
                        strcpy(_Biblioteca[_numLivro].editora, str);
                        separador++;
                    }
                    else if(separador == 2){
                        _Biblioteca[_numLivro].num_pags = atoi(str); //atoi transforma um int em char
                        separador++;
                    }

                    else if(separador == 3){
                        _Biblioteca[_numLivro].anoEdicao = atoi(str); //atoi transforma um int em char
                        separador++;
                    }
                    else if(separador == 4){
                        _Biblioteca[_numLivro].idioma = (char *) malloc (strlen(str)+1 * sizeof (char)); //reserva espaco do tipo char em função da quantidade de caracteres que vai ter em str
                        strcpy(_Biblioteca[_numLivro].idioma, str);
                        separador = 0;
                    }

                    else if (c == '@'){
                        if (separador == 0){
                            _Biblioteca[_numLivro].autor_es = (char **) malloc (1 * sizeof(char *)); // reservando espaço para uma unica string
                            j = _Biblioteca[_numLivro].numAutores;
                            _Biblioteca[_numLivro].autor_es[j] = (char *) malloc ((strlen(str) + 1) * sizeof(char *));
                            strcpy (_Biblioteca[_numLivro].autor_es[j], str);
                             _Biblioteca[_numLivro].numAutores++;
                        }
                    }
                    else{
                        j = _Biblioteca[_numLivro].numAutores;
                        _Biblioteca[_numLivro].autor_es = (char **) realloc (_Biblioteca[_numLivro].autor_es, (j+1) * sizeof(char *));
                        _Biblioteca[_numLivro].autor_es[j] = (char *) malloc ((strlen(str) + 1) * sizeof(char *));
                        strcpy (_Biblioteca[_numLivro].autor_es[j], str);
                        _Biblioteca[_numLivro].numAutores++;
                    }
                    separador = -1;
                }
                else if(c == '#'){
                if (separador == -1){
                    _Biblioteca[_numLivro].assunto = (char **) malloc (1 * sizeof(char *)); // reservando espaço para uma unica string
                    j = _Biblioteca[_numLivro].numAssunto;
                    _Biblioteca[_numLivro].assunto[j] = (char *) malloc ((strlen(str) + 1) * sizeof(char *));
                    strcpy (_Biblioteca[_numLivro].assunto[j], str);
                    _Biblioteca[_numLivro].numAssunto++;
                } else{
                    j = _Biblioteca[_numLivro].numAssunto;
                    _Biblioteca[_numLivro].assunto = (char **) realloc (_Biblioteca[_numLivro].assunto, (j+1) * sizeof(char *));
                    _Biblioteca[_numLivro].assunto[j] = (char *) malloc ((strlen(str) + 1) * sizeof(char *));
                    strcpy (_Biblioteca[_numLivro].assunto[j], str);
                    _Biblioteca[_numLivro].numAssunto++;
                }
                    separador = -2;
                }
                else{
                    separador = 0;
                    _numLivro++;
                }
            }
        }
    }

    fclose(Larq);
*/