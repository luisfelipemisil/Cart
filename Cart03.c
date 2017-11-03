#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define tamM 40
#define tamC 70

typedef struct{
	int linha,coluna,tama,dig;
	char tipo[3];
} dados;	

typedef struct{
	int x,y;
	char t;
} info;

void SalvaBitmap();
dados perguntaDadosPonto();
dados perguntaDados();
void mostraArq();
void tela();
void Circ();
void circulo ();
void retaInclRigUp();
void retaInclRigDown();
void retaInclLefDown();
void retaInclLefUp();
void retaHorDown();
void retaHorUp();
void retaVerDown(); 
void retaVerUp();
void imagem ();
char *Resalvar();
void mostraMatIma();
char *SalvaArquivo();
char *validaOpcao();
void opcoes();
int tioPita();
void mostraMatImaCopy();
void telacopy();
int testaArquivo();
void cart ();
void cursor();
char direcao();
int text();
info atalhos();
void layout();

int main () {
	FILE *arq;
	int i,txt[tamM] [tamM],l,h,j,k,tama,dig,ch,linY=tamM/2,colX=tamM/2;
	char trava='n',s,letra,ler[300],cir,sentido,*opcao,print[4],*nome,salva;
	info informacoes;
		cart();
		nome = SalvaArquivo(txt);
		while(trava=='n' || trava=='N'){
			informacoes=atalhos(txt,linY,colX,nome);			
			colX=informacoes.x;
			linY=informacoes.y;
			trava=informacoes.t;
	}
	/*	
	printf("Ver imagem? S|N :");
	scanf(" %c", &trava);
	if (trava=='s'||trava=='S'){
		imagem(nome);
	}
	system("pause");
	*/
	return 0;

}

int text(){
	char dig = 58;
	int textura;
	while(dig > 57){
		printf("Textura: ");
		dig=getch();
		while(dig < 49){
			dig=getch();
		}		
	}
	switch(dig){
		case 49:
			textura=176;
			break;
		case 50:
			textura=177;
			break;
		case 51:
			textura=178;
			break;
		case 52:
			textura=219;
			break;
		case 53:
			textura=255;
			break;
		case 54:
			textura=186;
			break;	
		default:
			break; 
	}

	return textura;
}
void cursor(int matriz[][tamM],int y, int x){
	int i,j,k,l,copy[40][tamC],p1,p2,p3,p4,ch;
	char ler[301],print[4];
	FILE *arq;
		arq=fopen("tela.txt","r");
		j=0;
		for(i=0;i<40;i++){
			fgets(ler,300, arq);
			l=0;
			for(k=0;ler[k]!='\n';k++){
				print[j] = ler[k];
				j++;
				if(j==3){
					ch= atoi(print);
					copy[i][l]=ch;
					j=0;
					l++;
				}
			}
		}
		fclose(arq);

	for(i=0;i<tamM;i++){
		for(j=0;j<tamM;j++){
			copy[i][j]=matriz[i][j];
		}
	}

	p1=y-1;
	p2=y+1;
	p3=x-1;
	p4=x+1;

	if(p1<tamM && p1 >=0){
		copy[p1][x] = 118;
	}
	else if(p2<tamM && p2 >=0){
		copy[p2][x] = 94;
	}
	if(p3 >=0){
		copy[y][p3] = 62;
	}
	else if(p4<tamM && p4 >=0){
		copy[y][p4] = 60;
	}
	
	telacopy(copy);

}
char *SalvaArquivo (int txt [] [tamM]){
	int i,j,k,l,ch;
	char s,*nome, copia[tamM],ler[300],print[4];
	nome=(char*) malloc(tamM*sizeof(char));
	strcpy(nome,"");
	FILE *arq;
	printf("Abrir arquivo? S|N : ");
	scanf(" %c", &s);
	if(s=='s' || s == 'S'){
		while(testaArquivo(copia)==0){
			printf("Arquivo: ");
			scanf(" %[^\n]", nome);
			strcpy(copia,nome);
			strcat(copia,".txt");
		}
		arq=fopen(copia,"r");
		j=0;
		for(i=0;i<tamM;i++){
			fgets(ler,200, arq);
			l=0;
			printf("\t\t");
			for(k=0;ler[k]!='\n';k++){
				print[j] = ler[k];
				j++;
				if(j==3){
					ch= atoi(print);
					txt [i] [l] = ch;
					printf("%c",ch);
					j=0;
					l++;
				}
			}
			printf("\n");
		}
		fclose(arq);
		system("pause");
	}
	else {
		printf("Criar novo arquivo? S|N : ");
		scanf(" %c", &s);
		if(s=='s' || s == 'S'){
			printf("Arquivo: ");
			scanf(" %[^\n]", nome);
			strcpy(copia,nome);
			strcat(copia,".txt");
			while(testaArquivo(copia)==1){
				printf("Arquivo jah existe.\n");
				printf("Arquivo: ");
				scanf(" %[^\n]", nome);
				strcpy(copia,nome);
				strcat(copia,".txt");
			}
			for(i=0;i<tamM;i++){
				for(j=0;j<tamM;j++){
					txt [i] [j] = 219;
				}
			}
		}

		for(i=0;i<tamM;i++){
				for(j=0;j<tamM;j++){
					txt [i] [j] = 219;
				}
			}
	}

	return nome;
}


