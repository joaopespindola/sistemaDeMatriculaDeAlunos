#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUANTIDADE 40
//Struct aluno com os dados iniciais para cadastro de alunos
struct aluno{
  int matricula;
  char curso[50];
  char nascimento[20];
  char nome[50];
};

/*struct dados com uma struct de vetor para armazenar cada aluno cadastrado em cada posicao do vetor*/
struct dados{
  struct aluno alunos[QUANTIDADE]; //struct de vetor
  int qtd; //variáveis de controle
};


/* funcao para cadastro de alunos*/
void cadastro(struct dados* T){//recebe struct dados como ponteiro
  int matricula;
  char nascimento[20];
  char nome[50];
  char curso[50];

  printf("\n---------------------------");
  printf("\n---INFORMACOES DO ALUNO----");
  printf("\n---------------------------");
  printf("\nNome: ");
  scanf("%[^\n]s", nome);// escaneia o nome ate o \n
  printf("Data de Nascimento: ");
  scanf("%s", nascimento);//escaneia a data de nascimento
  setbuf(stdin, NULL);
  printf("Curso: ");
  scanf("%[^\n]s", curso);//escaneia o curso ate o \n
  printf("Matricula: ");
  scanf("%d", &matricula);//escaneia o valor da matricula

  /* for variando de 0 ate a quantidade de alunos e fazendo a comparacao
  dos valores do vetor com o valor inserido, caso sejam iguais a mensagem
  Essa matricula ja existe sera acionada*/
  for(int i = 0; i < T->qtd; i++){
    if(T->alunos[i].matricula == matricula){
      printf("Essa matricula ja existe!\n");
      setbuf(stdin, NULL);
      getchar();
      return;
    }
  }
  /* copia dos dados digitados para as estruturas do struct aluno, e um
  aumento da quantidade de alunos em +1*/
  strcpy(T->alunos[T->qtd].nome, nome);
  strcpy(T->alunos[T->qtd].curso, curso);
  strcpy(T->alunos[T->qtd].nascimento, nascimento);
  T->alunos[T->qtd].matricula = matricula;
  T->qtd = T->qtd+1;



  setbuf(stdin, NULL);
  printf("-->Cadastrado com Sucesso!");
  /*o getchar é utilizado para que um caractere seja inserido e não vá
  diretamente de volta para a função menu antes da mensagem Cadastrado com
  Sucesso ser exibida*/
  getchar();

}

/*funcao com o objetivo de excluir a matricula digitada*/
void excluir_matricula(struct dados T[]){
  int matricula;
  printf("\n---------------------------");
  printf("\n----MATRICULA A EXCLUIR----");
  printf("\n---------------------------");
  printf("\nMatricula: ");
  scanf("%d", &matricula);//Escaneia o valor da matricula

  //laco de rep variando de 0 ate qtd de alunos
  for(int i = 0; i < T->qtd; i++){

    //comparacao entre matricula digitada e matriculas cadastradas
    if(T->alunos[i].matricula == matricula){
        for(int j = i; j < T->qtd-1; j++){ //reposiciona
          strcpy(T->alunos[j].nome, T->alunos[j+1].nome);
          strcpy(T->alunos[j].curso, T->alunos[j+1].curso);
          strcpy(T->alunos[j].nascimento, T->alunos[j+1].nascimento);
          T->alunos[j].matricula = T->alunos[j+1].matricula;
        }
      /* se a comparacao for True, um loop sera iniciado variando de j ate qtd-1,
caso seja a ultima matricula cadastrada, o loop sera encerrado.
Se nao for a ultima matricula, sera feita a copia das matriculas das posiçoes a frente
para as posiçoes anteriores.
*/
      T->qtd = T->qtd -1;
      setbuf(stdin, NULL);
      printf("Excluido com sucesso!");
      getchar();
      return;
    }
  }
  setbuf(stdin, NULL);
  // caso a matricula digitada nao exista.
  printf("Matricula nao encontrada!");
  getchar();
  return;
}

/*funcao que mostra todos os alunos cadastrados*/
void mostra_todos(struct dados T[]){

  /*laco de repeticao variando de 0 ate a qnt maxima de alunos, e
  imprimindo os dados a cada repeticao*/
  for(int i = 0; i < T->qtd; i++){
    printf("\n---------------------------\n");
    printf("Aluno: %s\n", T->alunos[i].nome);
    printf("Curso: %s\n", T->alunos[i].curso);
    printf("Nascimento: %s\n", T->alunos[i].nascimento);
    printf("Matricula: %d\n", T->alunos[i].matricula);
    printf("---------------------------\n");
  };

  //se a quantidade de alunos for 0
  if(T->qtd == 0){
    printf("\nNenhum aluno cadastrado!");
  }

  printf("\nAperte para retornar ao menu...");
  getchar();

}

