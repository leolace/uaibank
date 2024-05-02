#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[101];
	int age;
	float current_balance;
} User;

User new_user(int users_qnty) {
  char name[101];
  int age = 0;
  float current_balance = 0.0;
  User user;

  printf("\nDigite o nome do usuário: \n");
  scanf(" %19[^\n]", &name);  

  printf("\nDigite a idade do usuário: \n");
  scanf(" %d", &age);
  
  printf("\nDigite o saldo atual do usuário: \n");
  scanf(" %f", &current_balance);

  user.id = users_qnty;
  strcpy(user.name, name);
  user.age = age;
  user.current_balance = current_balance;

  return user;
}

void main() {
  User *users = (User*)malloc(sizeof(User));
  int users_qnty = 0;
  int opt;

  while (opt <= 5 && opt >= 0) {
    printf("Selecione uma opção: \n[1] - Criar um novo usuário\n[2] - Criar multiplos novos usuários\n[3] - Buscar um usuário por ID\n[4] - Deletar um usu[ario por ID\n[5] - Transferência de saldo entre usuários\n[qualquer outra tecla] - Sair\n-> ");
    scanf(" %d", &opt);
    
    switch (opt) {
	case 1:
	  users[users_qnty] = new_user(users_qnty);
	  users_qnty++;
	  break;
	default:
	  for (int j = 0; j < users_qnty; j++) {
	    printf("\n");
	    printf("ID: %d\nNome: %s\nIdade: %d\nSaldo atual: %f\n", users[j].id, users[j].name, users[j].age, users[j].current_balance);  
	  };

	  break;
      }
  }

  for (int i = 0; i < users_qnty; i++) {
    users[i] = new_user(i);
  };

    
  return;
}