int testaArquivo(char nome [30]){
	
	FILE *fp;
	fp=fopen(nome,"r");
	
	if(fp!=NULL){
    	fclose(fp);
    	return 1;
	}
	else{
    	return 0;
	}
}
char *Resalvar(int matriz[][tamM], char nome []){
	char salva;
	int i,j,k,t;
	FILE *arq;
	char s,cop[tamM],*copianome;

	printf("Salvar? S|N:");
	scanf(" %c", &salva);
	if(salva=='s'|| salva == 'S'){
		while(strlen(nome)==0){
			printf("Digite um nome:");
			scanf(" %s", nome);
		}	
			strcpy(cop,nome);
			strcat(cop,".txt");
		if(testaArquivo(cop)==0){
			arq=fopen(cop,"w");
			if(arq!=NULL){
				for(j=0;j<tamM;j++){	
					for(i=0;i<tamM;i++){
						fprintf(arq, "%d",matriz [j] [i]);
					}
					fprintf(arq,"\n");
				}
				fclose(arq);
			}
			else
				printf("Erro\n");
		}
		else{
			printf("Aquivo ja existe.\n");
			printf("Substituir? S|N : ");
			scanf(" %c", &s);
			if(s=='s' || s=='S'){
				arq=fopen(cop,"w");
				for(j=0;j<tamM;j++){	
					for(i=0;i<tamM;i++){
						fprintf(arq, "%d",matriz [j] [i]);
					}
					fprintf(arq,"\n");
				}
				fclose(arq);		
			}
			else{
				printf("Criar novo Arquivo? S|N : ");
				scanf("%s",&s);
				if(s=='s' || s=='S'){
					printf("Nome:");
					scanf(" %[^\n]", nome);
					strcpy(cop,nome);
					strcat(cop,".txt");
					while(testaArquivo(cop)==1){
						printf("Aquivo ja existe.\n");
						printf("Tente outro nome:" );
						scanf(" %[^\n]", cop);
						strcat(cop,".txt");
					}
					arq=fopen(cop,"w");
					for(j=0;j<tamM;j++){	
						for(i=0;i<tamM;i++){
							fprintf(arq, "%d",matriz [j] [i]);
						}
						fprintf(arq,"\n");
					}
					fclose(arq);		
				} 
			}	

		}
	}
	t=strlen(nome);
	copianome=(char*) malloc((t+1)*sizeof(char));
	strcpy(copianome,nome);

	return copianome;
}
void tela(char matriz[] [tamM]){
	system("cls");
	//layout();
	mostraMatIma(matriz);
}
void telacopy(char matriz[40] [tamC]){
	system("cls");
	//layout();
	mostraMatImaCopy(matriz);
}
void pintar(){

}

