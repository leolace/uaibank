#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int   id;
  char  name[101];
  int   age;
  float current_balance;
} User;

User new_user(int users_qnty) {
  char name[101];
  int age = 0;
  float current_balance = 0.0;
  User user;

  printf("\nDigite o nome do usuário: \n");
  scanf(" %100[^\n]", name);  

  printf("\nDigite a idade do usuário: \n");
  scanf(" %d", &age);
  
  printf("\nDigite o saldo atual do usuário: \nR$ ");
  scanf(" %f", &current_balance);

  user.id = users_qnty;
  strcpy(user.name, name);
  user.age = age;
  user.current_balance = current_balance;

  printf("\nUsuário %d adicionado com sucesso\n\n", user.id);

  return user;
}

void search_id(int id, User users[], int users_qnty) {
  int found = 0; 

  for (int i = 0; i < users_qnty; i++) {
    if (users[i].id == id) {
      printf("ID: %d\nNome: %s\nIdade: %d\nSaldo atual: %.2f\n", users[i].id, users[i].name, users[i].age, users[i].current_balance);
      found = 1;
      break; 
    }
  }

  if (!found) {
    printf("\nErro: Usuário %d não encontrado.\n", id);
  }
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
  //é pra printar os usuário que fizeram a troca?
  printf("Transferência entre usuários feita com sucesso!\n");
}

void remove_user(int id, User users[], int *users_qnty) {  //peguei o ponteiro para a quantidades de usuário já que quero modificar o original 
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

int main() {
  User users[100];
  int users_qnty = 0;
  int opt;
  
  do {
    printf("Selecione uma opção: \n[1] - Criar um novo usuário\n[2] - Criar multiplos novos usuários\n[3] - Buscar um usuário por ID\n[4] - Deletar um usuário por ID\n[5] - Transferência de saldo entre usuários\n[qualquer outra tecla] - Sair\n-> ");
    scanf(" %d", &opt);    

    switch (opt) {
      case 1:
        users[users_qnty] = new_user(users_qnty);
        users_qnty++;
        break;
      case 2: {
        int qnty;

        printf("Digite a quantidade de usuários: \n->");
        scanf("%d", &qnty);

        for (int i = qnty; i > 0; i--) {
          users[users_qnty] = new_user(users_qnty);
          users_qnty++;
        }

        printf("Operação concluída. %d usuários adicionados\n\n", qnty);
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
    printf("\n");
    printf("ID: %d\nNome: %s\nIdade: %d\nSaldo atual: %.2f\n\n", users[j].id, users[j].name, users[j].age, users[j].current_balance);  
  };

  return 0;
}

