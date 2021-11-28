#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*Grupo 11
Gabriela Rocha da Silva - RA 211152
M�rcio Soares de Oliveira Filho - RA 210498
Mateus Martins Freitas - RA 200026
Tamiris Tavares Lemes - RA 210216*/

//struct e union concession�ria
typedef struct endereco { 
 char logradouro[80]; 
 char bairro[15]; 
 char CEP[10]; 
 char cidade[15]; 
 char estado[3]; 
 char fone[12]; 
 char email[40]; 
}endereco; 
 
 
typedef struct infocarro { 
 char sigla; 
 int regcarro; 
}infocarro; 
 
 
typedef union dadoscarro { 
 char sigla; 
 struct infocarro reservado; 
}dadoscarro; 
 
 
typedef struct loja { 
 int regloja; //gerar autom�tico 
 char nome[30]; 
 char CNPJ[19]; 
 struct endereco end; 
 int sold; 
 int reserved; 
 union  dadoscarro  tabela[3]; 
}loja;

//structs union carros
typedef struct infoloja { 
 char sigla; 
 char CNPJ[19]; 
}infoloja; 
 
typedef union dadosloja { 
 char sigla; 
 struct infoloja reserva; 
}dadosloja; 
 
typedef struct montadora { 
 int regcarro; //gerar autom�tico 
 char modelo[20]; 
 char cor[10]; 
 float  valor; 
 union dadosloja status; 
}montadora;  

//fun��es da concession�ria
void alocaLoja(loja **p, int tam);
int verifica();
void grava(loja *p);
void cadastroConcessionaria(loja *p, int qtde);
void mostratotal(loja *p, int qtde);
char verificacnpj(loja *p, char *pcon);


//fun��es dos carros
void alocaCar(montadora **p, int tam);
int verificaCar();
void gravaCar(montadora *p);
void cadastroCar(montadora *p, int qtde);
void mostraCar(montadora *p, int qtde);
char consultaTotal(montadora *p, int qtde);
char consultaPs(montadora *p, int qtde, char status);
char consultaPm(montadora *p, char *pm);

//fun��es de reserva
char carrosD(montadora *p);
int verificacnpjCar(loja *p, char *pcon);
void reservarVeic(loja *p, montadora *pm, int nreg, char *pcon);
int verificaVeic(montadora *p,int reg);

void grava2(loja *p, char *str, int pos);
void gravaCar2(montadora *p, char *str, int pos);

