#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include<time.h>
#include<string.h>

const float FPS = 100;  
const int SCREEN_W = 960;
const int SCREEN_H = 540;
const float THETA = M_PI/4; 
const float R_C_F = 20;
const float VEL_TANK = 2.5;
const float PASSO_ANGULO = M_PI/90;
const float R_T = 5;




typedef struct ponto{
	float x;
	float y;
	} ponto;
	
typedef struct retangulo{
	
	ponto sup_esq;
	ponto inf_dir;	
	
}retangulo;

typedef struct tiro{
	ponto centro;
}tiro;

typedef struct tank{
	ponto centro;
	ponto A,B,C;
	ALLEGRO_COLOR cor;
	float angulo;
	float vel; 
	float x_comp, y_comp;
	float vel_angular;
	retangulo vida_bd;
	retangulo vida_pc;
	int menosvida;
	
}tank;


void initTank2(tank *t){
	t->centro.x = 900;
	t->centro.y = SCREEN_H/2;
	t->cor = al_map_rgb(rand()%256,rand()%256,rand()%256);
	
	t->A.x =0;
	t->A.y =-R_C_F;
	
	float alpha = M_PI/2 - THETA;
	float h = R_C_F * sin(alpha);
	float w = R_C_F * sin(THETA);
	
	t->B.x = -w;
	t->B.y = h;
	
	t->C.x= w;
	t->C.y= h;
	
	t->vel = 0;
	t->angulo = M_PI/2;
	t->x_comp = cos(t->angulo);
	t->y_comp =	sin(t->angulo);
	
	t->vel_angular =0;
	t->menosvida=0;
		
}

void initTank1(tank *t){
	t->centro.x = 60;
	t->centro.y = SCREEN_H/2;
	t->cor = al_map_rgb(rand()%256,rand()%256,rand()%256);
	
	t->A.x =0;
	t->A.y =-R_C_F;
	
	float alpha = M_PI/2 - THETA;
	float h = R_C_F * sin(alpha);
	float w = R_C_F * sin(THETA);
	
	t->B.x = -w;
	t->B.y = h;
	
	t->C.x= w;
	t->C.y= h;
	
	t->vel = 0;
	t->angulo = M_PI/2;
	t->x_comp = cos(t->angulo);
	t->y_comp =	sin(t->angulo);
	
	t->vel_angular =0;
	t->menosvida = 0;
	
}

void desenha_scenario(retangulo ret[],int u){
	int j = 0;
	al_clear_to_color(al_map_rgb(255,255,255));		
			
	for (j=0; j<u; j++){		
	al_draw_filled_rectangle(ret[j].sup_esq.x,ret[j].sup_esq.y, 
							ret[j].inf_dir.x, ret[j].inf_dir.y, 
							al_map_rgb(50,120,0)); }
		
	
}

void desenha_scenario2(){
	al_clear_to_color(al_map_rgb(255,255,255));
}

void Rotate(ponto *P, float Angle){
	float x=P->x, y=P->y;
	P->x=(x*cos(Angle))-(y*sin(Angle));
	P->y=(y*cos(Angle))+(x*sin(Angle));
	
}

void rotacionaTank(tank *t){
		
	if(t->vel_angular != 0){
		
		Rotate(&t->A, t->vel_angular);
		Rotate(&t->B, t->vel_angular);
		Rotate(&t->C, t->vel_angular);
	
	t->angulo+= t->vel_angular;	
	t->x_comp = cos(t->angulo);
	t->y_comp = sin(t->angulo);
	
	
	
	}
}

int colisaoTankcirculos(tank t1, tank t2){
	t1.centro.y += t1.vel*t1.y_comp;
	t1.centro.x += t1.vel*t1.x_comp;
	 
	 int normacirculos;
	 normacirculos = pow(t2.centro.x-t1.centro.x,2)+pow(t2.centro.y-t1.centro.y,2);
	 normacirculos = sqrt(normacirculos);
	 if (normacirculos>R_C_F*2){return 0;}
	 else return 1;	 
	 
 }

int colisaobordas(tank t){
	t.centro.y += t.vel*t.y_comp;
	t.centro.x += t.vel*t.x_comp;
	
	if (t.centro.x - R_C_F<0 || t.centro.x + R_C_F>SCREEN_W || t.centro.y - R_C_F<0 || t.centro.y + R_C_F>SCREEN_H){
		return 1;
	} 
	else return 0;}