/*funcao que mostra alunos por curso*/
void mostra_curso(struct dados T[]){//recebe a struct de vetor T[]
  char curso[50];
  int qtd = 0;
  printf("Digite o nome do curso: ");
  scanf("%[^\n]s", curso);//escaneia o nome do curso


  printf("\n---------------------------");
  printf("\n\t%s", curso);
  printf("\n---------------------------");

  //laco de repeticao variando de 0 ate qtd maxima*/
  for(int i = 0; i < T->qtd; i++){

    /* comparacao, se o curso bater com algum curso de aluno cadastrado, o
    codigo abaixo sera impresso*/
    if(strcmp(T->alunos[i].curso, curso) == 0){
      printf("\n---------------------------\n");
      printf("Aluno: %s\n", T->alunos[i].nome);
      printf("Curso: %s\n", T->alunos[i].curso);
      printf("Nascimento: %s\n", T->alunos[i].nascimento);
      printf("Matricula: %d\n", T->alunos[i].matricula);
      printf("---------------------------\n");
      qtd++;
    }
  }
  if(qtd == 0){
    //caso nao haja alunos cadastrados
    printf("\nNao ha alunos para esse curso\n");
  }
  setbuf(stdin, NULL);
  printf("\nAperte para retornar ao menu...");
  getchar();

}

/*funcao para abrir um .txt e ler seu conteudo para atribui-lo ao sistema de matriculas*/
void carrega_arquivo (struct dados T[]){
  FILE* arquivo;
  char nome_arquivo[50];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome_arquivo);

  //arquivo é aberto no formato leitura "r"
  arquivo = fopen(nome_arquivo, "r"); //abre arquivo e lê

  //se o arquivo estiver vazio, alerta de erro
  if(arquivo == NULL){
    printf("Erro ao carregar o arquivo!");
    setbuf(stdin, NULL);
    getchar();
    return;
  }

  T->qtd = 0; //seta em 0 para iniciar o loop
  setbuf(stdin, NULL);

  //roda até o final do arquivo lendo todas as linhas até uma linha vazia

  //fgets(        VARIAVEL,        TAMANHO_VAR, NOME_ARQUVIVO)
  //fgets(T->alunos[T->qtd].nome,        50,      arquivo)

  while(fgets(T->alunos[T->qtd].nome, 50, arquivo) != NULL){
    //indica o nome do aluno pro codigo
    T->alunos[T->qtd].nome[strcspn(T->alunos[T->qtd].nome, "\n")] = '\0';

    //indica o curso do aluno
    fgets(T->alunos[T->qtd].curso, 50, arquivo);
    T->alunos[T->qtd].curso[strcspn(T->alunos[T->qtd].curso, "\n")] = '\0';

    //indica a data de nascimento do aluno
    fgets(T->alunos[T->qtd].nascimento, 20, arquivo);
    T->alunos[T->qtd].nascimento[strcspn(T->alunos[T->qtd].nascimento, "\n")] = '\0';

    //indica a matricula do aluno
    fscanf(arquivo, "%d\n", &T->alunos[T->qtd].matricula);
    T->qtd++;
  }

  //fecha arquivo
  fclose(arquivo);
  printf("%s carregado com sucesso!", nome_arquivo);
  setbuf(stdin, NULL);
  getchar();

}

/*funcao salva as informacoes em um .txt previamente salvo caso ja exista um com o nome indicado ou cria um novo*/
void salva_arquivo (struct dados T[]){
  FILE* arquivo;
  char nome_arquivo[50];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nome_arquivo);

  //arquivo aberto em forma de escrita ("w" - write)
  arquivo = fopen(nome_arquivo, "w");

  //se arquivo nao existir ou estiver vazio, alertar erro
  if(arquivo == NULL){
    printf("Erro ao carregar o arquivo!");
    setbuf(stdin, NULL);
    getchar();
    return;
  }

  //zera variavel para iniciar o loop
  int quantidade = 0;

  //loop ate a quantidade de alunos, salvando as informacoes no arquivo
  while(quantidade < T->qtd){
    //fprintf(NOME_ARQUIVO, TEXTO_SALVO, NOME_DA_VARIAVEL_DE_ONDE_PUXOU)
    fprintf(arquivo, "%s\n", T->alunos[quantidade].nome);
    fprintf(arquivo, "%s\n", T->alunos[quantidade].curso);
    fprintf(arquivo, "%s\n", T->alunos[quantidade].nascimento);
    fprintf(arquivo, "%d\n", T->alunos[quantidade].matricula); //importante pular ultima linha
    quantidade++;
  }

  //fecha arquivo
  fclose(arquivo);
  printf("%s salvo com sucesso!", nome_arquivo);
  setbuf(stdin, NULL);
  getchar();
  return;
}

/*funcao que mostra uma matricula especifica requisitada*/
void mostra1(struct dados T[]){
  int matricula;
  printf("Digite a matricula: ");
  scanf("%d", &matricula);

  //laco variando de 0 ate qtd de alunos
  for(int i = 0; i < T->qtd; i++){
    //se alunos[i] = matricula digitada o codigo abaixo sera rodado
    if(T->alunos[i].matricula == matricula){
      printf("\n---------------------------\n");
      printf("Aluno: %s\n", T->alunos[i].nome);
      printf("Curso: %s\n", T->alunos[i].curso);
      printf("Nascimento: %s\n", T->alunos[i].nascimento);
      printf("Matricula: %d\n", T->alunos[i].matricula);
      printf("---------------------------\n");
      setbuf(stdin, NULL);
      printf("\nAperte para retornar ao menu...");
      getchar();
      return;
    }
  };
  setbuf(stdin, NULL);
  //caso a matricula digitada nao bata, sera exibido a mensagem abaixo
  printf("\nMatricula nao encontrada!");
  getchar();

}