int main(){	

setlocale(LC_ALL, "portuguese");
loja *pl=NULL;
montadora *pm=NULL;
char *pmodelo=NULL;
char *pconsulta=NULL;
char op, opr, opconsult, consulta[19], modelo[20], status;
int opcao=0, opcao2=0, qtde, qtdeCar, nreg, vm, opParcial, opsim;
pconsulta=&consulta[19];
pmodelo=&modelo[20];
int j;

alocaLoja(&pl, 1);
alocaCar(&pm, 1);
qtde=verifica();
qtdeCar=verificaCar();


do{
system("cls");
printf("\nMenu:\n[1]Cadastro Concession�ria\n[2]Consulta Concession�ria\n[3]Cadastro de Carros\n[4]Consulta Carro\n[5]Reservar Carro\n[6]Sa�da\n\n");
scanf("%i", &opcao);
fflush(stdin);

switch (opcao){
	
	case 1:	    if(qtde>4){
				  system("cls");
				  printf("\nFoi atingido o n�mero m�ximo de cadastros!\n");
				  system("pause");
				  op='N';
			    }//limite max
			    else{
				do{
					cadastroConcessionaria(pl,qtde+1);
					qtde++;
					printf("\nDeseja continuar <S/N>: ");
					scanf("%c", &op);
					fflush(stdin);
					mostratotal(pl, qtde);
					if(qtde>4){
						system("cls");
				  		printf("\nFoi atingido o n�mero m�ximo de cadastros!\n");
				  		system("pause");
				  		op='N';
			        }//if			    	
			    }while(op!='n' && op!='N');
			    }//else
				break;
			
	case 2:     do{
					system("cls");
					printf("\nDigite o CNPJ da empresa para consultar: ");
					scanf("%s", pconsulta);
					fflush(stdin);
					verificacnpj(pl, pconsulta);
					printf("\n\nDeseja continuar <S/N>: ");
					scanf("%c", &op);
					fflush(stdin);	
				}while(op!='n' && op!='N');
				break;
				
	case 3:    if(qtdeCar>49){
					system("cls");
				  	printf("\nFoi atingido o n�mero m�ximo de cadastros!\n");
				  	system("pause");
				  	op='N';
			    }//carro limite
			    else{
				do{
				   	cadastroCar(pm, qtdeCar+1);
				   	qtdeCar++;
				   	printf("\nDeseja continuar <S/N>: ");		
	               	scanf("%c", &op);
	               	fflush(stdin);
	            	mostraCar(pm, qtdeCar);
	               if(qtdeCar>49){
	             	system("cls");
	             	printf("\nFoi atingido o n�mero m�ximo de cadastros!\n");
				  	system("pause");
				  	op='N';
				 	}//if	
	            }while(op!='n' && op!='N');
	            }//else
				break;
	
	case 4:   do{
				system("cls");
				printf("\tOp��o de Consulta:");
				printf("\n\n[1]Consulta Total\n[2]Consulta Parcial\n[3]Sa�da\n\n");
				scanf("%c",&opcao2);
				fflush(stdin);
				switch (opcao2){
					case '1':   system("cls");
					            printf("\tConsulta Total:\n");
								consultaTotal(pm, qtdeCar);
								system("pause");
								break;
					
					case '2':   do{		
								system("cls");
								printf("\tConsulta Parcial:");
								printf("\n[1]Status\n[2]Modelo\n");
								scanf("%i", &opParcial);
								fflush(stdin);
								if(opParcial==1){								
								do{
									
									printf("\n\nDigite o status procurado: [r - reservado] [l - livre] ");;
									scanf("%c",&opconsult);
									fflush(stdin);
									if(opconsult!='r' && opconsult!='l')
										printf("\nStatus procurado n�o encontrado, digite novamente\n");
								}while(opconsult!='r' && opconsult!='l');
								
								switch(opconsult){
									case 'r': system("cls");
											  printf("\tConsulta por status");
											  status='R';
											  consultaPs(pm,qtdeCar,status);
											  printf("\n\n");
											  system("pause");
											  break;
											  
									case 'l': system("cls");
											  printf("\tConsulta por status");
											  status='L';
											  consultaPs(pm,qtdeCar,status);
											  printf("\n\n");
											  system("pause");
											  break;
								}//switch
								}//if
								else if(opParcial==2){									
											  system("cls");
											  printf("\tConsulta por modelo");
											  printf("\n\nDigite o modelo procurado: ");
											  scanf("%s", pmodelo);
											  fflush(stdin);
											  consultaPm(pm, pmodelo);
											  printf("\n\n");
											  system("pause");
											  break;
								}//else
							}while(opParcial!=1 && opParcial!=2);
						    break;
						
				}//switch opcao
				
				}while(opcao2!='3');
				break;
				
	case 5:   do{
					system("cls");
					printf("\tReserva de ve�culo");
					printf("\n\nDigite o CNPJ da empresa: ");
					gets(pconsulta);
					fflush(stdin);
					if(verificacnpjCar(pl, pconsulta)==7){
					system("cls");
					printf("\tReserva de ve�culo");
					
					 	system("cls");
					 	printf("\nDeseja verificar os ve�culos livres? <S - 1/N - 2>:  ");
					 	scanf("%i", &opsim);
					 	fflush(stdin);
					 	if(opsim!=2){
					 	printf("\tVe�culos livres:");
					 	carrosD(pm);
					 	printf("\n\n");
					 	system("pause");
						}
					 	
					do{
						system("cls");
						printf("\tReserva de ve�culo");
						printf("\n\nN�mero de registro do ve�culo desejado: ");
						scanf("%i",&nreg);
						fflush(stdin);
					if(verificaVeic(pm,nreg)==1){
						system("cls");
						reservarVeic(pl,pm,nreg-1,pconsulta);
						printf("\tReserva de ve�culo");
						printf("\n\nVe�culo reservado com sucesso!\n\n");
						printf("Deseja continuar?<S/N>\n");
						scanf("%c",&op);
						fflush(stdin);
						vm=1;
					}//if
					else{
						system("cls");
						printf("\tReserva de ve�culo");
						printf("\n\nO ve�culo procurado n�o est� dispon�vel!\n");
						printf("Deseja continuar?<S/N>\n");
						scanf("%c",&op);
						fflush(stdin);
						system("pause");
					}//else
					}while(vm!=1);
					}//if verifica cnpj carro
					else if(verificacnpjCar(pl, pconsulta)==8){
						system("cls");
						printf("\tReserva de ve�culo");
						printf("\n\nEssa empresa j� registrou tr�s veiculos\n");
						system("pause");
					}//ja registrou o max
				    else{
						system("cls");
						printf("\tReserva de ve�culo");
						printf("\n\nEsse CNPJ n�o est� registrado no sistema!\n");
						printf("\nDeseja continuar?<S/N>\n");
						scanf("%c",&op);
						fflush(stdin);
					}//else
				}while(op!='n' && op!='N');
				break;
}//switch opcao
}while(opcao!=6);
return 0;
}//main