int colisaoboradaMissel(float x, float y){	
	if (x - R_T<0 || x + R_T>SCREEN_W || y - R_T<0 || y + R_T>SCREEN_H){
		return 1;
	} 
	else return 0;}

int colisaoretangulos(tank t, retangulo ret[], int i){
int a =0, j=0;
float norma;
	t.centro.y += t.vel*t.y_comp;
	t.centro.x += t.vel*t.x_comp;
	for (j=0;j<i;j++){
	
	if (t.centro.x<=ret[j].sup_esq.x && t.centro.y>ret[j].sup_esq.y && t.centro.y<ret[j].inf_dir.y){
		if (abs(ret[j].sup_esq.x-t.centro.x)<R_C_F){a++;}}
	
	if (t.centro.x>=ret[j].inf_dir.x && t.centro.y>ret[j].sup_esq.y && t.centro.y<ret[j].inf_dir.y){
		if (abs(ret[j].inf_dir.x-t.centro.x)<R_C_F){a++;}}
		
	if (t.centro.y<=ret[j].sup_esq.y && t.centro.x>ret[j].sup_esq.x && t.centro.x<ret[j].inf_dir.x){
		if (abs(ret[j].sup_esq.y-t.centro.y)<R_C_F){a++;}}	
	
	if (t.centro.y>=ret[j].inf_dir.y && t.centro.x>ret[j].sup_esq.x && t.centro.x<ret[j].inf_dir.x){
		if (abs(ret[j].inf_dir.y-t.centro.y)<R_C_F){a++;}}	
		
			
	if(t.centro.x<=ret[j].sup_esq.x && t.centro.y<=ret[j].sup_esq.y){
    norma = pow((t.centro.x-ret[j].sup_esq.x),2)+pow((t.centro.y-ret[j].sup_esq.y),2);
    norma = sqrt(norma);
		if (norma<R_C_F){a++;}}
		
	 if(t.centro.x>=ret[j].inf_dir.x && t.centro.y<=ret[j].sup_esq.y){
    norma = pow((t.centro.x-ret[j].inf_dir.x),2)+pow((t.centro.y-ret[j].sup_esq.y),2);
    norma = sqrt(norma);
		if (norma<R_C_F){a++;}}
		
	 if(t.centro.x<=ret[j].sup_esq.x && t.centro.y>=ret[j].inf_dir.y){
    norma = pow((t.centro.x-ret[j].sup_esq.x),2)+pow((t.centro.y-ret[j].inf_dir.y),2);
    norma = sqrt(norma);
		if (norma<R_C_F){a++;}}	
		
	 if(t.centro.x>ret[j].inf_dir.x && t.centro.y>ret[j].inf_dir.y){
    norma = pow((t.centro.x-ret[j].inf_dir.x),2)+pow((t.centro.y-ret[j].inf_dir.y),2);
    norma = sqrt(norma);
		if (norma<R_C_F){a++;}}	
	}	
return a;}

int colisaomisseltank(float x, float y, tank t){
	
	int normacirculos;
	 normacirculos = pow(t.centro.x-x,2)+pow(t.centro.y-y,2);
	 normacirculos = sqrt(normacirculos);
	 if (normacirculos>R_C_F+R_T){return 0;}
	 else return 1;	 
	
	
}

int colisaoMisselRetangulos(float x, float y, retangulo ret[], int i){
	int a =0, j=0;
float norma;
	for (j=0;j<i;j++){
	if (y>=ret[j].sup_esq.y && x>=ret[j].sup_esq.x && x<=ret[j].inf_dir.x && y<=ret[j].inf_dir.y){
		a++;}
	
	if (x<=ret[j].sup_esq.x && y>=ret[j].sup_esq.y && y<=ret[j].inf_dir.y){
		if (abs(ret[j].sup_esq.x-x)<R_T){a++;}}
	
	if (x>=ret[j].inf_dir.x && y>=ret[j].sup_esq.y && y<=ret[j].inf_dir.y){
		if (abs(ret[j].inf_dir.x-x)<R_T){a++;}}
		
	if (y<=ret[j].sup_esq.y && x>=ret[j].sup_esq.x && x<=ret[j].inf_dir.x){
		if (abs(ret[j].sup_esq.y-y)<R_T){a++;}}	
	
	if (y>=ret[j].inf_dir.y && x>=ret[j].sup_esq.x && x<=ret[j].inf_dir.x){
		if (abs(ret[j].inf_dir.y-y)<R_T){a++;}}	
	
	
		
			
	if(x<=ret[j].sup_esq.x && y<=ret[j].sup_esq.y){
    norma = pow((x-ret[j].sup_esq.x),2)+pow((y-ret[j].sup_esq.y),2);
    norma = sqrt(norma);
		if (norma<R_T){a++;}}
		
	 if(x>=ret[j].inf_dir.x && y<=ret[j].sup_esq.y){
    norma = pow((x-ret[j].inf_dir.x),2)+pow((y-ret[j].sup_esq.y),2);
    norma = sqrt(norma);
		if (norma<R_T){a++;}}
		
	 if(x<=ret[j].sup_esq.x && y>=ret[j].inf_dir.y){
    norma = pow((x-ret[j].sup_esq.x),2)+pow((y-ret[j].inf_dir.y),2);
    norma = sqrt(norma);
		if (norma<R_T){a++;}}	
		
	 if(x>ret[j].inf_dir.x && y>ret[j].inf_dir.y){
    norma = pow((x-ret[j].inf_dir.x),2)+pow((y-ret[j].inf_dir.y),2);
    norma = sqrt(norma);
		if (norma<R_T){a++;}}	
	}	
return a;
	
}



