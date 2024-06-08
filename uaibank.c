#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct {
  int   id;
  char  *name;
  int   age;
  float current_balance;
} User;

void write_users_to_file(User *users, int users_qnty) {
  FILE *file = fopen("file.txt", "w");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  for (int i = 0; i < users_qnty; i++) {
    User user = users[i];
    fprintf(file, "%d, %s, %d, %.2f\n", user.id, user.name, user.age, user.current_balance);
  }

  fclose(file);
}

int random_number() {
  srand(time(NULL));
  int random_number = rand() % 1000 + 1;

  return random_number;
}

User* parse_user_line(char *line) {
  User *user = (User*)(malloc(sizeof(User)));
    
  char *id = (char*)(malloc(strlen(line) + 1));
  char *name = (char*)(malloc(101));
  char *age = (char*)(malloc(4));
  char *current_balance = (char*)(malloc(strlen(line) + 1));
  
  user->id = 0;
  strcpy(name, "");
  user->age = 0;
  user->current_balance = 0.0;
  
  int count = 0;
  int size = 0;
  
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] == ',' && line[i + 1] == ' ') {
      count++;
      i += 2;
    }

    switch (count) {
    case 0:
      id[i] = line[i];
      id[i + 1] = '\0';
      break;
    case 1:
      name[i - strlen(id) - 2] = line[i];
      name[i - strlen(id) - 1] = '\0';
      break;
    case 2:
      age[i - strlen(id) - strlen(name) - 4] = line[i];
      age[i - strlen(id) - strlen(name) - 3] = '\0';
      break;
    case 3:
      current_balance[i - strlen(id) - strlen(name) - strlen(age) - 6] = line[i];
      current_balance[i - strlen(id) - strlen(name) - strlen(age) - 5] = '\0';
      break;
    default:
      break;
    };
  }

  user->id = atoi(id);
  user->name = (char*)(malloc(101 * sizeof(char)));
  snprintf(user->name, 101 * sizeof(char), name);
  user->age = atoi(age);
  user->current_balance = atof(current_balance);
  
  free(name);
  free(age);
  free(current_balance);
  free(id);

  return user;
}

int parse_users(User **users) {
  char line[256];
  int index = 0;
  User *tempUsers = NULL;
  FILE *file = fopen("file.txt", "r");

  printf("Carregando banco de dados...\n");

  while(fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;
    if (line[0] == '\0') {
      continue;
    }
    
    User *user = parse_user_line(line);
    tempUsers = (User*)(realloc(*users, sizeof(User) * (index + 1)));

    *users = tempUsers;

    memcpy(&(*users)[index], user, sizeof(User));
    free(user);
    index++;
  }

  printf("[%d usuários carregados!]\n", index);
  fclose(file);

  return index;
}

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
    scanf(" %[^\n]%*c", name);

    if (strlen(name) > 100) {
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

  user->id = random_number();
  user->name = (char*)malloc(101 * sizeof(char));
  snprintf(user->name, 101 * sizeof(char), name);
  user->age = age;
  user->current_balance = current_balance;

  printf("\nUsuário %d adicionado com sucesso\n", user->id);

  return user;
}

int search_index_by_id(int id, User users[], int users_qnty) {
  for (int i = 0; i < users_qnty; i++) {
    if (users[i].id == id) {
      return i;
    }
  }

  return -1;
}

void transfer_money(int id_origin, int id_destination, User users[], int users_qnty, float amount) {
  int user_origin_index = search_index_by_id(id_origin, users, users_qnty);
  int user_destination_index = search_index_by_id(id_destination, users, users_qnty);
  
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

void remove_user(int searching_id, User **users, int *users_qnty) {
  int user_index = search_index_by_id(searching_id, *users, *users_qnty);

  if (user_index == -1) {
    printf("Erro: Usuário  %d não encontrado.\n", searching_id);
    return;
  }
  
  for (int j = user_index; j < *users_qnty - 1; j++) {
    (*users)[j] = (*users)[j + 1];
  }
  
  (*users_qnty) -= 1;

  User *new_users = realloc(*users, sizeof(User) * (*users_qnty));
  if (new_users == NULL && *users_qnty > 0) {
    printf("Erro ao realocar memória.\n");
    return;
  }
  *users = new_users;

  printf("Usuario %d deletado com sucesso\n", searching_id);
}

int main() {
  setlocale(LC_ALL, "Portuguese_Brasil.1252");
  
  User *users = (User*) malloc(sizeof(User));
  int added_users = parse_users(&users);

  if (users == NULL) {
    printf("Error: memory allocation for users failed");
    return 1;
  }
  
  char opt;
  int users_qnty = added_users;

  printf("############ BEM-VIND@ AO UAIBANK! ############\n");
  
  do {
    printf("\nSelecione uma opção: \n[1] - Criar um novo usuário\n[2] - Criar multiplos novos usuários\n[3] - Buscar um usuário por ID\n[4] - Transferência de saldo entre usuários\n[5] - Deletar um usuário por ID\n[qualquer outra tecla] - Sair\n-> ");
    scanf(" %c", &opt);    

    switch (opt) {
    case '1':
      printf("\n------- CRIAR NOVO USUARIO -------\n");
      users = (User*) realloc(users, sizeof(User) * (users_qnty + 1));
      User *user = new_user(users_qnty);
      
      if(user == NULL) {
	free(users);
	printf("Error: memory allocation for user failed");
	break;
      }

      users[users_qnty] = *user;
      
      write_users_to_file(users, users_qnty);
	  
      free(user);
      users_qnty++;
      break;
    case '2':
      printf("\n------- CRIAR MULTIPLOS USUARIOS -------\n");
      int users_qnty_in_row = 0;

      printf("Digite a quantidade de usuários: \n-> ");
      scanf("%d", &users_qnty_in_row);

      for (int i = users_qnty_in_row; i > 0; i--) {
	users = (User*) realloc(users, sizeof(User) * (users_qnty + 1));
	User *user = new_user(users_qnty);
	      
	if(user == NULL) {
	  free(users);
	  printf("Error: memory allocation for user failed");
	  break;
	}
	
	users[users_qnty] = *user;
	
	write_users_to_file(users, users_qnty);
	
	free(user);
	users_qnty++;
      }

      printf("Operação concluída. %d usuários adicionados\n", users_qnty_in_row);
      break;
    case '3':
      printf("\n------- PROCURAR USUARIO -------\n");
      int id;
      printf("Digite o id do usuário que deseja buscar:\n-> ");
      scanf("%d", &id);
      
      int user_id = search_index_by_id(id, users, users_qnty);

      if (user_id == -1) {
	printf("Erro: Usuário %d não encontrado.\n", id);
	break;
      }
      
      User user_found = users[user_id];
      
      printf("\nID: %03d\nNome: %s\nIdade: %d\nSaldo atual: R$ %.2f\n", user_found.id, user_found.name, user_found.age, user_found.current_balance);
      break;
    case '4':
      printf("\n------- TRANSFERENCIA -------\n");
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
    case '5': {
      printf("\n------- DELETAR USUARIO -------\n");
      int id;
      printf("Digite o ID do usuário que deseja remover:\n-> ");
      scanf("%d", &id);
      
      remove_user(id, &users, &users_qnty);
      write_users_to_file(users, users_qnty);
      break;
    }
    default:
      break;
    }
  } while (atoi(&opt) <= 5 && atoi(&opt) > 0);

  write_users_to_file(users, users_qnty);
  printf("Dados gravados com sucesso em file.txt\n\n");

  free(users);
  return 0;
}

