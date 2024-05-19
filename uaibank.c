#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int   id;
  char  name[101];
  int   age;
  float current_balance;
} User;

User* new_user(int users_qnty) {
  char name[101];
  int age = 0;
  float current_balance = 0.0;
  User *user = (User*)malloc(sizeof(User));

  if (user == NULL) {
    printf("Error: memory allocation for user failed");
    return NULL;
  }

  printf("\nDigite o nome do usuário: \n");
  scanf(" %100[^\n]", name);  

  printf("\nDigite a idade do usuário: \n");
  scanf(" %d", &age);
  
  printf("\nDigite o saldo atual do usuário: \nR$ ");
  scanf(" %f", &current_balance);

  user->id = users_qnty;
  strcpy(user->name, name);
  user->age = age;
  user->current_balance = current_balance;

  printf("\nUsuário %d adicionado com sucesso\n\n", user->id);

  return user;
}

int search_id(int id, User users[], int users_qnty) {
  for (int i = 0; i < users_qnty; i++) {
    if (users[i].id == id) {
      printf("ID: %d\nNome: %s\nIdade: %d\nSaldo atual: %.2f\n", users[i].id, users[i].name, users[i].age, users[i].current_balance);
      return i;
    }
  }


  printf("\nErro: Usuário %d não encontrado.\n", id);
  return -1;

}

void transfer_money(int id_origin, int id_destination, User users[], int users_qnty, float amount) {
  for (int i = 0; i < users_qnty; i++) {
    if (users[i].id == id_origin) {
      users[i].current_balance -= amount;
    }
    if (users[i].id == id_destination) {
      users[i].current_balance += amount;
    }
  }

  printf("Transferência entre usuários feita com sucesso!\n");
}

void remove_user(int id, User users[], int *users_qnty) { 
  int found = 0;
  for (int i = 0; i < *users_qnty; i++) {
    if (users[i].id == id) {
      found = 1;
      for (int j = i; j < *users_qnty - 1; j++) {
	users[j] = users[j + 1];
      }
      (*users_qnty)--;
      printf("Usuário  %d removido com sucesso.\n", id);
      break;
    }
  }
  if (!found) {
    printf("Erro: Usuário  %d não encontrado.\n", id);
  }
}

const int MAX_USERS_SIZE = 20;

int main() {
  int users_qnty = 1;
  User *users = malloc(MAX_USERS_SIZE * sizeof(User));
  int opt;

  if (users == NULL) {
    printf("Error: memory allocation for users failed");
    return 1;
  }
  
  do {
    printf("Selecione uma opção: \n[1] - Criar um novo usuário\n[2] - Criar multiplos novos usuários\n[3] - Buscar um usuário por ID\n[4] - Deletar um usuário por ID\n[5] - Transferência de saldo entre usuários\n[qualquer outra tecla] - Sair\n-> ");
    scanf(" %d", &opt);    

    switch (opt) {
    case 1:
      User *user = new_user(users_qnty);
      
      if(user == NULL) {
	free(users);
	printf("Error: memory allocation for user failed");
	return 1;
      }
      
      memcpy(&users[users_qnty], user, sizeof(User));
      free(user);
      
      users_qnty++;
      break;
    case 2: {
      int users_qnty_in_row = 0;

      printf("Digite a quantidade de usuários: \n->");
      scanf("%d", &users_qnty_in_row);

      for (int i = users_qnty_in_row; i > 0; i--) {
	User *user = new_user(users_qnty);

	      
	if(user == NULL) {
	  free(users);
	  printf("Error: memory allocation for user failed");
	  return 1;
	}
      
	memcpy(&users[users_qnty], user, sizeof(User));
	free(user);
      
	users_qnty++;
      }

      printf("Operação concluída. %d usuários adicionados\n\n", users_qnty_in_row);
      break;
    }
    case 3: {
      int ind; // id do usuário
      printf("Digite o id do usuário que deseja buscar: ");
      scanf("%d", &ind);
      search_id(ind, users, users_qnty);
      break;
    }
    case 4: {
      int id_origin, id_destination;
      float amount;
      printf("Digite o id de origem, id de destino e a quantia que deseja transferir:\n");
      scanf("%d %d %f", &id_origin, &id_destination, &amount);
      transfer_money(id_origin, id_destination,users,users_qnty, amount);
      break;
      //ver duvida sobre printar ou n
    }
    case 5:{
      int id_remove;
      printf("Digite o ID do usuário que deseja remover: ");
      scanf("%d", &id_remove);
      remove_user(id_remove, users, &users_qnty);
      break;

    }

    default:
      break;
    }

  } while (opt <= 5 && opt > 0);

  for (int j = 0; j < users_qnty; j++) {
    if (users[j].id != 0) {
      printf("\n");
      printf("ID: %d\nNome: %s\nIdade: %d\nSaldo atual: %.2f\n\n", users[j].id, users[j].name, users[j].age, users[j].current_balance);  
    }
  };

  free(users);

  return 0;
}

