#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
void password_generator(char * password_space);




int main(int argc, char const *argv[])
{
	struct usuario
	{
		char nome[10];
		char password[9];
		struct usuario* next;
	};

	struct usuario adm;
	strcpy(adm.nome, "Rodrigo");
	password_generator(adm.password);
	adm.next = NULL;
	struct  usuario** ponteiro = &adm.next;
	while(1){
		char current_nome[8];
		char current_password[9];
		printf("------------SISTEMA DE CADASTRO-------------");
		scanf("%s", &current_nome);
		if(current_nome[0] == 's'){
			break;
		}
		password_generator(current_password);
		printf("Testing \n");

		while(1){

			if(*ponteiro == NULL){
				printf("%s \n", current_nome);
				*ponteiro = malloc(sizeof(struct usuario));
				strcpy((*ponteiro)->nome, current_nome );

				printf("_------------------------------Teste------------------------ \n");
				printf("Entrou \n ");
				printf("%s", current_nome);
				printf("%s \n", ( *ponteiro)->password);

				printf("_--------------------------------------------------------- \n");
				strcpy((*ponteiro)->password, current_password);
				(*ponteiro)->next = NULL;
				printf("criado");

				ponteiro = &((*ponteiro)->next);
				break;
			}
			else{

			}

		}

	}

	struct  usuario** ponteiro2 = &adm.next;

	while(1){

		if(*ponteiro2 == NULL){
				break;
			}
			else{
				printf("_--------------------------------------------------------- \n");
				printf("Entrou");
				printf("%s \n", (*ponteiro2)->nome);
				printf("%s \n", (*ponteiro2)->nome);

				printf("_--------------------------------------------------------- \n");
				ponteiro2 = &((*ponteiro2)->next);
			}

	}
	return 0;



 }



void password_generator(char * password_space){
	srand(time(0));
	int number_char = 9;
	char new_char[9];

	printf("%d \n", number_char);
	for(int i=0; i<number_char; i++){
		new_char[i] = (char) rand()%127+1;
		while ( 1){
			if(new_char[i]>=48 && new_char[i] <=57){
				break;
			}
			else if(new_char[i]>=65 && new_char[i] <=90){
				break;
			}

			new_char[i] = (char) rand()%127+1;
		}
	}
	strcpy(password_space, new_char);
}