//fun��es concession�ria

void alocaLoja(loja **p, int tam){
	if((*p=(loja*)realloc(*p, tam*sizeof(loja)))==NULL)
		exit(1);
}//alocaLoja

int verifica(){
	long int cont=0;
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
		return cont;
	else{
		fseek(fptr,0,2);
		cont=ftell(fptr)/sizeof(loja);
		fclose(fptr);
		return cont;
	}//else
}//verifica

void grava(loja *p){
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin", "ab"))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{
		fwrite(p, sizeof(loja), 1, fptr);
	}
	fclose(fptr); 
}//grava

void cadastroConcessionaria(struct loja *p,int qtde){
	int i;
	system("cls");
	p->regloja=qtde;
	printf("\nRegistro: %i", p->regloja);
	printf("\nNome: ");
	gets(p->nome);
	fflush(stdin);
	printf("\nCNPJ: ");
	gets(p->CNPJ);
	fflush(stdin);
	printf("\n\nCadastro do Endere�o \n");
	printf("\nLogradouro: ");
	gets(p->end.logradouro);
	fflush(stdin);
	printf("\nBairro: ");
	gets(p->end.bairro);
	fflush(stdin);
	printf("\nCEP: ");
	gets(p->end.CEP);
	fflush(stdin);
	printf("\nCidade: ");
	gets(p->end.cidade);
	fflush(stdin);
	printf("\nEstado: ");
	gets(p->end.estado);
	for(i=0; i<2; i++){
		if(*(p->end.estado)>=97 && *(p->end.estado)<=122)
			*(p->end.estado)-=32;
	}//for maiuscula
	printf("\nFone: ");
	gets(p->end.fone);
	fflush(stdin);
	printf("\nEmail: ");
	gets(p->end.email);
	fflush(stdin);
	p->sold=0;
	p->reserved=0;
	p->tabela[0].sigla='L';
	p->tabela[1].sigla='L';
	p->tabela[2].sigla='L';
	grava(p);
}//cadastro

void mostratotal(loja *p, int qtde){
int i;
FILE *fptr=NULL;
system("cls");
if((fptr=fopen("concessionaria.bin", "rb"))==NULL)
  printf("\nErro ao abrir o arquivo");
else{
	for(i=0;i<qtde;i++){
	 	fseek(fptr,i*sizeof(loja),0);
	 	fread(p,sizeof(loja),1,fptr);
	 	printf("\nRegistro: %i\nNome: %s\nCNPJ: %s\nSold: %i\nTabela 0: %c\nTabela 1: %c\nTabela 2: %c\n\n",p->regloja,p->nome,p->CNPJ,p->sold,p->tabela[0].sigla,p->tabela[1].sigla,p->tabela[2].sigla);
	 }//for
	 fclose(fptr);
}//else
system("pause");
}//mostra

