#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
  int   id;
  char  *name;
  int   age;
  float current_balance;
} User;

User* new_user(int users_qnty) {
  char *name = (char*)malloc(101 * sizeof(char));
  int age = 0;
  float current_balance = 0.0;
  User *user = (User*)malloc(sizeof(User));

  if (user == NULL || name == NULL) {
    printf("Error: memory allocation for user failed");
    free(name);
    return NULL;
  }

  do {
    printf("Digite o nome do usuário: \n-> ");
    scanf(" %s", name);
        
    if (strlen(name) + 1 > 100) {
      printf("O nome deve ter menos que 100 caracteres. Tente novamente.\n ");
    }
  } while (strlen(name) + 1 > 100);

  printf("Digite a idade do usuário: \n-> ");
  scanf(" %d", &age);

  while (age < 0) {  
    printf("Digite a idade do usuário: \n-> ");
    scanf(" %d", &age);
  
    printf("A idade deve ser maior de zero.\n");
  }
  
  printf("Digite o saldo atual do usuário: \n-> R$ ");
  scanf(" %f", &current_balance);

  while (current_balance < 0) {
    printf("Saldo deve ser maior ou igual a zero.\n");
      
    printf("Digite o saldo atual do usuário: \n-> R$ ");
    scanf(" %f", &current_balance);
  }

  user->id = users_qnty;
  user->name = (char*)malloc(101 * sizeof(char));
  snprintf(user->name, 101 * sizeof(char), name);
  user->age = age;
  user->current_balance = current_balance;

  printf("\nUsuário %03d adicionado com sucesso\n", user->id);

  return user;
}

int search_id(int id, User users[], int users_qnty) {
  for (int i = 0; i < users_qnty; i++) {
    if (users[i].id == id) {
      return i;
    }
  }

  return -1;
}

void transfer_money(int id_origin, int id_destination, User users[], int users_qnty, float amount) {
  int user_origin_index = search_id(id_origin, users, users_qnty);
  int user_destination_index = search_id(id_destination, users, users_qnty);
  
  if(user_origin_index == -1 || user_destination_index == -1){
    printf("Algum dos usuários não foi encontrado.\n");
    return;
  } else if (users[user_origin_index].current_balance - amount < 0) {
    printf("Saldo insuficiente.\n");
    return;
  };
  
  users[user_origin_index].current_balance -= amount;
  users[user_destination_index].current_balance += amount;

  printf("Transferência entre usuários feita com sucesso!\n");
  return;
}

void remove_user(int id, User users[], int *users_qnty) {
  int user_index = search_id(id, users, *users_qnty);

  if (user_index == -1) {
    printf("Erro: Usuário  %d não encontrado.\n", id);
    return;
  }
  
  for (int j = user_index; j < *users_qnty - 1; j++) {
    users[j] = users[j + 1];
  }
  
  printf("Usuário  %d removido com sucesso.\n", id);
}

const int MAX_USERS_SIZE = 20;

int main() {
  setlocale(LC_ALL, "Portuguese_Brasil.1252");
  
  int users_qnty = 0;
  User *users = malloc(sizeof(User));
  int opt;

  if (users == NULL) {
    printf("Error: memory allocation for users failed");
    return 1;
  }
  
  do {
    printf("\nSelecione uma opção: \n[1] - Criar um novo usuário\n[2] - Criar multiplos novos usuários\n[3] - Buscar um usuário por ID\n[4] - Transferência de saldo entre usuários\n[5] - Deletar um usuário por ID\n[qualquer outra tecla] - Sair\n-> ");
    scanf(" %d", &opt);    

    switch (opt) {
    case 1:
      realloc(users, sizeof(users) + 1);
      User *user = new_user(users_qnty);
      
      if(user == NULL) {
	free(users);
	printf("Error: memory allocation for user failed");
	break;
      }
      
      memcpy(&users[users_qnty], user, sizeof(User));
      free(user);

      users_qnty++;
      break;
    case 2: {
      int users_qnty_in_row = 0;

      printf("Digite a quantidade de usuários: \n-> ");
      scanf("%d", &users_qnty_in_row);

      for (int i = users_qnty_in_row; i > 0; i--) {
	realloc(users, sizeof(users) + 1);
	User *user = new_user(users_qnty);

	      
	if(user == NULL) {
	  free(users);
	  printf("Error: memory allocation for user failed");
	  break;
	}
      
	memcpy(&users[users_qnty], user, sizeof(User));
	free(user);
      
	users_qnty++;
      }

      printf("Operação concluída. %d usuários adicionados\n", users_qnty_in_row);
      break;
    }
    case 3: {
      int id;
      
      printf("Digite o id do usuário que deseja buscar:\n-> ");
      scanf("%03d", &id);
      
      int user_id = search_id(id, users, users_qnty);

      if (user_id == -1) {
	printf("Erro: Usuário %d não encontrado.\n", id);
	break;
      }
      
      User user_found = users[user_id];
      
      printf("\nID: %03d\nNome: %s\nIdade: %d\nSaldo atual: R$ %.2f\n", user_found.id, user_found.name, user_found.age, user_found.current_balance);
      break;
    }
    case 4: {
      int id_origin, id_destination;
      float amount = 0.0;
      
      printf("Digite o ID de origem\n-> ");
      scanf("%d", &id_origin);
      
      printf("Digite o ID de destino\n-> ");
      scanf("%d", &id_destination);

      if (id_origin < 0 || id_destination < 0) {
	printf("Digite um ID valido.\n");
        break;
      }
      
      printf("Digite a quantia que deseja transferir\n-> R$ ");
      scanf("%f", &amount);
      
      transfer_money(id_origin, id_destination, users, users_qnty, amount);
      
      break;
    }
    case 5:{
      int id;
      printf("Digite o ID do usuário que deseja remover:\n-> ");
      scanf("%d", &id);
      remove_user(id, users, &users_qnty);
      break;
    }

    default:
      break;
    }
  } while (opt <= 5 && opt > 0);

  FILE *file;
  file = fopen("file.txt", "w");

  for (int j = 1; j < users_qnty; j++) {
    printf("\n");
    printf("ID: %d\nNome: %s\nIdade: %d\nSaldo atual: %.2f\n\n", users[j].id, users[j].name, users[j].age, users[j].current_balance);
    fprintf(file, "%s, %d, %.2f\n", users[j].name, users[j].age, users[j].current_balance);
  };

  printf("Dados gravados com sucesso em file.txt\n\n");

  fclose(file);
  free(users);

  return 0;
}