void desenha_powerup(){
	
	

	//al_draw_filled_circle(float cx, float cy, float r, ALLEGRO_COLOR color)
	
	
}


void atualizaTanque(tank *t,tank *t2,retangulo ret[],int u){
	int estado=0;
	estado += colisaoTankcirculos(*t,*t2);
	
	estado += colisaobordas(*t);
	
	estado +=colisaoretangulos(*t, ret,u);
	
	rotacionaTank(t);
	if (estado==0){	
		
	t->centro.y += t->vel*t->y_comp;
	t->centro.x += t->vel*t->x_comp;
	}
	
	t->vida_pc.sup_esq.x = t->centro.x + 5;
	t->vida_pc.inf_dir.x = t->centro.x + 55-t->menosvida;
	t->vida_pc.sup_esq.y = t->centro.y + 20;	
	t->vida_pc.inf_dir.y = t->centro.y + 35;
	
	t->vida_bd.sup_esq.x = t->centro.x + 5;
	t->vida_bd.inf_dir.x = t->centro.x + 55;
	t->vida_bd.sup_esq.y = t->centro.y + 20;	
	t->vida_bd.inf_dir.y = t->centro.y + 35;
	
}

void desenha_Tank(tank t){
	
	al_draw_circle(t.centro.x, t.centro.y, R_C_F, t.cor,1);	
	al_draw_filled_triangle(t.A.x + t.centro.x, t.A.y + t.centro.y,
							t.B.x + t.centro.x, t.B.y + t.centro.y,
							t.C.x + t.centro.x, t.C.y + t.centro.y,
							t.cor);
							
	al_draw_filled_rectangle(t.vida_pc.sup_esq.x, t.vida_pc.sup_esq.y,
					  t.vida_pc.inf_dir.x, t.vida_pc.inf_dir.y,
					al_map_rgb(180,0,0));
							
	al_draw_rectangle(t.vida_bd.sup_esq.x, t.vida_bd.sup_esq.y,
					  t.vida_bd.inf_dir.x, t.vida_bd.inf_dir.y,
					al_map_rgb(0,0,0),2);
				
	
}

void initTiro1 (tiro *missel, tank t){
	missel->centro.x = t.A.x;
	missel->centro.y = t.A.y;	
	
}

void initTiro2 (tiro *missel, tank t){
	missel->centro.x = t.A.x;
	missel->centro.y = t.A.y;	
	
}
 
void atualizaTiro(tiro *missel,tank *t,tank *t2,retangulo ret[],int u,int *espaco,int x_centro, int y_centro){
		int a=0, estado = 0, vida=0;
		float teste_x,teste_y;
		float m=0;
		float hipotenusa=0;
		float nova_hipotenusa=0;
		a = *espaco;
	
	if(a>=1){
		hipotenusa=sqrt(pow(missel->centro.y-y_centro,2)+ pow(missel->centro.x-x_centro,2));
		nova_hipotenusa = hipotenusa+5;
		teste_x=(nova_hipotenusa/hipotenusa)*(missel->centro.x-x_centro)+x_centro;
		teste_y=(nova_hipotenusa/hipotenusa)*(missel->centro.y-y_centro)+y_centro;
		estado += colisaoboradaMissel(teste_x,teste_y);
		estado += colisaomisseltank(teste_x,teste_y,*t2);
		estado += colisaoMisselRetangulos(teste_x,teste_y,ret,u);
		vida += colisaomisseltank(teste_x,teste_y,*t2);
		if (estado==0){
		missel->centro.x = (nova_hipotenusa/hipotenusa)*(missel->centro.x-x_centro)+x_centro;
		missel->centro.y = (nova_hipotenusa/hipotenusa)*(missel->centro.y-y_centro)+y_centro;}
		else {*espaco = 0;}}		
		
	
	if (a == 0){
	missel->centro.y=t->A.y+t->centro.y; 
	missel->centro.x=t->A.x+t->centro.x;
	}
	t2->menosvida += vida*10;
	
	}
 