/*altera os dados de uma matricula ja cadastrada*/
int altera_dados(struct dados T[]){
  int matricula;
  printf("Digite a matricula: ");
  scanf("%d", &matricula);

  //loop de variando de 0 ate qtd de alunos
  for(int i = 0; i < T->qtd; i++){
    //se alunos[i] = matricula digitada, codigo abaixo ira rodar.
    if(T->alunos[i].matricula == matricula){
      //imprime dados do aluno
      printf("\n---------------------------\n");
      printf("-----Aluno encontrado!-----\n");
      printf("---------------------------\n");
      printf("Aluno: %s\n", (*T).alunos[i].nome);
      printf("Curso: %s\n", T->alunos[i].curso);
      printf("Nascimento: %s\n", T->alunos[i].nascimento);
      printf("Matricula: %d\n", T->alunos[i].matricula);
      printf("---------------------------\n");

      //digita novos os novos dados
      setbuf(stdin, NULL);
      printf("Digite o novo nome: ");
      scanf("%[^\n]s", T->alunos[i].nome);
      setbuf(stdin, NULL);
      printf("Digite o novo curso: ");
      scanf("%[^\n]s", T->alunos[i].curso);
      setbuf(stdin, NULL);
      printf("Digite o novo nascimento: ");
      scanf("%s", T->alunos[i].nascimento);

      printf("\nAlterado com sucesso!\n");

      setbuf(stdin, NULL);
      printf("\nAperte para retornar ao menu...");
      getchar();
      return -1;
    }
  };
  //caso nao encontre a matrícula, printara Aluno nao encontrado
  printf("\nAluno nao encontrado!\n");
  setbuf(stdin, NULL);
  printf("\nAperte para retornar ao menu...");
  getchar();
  return 0;
}

/*funcao que imprime os cursos existentes na tela*/
void imprime_cursos(struct dados T[]){
  if(T->qtd > 0){//se a qtd de alunos for maior que 0 inciara o codigo
    char cursos[50][50]= {};
    int new_qtd = 1;
    int valores;

    strcpy(cursos[0],T->alunos[0].curso);

    for(int i = 0; i < T->qtd; i++){
      valores = 0;
      for(int j = 0; j < new_qtd; j++){
        /*se a comparacao cursos[j] e T->alunos[i].curso for != 0 o if sera acionado*/
          if(strcmp(cursos[j],T->alunos[i].curso) != 0){
            valores++;

              if(valores == new_qtd){
                //se valores for igual a new_qtd, havera uma copia de string de T->alunos[i].curso para cursos[new_qtd]
                strcpy(cursos[new_qtd], T->alunos[i].curso);
                new_qtd++;
            }
          }
      }
    }

    printf("\n---------------------------");
    printf("\n-----CURSOS NO SISTEMA-----");
    printf("\n---------------------------");
    for(int i = 0; i < new_qtd; i++){
      printf("\n---------------------------");
      printf("\n\t%s", cursos[i]);
      printf("\n---------------------------");
    }


  }
    //se qtd de alunos for menor que 0, o else ira rodar
  else{
    printf("Ainda nao tem alunos cadastrados em cursos");
  }
  setbuf(stdin, NULL);
  printf("\nAperte para retornar ao menu...");
  getchar();
}

void menu(){
	int opcao;
	struct dados T = {};
  T.qtd= 0;



	while(1){
    system("clear");
		printf("\nBem vindo ao Sistema de Matriculas de alunos ");
		printf("\n1- Cadastrar ");
    printf("\n2- Alterar dados ");
		printf("\n3- Mostrar Todos");
		printf("\n4- Mostrar um");
    printf("\n5- Mostrar alunos por curso");
    printf("\n6- Mostrar cursos");
    printf("\n7- Excluir por matricula");
    printf("\n8- Carregar do arquivo");
    printf("\n9- Salvar alteracoes");
		printf("\n0- Sair ");
		printf("\nDigite opcao: ");
		scanf("%d", &opcao);

    setbuf(stdin, NULL);
		if(opcao == 1) cadastro(&T);
    if(opcao == 2) altera_dados(&T);
		if(opcao == 3) mostra_todos(&T);
		if(opcao == 4) mostra1(&T);
    if(opcao == 5) mostra_curso(&T);
    if(opcao == 6) imprime_cursos(&T);
    if(opcao == 7) excluir_matricula(&T);
    if(opcao == 8) carrega_arquivo(&T);
    if(opcao == 9) salva_arquivo(&T);
		if(opcao == 0) return;
	}
}

int main(){
	menu();
}