void retaVerDown (int matriz [] [tamM], int linha, int coluna ,int tama , int dig) {
	int i;
	for (i=0;i<tama && (linha)+i < tamM ;i++){
		matriz[(linha)+i] [coluna] = dig;
	}
}
void retaVerUp (int matriz [] [tamM], int linha, int coluna ,int tama , int dig) {
	int i;
	for (i=0;i<tama && (linha)+i > 0 ;i++){
		matriz[(linha)-i] [coluna] = dig;
	}
}
void retaInclRigUp(int matriz [] [tamM], int linha, int coluna ,int tama , int dig){
	int i;
	for (i=0;i<tama && (linha)+i < tamM && (coluna)+i < tamM ;i++){
		matriz[(linha)-i] [(coluna)-i] = dig;
	}
}
void retaInclRigDown(int matriz [] [tamM], int linha, int coluna ,int tama , int dig){
	int i;
	for (i=0;i<tama && (linha)+i < tamM && (coluna)+i < tamM ;i++){
		matriz[(linha)+i] [(coluna)+i] = dig;
	}
}
void retaHorDown(int matriz [] [tamM], int linha, int coluna ,int tama , int dig){
	int i;
	for (i=0;i<tama && (coluna)+i < tamM ;i++){
		matriz[linha] [(coluna)-i] = dig;					
	}
}
void retaHorUp(int matriz [] [tamM], int linha, int coluna ,int tama , int dig){
	int i;
	for (i=0;i<tama && (coluna)+i < tamM ;i++){
		matriz[linha] [(coluna)+i] = dig;					
	}
}
void retaInclLefDown(int matriz [] [tamM], int linha, int coluna ,int tama , int dig){
	int i;
	for (i=0;i<tama && (linha)+i < tamM && (coluna)-i >= 0 ;i++){
		matriz[(linha)+i] [(coluna)-i] = dig;
	}
}
void retaInclLefUp(int matriz [] [tamM], int linha, int coluna ,int tama , int dig){
	int i;
	for (i=0;i<tama && (linha)+i < tamM && (coluna)-i >= 0 ;i++){
		matriz[(linha)-i] [(coluna)+i] = dig;
	}
}
void cart(){
	int j,i,k,letra,ch;
	char nome[30],cha[1],ler[201],print[4];
	FILE *arq, *trad;
	arq = fopen("cart.txt","r");
	if(arq!=NULL){
		//printf("\t\t");
		while(!feof(arq)){
			fgets(ler,200, arq);
			j=0;
			printf("\t\t");
			for( k = 0 ;!feof(arq) && ler[k] != '\n' ; k++){
				print[j] = ler[k];
				j++;
				if(j==3){
					ch= atoi(print);
					printf("%c",ch);
					j=0;		
				}
			}
			printf("\n");				
		}
		fclose(arq);
		printf("\t\tCriado por Luis Felipe Miranda da Silva\n");
		printf("\t\t30/10/2017\n\n");
	}
	else {
		printf("ERRO ao abrir o arquivo.\n");
	}
	//system("pause");
}
int tioPita(int x, int hipote){
	int y;
	y=pow(hipote,2)-pow(x,2);
	y=sqrt(y);
	return y;
} 
void quadrado(){
	int posi,tex,i,x,tama,j,k,l,tam;
	tam=tama/2;
	x+tam;
	x-tam;
	
}
void Circ(int matriz [] [tamM], int y , int x , int raio,int dig){
	//printf("%d %d\n",y,x );
	int posi,tex,i,j,k,l=1,px1,px2,px3,px4,py1,py2,py3,py4,px11,px21,px31,px41,py11,py21,py31,py41;

	for(i=0;i<raio;i++){
		posi=tioPita(i,raio);	
		
		px1=x+i;
		py1=y+posi;
		px11=x+posi;
		py11=y+i;	
		if(px1>=0 && px1 < tamM && py1>=0 && py1 <tamM){
			matriz[px1] [py1] = dig; 
		}
		if(px11>=0 && px11 < tamM && py11>=0 && py11 <tamM){ 
			matriz[px11] [py11] = dig;
		}
		px2=x-i;
		py2=y+posi;
		px21=x-posi;
		py21=y+i;
		if(px2>=0 && px2 <tamM && py2>=0 && py2 <tamM){
			matriz[px2] [py2] = dig; 
		}
		if(px21>=0 && px21 <tamM && py21>=0 && py21 <tamM){
			matriz[px21] [py21] = dig;
		}
		px3=x-i;
		py3=y-posi;
		px31=x-posi;
		py31=y-i;
		if(px3>=0 && px3 <tamM && py3>=0 && py3 <tamM){
			matriz[px3] [py3] = dig;
		}
		if(px31>=0 && px31<tamM && py31>=0 && py31 <tamM){
			matriz[px31] [py31] = dig;
		}
		px4=x+i;
		py4=y-posi;
		px41=x+posi;
		py41=y-i;
		if(px4>=0 && px4 < tamM && py4>=0 && py4 <tamM){
			matriz[px4] [py4] = dig;
		}
		if(px41>=0 && px41 < tamM && py41>=0 && py41 <tamM){
			matriz[px41] [py41] = dig;
		}
		//printf("px1 %d, px2 %d, px3 %d, px4 %d, py1 %d, py2 %d, py3 %d, py4 %d,\n", px1,px2,px3,px4,py1,py2,py3,py4);
		//printf("px11 %d, px21 %d, px31 %d, px41 %d, py11 %d, py21 %d, py31 %d, py41 %d \n",px11,px21,px31,px41,py11,py21,py31,py41);

	}
	//system("pause");
}
void mostraArq(char nome[tamM]){
	FILE *arq;
	int cont=0;
	char linha [200];
	arq=fopen(nome,"rt");
	if(arq!=NULL){
		while(!feof(arq)){
			fscanf(arq," %[^\n]", linha);
			printf("%c| %s\n",cont,linha);
			cont++;
		}
	}
	fclose(arq);
}