void desenhaTiro(tiro missel){
	al_draw_filled_circle(missel.centro.x, missel.centro.y,R_T,al_map_rgb(0,0,0));
}


int main(int argc, char **argv){
	int v =0;
	srand(time(NULL)); int vida1 = 0; int vida2 = 0; 
	int a=0; ALLEGRO_COLOR cor_vencedor;
	char vencedor[]= "O vencedor foi o jogador Tanque _";
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
  
  
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	/*//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}*/
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   
	//INICIO DE EVENTOS
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_install_audio();
	al_init_acodec_addon();
	
	al_reserve_samples(6);
	
	//allegro sample uma struct
	ALLEGRO_SAMPLE *som = NULL;
	ALLEGRO_SAMPLE *explosao = NULL;
	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;
	
	//allegro load sample 
	som = al_load_sample("tiro.wav");
	explosao = al_load_sample("Explosion__010.ogg");
	song = al_load_sample("Boss Battle.ogg");
	
	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	
	
	
	
	tank tanque_1, tanque_2;
	initTank1(&tanque_1);
	initTank2(&tanque_2);
	
	tiro missel_1, missel_2;
	initTiro1(&missel_1, tanque_1);
	initTiro2(&missel_2, tanque_2);
	
	
	//inicia o temporizador
	al_start_timer(timer);
	
	
	// inicia quantidade maxima de retangulos
	
	// devo criar um desenha cenário baseado besses structs amanha
	int i=0;
	int aux =0;
	int espacoa=0;
	int espacob=0;
	int x_centro1 = 0, y_centro1 = 0;
	int x_centro2 = 0, y_centro2 = 0;
	retangulo ret[15];
	for (i=0;i<15;i++){
	aux = rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand()+rand();
	aux = 0;// tentando variar o rand;
	aux =0;
	ret[i].sup_esq.x =(rand()%300)+100;
	
	ret[i].sup_esq.y =(rand()%200)+80;
	
	ret[i].inf_dir.x =(rand()%500)+280;
	
	ret[i].inf_dir.y =(rand()%300)+80;
	
	if(ret[i].sup_esq.x>ret[i].inf_dir.x){
		aux = ret[i].sup_esq.x;
		ret[i].sup_esq.x = ret[i].inf_dir.x;
		ret[i].inf_dir.x = aux;}
	if(ret[i].sup_esq.y>ret[i].inf_dir.y){
		aux = ret[i].sup_esq.y;
		ret[i].sup_esq.y = ret[i].inf_dir.y;
		ret[i].inf_dir.y = aux;}	
	}
	
	int u = (rand()%5)+1;
	
	
	int playing = 1;
	
	
	while(playing) {
		al_play_sample_instance(songInstance);
		
		if(tanque_1.menosvida>40){
				al_stop_sample_instance(songInstance);
				al_play_sample(explosao,5.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
				vida2 = (tanque_2.vida_pc.inf_dir.x-tanque_2.vida_pc.sup_esq.x)/10 ;		
				vencedor[32]= '2';
				cor_vencedor = tanque_2.cor;
				v=2;
			break;}
			
		if(tanque_2.menosvida>40){
			al_stop_sample_instance(songInstance);
			al_play_sample(explosao,5.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
			vida1 = (tanque_1.vida_pc.inf_dir.x-tanque_1.vida_pc.sup_esq.x)/10 ;		
			vencedor[32]= '1';
			cor_vencedor = tanque_1.cor;
			v=1;
			break;}
			
			
		
		
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			
		
		
		desenha_scenario(ret,u);	
		
		atualizaTanque(&tanque_1,&tanque_2,ret,u);
		
		
		atualizaTanque(&tanque_2,&tanque_1,ret,u);
		
		atualizaTiro(&missel_1,&tanque_1,&tanque_2,ret,u,&espacoa, x_centro1,y_centro1);
		atualizaTiro(&missel_2,&tanque_2,&tanque_1,ret,u,&espacob, x_centro2,y_centro2);
		
		desenha_Tank(tanque_1);
		desenha_Tank(tanque_2);
		
		desenhaTiro(missel_1);
		desenhaTiro(missel_2);
		
		

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
				
				
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}

		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {			
				switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_W:
					tanque_1.vel-=VEL_TANK;
				break;
					
					case ALLEGRO_KEY_S:
						tanque_1.vel+=VEL_TANK;
				break;
				
				case ALLEGRO_KEY_A:
						tanque_1.vel_angular-=PASSO_ANGULO;
				break;
				
				case ALLEGRO_KEY_D:
						tanque_1.vel_angular+=PASSO_ANGULO;
				break;
				
				case ALLEGRO_KEY_SPACE:
				if (espacoa == 0){
					al_play_sample(som,5.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
					espacoa++;
					x_centro1 = tanque_1.centro.x;
					y_centro1 = tanque_1.centro.y;}
					break;
				
				
				
				
				
				
				case ALLEGRO_KEY_UP:
						tanque_2.vel -= VEL_TANK;
					break;
					
					case ALLEGRO_KEY_DOWN:
						tanque_2.vel += VEL_TANK;
				break;

				case ALLEGRO_KEY_LEFT:
						tanque_2.vel_angular-=PASSO_ANGULO;
					break;
				
				case ALLEGRO_KEY_RIGHT:
						tanque_2.vel_angular+=PASSO_ANGULO;
					break;
				
				case ALLEGRO_KEY_PAD_ENTER:
					if (espacob == 0){
					al_play_sample(som,5.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,0);
					espacob++;
					x_centro2 = tanque_2.centro.x;
					y_centro2 = tanque_2.centro.y;}
					break;
				
				
				}
				
			
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_W:
						tanque_1.vel += VEL_TANK;
					break;
					
					case ALLEGRO_KEY_S:
						tanque_1.vel -= VEL_TANK;
				break;
				
				case ALLEGRO_KEY_A:
						tanque_1.vel_angular+=PASSO_ANGULO;
					break;
				
				case ALLEGRO_KEY_D:
						tanque_1.vel_angular-=PASSO_ANGULO;
					break;
				
				
				
				case ALLEGRO_KEY_UP:
						tanque_2.vel += VEL_TANK;
					break;
					
					case ALLEGRO_KEY_DOWN:
						tanque_2.vel -= VEL_TANK;
				break;
				
				
				case ALLEGRO_KEY_LEFT:
						tanque_2.vel_angular+=PASSO_ANGULO;
					break;
				
				case ALLEGRO_KEY_RIGHT:
						tanque_2.vel_angular-=PASSO_ANGULO;
					break;
			
				
				
				}
			
			
			
		}
				

	} //fim do while
    al_clear_to_color(al_map_rgb(255,255,255));
	//reinicializa a tela
	//FILE *historico;
	ALLEGRO_FONT *texto = al_load_font("spaceage.ttf", 25, 0.5);
	if(tanque_2.menosvida>40 ||tanque_1.menosvida>40){
	FILE *backup;
	char pontuacao[40];
	
	sprintf(pontuacao, "Pontos de vida Tanque 1: %d Tanque 2: %d", vida1, vida2);
	al_draw_text(texto,cor_vencedor, SCREEN_W/7, SCREEN_H/2, 0, pontuacao);
	al_draw_text(texto,cor_vencedor, SCREEN_W/7+30, SCREEN_H/4+60, 0, vencedor);
	
	backup = fopen ("backup.txt", "a");
	
	fprintf(backup, "%d\n" , v);
	fclose(backup);
	
	FILE *back= fopen("backup.txt", "r");
	FILE *historico = fopen("historico.txt", "w");

	int vencedor1 = 0, vencedor2 = 0;
	char valor[2];
	while(!feof(back)){
		fgets(valor,2,back);
		if(valor[0]=='1'){
			vencedor1++;
			} 
			
		if(valor[0]=='2'){
			vencedor2++;
		}
	} 
		fprintf(historico, "O Jogador 1 venceu %d vezes e o Jogador 2 venceu %d vezes" ,vencedor1,vencedor2 );
		fclose(back);
		fclose(historico);	
	}
	
	al_flip_display();	
    al_rest(3);	
	
   
	al_destroy_timer(timer);
	al_destroy_sample(som);
	al_destroy_sample(explosao);
	al_destroy_sample_instance(songInstance);
	al_destroy_sample(song);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}