char verificacnpj(loja *p, char *pcon){
	int aux, i, a, nao=0, sim=0;
	FILE *fptr=NULL;
	aux=verifica();
	
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
		printf("\nErro");
		
	else{
		for(i=0; i<aux; i++){
			fseek(fptr, i*sizeof(loja),0);
			fread(p, sizeof(loja), 1, fptr);
			
			if(strcmp(p->CNPJ, pcon)==0){
				sim=1;
				printf("\n\tNome\t\tSold\t\tReserved\tTabela 0\tTabela 1\tTabela 2\n\t%s\t\t%i\t\t%i\t\t%c\t\t%c\t\t%c",p->nome,p->sold,p->reserved,p->tabela[0].sigla, p->tabela[1].sigla, p->tabela[2].sigla);
			}
			else{
				nao=1;
			}
		}//for
		
		if(nao==1 && sim!=1){
			printf("\nN�o h� registro dessa empresa.\n");
		}
		
		fclose(fptr);
	}//else
	
}//verificacnpj


//fun��es carro

void alocaCar(montadora **p,int tam){
	if((*p=(montadora*)realloc(*p, tam*sizeof(montadora)))==NULL)
		exit(1);
}//aloca_car

int verificaCar(){
	long int cont=0;
	FILE *fptr=NULL;

	if((fptr=fopen("carro.bin","rb"))==NULL)
		return cont;
	else{
  		fseek(fptr,0,2);
  		cont=ftell(fptr)/sizeof(montadora);
  		fclose(fptr);
  		return cont;
	}//else
}//verifica carro

void gravaCar(montadora *p){
FILE *fptr=NULL;
if((fptr=fopen("carro.bin","ab"))==NULL)
 printf("\nErro ao abrir o arquivo");
else
  fwrite(p,sizeof(montadora),1,fptr);
fclose(fptr);
}//grava carro

void cadastroCar(montadora *p, int qtde){
	system("cls");
	p->regcarro=qtde;
	printf("\nRegistro: %i", p->regcarro);
	printf("\nModelo: ");
	gets(p->modelo);
	fflush(stdin);
	printf("\nCor: ");
	gets(p->cor);
	fflush(stdin);
	printf("\nValor: ");
	scanf("%f",&(p->valor));
	fflush(stdin);
	p->status.sigla='L';
	gravaCar(p);
}//cadastroCar

void mostraCar(montadora *p, int qtde){
	
	int i;
	FILE *fptr=NULL;
	system("cls");
	if((fptr=fopen("carro.bin", "rb"))==NULL)
  	printf("\nErro ao abrir o arquivo");
	else{
	for(i=0;i<qtde;i++){
	 	fseek(fptr,i*sizeof(montadora),0);
	 	fread(p,sizeof(montadora),1,fptr);
	 	printf("\nRegistro: %i\nModelo: %s\nCor: %s\nValor: %.2f\nStatus: %c\n\n",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
	 }//for
	 fclose(fptr);
	}//else
	system("pause");
	
}//mostraCar

char consultaTotal(montadora *p, int qtde){
	FILE *fptr=NULL;
	int i;
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<qtde;i++){
 	 		fseek(fptr,i*sizeof(montadora),0);
  	 		fread(p,sizeof(montadora),1,fptr);
  	 		printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
		}//for
	printf("\n\n");
   	fclose(fptr);;
  }//else
}//consulta total

char consultaPs(montadora *p,int qtde,char status){
	FILE *fptr=NULL;
	int i;
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<qtde;i++){
  			fseek(fptr,i*sizeof(montadora),0);
  	 		fread(p,sizeof(montadora),1,fptr);
  			if(p->status.sigla==status)
  		 		printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);	
  		}//for
	fclose(fptr);
  }//else
}//consulta p status

char consultaPm(montadora *p, char *pmo){
	FILE *fptr=NULL;
	int i,aux, sim=0, nao=0;
	aux=verificaCar();
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		
  		for(i=0;i<aux;i++){
  			
  			fseek(fptr, i*sizeof(montadora),0);
			fread(p, sizeof(montadora), 1, fptr);
			
			if(strcmp(p->modelo, pmo)==0){
				sim=1;
				printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
				printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);
			}
			else{
				nao=1;
			}
		}//for
		
		if(nao==1 && sim!=1){
			printf("\nN�o h� registro dessa empresa.\n");
		}
		
		fclose(fptr);
  		
  }//else
}//consulta p modelo