void mostraMatIma(int m [] [tamM], int linha){
	int i,j;
	printf("\t\t");
	for(i=0;i<tamM;i++){
		printf("\t\t");
		for(j=0;j<tamM;j++){
			printf("%c",m [i] [j]);
		}
		printf("\n");
		//txt [i] [j] = '\0';
	}
}
void mostraMatImaCopy(int m [40] [tamC]){
	int i,j;
	for(i=0;i<40;i++){
		for(j=0;j<tamC;j++){
			printf("%c",m [i] [j]);
		}
		printf("\n");
		//txt [i] [j] = '\0';
	}
}

void imagem ( char arquivo[tamM]) {

	int j,i,k,letra,ch;
	char nome[tamM],cha[1],ler[201],print[4];
	FILE *arq;
	arq = fopen(arquivo,"r");
	
	if(arq!=NULL){
		while(!feof(arq)){ // vai ate o final do arquivo
			fgets(ler,200, arq);
			j=0;
			for( k = 0 ;!feof(arq) && ler[k] != '\n' ; k++){		
				print[j] = ler[k];
				j++;
				if(j==3){
					ch= atoi(print);
					printf("%c",ch);
					j=0;
				}
			}
			printf("\n");				
		}
		fclose(arq);
	}
	else {
		printf("ERRO ao abrir o arquivo.\n");
	}
}