//fun��es de reserva

char carrosD(montadora *p){
	FILE *fptr=NULL;
	int i,aux;
	aux=verificaCar();

	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		printf("\n\tRegistro\tModelo\t\tCor\t\tValor\t\tStatus");
  		for(i=0;i<aux;i++){
  			fseek(fptr,i*sizeof(struct montadora),0);
  	 		fread(p,sizeof(struct montadora),1,fptr);
  	 		if(p->status.sigla=='L')
  	  			printf("\n\t%i\t\t%s\t\t%s\t\t%.2f\t\t%c",p->regcarro,p->modelo,p->cor,p->valor,p->status.sigla);	
    	}//for
	fclose(fptr);
  }//else
}//carros disponiveis

int verificacnpjCar(loja *p, char *pcon){
	int aux,i;
	FILE *fptr=NULL;
	aux=verifica();

	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
		printf("\nErro");
	
	else{
  		for(i=0;i<aux;i++){
  			fseek(fptr,i*sizeof(struct loja),0);
  			fread(p,sizeof(struct loja),1,fptr);
  			
  			if(strcmp(p->CNPJ, pcon)==0){
  				if(p->reserved>=3){
  					return 8;   //nao pode executar
				}
				else
					return 7;
			}//if
		}//for
	fclose(fptr);
  }//else	
}//verifica cnpj carro

void reservarVeic(loja *p, montadora *pm, int nreg, char *pcon){
	FILE *fptr=NULL;
	int i, aux, pos;
	aux=verifica();
	
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
		printf("\nErro");
	else{
		
		for(i=0;i<aux;i++){
			
			fseek(fptr,i*sizeof(struct loja),0);
  			fread(p,sizeof(struct loja),1,fptr);
  			
  			if(strcmp(p->CNPJ, pcon)==0){
  				pos=i;
  				p->reserved+=1;
  				if(p->reserved<=1){
  					if(p->tabela[0].reservado.sigla=='L'){
  						p->tabela[0].reservado.sigla='R';
  						p->tabela[0].reservado.regcarro=nreg;
					}
				}
  				else if(p->reserved<=2){
  					if(p->tabela[1].reservado.sigla=='L'){
  						p->tabela[1].reservado.sigla='R';
  						p->tabela[1].reservado.regcarro=nreg;
					}
				}
				else if(p->reserved<=3){
  					if(p->tabela[2].reservado.sigla=='L'){
  						p->tabela[2].reservado.sigla='R';
  						p->tabela[2].reservado.regcarro=nreg;
					}
				}
			}//if
			fclose(fptr);
		}//else	


	FILE *fptr2=NULL;
	if((fptr2=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
 		
		pm->status.sigla='R';
  		pm->status.reserva.CNPJ[19]=*pcon;
  		fclose(fptr2);
    }//else	
    grava2(p, "rb+", pos);
    gravaCar2(pm, "rb+", nreg);
}//reservar veiculo
}
int verificaVeic(montadora *p,int reg){
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin","rb"))==NULL)
		printf("\nErro");
	else{
  		fseek(fptr,(reg-1)*sizeof(struct montadora),0);
  		fread(p,sizeof(struct montadora),1,fptr);
  		if(p->status.sigla=='L')
  			return 1;	
  		else
  			return 0;
	fclose(fptr);
}//else
}//verifica veiculo

void grava2(loja *p, char *str, int pos){
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin", str))==NULL)
		printf("\nErro ao abrir o arquivo");
	else{
		if(strcmp(str,"rb+")==0)  //compara string
			fseek(fptr, pos*sizeof(loja), 0);
			fwrite(p,sizeof(loja),1,fptr);
	}//else
	fclose(fptr);
}//grava


void gravaCar2(montadora *p, char *str, int pos){
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin", str))==NULL)
		printf("\nErro ao abrir o arquivo");
	else{
		if(strcmp(str,"rb+")==0)  //compara string
			fseek(fptr, pos*sizeof(montadora), 0);
			fwrite(p,sizeof(montadora),1,fptr);
	}//else		
fclose(fptr);
}//grava car