info atalhos(int txt [] [tamM], int linY, int colX,char nome [tamM]) {
			
	char letra,trava='n',*novoNome,sentido='l';
	int dig,tama;
	info dados;
			cursor(txt,linY,colX);

			letra=getch();
			//tela(txt);	
			if(letra=='s'){
				linY+=1;
				if(linY>=tamM){
					linY=tamM-1;
				}	
			}
			else if(letra=='w'){
				linY-=1;
				if(linY<=0){
					linY=0;
				}		
			}
			else if(letra=='a'){
				colX-=1;
				if(colX<=0){
					colX=0;  
				}		
			}
			else if(letra=='d'){
				colX+=1;
				if(colX>=tamM){
					colX=tamM-1;  
				}		
			}
			else if (letra=='1'){
				txt[linY][colX]=176;
			}
			else if (letra=='2'){
				txt[linY][colX]=177;
			}
			else if (letra=='3'){
				txt[linY][colX]=178;
			}
			else if (letra=='4'){
				txt[linY][colX]=219;
			}
			else if (letra=='5'){
				txt[linY][colX]=255;
			}
			else if (letra=='6'){
				txt[linY][colX]=186;
			}
			else if (letra=='c'){
				printf("Tamanho: ");
				scanf("%d", &tama);
				dig=text();
				Circ(txt,colX,linY,tama,dig);
			}
			else if (letra=='p'){
				novoNome = Resalvar(txt, nome);
				SalvaBitmap(txt, novoNome);				
			}
			else if (letra=='\\'){
				printf("Tamanho: ");
				scanf("%d", &tama);
				printf("Sentido + | - :");
				while (sentido == 'l'){
					scanf(" %c", &sentido);
				}
				if(sentido=='-'){
					dig=text();
					retaInclRigDown(txt,linY,colX,tama ,dig);		
				}
				else {
					dig=text();
					retaInclRigUp(txt,linY,colX,tama ,dig);		
				}
				sentido ='l';
			}
			else if (letra=='/'){
				printf("Tamanho: ");
				scanf("%d", &tama);
				printf("Sentido + | - :");
				while (sentido != '-' && sentido != '+'){
					scanf(" %c", &sentido);
				}
				if(sentido=='-'){
					dig=text();
					retaInclLefDown(txt,linY,colX,tama ,dig);		
				}
				else {
					dig=text();
					retaInclLefUp(txt,linY,colX,tama ,dig);		
				}
				sentido='l';
			}
			else if (letra=='-'){
				printf("Tamanho: ");
				scanf("%d", &tama);
				printf("Sentido + | - :");
				while (sentido != '-' && sentido != '+'){
					scanf(" %c", &sentido);
				}
				if(sentido=='-'){
					dig=text();
					retaHorDown(txt,linY,colX,tama ,dig);		
				}
				else {
					dig=text();
					retaHorUp(txt,linY,colX,tama ,dig);		
				}
				sentido='l';
			}
			else if (letra=='|'){
				printf("Tamanho: ");
				scanf("%d", &tama);
				printf("Sentido + | - :");
				while (sentido != '-' && sentido != '+'){
					scanf(" %c", &sentido);
				}
				if(sentido=='-'){
					dig=text();
					retaVerDown(txt,linY,colX,tama ,dig);		
				}
				else {
					dig=text();
					retaVerUp(txt,linY,colX,tama ,dig);		
				}
				sentido='l';
			}
			else if (letra=='e'){
				printf("Sair? S|N:");
				scanf(" %c", &trava);
				novoNome = Resalvar(txt, nome);
				SalvaBitmap(txt, novoNome);
			}
		
			dados.x=colX;
			dados.y=linY;
			dados.t=trava;

		return dados;

}
void SalvaBitmap(int matriz [] [tamM], char arquivNo []){
		FILE *arq;
		int j,k,l;
		char p,cop[tamM];
		int i [11]={0x42,0x4d,0xf6,0x12,0x00,0x36,0x28,0x1e,0x01,0x18,0xc0};
		int c176=0xe6,c177=0xb4,c178=0x78,c219=0xff,c255=0x00,c186=0xff;

		strcpy(cop,arquivNo);
		strcat(cop,".bmp");

		arq=fopen(cop, "w");
		if(arq!=NULL){
			for(k=0;k<4;k++){
				fprintf(arq,"%c",i[k]);
			}
			for(k=0;k<6;k++){
				fprintf(arq,"%c",i[4]);
			}	
			fprintf(arq,"%c",i[5]);
			for(k=0;k<3;k++){
				fprintf(arq,"%c",i[4]);
			}
			fprintf(arq,"%c",i[6]);	
			for(k=0;k<3;k++){
				fprintf(arq,"%c",i[4]);
			}
			fprintf(arq,"%c",i[6]);
			for(k=0;k<3;k++){
				fprintf(arq,"%c",i[4]);
			}
			fprintf(arq,"%c",i[6]);
			for(k=0;k<3;k++){
				fprintf(arq,"%c",i[4]);
			}
			fprintf(arq,"%c",i[8]);
			fprintf(arq,"%c",i[4]);
			fprintf(arq,"%c",i[9]);
			for(k=0;k<5;k++){
				fprintf(arq,"%c",i[4]);
			}
			fprintf(arq,"%c",i[10]);
			fprintf(arq,"%c",i[3]);
			for(k=0;k<=17;k++){
				fprintf(arq,"%c",i[4]);
			}
			for(l=tamM-1;l>=0;l--){
				for(j=0;j<tamM;j++){
					if(matriz[l] [j] == 176){
						fprintf(arq,"%c%c%c",c176,c176,c176);
					}
					else if(matriz[l] [j] == 177){
						fprintf(arq,"%c%c%c",c177,c177,c177);
					}
					else if(matriz[l] [j] == 178){
						fprintf(arq,"%c%c%c",c178,c178,c178);
					}
					else if(matriz[l] [j] == 219){
						fprintf(arq,"%c%c%c",c219,c219,c219);
					}
					else if(matriz[l] [j] == 255){
						fprintf(arq,"%c%c%c",c255,c255,c255);
					}
					else if(matriz[l] [j] == 186){
						fprintf(arq,"%c%c%c",0,0,c186);
					}
				}
			
			//fprintf(arq,"%c%c",0,0);
		}
		}
		fclose(arq);
		//rename("novo.bmp",nome);
}
/*

char *validaOpcao(){
	char *opcao = (char*) malloc(20*sizeof(char));

	while((strcmp(opcao,"reta")!=0) && (strcmp(opcao,"ponto")!=0) && (strcmp(opcao,"circulo")!=0)){
		printf("Opcoes: | reta | ponto | circulo | sair | Escreva o que deseja:");
		scanf(" %s", opcao);
		if ((strcmp(opcao,"sair")==0)){
			return NULL;
		}
		strlwr(opcao);
	}
	return opcao;
}

dados perguntaDados(){
	
	dados pergunta;

	printf("Inicio 2 posicoes:");
	scanf("%d %d",&pergunta.linha ,&pergunta.coluna);
	printf("Tamanho: ");
	scanf("%d",&pergunta.tama);
	printf("Tipo? \\+ \\- |+ |- /+ /- --+ --- oE oF:");
	scanf(" %s", pergunta.tipo);			
	printf(" %c176%c  %c177%c %c178%c %c219%c %c255%c\n",176,176,177,177,178,178,219,219,255,255);
	printf("Escolha testura: ");
	scanf("%d",&pergunta.dig);

	return pergunta;
}
dados perguntaDadosPonto(){
	
	dados pergunta;

	printf("Inicio 2 posicoes:");
	scanf("%d %d",&pergunta.linha ,&pergunta.coluna);
	printf(" %c176%c  %c177%c %c178%c %c219%c %c255%c\n",176,176,177,177,178,178,219,219,255,255);
	printf("Escolha testura: ");
	scanf("%d",&pergunta.dig);
	return pergunta;
}  
void opcoes( char txt [] [tamM] , char opcao[20]){
	dados pergunta;

	if(strcmp(opcao,"reta") == 0){
		pergunta=perguntaDados();
		if(strcmp(pergunta.tipo,"\\-")==0){
			retaInclRigDown(txt, pergunta.linha, pergunta.coluna ,pergunta.tama ,pergunta.dig);	
		}
		else if(strcmp(pergunta.tipo,"\\+")==0){
			retaInclRigUp(txt, pergunta.linha, pergunta.coluna ,pergunta.tama ,pergunta.dig);	
		}
		else if (strcmp(pergunta.tipo,"---")==0){
			retaHorDown(txt, pergunta.linha, pergunta.coluna ,pergunta.tama ,pergunta.dig);	
		}
		else if (strcmp(pergunta.tipo,"--+")==0){
			retaHorUp(txt, pergunta.linha, pergunta.coluna ,pergunta.tama ,pergunta.dig);	
		}
		else if (strcmp(pergunta.tipo,"/-")==0){
			retaInclLefDown(txt, pergunta.linha, pergunta.coluna ,pergunta.tama,pergunta.dig);
		}
		else if (strcmp(pergunta.tipo,"/+")==0){
			retaInclLefUp(txt, pergunta.linha, pergunta.coluna ,pergunta.tama ,pergunta.dig);
		}
		else if (strcmp(pergunta.tipo,"|-")==0){
			retaVerDown(txt, pergunta.linha, pergunta.coluna ,pergunta.tama,pergunta.dig);						
		}
		else if (strcmp(pergunta.tipo,"|+")==0){
			retaVerUp(txt, pergunta.linha, pergunta.coluna ,pergunta.tama,pergunta.dig);						
		}
		tela(txt);			
	}
	else if (strcmp(opcao,"circulo")==0){
			printf("Inicio 2 posicoes:");
			scanf("%d %d",&pergunta.linha ,&pergunta.coluna);
			printf("Raio: ");
			scanf("%d",&pergunta.tama);
			printf(" %c176%c  %c177%c %c178%c %c219%c %c255%c\n",176,176,177,177,178,178,219,219,255,255);
			scanf("%d",&pergunta.dig);
			Circ(txt, pergunta.linha, pergunta.coluna ,pergunta.tama,pergunta.dig);
			tela(txt);
		}
	else if (strcmp(opcao,"ponto")==0){	
		pergunta=perguntaDadosPonto();
		txt [pergunta.linha-1] [pergunta.coluna-1] = pergunta.dig;
		tela(txt);
	}
}



Primeira função de gerar circulo, não eficiente.

void circulo (int matriz [] [tamM], int linha, int coluna, int tama,int dig ){
	int i,j,li,ci, l4_30,c4_30,c1_30,l1_30,l6,c6,l9,c9,l7_30,c7_30,l10_30,c10_30,l12,c12,c3,l3;
																						 // nao pode ser maior que a hipotenusa;			
	if (linha < 1 || coluna < 1 || linha >= tamM || coluna >= tamM  || (tama < 0 || tama >= tamM )) {	
		printf("Erro <x.x> : tamanho invalido.\n");
	}
	else {

		l4_30=(linha-1)+(tama-1); // linha do ponteiro referente a 04:30
		c4_30=(coluna-1)+(tama-1);// coluna do ponteiro referente a 04:30 

		l6=(linha-1)+(tama+1);// linha do ponteiro referente ao 06:00
		c6=(coluna-1);// coluna do ponteiro referente a 06:00

		l9=(linha-1);// linha do ponteiro referente ao 09:00
		c9=(coluna-1)-(tama+1);// coluna do ponteiro referente a 09:00

		l7_30=(linha-1)+(tama-1);// linha do ponteiro referente ao 07:30
		c7_30=(coluna-1)-(tama-1);// coluna do ponteiro referente a 07:30

		l1_30=(linha-1)-(tama-1);// linha do ponteiro referente ao 01:30
		c1_30=(coluna-1)+(tama-1);// coluna do ponteiro referente a 01:30
		Criado por Luis Felipe 03-11-2017

		l12=(linha-1)-(tama+1);// linha do ponteiro referente ao 12:00
		c12=(coluna-1);// coluna do ponteiro referente a 12:00

		l3=(linha-1);// linha do ponteiro referente ao 03:00
		c3=(coluna-1)+(tama+1);// coluna do ponteiro referente a 03:00

		l10_30=(linha-1)-(tama-1); // linha do ponteiro referente ao 10:30
		c10_30=(coluna-1)-(tama-1);// coluna do ponteiro referente a 10:30

		if(tama>5){c1_30--;l1_30++;c4_30--;l4_30--;c7_30++;l7_30--;c10_30++;l10_30++;}
		if(tama>10){c1_30-=2;l1_30+=2;c4_30-=2;l4_30-=2;c7_30+=2;l7_30-=2;c10_30+=2;l10_30+=2;}

		if( l12 >= 0 && l12 < tamM && c12 >= 0 && c12 < tamM){
			matriz [  l12  ] [  c12  ] = dig; // |+  12:00/00:00h
		}

		if(l1_30>=0 && l1_30 < tamM && c1_30 >=0 && c1_30 < tamM){	
			matriz [ l1_30 ] [ c1_30 ] = dig; // /+  01:30h
		}

		if ( l3>=0 && l3 < tamM && c3 >=0 && c3 <= tamM){
			matriz [   l3  ] [   c3  ] = dig; // --+ 03:00h
		}

		if (l4_30>=0 && l4_30<tamM && c4_30 >=0 && c4_30 < tamM) {
			matriz [ l4_30 ] [ c4_30 ] = dig; // \ - 04:30h
		}

		if (l6 >=0 && l6 < tamM && c6 >= 0 && c6 < tamM){
			matriz [  l6   ] [   c6  ] = dig; // |-  06:00h
		}

		if (l7_30>=0 && l7_30 < tamM && c7_30 >= 0 && c7_30 < tamM) {
			matriz [ l7_30 ] [ c7_30 ] = dig; // /-  07:30h
		}

		if (l9 >=0 && l9 < tamM && c9 >=0 && c9 < tamM){
			matriz [  l9   ] [   c9  ] = dig; // -- -09:00h
		}

		if (l10_30>0 && l10_30 <tamM && c10_30 >=0 && c10_30 <tamM){	 
			matriz [ l10_30] [ c10_30] = dig; // \ + 10:30h
		}
		if(c10_30<tamM && l10_30>= 0){
			li=l12;
			while(li<0){
				li++;
			}
			i=1;
			while(c12-i>=tamM){
				i++;
			}	
			for(; c12-i != c10_30 && c12-i >= 0 && li < tamM ;i++){ // monta imagem de 12h ate 10:30;
				if(i%2==0){
					li++;
				}	
					matriz[li][c12-i] = dig;							
			}
		}
		if(c1_30>=0 && l1_30 >=0){
			li=l12;
			while(li<0){
				li++;
			}
			i=1;
			while(c12+i<0){
				i++;
			}	
			
			for(; c12+i != c1_30 && c12+i < tamM && li < tamM ;i++){ // monta imagem de 12h ate 01:30;
				if(i%2==0){
					li++;
				}	
					matriz[li][c12+i] = dig;							
			}
		}
        if(c7_30 <tamM && l7_30 < tamM){
			li=l6;
			while(li>=tamM){
				li--;
			}
			i=1;
			while(c6-i>=tamM){
				i++;
			}	
			for(; c6-i != c7_30 && c6-i >= 0 && li >= 0 ;i++){ // monta imagem de 6h ate 07:30;
				if(i%2==0){
					li--;
				}	
					matriz[li][c6-i] = dig;							
			}
		}
		if( c4_30 >=0 && l4_30 < tamM){
			li=l6;
			while(li>=tamM){
				li--;
			}
			i=1;
			while(c6+i<0){
				i++;
			}
			for(; c6+i != c4_30 && c6+i < tamM && li >= 0 ;i++){// monta imagem de 6h ate 4:30
				if(i%2==0){
					li--;
				}	
					matriz[li][c6+i] = dig;							
			}
		}
		if(l1_30<tamM && c1_30 < tamM){
			ci=c3;
			while(ci > tamM ){
				ci--;
			}
			i=1;
			while(l3-i >=tamM){
				i++;
			}
			for(; l3-i != l1_30 && l3-i >= 0 && ci >= 0 ;i++){// monta imagem de 3h ate 01:30;
				if(i%2==0){
					ci--;
				}	
					matriz[l3-i][ci] = dig;							
			}
		}
		if(l4_30>=0 && c4_30 <tamM){
			ci=c3;
			while(ci >= tamM ){
				ci--;
			}
			i=1;
			while(l3+i<0){
				i++;
			}		
			for(; l3+i != l4_30 && l3+i < tamM && ci >= 0 ;i++){// monta imagem de 3h ate 04:30;
				if(i%2==0){
					ci--;
				}	
					matriz[l3+i][ci] = dig;							
			}
		}
		if(l10_30<tamM && c10_30 >= 0){
			ci=c9;
			while(ci<0){
				ci++;
			}
			i=1;
			while(l9-i>=tamM){
				i++;
			}
			 
			for(; l9-i != l10_30 && l9-i >= 0 && ci < tamM ;i++){// monta imagem de 9h ate 10:30;
				if(i%2==0){
					ci++;
				}	
					matriz[l9-i][ci] = dig;							
			}
		}
		if(l7_30>=0 && c7_30 >=0){
			ci=c9;
			while(ci<0){
				ci++;
			}
			i=1;
			while(l9+i<0){
				i++;
			}
			
			for(i=1; l9+i != l7_30 && l9+i < tamM && ci < tamM ;i++){// monta imagem de 9h ate 07:30;
				if(i%2==0){
					ci++;
				}	
					matriz[l9+i][ci] = dig;							
			}	
		}
	}
}
*/

