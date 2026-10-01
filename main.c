#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>

typedef struct personnage
{
    float x, y;
    BITMAP* haut[9];
    BITMAP* bas[9];
    BITMAP* gauche[9];
    BITMAP* droite[9];
    char nom[20];

    int direction, en_deplacement;
    int frame;
    int nb_vie;

    int frame1, frame2;
    BITMAP* danse[6];
    BITMAP* defaite[6];
}t_personnage;

/// loading
typedef struct rat {
    BITMAP* sprites[4];
    int frame_actuelle;
    int x;
    int y;
    int vitesse;
} t_rat;

typedef struct stat{
    char nom[20];
    char performance[20];
    char jeux[20];
    int presence;


}t_stat;


/// guitar hero
#define TAILLE 50
typedef struct touche
{
    BITMAP* couleur[5];
    float x, y;
    float taille;
    int frame;
    int vie;
    int passer;
}t_touche;

/// jackpot
typedef struct symboles_casino
{
    BITMAP* image;
    int x_gauche, y_gauche;
    int x_milieu, y_milieu;
    int x_droite, y_droite;
    bool en_deroulement;
    bool dans_la_partie;
    bool victory_casino;

}t_symboles_casino;

/// flappy bird
typedef struct bird
{
    BITMAP* droite[4];
    float x, y;
    int frame;
    int vie;
}t_bird;
typedef struct tuyaux
{
    int x,y;
}t_tuyaux;

/// surprise
typedef struct
{
    BITMAP* surpris;
    float taille;
}t_surprise;

/// street fighter
typedef struct personnage_street_fighter
{
    int x,y;
    int x_hadoken, y_hadoken;

    BITMAP* STREET_FIGHTER_gauche[3];
    BITMAP* STREET_FIGHTER_droite[3];

    int en_deplacement;
    bool projectile;
    bool en_train_de_sauter, vers_le_haut;

    int vie;
}t_personnage_street_f;

/// paris zombique
typedef struct joueurs {
    int numero;
    char pari[10];
    int ticket;
} t_joueur;
typedef struct fille {
    BITMAP *droite[11];
    int x, y;
    int frameZombie;
    int zombie_qui_court;
    int gagnant;
} t_fille;
typedef struct garcon {
    BITMAP *droite[11];
    int x, y;
    int frameZombie;
    int zombie_qui_court;
    int gagnant;
} t_garcon;
typedef struct squelette {
    BITMAP *droite[11];
    int x, y;
    int frameZombie;
    int zombie_qui_court;
    int gagnant;
} t_squelette;
typedef struct zombie {
    BITMAP *droite[4];
    int x, y;
    int frameZombie;
    int zombie_qui_court;
    int gagnant;
} t_zombie;

/// option de pari
enum pari {
    COUREUR1,
    COUREUR2,
    COUREUR3,
    COUREUR4,
};

/// traverse de riviere
typedef struct bidon{
    int x;
    int y;
    BITMAP *bidon;
    int presence;
}t_bidon;
typedef struct mouv{
    int dx[4];
    int frame;
}t_mouv;
typedef struct jeu{
    int tour;
    int etape;
    int cmpt;
    int victoir;
    int defaite;
}t_jeu;

typedef struct {
    double debut,fin,tot;
    BITMAP* haut[9];
    BITMAP* bas[9];
    BITMAP* gauche[9];
    BITMAP* droite[9];
    int x;
    int y;
    int direction;
    int frame;
    int deplacement;
}t_joueurs;

// tir au ballon
typedef struct ballon {
    int posx, posy;
    int depx, depy;
    int rayon;
    int couleur;
    int affichage;
} t_ballons;

void initialisation()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);


    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,900,650,0,0))!=0)
    {     allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE); }

    install_keyboard();
    install_mouse();
}


void creation_sprite_perso(t_personnage* personnage, BITMAP* bitmap, int taille_w, int taille_h)
{
    for (int i = 0; i < 9; ++i)
    {
        personnage->haut[i] = create_sub_bitmap(bitmap, i * taille_w, 518, taille_w, taille_h);
        personnage->bas[i] = create_sub_bitmap(bitmap, i * taille_w, 648, taille_w, taille_h);
        personnage->gauche[i] = create_sub_bitmap(bitmap, i * taille_w, 584, taille_w, taille_h);
        personnage->droite[i] = create_sub_bitmap(bitmap, i * taille_w, 711, taille_w, taille_h);
    }
}



/// choix du joueur
void retirer_chapeau(char* chaine) {
    int longueur = strlen(chaine);
    if (longueur > 0) {
        chaine[longueur - 1] = '\0';
    }
}
void entrer_le_nom(t_personnage personnage[2], BITMAP* buffer){
    char c,d;
    int i=0;
    int tour=0;

    do {
        c= readkey() & 0xFF;
        personnage[tour].nom[i] = c;
        if (personnage[tour].nom[i] != key[KEY_ENTER]) {
            personnage[tour].nom[i + 1] = '\0';
            textprintf_ex(screen,font,330+7*i,230,makecol(255,255,255),-1,"%c",c);
            i++;
        }

    } while (personnage->nom[i - 1] != 13);
    retirer_chapeau(personnage[tour].nom);

    textout_centre_ex(buffer, font, personnage[tour].nom, 147, 310, makecol(255, 255, 255), -1);

    textout_centre_ex(buffer, font, "Joueur 2, quel est votre pseudo?", 200, 250, makecol(255, 255, 255), -1);
    blit(buffer, screen, 0, 0, 0, 0, 900, 650);

    i = 0;
    tour=1;
    do {
        d=readkey() & 0xFF;
        personnage[tour].nom[i] = d;
        if (personnage[tour].nom[i] != key[KEY_ENTER]) {
            personnage[tour].nom[i + 1] = '\0';
            textprintf_ex(screen,font,330+7*i,250,makecol(255,255,255),-1,"%c",d);
            i++;
        }
    } while (personnage[tour].nom[i - 1] != 13);
    retirer_chapeau(personnage[tour].nom);
    textout_centre_ex(buffer, font, personnage[tour].nom, 147, 460, makecol(255, 255, 255), -1);
    blit(buffer, screen, 0, 0, 0, 0, 900, 650);

}

int detection_changement(int choix)
{
    if (key[KEY_LEFT] || (mouse_b==1 && mouse_x>541 && mouse_x<577 && mouse_y>569 && mouse_y<599))
    {
        rest(300);
        if (choix == 0) return 3;
        else return choix-1;
    }
    else if (key[KEY_RIGHT] || (mouse_b==1 && mouse_x>755 && mouse_x<789 && mouse_y>569 && mouse_y<599))
    {
        rest(300);
        if (choix == 3) return 0;
        else return choix+1;
    }
    return choix;
}

void maj_personnage(t_personnage* personnage)
{
    if (mouse_x >= (SCREEN_W / 2) + 160) personnage->direction = 3;
    else personnage->direction = 2;
}

void affichage_perso(t_personnage* personnage, BITMAP* buffer, int taille_w, int taille_h, int d_w, int d_h)
{
    BITMAP* PERSO;
    switch (personnage->direction)
    {
        case 0:
            PERSO = personnage->haut[personnage->frame];
            break;
        case 1:
            PERSO = personnage->bas[personnage->frame];
            break;
        case 2:
            PERSO = personnage->gauche[personnage->frame];
            break;
        case 3:
            PERSO = personnage->droite[personnage->frame];
            break;
    }
    masked_stretch_blit(PERSO, buffer,0,0,taille_w,taille_h, personnage->x, personnage->y, d_w, d_h);
}

void affichage_perso_mini(t_personnage* personnage, BITMAP* buffer, int taille_w, int taille_h, int joueur, int x, int y)
{
    if (joueur!=-1)  masked_stretch_blit(personnage->droite[0], buffer,0,0,taille_w,taille_h, x, y, SCREEN_W/7, SCREEN_H/7);
}

void detection_selection(int* joueur_1, int* joueur_2, int choix, BITMAP* buffer)
{
    int blanc = makecol(255,255,255);
    int rouge = makecol(255,0,0);
    if (*joueur_1==-1)
    {
        rectfill(buffer, 106,338,174,400, blanc);
        if(key[KEY_SPACE] || (mouse_b==1 && mouse_x>580 && mouse_x<749 && mouse_y>569 && mouse_y<599))
        {
//            rest(100);
            *joueur_1 = choix;
        }
        return;
    }
    else if (*joueur_2 == -1)
    {
        if (*joueur_1==choix)
        {
            rectfill(buffer, 106,485,174,546, rouge);
            return;
        }
        else rectfill(buffer, 106,485,174,546, blanc);


        if (key[KEY_SPACE] || (mouse_b==1 && mouse_x>580 && mouse_x<749 && mouse_y>569 && mouse_y<599))
        {
//            rest(100);
            *joueur_2 = choix;
        }
    }
}


/// map

void maj_perso_map(t_personnage* personnage, int interdit) {
    float vitesse = 1.5;
    personnage->en_deplacement = 0;
    if (interdit == 0)
    {
        if (key[KEY_UP]) {
            personnage->y -= vitesse;
            personnage->direction = 0;
            personnage->en_deplacement = 1;
        }
        if (key[KEY_DOWN]) {
            personnage->y += vitesse;
            personnage->direction = 1;
            personnage->en_deplacement = 1;
        }
        if (key[KEY_LEFT]) {
            personnage->x -= vitesse;
            personnage->direction = 2;
            personnage->en_deplacement = 1;
        }
        if (key[KEY_RIGHT]) {
            personnage->x += vitesse;
            personnage->direction = 3;
            personnage->en_deplacement = 1;
        }
    }

}

int detection_mini_jeu(t_personnage* personnage, BITMAP* fondcol, int joueur) {
    int p = getpixel(fondcol, (int) personnage[joueur].x+34, (int) personnage[joueur].y+30);
    if (p == makecol(0, 0, 255)) return 1; // guitar hero
    if (p == makecol(0, 255, 0)) return 2; // traverse de riviere
    if (p == makecol(0, 255, 255)) return 3; // jackpot
    if (p == makecol(255, 255, 0)) return 4; // flappy bird
    if (p == makecol(255, 0, 0)) return 5; // surprise
    if (p == makecol(255, 0, 255)) return 6; // street fighter
    if (p == makecol(100, 0, 0)) return 7; // paris zombique
    if (p == makecol(0, 0, 100)) return 8; // tir au ballon
    if (p == makecol(0, 100, 0)) return 9; // stat
    if (p == makecol(100, 100, 100)) return 10;
    else return 0;
}

int collision_interdit(t_personnage* personnage, BITMAP* fondcol, int joueur)
{
    if(key[KEY_UP])
    {
        int p = getpixel(fondcol, (int) personnage[joueur].x + 34, (int) personnage[joueur].y + 30);
        if (p == makecol(0, 0, 0))
        {
            return -1;
        }else return 0;
    }
    if(key[KEY_DOWN])
    {
        int p = getpixel(fondcol, (int) personnage[joueur].x + 34, (int) personnage[joueur].y + 34);
        if (p == makecol(0, 0, 0))
        {
            return -1;
        }else return 0;
    }
    if(key[KEY_RIGHT])
    {
        int p = getpixel(fondcol, (int) personnage[joueur].x + 36, (int) personnage[joueur].y + 32);
        if (p == makecol(0, 0, 0))
        {
            return -1;
        }else return 0;
    }
    if(key[KEY_LEFT])
    {
        int p = getpixel(fondcol, (int) personnage[joueur].x + 32, (int) personnage[joueur].y +32);
        if (p == makecol(0, 0, 0))
        {
            return -1;
        }else return 0;
    }
}

void home_pos(t_personnage* personnage)
{
    for (int i = 0; i < 4; ++i) {
        personnage[i].x = 430;
        personnage[i].y = 410;
    }
}

void gestion_vie_personnage(BITMAP* buffer, t_personnage* personnage, int joueur_tour, BITMAP* image_vie, int enlever, bool* decision, int nb_ticket)
{
    if(key[KEY_U])
    {
        personnage[joueur_tour].nb_vie -=1;
        rest(1000);
    }
    if (enlever)
    {
        if (*decision == true)
        {
            *decision = false;
            if (nb_ticket == -1 && personnage[joueur_tour].nb_vie==5) return;
            personnage[joueur_tour].nb_vie -= nb_ticket;
        }
    }
    else
    {
        for (int i = 1; i < personnage[joueur_tour].nb_vie + 1; ++i)
        {
            masked_blit(image_vie, buffer, 0, 0, SCREEN_W - i * image_vie->w, 0, image_vie->w, image_vie->h);
        }
    }
}

int condition_de_victoire_globale(t_personnage* personnage, int joueur1, int joueur2)
{
    if (personnage[joueur1].nb_vie == 0) return 1;
    if (personnage[joueur2].nb_vie == 0) return 2;
    return 0;
}

/// tour

int changement_tour_joueur(int* tour, int joueur_1, int joueur_2)
{
    if(*tour>2) *tour=1;
    if (*tour == 1) return joueur_1;
    else if (*tour == 2) return joueur_2;
}

int inv_changement_tour_joueur(int* tour, int joueur_1, int joueur_2)
{
    if(*tour>2) *tour=1;
    if (*tour == 1) return joueur_2;
    else if (*tour == 2) return joueur_1;
}


/// loading

void maj_rat(t_rat* rat) {
    rat->x += rat->vitesse;
    rat->frame_actuelle++;
    if (rat->frame_actuelle >= 4) {
        rat->frame_actuelle = 0;
    }
    rat->vitesse += 1;
}

void dessin_rats(t_rat* rat, BITMAP* buffer) {
    clear(buffer);
    BITMAP* fond = load_bitmap("../background_loading.bmp", NULL);
    if (fond != NULL) {
        blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        destroy_bitmap(fond);
    }
    masked_stretch_blit(rat->sprites[rat->frame_actuelle],buffer,0, 0,rat->sprites[rat->frame_actuelle]->w,rat->sprites[rat->frame_actuelle]->h,rat->x, rat->y, 100,50);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void init_loading(t_rat* rat, BITMAP* buffer)
{
    rat->sprites[0] = load_bitmap("../rat.bmp", NULL);
    rat->sprites[1] = load_bitmap("../rat2.bmp", NULL);
    rat->sprites[2] = load_bitmap("../rat3.bmp", NULL);
    rat->sprites[3] = load_bitmap("../rat4.bmp", NULL);

    rat->x = 0;
    rat->y = 600 - rat->sprites[0]->h / 2;
    rat->vitesse = 5;
    rat->frame_actuelle = 0;
}

void loading(t_rat* rat, BITMAP* buffer)
{
    while (rat->x <= SCREEN_W) {
        maj_rat(rat);
        dessin_rats(rat, buffer);
        rest(50);
    }
}



/// fin jeu

void creation_sprite_danse(t_personnage* personnage, BITMAP* bitmap_sprite) {
    int taille_w = 65;
    int taille_h_v = 900;
    int taille_h_d = 1290;

    for (int i = 0; i < 6; ++i) {
        personnage->danse[i] = create_sub_bitmap(bitmap_sprite, i * taille_w, taille_h_v, taille_w, taille_h_v);
    }
    for (int j = 0; j < 5; ++j) {
        personnage->defaite[j] = create_sub_bitmap(bitmap_sprite, j * taille_w, taille_h_d, taille_w, taille_h_d);
    }
}

void affichage_danse_fin(t_personnage* personnage, BITMAP* buffer, int a, int joueur1, int joueur2)
{
    BITMAP* DANSE;
    BITMAP* DANSE2;
    BITMAP* DEFAITE;
    BITMAP* DEFAITE2;



    switch (a) {
        case 1:

            DANSE = personnage[joueur1].danse[personnage[joueur1].frame1];
            masked_stretch_blit(DANSE, buffer , 0, 0, 65, 65, 390, 350, 240, 280);

            DEFAITE = personnage[joueur2].defaite[personnage[joueur2].frame2];
            masked_stretch_blit(DEFAITE, buffer , 0, 0, 65, 53, 620, 430, 80, 100);
            break;
        case 2: /// jeu jackpot
            DEFAITE = personnage[joueur1].defaite[personnage[joueur1].frame2];
            masked_stretch_blit(DEFAITE, buffer, 0, 0, 65, 53, 390, 350, 240, 280);
            break;
        case 3: /// jeu jackpot


            DANSE = personnage[joueur1].danse[personnage[joueur1].frame1];
            masked_stretch_blit(DANSE, buffer , 0, 0, 65, 65, 390, 350, 240, 280);
            break;
        case 4: /// jeu paris zombique
            DEFAITE = personnage[joueur1].defaite[personnage[joueur1].frame2];
            masked_stretch_blit(DEFAITE, buffer, 0, 0, 65, 53, 220, 350, 240, 280);

            DEFAITE2 = personnage[joueur2].defaite[personnage[joueur2].frame2];
            masked_stretch_blit(DEFAITE2, buffer, 0, 0, 65, 53, 500, 350, 240, 280);
            break;
        case 5:
            DEFAITE2 = personnage[joueur2].defaite[personnage[joueur1].frame2];
            masked_stretch_blit(DEFAITE2, buffer, 0, 0, 65, 53, 180, 250, 240, 280);

            DANSE = personnage[joueur1].danse[personnage[joueur2].frame1];
            masked_stretch_blit(DANSE, buffer , 0, 0, 65, 65, 550, 250, 240, 280);
            break;
    }
}

void affichage_vic_ou_def(BITMAP* buffer, BITMAP* victoire, BITMAP* defaite, int* taille_vic, int* taille_def, float* depart_vx, int* depart_vy, float* departdx, int* departdy, int a)
{

    switch(a){
        case 1:
            /// victoire jau
            if(victoire->h+*taille_vic < 200)
            {
                *taille_vic += 2;
                *depart_vx = *depart_vx-1;
                *depart_vy = *depart_vy-1;

                masked_stretch_blit(victoire, buffer, 0, 0, victoire->w, victoire->h,*depart_vx, *depart_vy, victoire->w+*taille_vic, victoire->h+*taille_vic);

            }
            if(victoire->h+*taille_vic >= 200) masked_stretch_blit(victoire, buffer, 0, 0, victoire->w, victoire->h,*depart_vx, *depart_vy, victoire->w+*taille_vic, victoire->h+*taille_vic);
            break;
        case 2:
            /// defaite gris

            if(defaite->h+*taille_def < 150)
            {
                *taille_def += 2;
                *departdx = *departdx-1;
                *departdy = *departdy-2;

                masked_stretch_blit(defaite, buffer, 0, 0, defaite->w, defaite->h,*departdx, *departdy, defaite->w+*taille_def, defaite->h+*taille_def);

            }
            if(defaite->h+*taille_def >= 150) masked_stretch_blit(defaite, buffer, 0, 0, defaite->w, defaite->h,*departdx, *departdy, defaite->w+*taille_def, defaite->h+*taille_def);
            break;
    }
}

void exit_mini_jeu(t_personnage* personnage, int* clic, int* clic_dans_accueil, int* tour, int a)
{
    if(mouse_x>710 && mouse_x<880 && mouse_y>600 && mouse_y<640 && mouse_b || *clic==2) {
        *clic = 0;

        *clic_dans_accueil = 4;
        home_pos(personnage);
        switch (a) {
            case 0:
                *tour = *tour;
                break;
            case 1:
                *tour = *tour+1;
                break;
        }
    }
}

void init_vicoudef(int* taille_vic, float* depart_vx, int* depart_vy , int* taille_def, float* departdx, int* departdy, int* vic_ou_def )
{
    *taille_vic =0;
    *depart_vx = 340;
    *depart_vy = 100;
    *taille_def =0;
    *departdx = 340;
    *departdy = 180;
    *vic_ou_def =0;
}

void frame_count(t_personnage* personnage, int* frame1_counter, int* frame1_counter2)
{
    for (int y = 0; y < 4; ++y) {
        *frame1_counter = *frame1_counter+1;
        *frame1_counter2 = *frame1_counter2+1;
        if (*frame1_counter >= 7) {
            personnage[y].frame1++;
            *frame1_counter = 0;
        }
        if (personnage[y].frame1 >= 6) {
            personnage[y].frame1 = 0;
        }
        if (*frame1_counter2 >= 15)
        {
            personnage[y].frame2++;
            *frame1_counter2 = 0;
        }
        if (personnage[y].frame2 >= 5) {
            personnage[y].frame2 = 0;
        }
    }
}


/// jeu guitar hero (marina)

void separer_couleur(t_touche* touche, BITMAP* bitmap)
{
    int taille_w = 29;
    int taille_h = 19;

    for (int j = 0; j < 5; j++) {
        touche->couleur[j] = create_sub_bitmap(bitmap, j * taille_w, 0* taille_h, taille_w, taille_h);
    }
}

void deplacer_touche(t_touche* touche, int couleur, BITMAP* touches, BITMAP* buffer)
{
    BITMAP* frame;

    frame = touche->couleur[touche->frame];

    int taille_w = 29;
    int taille_h = 19;


    switch (couleur){
        case 0 : // vert
            touche->y += 1;
            touche->x -= 0.5;

            masked_stretch_blit(frame, buffer, 0, 0, taille_w, taille_h, touche->x, touche->y, frame->w+touche->taille, frame->h+touche->taille );
            break;
        case 1 : // rouge
            touche->y += 1;
            touche->x -= 0.3;

            masked_stretch_blit(frame, buffer, 0, 0, taille_w, taille_h, touche->x+29, touche->y, frame->w+touche->taille, frame->h+touche->taille );
            break;
        case 2 : // jaune
            touche->y += 1;
            touche->x -= 0.07;

            masked_stretch_blit(frame, buffer, 0, 0, taille_w, taille_h, touche->x+58, touche->y, frame->w+touche->taille, frame->h+touche->taille );
            break;
        case 3 : //bleu
            touche->y += 1;
            touche->x += 0.15;

            masked_stretch_blit(frame, buffer, 0, 0, taille_w, taille_h, touche->x+87, touche->y, frame->w+touche->taille, frame->h+touche->taille );
            break;
        case 4 : //orange
            touche->y += 1;
            touche->x += 0.35;

            masked_stretch_blit(frame, buffer, 0, 0, taille_w, taille_h, touche->x+116, touche->y, frame->w+touche->taille, frame->h+touche->taille );
            break;
    }

}

void collision_gh(t_touche touche[TAILLE], BITMAP* fondbis, int i)
{
    if(key[KEY_G]) // vert
    {
        int p = getpixel(fondbis, (int)touche[i].x+15, (int)touche[i].y+10);
        if(p == makecol(0, 255, 0)) touche[i].passer = 1 ;
        else touche[i].vie = 1;
    }
    if(key[KEY_H]) // rouge
    {
        int p = getpixel(fondbis, (int)touche[i].x+45, (int)touche[i].y+10);
        if(p == makecol(255, 0, 0)) touche[i].passer = 1;
        else touche[i].vie = 1;
    }
    if(key[KEY_J]) // jaune
    {
        int p = getpixel(fondbis, (int)touche[i].x+75, (int)touche[i].y+10);
        if(p == makecol(255, 255, 0)) touche[i].passer = 1;
        else touche[i].vie = 1;
    }
    if(key[KEY_K]) // bleu
    {
        int p = getpixel(fondbis, (int)touche[i].x+105, (int)touche[i].y+10);
        if(p == makecol(0, 0, 255)) touche[i].passer = 1;
        else touche[i].vie = 1;
    }
    if(key[KEY_L]) // orange (cyan)
    {
        int p = getpixel(fondbis, (int)touche[i].x+135, (int)touche[i].y+10);
        if(p == makecol(0, 255, 255)) touche[i].passer = 1;
        else touche[i].vie = 1;
    }
}

void init_guitar_hero(t_touche* touche, int* j, int* press, int* round_gh, int* joueur_def, int* joueur_vic)
{
    for (int m = 0; m < TAILLE; ++m) {
        touche[m].frame = rand()%5;
        touche[m].x = 375;
        touche[m].y = 290;
        touche[m].taille = 1;
        touche[m].passer = 0;
        touche[m].vie = 0;
    }
    *j = 0; // pour plusieurs touches affichées sur lecran en simultané
    *press = 0; // pour detecter bonne touche
    *round_gh = 1;

    *joueur_def = -1;
    *joueur_vic = -1;
}


/// jeu jackpot (octave)

int detection_clic()
{
    /// Detection du clic dans la bonne partie de la fenetre de jeu (rectangle)
    if(mouse_b & 1)
    {
        if (mouse_x >= 645 && mouse_x <= 700)
        {
            if (mouse_y >= 260 && mouse_y <= 420)
            {
                return 1;
            }
        }
    }
    else if (key[KEY_ENTER]) return 1;              /// Detection pour la touche enter
    return 0;                                       /// Si pas de detection
}

void deplacement_symboles_casino(t_symboles_casino* symbolesCasino, int *frame_counter, BITMAP* buffer, int * deplacement_g, int * deplacement_m, int * deplacement_d,  int taille_h, int nb_rand_1, int nb_rand_2, int nb_rand_3)
{
    /// Deplacement de la bande a droite


    if(*frame_counter<=nb_rand_1)
    {
        if (*deplacement_g >= 600) *deplacement_g = -100;
        else *deplacement_g += 1;
    }


    if (*frame_counter <= nb_rand_1 +nb_rand_2)
    {
        if (*deplacement_m >= 555) *deplacement_m = -100;
        else *deplacement_m += 2;
    }

    if (*frame_counter <= nb_rand_1 +nb_rand_2 + nb_rand_3)
    {
        if (*deplacement_d >= 555) *deplacement_d = -100;
        else *deplacement_d += 3;
    }
    else
    {
        symbolesCasino->en_deroulement = false;

        *frame_counter = 0;
        rest(1000);
    }
}

void verif_tirage_gagnant(int deplacement_g, int deplacement_m, int deplacement_d, t_symboles_casino* symbolesCasino)
{
    if (deplacement_g >= 250) deplacement_g -=300;
    if (deplacement_m >= 250) deplacement_m -=300;
    if (deplacement_d >= 250) deplacement_d -=300;

//    if (deplacement_g == 100 || deplacement_g == 175 || deplacement_g==250) symbolesCasino->victory_casino = true;
    if (deplacement_g == deplacement_m && deplacement_m == deplacement_d) symbolesCasino->victory_casino = true;
}

void affichage_avant_debut(t_symboles_casino* symbolesCasino, BITMAP* buffer, BITMAP* Message_attente_casino)
{
    if (detection_clic(buffer))
    {
        symbolesCasino->dans_la_partie = true;
        symbolesCasino->en_deroulement = true;
    }
    else blit(Message_attente_casino, buffer, 0, 0, 385, 269, Message_attente_casino->w,Message_attente_casino->h);
}

void affichage_jackpot(t_symboles_casino* symbolesCasino, BITMAP* buffer, int source_y_g, int source_y_m, int source_y_d, int taille_h)
{
    masked_blit(symbolesCasino->image, buffer, 0, source_y_g, symbolesCasino->x_gauche,symbolesCasino->y_gauche, symbolesCasino->image->w, taille_h);
    masked_blit(symbolesCasino->image, buffer, 0, source_y_m, symbolesCasino->x_milieu,symbolesCasino->y_milieu, symbolesCasino->image->w, taille_h);
    masked_blit(symbolesCasino->image, buffer, 0, source_y_d, symbolesCasino->x_droite,symbolesCasino->y_droite, symbolesCasino->image->w, taille_h);

    for (int i = 0; i < 3; ++i)
    {
        line(buffer, 377, 345 + i, 623, 345 + i, makecol(0, 0, 0));
    }
}

void init_jackpot(t_symboles_casino* symbolesCasino, int* taille_hauteur_j, int* frame_counter_jackpot, int* deplacement_g, int* deplacement_m, int* deplacement_d, int* nb_rand_1, int* nb_rand_2, int* nb_rand_3)
{
    symbolesCasino->image = load_bitmap("../sprite_symboles.bmp", NULL);
    symbolesCasino->y_droite = symbolesCasino->y_gauche = symbolesCasino->y_milieu = 270;
    symbolesCasino->x_gauche = 380 +0*80;
    symbolesCasino->x_milieu = 380 +1*80;
    symbolesCasino->x_droite = 380 +2*80;
    symbolesCasino->en_deroulement = false;
    symbolesCasino->dans_la_partie = false;
    symbolesCasino->victory_casino = false;

    *taille_hauteur_j = 150;
    *frame_counter_jackpot = 0;
    *deplacement_g = 0;
    *deplacement_m = 330;
    *deplacement_d = 500;

    *nb_rand_1 = 100+(rand()%400);
    *nb_rand_2 = 100+(rand()%400);
    *nb_rand_3 = 100+(rand()%400);
}


/// flappy bird (marina)

void separer_bitmap_bird(t_bird* bird, BITMAP* bitmap)
{
    int taille_w = 70;
    int taille_h = 60;

    for (int j = 0; j < 4; j++) {
        bird->droite[j] = create_sub_bitmap(bitmap, j * taille_w, 0* taille_h, taille_w, taille_h);
    }
}

void dessiner_bird(t_bird* bird, BITMAP* buffer)
{
    BITMAP* frame;

    frame = bird->droite[bird->frame];

    masked_blit(frame, buffer, 0, 0, bird->x, bird->y, frame->w, frame->h);
}

void maj_bird(t_bird* bird, float vitesse)
{
    if (key[KEY_UP]) bird->y -= vitesse;
    if (key[KEY_DOWN]) bird->y += vitesse;
}

void deplacer_bird(t_bird* bird, float vitesse)
{
    bird->x += vitesse;
    if (bird->x >=880) bird->x = 0;
}

void collision_bird(t_bird* bird, BITMAP* fond)
{
    for (int i = 0; i < 60; ++i) {
        for (int j = 0; j < 70; ++j) {
            int p = getpixel(fond, (int)bird->x+j, (int)bird->y+i);
            if(p == makecol(118, 194, 44)) bird->vie = 1;
        }
    }
}

void init_flappy_bird(t_bird* bird, int* joueur_def, int* joueur_vic, int*re_fp, int* round_fp)
{
    bird->frame = 0;
    bird->x = 20;
    bird->y = 300;
    bird->vie = 0;

    *joueur_def = -1;
    *joueur_vic = -1;
    *re_fp = 0;
    *round_fp = 1;
}


/// street fighter (octave)

void creation_sprite_perso_street_f(t_personnage_street_f * personnage, BITMAP* bitmap, int taille_w, int taille_h)
{
    for (int i = 1; i < 3; ++i)
    {
        personnage->STREET_FIGHTER_gauche[0]= create_sub_bitmap(bitmap, 0, 1093, taille_w, taille_h);
        personnage->STREET_FIGHTER_gauche[i]= create_sub_bitmap(bitmap, taille_w + (i-1)*(7*taille_w), 1093, taille_w, taille_h);

        personnage->STREET_FIGHTER_droite[0]= create_sub_bitmap(bitmap, 0, 1220, taille_w, taille_h);
        personnage->STREET_FIGHTER_droite[i]= create_sub_bitmap(bitmap, taille_w + (i-1)*(7*taille_w), 1220, taille_w, taille_h);
    }
}

void collision_street_f(t_personnage_street_f * personnage1, t_personnage_street_f * personnage2, BITMAP* buffer, int* frame_counter)
{
    if(personnage2->x - personnage1->x >0 && personnage2->x - personnage1->x <100)
    {
        if(personnage2->y - personnage1->y > -90     &&      personnage2->y - personnage1->y < 90)
        {
            if (personnage1->en_deplacement == 2 && *frame_counter > 160) {
                *frame_counter = 0;
                personnage2->vie -= 1;
            }
            if (personnage2->en_deplacement == 2 && *frame_counter > 160) {
                *frame_counter = 0;
                personnage1->vie -= 1;
            }
        }
    }

    ///         les boules de jeu / projectiles
    if (personnage2->x - personnage1->x_hadoken >-140 && personnage2->x - personnage1->x_hadoken <-50)
    {
        if (personnage2->y - personnage1->y_hadoken <-114 && personnage2->y - personnage1->y_hadoken> -190) {
            personnage1->y_hadoken = -100;
            personnage2->vie-=1;
        }
    }

    if (personnage2->x_hadoken - personnage1->x <165 && personnage2->x_hadoken - personnage1->x > 90)
    {
        if (personnage1->y - personnage2->y_hadoken <-114 && personnage1->y - personnage2->y_hadoken> -190)
        {
            personnage2->y_hadoken = -100;
            personnage1->vie-=1;
        }
    }
}

void affichage_vie_street_f(BITMAP* buffer, t_personnage_street_f* personnage1, t_personnage_street_f* personnage2)
{
    int rouge = makecol(250,0,0);
    rectfill(buffer, 440-personnage1->vie*20,10,440,50,rouge);
    rectfill(buffer, 460,10,460 + personnage2->vie*20,50,rouge);
}

void deplacement_street(t_personnage_street_f * personnage, int frappe, int haut, int hadoken, int gauche, int droite, int ecart, int *frame_counter_street, BITMAP* buffer, t_personnage_street_f * personnage_autre)
{
    int vitesse =1;
    personnage->en_deplacement = 0;
    if (key[gauche] && personnage->x>=0 - ecart*2)
    {
        personnage->x -= vitesse;
        personnage->en_deplacement=1;
    }
    if(key[droite] && personnage->x<=SCREEN_W-ecart*3)
    {
        personnage->x += vitesse;
        personnage->en_deplacement=1;
    }

    ///             SAUT
    if (key[haut] && personnage->en_train_de_sauter==false && personnage->vers_le_haut == false)
    {
        personnage->en_train_de_sauter = true;
        personnage->vers_le_haut = true;
    }
    if(personnage->vers_le_haut==true)
    {
        personnage->y -= vitesse;
        if (personnage->y <175) personnage->vers_le_haut = false;
    }
    else if (personnage->y <400)personnage->y += vitesse;
    else personnage->en_train_de_sauter = false;


    if (key[frappe])
    {
        if (*frame_counter_street<40) personnage->en_deplacement = 2;
        if (*frame_counter_street>200)
        {
            personnage->en_deplacement = 2;
            *frame_counter_street = 0;
        }
    }
}

void hadoken(t_personnage_street_f* personnage1, t_personnage_street_f* personnage2, BITMAP* buffer, BITMAP* hadoken)
{
    int vitesse = 1;
    int cooldown = 1000;
    if (key[KEY_DOWN] && personnage1->projectile==false)
    {
        personnage1->y_hadoken = personnage1->y + 115;          ///         + constantes pour que le projectile parte depuis les bras
        personnage1->x_hadoken = personnage1->x+70;
        personnage1->projectile = true;
    }
    if (personnage1->projectile)
    {
        personnage1->x_hadoken += vitesse;
        if (personnage1->x_hadoken >= SCREEN_W+ cooldown + hadoken->w) personnage1->projectile=false;
    }

    if (key[KEY_S] && personnage2->projectile==false)
    {
        personnage2->y_hadoken = personnage2->y + 115;          ///         + constantes pour que le projectile parte depuis les bras
        personnage2->x_hadoken = personnage2->x+90;
        personnage2->projectile = true;
    }
    if (personnage2->projectile)
    {
        personnage2->x_hadoken -= vitesse;
        if (personnage2->x_hadoken <  -cooldown- hadoken->w) personnage2->projectile=false;
    }

    draw_sprite(buffer, hadoken, personnage1->x_hadoken, personnage1->y_hadoken);
    draw_sprite_h_flip(buffer, hadoken, personnage2->x_hadoken, personnage2->y_hadoken);
}

void init_street_f(t_personnage_street_f* personnageStreetF, int joueur_1, int joueur_2)
{
    for (int i = 0; i < 4; ++i) {
        personnageStreetF[i].x = (SCREEN_W / 2) - 10;
        personnageStreetF[i].x_hadoken = 0;
        personnageStreetF[i].y_hadoken = -400;
        personnageStreetF[i].y = 400;
        personnageStreetF[i].en_deplacement = 0;
        personnageStreetF[i].vie = 10;
        personnageStreetF[i].en_train_de_sauter = false;
        personnageStreetF[i].vers_le_haut = false;
        personnageStreetF[i].projectile = false;
    }
    personnageStreetF[joueur_1].x=0;
    personnageStreetF[joueur_2].x=400;
}


/// paris zombique (chloe)

void init_zombies(t_fille *fille, t_garcon *garcon, t_squelette *squelette, t_zombie *zombie, int* deplacement_zombies, int* joueur_def, int* joueur_vic)
{
    (*fille).frameZombie = 0;
    (*fille).x = -30;
    (*fille).y = SCREEN_H / 2 + 20;
    (*fille).x = -18;
    (*fille).y = 365;
    (*garcon).frameZombie = 0;
    (*garcon).x = 0;
    (*garcon).y = 95;
    (*garcon).y = 150;
    (*squelette).frameZombie = 0;
    (*squelette).x = 0;
    (*squelette).y = 200;
    (*squelette).x = 5;
    (*squelette).y = 290;
    (*zombie).frameZombie = 0;
    (*zombie).x = 0;
    (*zombie).y = 150;
    (*zombie).x = 5;
    (*zombie).y = 220;

    *deplacement_zombies = 1;
    *joueur_def = -1;
    *joueur_vic = -1;

}

void separerBitapZombie(t_fille *fille, t_garcon *garcon, t_squelette *squelette, t_zombie *zombie,BITMAP *bitmap, BITMAP *bitmap2, BITMAP *bitmap3, BITMAP *bitmap4) {
    int largeur_fille = 75;
    int hauteur_fille = 70;
    for (int j = 0; j < 11; j++) {
        fille->droite[j] = create_sub_bitmap(bitmap, j * largeur_fille, 325 + hauteur_fille, largeur_fille,
                                             hauteur_fille);
    }
    int largeur_garcon = 65;
    int hauteur_garcon = 70;
    for (int j = 0; j < 11; j++) {
        garcon->droite[j] = create_sub_bitmap(bitmap2, j * largeur_garcon, 325 + hauteur_garcon, largeur_garcon,
                                              hauteur_garcon);
    }
    int largeur_squelette = 62;
    int hauteur_squelette = 80;
    for (int j = 0; j < 11; j++) {
        squelette->droite[j] = create_sub_bitmap(bitmap3, j * largeur_squelette + 35, hauteur_squelette,
                                                 largeur_squelette, hauteur_squelette);
    }
    int largeur_zombie = 48;
    int hauteur_zombie = 200;
    for (int j = 0; j < 4; j++) {
        zombie->droite[j] = create_sub_bitmap(bitmap4, j * largeur_zombie + 10, hauteur_zombie, largeur_zombie,
                                              hauteur_zombie);
    }
}

void dessiner_zombie(t_fille *fille, t_garcon *garcon, t_squelette *squelette, t_zombie *zombie, BITMAP *buf_zombie) {
    BITMAP *zombie1;
    BITMAP *zombie2;
    BITMAP *zombie3;
    BITMAP *zombie4;
    zombie1 = fille->droite[fille->frameZombie];
    masked_blit(zombie1, buf_zombie, 0, 0, fille->x, fille->y, zombie1->w, zombie1->h);
    zombie2 = garcon->droite[garcon->frameZombie];
    masked_blit(zombie2, buf_zombie, 0, 0, garcon->x, garcon->y, zombie2->w, zombie2->h);
    zombie3 = squelette->droite[squelette->frameZombie];
    masked_blit(zombie3, buf_zombie, 0, 0, squelette->x, squelette->y, zombie3->w, zombie3->h);
    zombie4 = zombie->droite[zombie->frameZombie];
    masked_blit(zombie4, buf_zombie, 0, 0, zombie->x, zombie->y, zombie2->w, zombie2->h);
}

void maj_zombbie(t_fille *fille, t_garcon *garcon, t_squelette *squelette, t_zombie *zombie) {
    int vitesse = rand() % 10;
    int vitesse2 = rand() % 10;
    int vitesse3 = rand() % 10;
    int vitesse4 = rand() % 10;
    fille->x += vitesse;
    garcon->x += vitesse2;
    garcon->zombie_qui_court = 1;
    squelette->x += vitesse3;
    zombie->x += vitesse4;
}

int victoire_zombie(t_fille *fille, t_garcon *garcon, t_squelette *squelette, t_zombie *zombie, int* deplacement_zombies) {
    fille->gagnant = 950;
    garcon->gagnant = 945;
    squelette->gagnant = 940;
    zombie->gagnant = 947;
    if (*deplacement_zombies == 1) {
        if (squelette->x >= squelette->gagnant && garcon->x != garcon->gagnant && fille->x != fille->gagnant && zombie->x != zombie->gagnant)
        {
            *deplacement_zombies = 0;
            return 1;
        }
        else if (fille->x >= fille->gagnant && garcon->x != garcon->gagnant && squelette->x != squelette->gagnant && zombie->x != zombie->gagnant)
        {
            *deplacement_zombies = 0;
            return 2;
        }
        else if (zombie->x >= zombie->gagnant && garcon->x != garcon->gagnant && squelette->x != squelette->gagnant && fille->x != fille->gagnant)
        {
            *deplacement_zombies = 0;
            return 3;
        }
        else if (garcon->x >= garcon->gagnant && fille->x != fille->gagnant && squelette->x != squelette->gagnant && zombie->x != zombie->gagnant)
        {
            *deplacement_zombies = 0;
            return 4;
        }
        else return 0;
    }
}


///  traversee de riviere

void init_sprite (t_joueurs *personnage, BITMAP* bitmap, int taille_w, int taille_h, t_jeu *jeu)
{
    for (int i = 0; i < 9; ++i) {
        personnage->haut[i] = create_sub_bitmap(bitmap, i * taille_w, 518, taille_w, taille_h);
        personnage->bas[i] = create_sub_bitmap(bitmap, i * taille_w, 648, taille_w, taille_h);
        personnage->gauche[i] = create_sub_bitmap(bitmap, i * taille_w, 584, taille_w, taille_h);
        personnage->droite[i] = create_sub_bitmap(bitmap, i * taille_w, 711, taille_w, taille_h);
    }
}

void affichage_perso_t(t_joueurs* joueurs, BITMAP* buffer, int taille_w, int taille_h, t_jeu *jeu, BITMAP* test)
{
    BITMAP* PERSO ;

    switch (joueurs->direction)
    {
        case 0:
            PERSO = joueurs->haut[joueurs->frame];
            break;
        case 1:
            PERSO= joueurs->bas[joueurs->frame];
            break;
        case 2:
            PERSO = joueurs->gauche[joueurs->frame];
            break;
        case 3:
            PERSO = joueurs->droite[joueurs->frame];
            break;
        case 4:
            PERSO=joueurs->haut[6];
            break;
    }
    masked_stretch_blit(test, buffer,0,0,taille_w,taille_h, joueurs->x, joueurs->y, taille_w*1.5 , taille_h*2);
}

void deplacement_depart(t_joueurs *personnage, t_jeu *jeu)
{
    int vitesse = 1;
    personnage->deplacement = 0;
    if(personnage->deplacement==0) personnage->direction=4;
    if (key[KEY_LEFT]) {
        personnage->x -= vitesse;
        personnage->direction = 2;
        personnage->deplacement = 1;
    }
    if (key[KEY_RIGHT]) {
        personnage->x += vitesse;
        personnage->direction = 3;
        personnage->deplacement = 1;
    }
}

void deplacement_b(t_bidon *bidon,t_mouv *mouv, BITMAP* buffer,int j){
    if(mouv->frame==5){
        if(j%2==0){
            bidon[j].x=bidon[j].x+mouv->dx[j];
            if(bidon[j].x>820 ){
                bidon[j].x=-600;
                bidon[j].presence=1;
            }
        }else
        {
            bidon[j].x=bidon[j].x-mouv->dx[j];
            if(bidon[j].x<-400 ){
                bidon[j].x=820;
                bidon[j].presence=1;
            }
        }

    }

    if(bidon[j].presence==1) {
        switch (j) {
            case 0 :
                mouv->dx[j]=rand()%2+1;
                break;
            case 1:
                mouv->dx[j]=rand()%3+2;
                break;
            case 2:
                mouv->dx[j]=rand()%4+3;
                break;
            case 3:
                mouv->dx[j]=rand()%5+4;
                break;
        }
        bidon[j].presence=0;
    }
    masked_blit(bidon[j].bidon,buffer,0,0,bidon[j].x,bidon[j].y,buffer->w,buffer->h);
}

int deplacement_s(t_joueurs *joueurs, t_bidon bidon[], int direction, t_jeu *jeu, BITMAP *buffer){
    int xbidon1;
    int xbidon2;
    int xbidon3;
    xbidon1=bidon[jeu->cmpt].x;
    xbidon2=bidon[jeu->cmpt].x+320;
    xbidon3=bidon[jeu->cmpt].x+520;
    if(key[KEY_UP]&& xbidon1< joueurs->x && xbidon1> joueurs->x-150 && bidon[jeu->cmpt].y>joueurs->y ){
        direction=1;
        jeu->cmpt++;
        rest(100);
    }else if (key[KEY_UP]&& xbidon2< joueurs->x && xbidon2> joueurs->x-150 && bidon[jeu->cmpt].y>joueurs[jeu->tour].y  ){
        direction=2;
        jeu->cmpt++;
        rest(100);
    }else if (key[KEY_UP]&& xbidon3< joueurs->x && xbidon3> joueurs->x-150 && bidon->y>joueurs->y ){
        direction=3;
        jeu->cmpt++;
        rest(100);
    }else if (key[KEY_UP]&& jeu->cmpt>=4){
        ////c ets la victoire
        direction=4;
        jeu->victoir=1;
        rest(100);
    }else if (key[KEY_UP]){
        jeu->defaite=1;
        ///// c est la defaite
    }
    return direction;
}

void mouv2(int direction, t_joueurs *joueurs, t_bidon bidon[], BITMAP* buffer, t_jeu *jeu){
    switch (direction) {
        case 1:
            jeu->etape=1;
            break;
        case 2:
            jeu->etape=2;
            break;
        case 3:
            jeu->etape=3;
            break;
        case 4:
            jeu->etape=4;
            break;
        case 5:
            jeu->etape=5;

    }
    switch (jeu->etape) {
        case 1:
            joueurs->x=bidon[(jeu->cmpt-1)].x;
            joueurs->y=bidon[(jeu->cmpt-1)].y-80;
            break;
        case 2:
            joueurs->x=bidon[(jeu->cmpt-1)].x+320;
            joueurs->y=bidon[(jeu->cmpt-1)].y-80;
            break;
        case 3:
            joueurs->x=bidon[(jeu->cmpt-1)].x+520;
            joueurs->y=bidon[(jeu->cmpt-1)].y-80;
            break;
        case 4:
            joueurs->y=90;
        case 5:
            rectfill(buffer,0,0,200,200, makecol(255,0,0));
    }
}

void mort(t_joueurs *joueurs, BITMAP* buffer, t_jeu *jeu){
    if(joueurs->x>800 || joueurs->x<0)
    {
        jeu->defaite=1;
    }
}

void init_tot(t_bidon bidon[], t_joueurs *joueurs, t_jeu *jeu, t_mouv * mouv, int *direction, int* joueur_def, int* joueur_vic, int* round){
    jeu->tour=0;
    for (int i = 0; i < 4; ++i) {
        bidon[i].y=450-i*70;
        if(i%2==0){
            bidon[i].x=-400;
        }else{
            bidon[i].x=900;
        }
    }
    joueurs->x=SCREEN_W/2+100;
    joueurs->y=415;
    joueurs->frame=0;
    joueurs->direction = 0;
    joueurs->frame = 0;
    mouv->frame=0;
    jeu->cmpt=0;
    *direction=0;

    *joueur_def = -1;
    *joueur_vic = -1;;
    *round = 1;
}


/// tir au ballon


void victoire_ballons(const int *tempsTotal) {
    if (tempsTotal[0] < tempsTotal[1] && tempsTotal[0] != 0) {
        printf("Le joueur 1 a gagné !\n");
        allegro_message("Bravo joueur 1!");
    } else if (tempsTotal[1] < tempsTotal[0] && tempsTotal[1] != 0) {
        printf("Le joueur 2 a gagné !\n");
        allegro_message("Bravo joueur 2!");
    } else if ((tempsTotal[1] < tempsTotal[0] && tempsTotal[1] == 0)) {
        allegro_message("victoire du joueur 1 par abandon");
    } else if ((tempsTotal[0] < tempsTotal[1] && tempsTotal[0] == 0)) {
        allegro_message("victoire du joueur 2 par abandon");
    } else {
        printf("Égalité !\n");
        allegro_message("Egalité!");
    }
}

t_ballons *creerBallons() {
    t_ballons *acteur;
    int r = 40;
    acteur = (t_ballons *) malloc(1 * sizeof(t_ballons));
    acteur->posx = rand() % (SCREEN_W - 2 * r) + r;
    acteur->posy = rand() % (SCREEN_H - 2 * r) + r;

    do {
        acteur->depx = rand() % 17 - 5;
        acteur->depy = rand() % 17 - 5;
    } while (acteur->depx == 0 || acteur->depy == 0);

    acteur->rayon = r;
    acteur->affichage = 1;

    return acteur;
}

void remplirTabBallons(t_ballons *tab[10]) {
    int i;
    for (i = 0; i < 10; i++)
        tab[i] = creerBallons();
}

void actuBallons(t_ballons *acteur) {
    if (acteur->affichage == 1) {
        if ((acteur->posx - acteur->rayon < 0 && acteur->depx < 0) ||
            (acteur->posx + acteur->rayon > SCREEN_W && acteur->depx > 0))
            acteur->depx = -acteur->depx;

        if ((acteur->posy - acteur->rayon < 0 && acteur->depy < 0) ||
            (acteur->posy + acteur->rayon > SCREEN_H && acteur->depy > 0))
            acteur->depy = -acteur->depy;

        acteur->posx = acteur->posx + acteur->depx;
        acteur->posy = acteur->posy + acteur->depy;
    } else {
        acteur->posx = -35;
        acteur->posy = -35;
        acteur->depx = 0;
        acteur->depy = 0;
    }
}

void actuTabBallons(t_ballons *tab[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        actuBallons(tab[i]);
    }
}

void dessinerBallons(BITMAP *buffer, t_ballons *acteur) {
    circlefill(buffer, acteur->posx, acteur->posy, acteur->rayon, acteur->couleur);
}

void dessinerTabBallons(BITMAP *buffer, t_ballons *tab[10]) {
    int i;
    for (i = 0; i < 10; i++)
        dessinerBallons(buffer, tab[i]);
}

void plusDeBallons(BITMAP *buffer, t_ballons *acteur) {
    if (mouse_b & 1) {
        if (getpixel(buffer, mouse_x, mouse_y) == acteur->couleur) {
            acteur->affichage = 0;
        }
    }
}

void TabPlusDeBallons(BITMAP *buffer, t_ballons *tab[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        plusDeBallons(buffer, tab[i]);
    }
}


//// stat
void statistique(FILE *fichier,t_personnage personnage[],int choix_jeu,int choix_tour,double performance){
    fichier= fopen("../statistique.txt","a+");
    char nom_jeu[20];
    if (fichier != NULL) {

        switch (choix_jeu) {
            case 1:
                strcpy(nom_jeu,"guitare");
                break;
            case 2:
                strcpy(nom_jeu,"riviere");
                break;
            case 3:
                strcpy(nom_jeu,"jacpot");
                break;
            case 4:
                strcpy(nom_jeu,"bird");
                break;
            case 6:
                strcpy(nom_jeu,"street");
                break;
            case 7 :
                strcpy(nom_jeu,"parie");
                break;
            case 8:
                break;
        }
        fprintf(fichier,"%f   %s  %s  \n ",performance,personnage[choix_tour].nom,nom_jeu);

    } else {
        printf("Erreur lors de la création du fichier.\n");
        //return 1;
    }

    fclose(fichier);
}



int main() {
    ///         Initialisations
    initialisation();
    srand(time(NULL));

    ///         Creation des BITMAP
    // sprites perso
    BITMAP* sprite_octave = load_bitmap("../sprite_octave.bmp", NULL);
    BITMAP* sprite_marina = load_bitmap("../sprite_marina.bmp", NULL);
    BITMAP* sprite_mathis = load_bitmap("../sprite_mathis.bmp", NULL);
    BITMAP* sprite_chloe = load_bitmap("../sprite_chloe.bmp", NULL);

    BITMAP* BG_accueil = load_bitmap("../BG_accueil.bmp", NULL);
    BITMAP* BG_choix_du_joueur = load_bitmap("../BG_choix_du_joueur.bmp", NULL);
    BITMAP* regles = load_bitmap("../regles.bmp", NULL);

    // map
    BITMAP* map = load_bitmap("../map.bmp", NULL);
    BITMAP* collision = load_bitmap("../map.collision.bmp", NULL);
    BITMAP* image_vie = load_bitmap("../vie.bmp", NULL);

    // templates debut
    BITMAP* template_gh = load_bitmap("../guitarherobmp.bmp",NULL);
    BITMAP* template_jackpot = load_bitmap("../Jackpot.bmp", NULL);
    BITMAP* template_fp = load_bitmap("../flappy_bird_debut.bmp", NULL);
    BITMAP* template_pz = load_bitmap("../paris_zombique.bmp", NULL);
    BITMAP* template_tr = load_bitmap("../traverse_riviere.bmp", NULL);
    BITMAP* template_st = load_bitmap("../street_fighter.bmp", NULL);
    BITMAP* template_tb = load_bitmap("../template_tr.bmp", NULL);


    // template fin
    BITMAP *fond_fin = load_bitmap("../template fin.bmp", NULL);
    BITMAP *victoire = load_bitmap("../victoire.bmp", NULL);
    BITMAP *defaite = load_bitmap("../defaite.bmp", NULL);

    BITMAP* fin_jeu = load_bitmap("../FIN.bmp", NULL);

    // guitar hero
    BITMAP *fond_gh= load_bitmap("../fond.bmp", NULL);
    BITMAP *fond_collision_gh= load_bitmap("../fond_bis.bmp", NULL);
    BITMAP *touches = load_bitmap("../sprite_touche.bmp", NULL);

    // jackpot
    BITMAP* BG_casino = load_bitmap("../BG_casino.bmp", NULL);
    BITMAP* Message_attente_casino = load_bitmap("../Message_attente_casino.bmp", NULL);

    // flappy bird
    BITMAP *fond_flappy= load_bitmap("../fond_flappybird.bmp", NULL);
    BITMAP *sprite_oiseau = load_bitmap("../flappy.bmp", NULL);
    BITMAP* img_tuyaux = load_bitmap("../tuyaux.bmp", NULL);

    // street fighter
    BITMAP* background_st = load_bitmap("../background_street_f.bmp", NULL);
    BITMAP* hadoken_sprite = load_bitmap("../hadoken.bmp", NULL);

    // paris zombique
    BITMAP *paris_zombique = load_bitmap("../BG_paris.bmp", NULL);
    BITMAP *sprite = load_bitmap("../sprite.bmp", NULL);
    BITMAP *sprite2 = load_bitmap("../sprite2.bmp", NULL);
    BITMAP *sprite3 = load_bitmap("../sprite3.bmp", NULL);
    BITMAP *sprite4 = load_bitmap("../sprite4.bmp", NULL);

    // traverse riviere
    BITMAP* fond_tr = load_bitmap("../fond_tr.bmp",NULL);

    // tir au ballon
    BITMAP *fond_tir = load_bitmap("../BG_tirballons.bmp", NULL);

    // buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);




    ///         Definition de la structure
    t_personnage personnage[4];
    for (int i = 0; i < 4; ++i) {
        personnage[i].x = (SCREEN_W / 2) - 10;
        personnage[i].y = 240;
        personnage[i].direction = 1;
        personnage[i].en_deplacement = 1;
        personnage[i].frame = 0;
        personnage[i].nb_vie= 5;
        personnage[i].frame1 = 0;
        personnage[i].frame2 = 0;
    }


    ///         variables (pour tout le jeu)
    int vaincqueur = 0;
    int frame_counter = 0;
    int taille_h = 68;
    int taille_w = 64;
    int ecart = 50;
    bool gestion_vie = true;
    int joueur_def = -1;
    int joueur_vic = -1;

    // tours
    int joueur_tour = 1;
    int inv_joueur_tour;
    int tour = 1;
    int marche = 0;
    int clic = 0;

    ///         variables pour accueil
    int clic_dans_accueil = 0;
    int choix_perso = 0;

    int joueur_1=-1;
    int joueur_2=-1;

    ///         variable pour map
    int interdit;
    int choix_jeu = 0;

    ///         variable loading
    t_rat rat;
    init_loading(&rat, buffer);

    ///        variable pour template fin
    // victoire
    int taille_vic =0;
    float depart_vx = 340;
    int depart_vy = 100;
    // defaite
    int taille_def =0;
    float departdx = 340;
    int departdy = 180;
    int vic_ou_def =0;

    int frame1_counter = 0;
    int frame1_counter2 = 0;


    ///         variables guitar hero
    //parametre struct touche
    t_touche touche[TAILLE];
    for(int i=0; i<TAILLE; i++)
    {
        touche[i].vie = 0;
        separer_couleur(&touche[i], touches);
    }
    int j; // pour plusieurs touches affichées sur lecran en simultané
    int press; // pour detecter bonne touche
    int round_gh;
    int joueur_vic_gh;
    int joueur_def_gh;

    clock_t temps_1_gh, temps_1bis_gh, temps_2_gh, temps_2bis_gh;
    double temps_final1_gh, temps_final2_gh;

    ///         variables jackpot
    t_symboles_casino symbolesCasino;
    int taille_hauteur_j;
    int frame_counter_jackpot;
    int deplacement_g;
    int deplacement_m;
    int deplacement_d;
    int nb_rand_1;
    int nb_rand_2;
    int nb_rand_3;

    init_jackpot(&symbolesCasino, &taille_hauteur_j, &frame_counter_jackpot, &deplacement_g, &deplacement_m, &deplacement_d, &nb_rand_1, &nb_rand_2, &nb_rand_3);


    ///         variable flappy bird
    t_bird bird;
    int joueur_vic_fp;
    int joueur_def_fp;
    int re_fp;
    int round_fb = 1;
    init_flappy_bird(&bird, &joueur_def_fp, &joueur_vic_fp, &re_fp, &round_fb);
    separer_bitmap_bird(&bird, sprite_oiseau);

    t_tuyaux tuyaux[4];
    for (int i = 0; i < 4; ++i) {
        tuyaux[i].x = 170 + i * 200;
        tuyaux[i].y = 300 + rand() % 200;
    }
    int frame_counter_bird= 0;
    int ecartement = 100;


    clock_t temps_1_fp, temps_1bis_fp, temps_2_fp, temps_2bis_fp;
    double temps_final1_fp, temps_final2_fp;

    ///         variable pour surprise
    t_surprise surprise;
    surprise.surpris = load_bitmap("../surprise.bmp", NULL);
    int depart1 = 330;
    int depart2 = 250;

    ///        variable street fighter
    t_personnage_street_f personnageStreetF[4];
    init_street_f(personnageStreetF, joueur_1, joueur_2);
    int frame_counter_street=0;
    int frame_counter_street2=0;
    creation_sprite_perso_street_f(&personnageStreetF[0],sprite_octave,taille_w, taille_h);
    creation_sprite_perso_street_f(&personnageStreetF[1],sprite_marina,taille_w, taille_h);
    creation_sprite_perso_street_f(&personnageStreetF[2],sprite_mathis,taille_w, taille_h);
    creation_sprite_perso_street_f(&personnageStreetF[3],sprite_chloe,taille_w, taille_h);


    ///        variables paris zombique
    t_fille fille;
    t_garcon garcon;
    t_squelette squelette;
    t_zombie zombie;
    int deplacement_zombies;
    int joueur_vic_pz;
    int joueur_def_pz;

    init_zombies(&fille, &garcon, &squelette, &zombie, &deplacement_zombies, &joueur_def_pz,&joueur_vic_pz);
    separerBitapZombie(&fille, &garcon, &squelette, &zombie, sprite, sprite2, sprite3, sprite4);

    int zombie_compteur = 0;
    int zombie_avance_ou_pas = 0;
    int zombieGagnant;
    int pari_joueur1 = 0;
    int pari_joueur2 = 0;
    int joueur_actif = 1;

    ///      variables traverse riviere
    t_bidon bidon[4];
    t_mouv mouv;
    t_joueurs joueurs[2];
    //joueurs[0] = joueurs[joueur_tour];
    //joueurs[1] = joueurs[inv_joueur_tour];
    t_jeu jeu;
    int direction=0;

    int round_tr;
    int joueur_vic_tr;
    int joueur_def_tr;

    clock_t temps_1_tr, temps_1bis_tr, temps_2_tr, temps_2bis_tr;
    double temps_final1_tr, temps_final2_tr;


    init_tot(bidon,joueurs,&jeu,&mouv,&direction, &joueur_def_tr, &joueur_vic_tr, &round_tr);
    for (int i = 0; i < 4; ++i) {
        if(i%2==0){
            bidon[i].bidon=load_bitmap("../deux_sacs.bmp",NULL);
        }else{
            bidon[i].bidon=load_bitmap("../deux_canettes.bmp",NULL);
        }
    }

    int frame_counteur=0;
    for (int i = 0; i < 4; ++i) {
        mouv.dx[i]=3+i;
        bidon[i].presence=0;
    }





    ///         variables tir au ballon
    t_ballons *mesActeurs[10];
    t_ballons **tab_acteurs = malloc(10 * sizeof(t_ballons));

    for (int i = 0; i < 10; i++) {
        tab_acteurs[i] = creerBallons();
    }
    tab_acteurs[0]->couleur = makecol(0, 128, 0);     // vert
    tab_acteurs[1]->couleur = makecol(255, 0, 0);     // rouge
    tab_acteurs[2]->couleur = makecol(255, 105, 180); // rose
    tab_acteurs[3]->couleur = makecol(255, 255, 0);   // jaune
    tab_acteurs[4]->couleur = makecol(255, 165, 0);   // orange
    tab_acteurs[5]->couleur = makecol(0, 255, 255);   // cyan
    tab_acteurs[6]->couleur = makecol(0, 0, 255);     // bleu
    tab_acteurs[7]->couleur = makecol(160, 82, 45);   // marron
    tab_acteurs[8]->couleur = makecol(255, 255, 255); // blanc
    tab_acteurs[9]->couleur = makecol(128, 128, 128); // gris

    remplirTabBallons(mesActeurs);
    int temps = 0;



    ///         Creation des sprites
    creation_sprite_perso(&personnage[0], sprite_octave, taille_w, taille_h);
    creation_sprite_perso(&personnage[1], sprite_marina, taille_w, taille_h);
    creation_sprite_perso(&personnage[2], sprite_mathis, taille_w, taille_h);
    creation_sprite_perso(&personnage[3], sprite_chloe, taille_w, taille_h);

    creation_sprite_danse(&personnage[0], sprite_octave);
    creation_sprite_danse(&personnage[1], sprite_marina);
    creation_sprite_danse(&personnage[2], sprite_mathis);
    creation_sprite_danse(&personnage[3], sprite_chloe);
    ///stat
    FILE *fichier=NULL;
    fichier= fopen("../statistique.txt","a+");
    t_stat stat;int choix_ou_pas=0;

    while (!key[KEY_ESC])
    {
        /// Programme pour afficher l'accueil et gestion du lancement du jeu

        if(clic_dans_accueil==0)        /// Programme pour afficher l'accueil et gestion du lancement du jeu
        {
            if(mouse_x>110 && mouse_x<400 && mouse_y>480 && mouse_y<560 && mouse_b==1) clic_dans_accueil = 1;
            if(mouse_x>130 && mouse_x<360 && mouse_y>340 && mouse_y<420 && mouse_b==1) clic_dans_accueil = 2;
            else blit(BG_accueil,buffer,0,0,0,0,BG_accueil->w,BG_accueil->h);
        }
        else if (clic_dans_accueil==1)     /// choix du joueur
        {
            blit(BG_choix_du_joueur, buffer,0,0,0,0,BG_choix_du_joueur->w, BG_choix_du_joueur->h);
            if(choix_ou_pas==0) {
                textout_centre_ex(buffer, font, "Joueur 1, quel est votre pseudo?", 200, 230, makecol(255, 255, 255),
                                  -1);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                entrer_le_nom(personnage, buffer);
                printf(" joueur %d ,%s", joueur_tour, personnage[joueur_tour - 1].nom);
                printf("joueur %d,%s", joueur_tour + 1, personnage[joueur_tour].nom);
                readkey();
                choix_ou_pas=1;
            }
            choix_perso = detection_changement(choix_perso);

            maj_personnage(&personnage[choix_perso]);

            affichage_perso(&personnage[choix_perso],buffer, taille_w, taille_h, SCREEN_W/2, SCREEN_H/2);
            affichage_perso_mini(&personnage[joueur_1],buffer, taille_w, taille_h, joueur_1, 82,327);
            affichage_perso_mini(&personnage[joueur_2],buffer, taille_w, taille_h, joueur_2, 82,470);

            detection_selection(&joueur_1,&joueur_2,choix_perso,buffer);


            rest(1);

            if (joueur_1!=-1 && joueur_2!=-1)
            {
                loading(&rat, buffer);
                clic_dans_accueil = 4;
                home_pos(personnage);
            }
        }
        else if (clic_dans_accueil==2)
        {
            blit(regles,buffer,0,0,0,0,SCREEN_W, SCREEN_H);
            if(mouse_x>700 && mouse_x<900 && mouse_y>500 && mouse_y<650 && mouse_b) clic_dans_accueil = 0;
        }
        else if (clic_dans_accueil==3)
        {

        }
        else if (clic_dans_accueil==4) {     /// map

            
            stretch_blit(map, buffer, 0, 0, map->w, map->h, 0, 0, buffer->w, buffer->h);

            joueur_tour = changement_tour_joueur(&tour, joueur_1, joueur_2);
            inv_joueur_tour = inv_changement_tour_joueur(&tour, joueur_1, joueur_2);

            interdit = collision_interdit(personnage, collision, joueur_tour);

            if(choix_jeu==0) maj_perso_map(&personnage[joueur_tour], interdit);

            affichage_perso(&personnage[joueur_tour], buffer, taille_w, taille_h, 70, 70);

            gestion_vie_personnage(buffer, personnage, joueur_tour,image_vie, 0, &gestion_vie, 0);
            gestion_vie = true;

            choix_jeu = detection_mini_jeu(personnage, collision, joueur_tour);

            if (choix_jeu != 0) clic_dans_accueil = 5;

            rest(1);

            clic=0; // pour rentrer dans un jeu (start)
            /// variables pour pouvoir recommencer un meme jeu
            init_loading(&rat, buffer);
            init_guitar_hero(touche, &j, &press, &round_gh, &joueur_def_gh, &joueur_def_gh);
            init_flappy_bird(&bird, &joueur_def_fp, &joueur_vic_fp, &re_fp, &round_fb);
            init_street_f(personnageStreetF, joueur_1, joueur_2);
            init_jackpot(&symbolesCasino, &taille_hauteur_j, &frame_counter_jackpot, &deplacement_g, &deplacement_m, &deplacement_d, &nb_rand_1, &nb_rand_2, &nb_rand_3);
            init_zombies(&fille, &garcon, &squelette, &zombie, &deplacement_zombies, &joueur_def_pz, &joueur_vic_pz);
            init_tot(bidon, joueurs, &jeu, &mouv, &direction, &joueur_def_tr, &joueur_vic_tr,&round_tr);
            init_vicoudef(&taille_vic, &depart_vx, &depart_vy , &taille_def, &departdx, &departdy, &vic_ou_def );

            vaincqueur = condition_de_victoire_globale(personnage, joueur_1, joueur_2);
            if (vaincqueur != 0) clic_dans_accueil = 6;

        }
        else if(clic_dans_accueil==5)    /// tous les mini jeux
        {
            switch (choix_jeu)
            {
                case 1: ////////////// guitar hero (marina)
                    blit(template_gh,buffer,0,0,0,0,SCREEN_W, SCREEN_H);
                    show_mouse(buffer);
                    blit(buffer,screen,0,0,0,0,screen->w,screen->h);

                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if(mouse_x>630 && mouse_x<760 && mouse_y>460 && mouse_y<510 && mouse_b || clic==1){
                        clic = 1;
                        loading(&rat, buffer);
                        if(clic == 1){
                            temps_1_gh = clock(); // debut temps premier joueur;
                            clic = 2;
                        }
                        while(touche[j].y != 600 && choix_jeu==1  && clic_dans_accueil!=4)
                        {
                            stretch_blit(fond_gh, buffer, 0, 0, fond_gh->w, fond_gh->h, 0, 0, buffer->w, buffer->h);
                            /// deplacement (repetition)
                            // k, h pour eviter pb avec le j++, avant fin du mvt -> j.y n'atteind jamais 550 (touche)
                            touche[j].taille += 0.15;
                            for(int k=0; k<TAILLE; k++)
                            {
                                if(j>k) touche[j-(k+1)].taille += 0.15;
                            }
                            deplacer_touche(&touche[j], touche[j].frame, touches, buffer);
                            for(int h=0; h<TAILLE; h++)
                            {
                                if(j>h) deplacer_touche(&touche[j-(h+1)], touche[j-(h+1)].frame, touches, buffer);
                            }
                            /// collision
                            for (int p = 0; p < TAILLE; ++p) {
                                if(touche[p].y >= 500 && touche[p].y <= 550)
                                {
                                    press = p;
                                    break;
                                }
                            }
                            collision_gh(touche, fond_collision_gh, press);
                            if(touche[press].y > 550)
                            {
                                if (touche[press].passer == 1) touche[press].x = 1000;
                                if (touche[press].passer == 0) touche[press].vie = 1;
                            }
                            ///  repetition
                            if(touche[j].y == 350) j=j+1;
                            if(j==TAILLE) j=0;
                            ///  fin partie
                            for (int n = 0; n < TAILLE; ++n)
                            {
                                if(touche[n].vie == 1)
                                {
                                    if(round_gh == 2)
                                    {
                                        vic_ou_def = 1;
                                        if(clic_dans_accueil != 4)
                                        {
                                            if(clic == 2) {
                                                clic = 3;
                                                temps_2bis_gh = clock(); // fin temps deuxieme joueur

                                                temps_final1_gh = (float)(temps_1bis_gh - temps_1_gh)/CLOCKS_PER_SEC;
                                                temps_final2_gh = (float)(temps_2bis_gh - temps_2_gh)/CLOCKS_PER_SEC;
                                                stat.presence=0;
                                                if (temps_final1_gh >= temps_final2_gh) {
                                                    gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1, &gestion_vie, 0);
                                                    joueur_vic_gh = joueur_tour;
                                                    joueur_def_gh = inv_joueur_tour;
                                                } else {
                                                    gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1, &gestion_vie, 1);
                                                    joueur_def_gh = joueur_tour;
                                                    joueur_vic_gh = inv_joueur_tour;
                                                }
                                            }
                                            if(stat.presence==0){
                                                statistique(fichier,personnage,choix_jeu,joueur_tour,temps_final1_gh);
                                                statistique(fichier,personnage,choix_jeu,joueur_tour,temps_final2_gh);
                                                stat.presence=1;
                                            }
                                            stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,buffer->h);
                                            affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def, &depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);
                                            affichage_danse_fin(personnage, buffer, vic_ou_def,  joueur_vic_gh, joueur_def_gh);
                                            frame_count(personnage, &frame1_counter, &frame1_counter2);
                                            exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                                            show_mouse(buffer);
                                        }
                                    }
                                    if(round_gh == 1){
                                        temps_1bis_gh = clock(); // fin temps premier joueur
                                        rectfill(screen, 0, 0, 900, 650, makecol(40, 40, 40));
                                        textprintf_ex(buffer, font, 200, SCREEN_H/2, makecol(255, 255, 255), -1, "Le tour du prochain joueur va commencer prochainement preparez vous");
                                        j=0;
                                        init_guitar_hero(touche, &j, &press, &round_gh, &joueur_def_gh, &joueur_def_gh);
                                        round_gh = 2;
                                        rest(5000);
                                        temps_2_gh = clock(); // debut temps deuxieme joueur
                                    }
                                    break;
                                }
                            }
                            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
                            rest(1);
                        }
                    }
                    break;
                case 2: /////////////// traverse de riviere (mathis)


                    blit(template_tr,buffer,0,0,0,0,SCREEN_W, SCREEN_H);
                    show_mouse(buffer);
                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if(mouse_x>570 && mouse_x<700 && mouse_y>470 && mouse_y<520 && mouse_b || clic==1) {
                        if (clic == 0) {
                            loading(&rat, buffer);
                            clic = 1;
                            temps_1_tr = clock();
                        }

                        blit(fond_tr, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        deplacement_depart(joueurs, &jeu);

                        affichage_perso_t(joueurs, buffer, taille_w, taille_h, &jeu, sprite_mathis);
                        for (int i = 0; i < 4; ++i) {
                            deplacement_b(bidon, &mouv, buffer, i);
                        }

                        mouv2(deplacement_s(joueurs, bidon, direction, &jeu, buffer), joueurs, bidon, buffer, &jeu);
                        mort(joueurs, buffer, &jeu);
                        mouv.frame++;
                        if (mouv.frame > 7) {
                            mouv.frame = 0;
                        }

                        /// vic
                        if (jeu.victoir == 1) {
                            if (round_tr == 2) {
                                vic_ou_def = 1;
                                if (clic == 2) {
                                    clic = 3;
                                    temps_2bis_tr = clock(); // fin temps deuxieme joueur

                                    temps_final1_tr = temps_1bis_tr - temps_1_tr;
                                    temps_final2_tr = temps_2bis_tr - temps_2_tr;
                                    if (temps_final1_tr >= temps_final2_tr) {
                                        gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1,&gestion_vie, 0);
                                        joueur_vic_tr = joueur_tour;
                                        joueur_def_tr = inv_joueur_tour;
                                    } else {
                                        gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1,&gestion_vie, 1);
                                        joueur_def_tr = joueur_tour;
                                        joueur_vic_tr = inv_joueur_tour;
                                    }
                                    stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,buffer->h);
                                    affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,&depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);
                                    affichage_danse_fin(personnage, buffer, vic_ou_def, joueur_vic_tr, joueur_def_tr);
                                    frame_count(personnage, &frame1_counter, &frame1_counter2);
                                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                                    show_mouse(buffer);
                                }
                            }
                            if (round_tr == 1) {
                                temps_1bis_tr = clock(); // fin temps premier joueur
                                rectfill(screen, 0, 0, 900, 650, makecol(40, 40, 40));
                                textprintf_ex(buffer, font, 200, SCREEN_H/2, makecol(255, 255, 255), -1, "Le tour du prochain joueur va commencer prochainement preparez vous");                                jeu.victoir = 0;
                                init_tot(bidon, joueurs, &jeu, &mouv, &direction, &joueur_def_tr, &joueur_vic_tr,&round_tr);
                                round_tr = 2;
                                rest(5000);
                                temps_2_tr = clock(); // debut temps deuxieme joueur
                            }


                            break;
                        }

                        if(jeu.defaite == 1) {
                            stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w, buffer->h);
                            affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def, &depart_vx,
                                                 &depart_vy, &departdx, &departdy, 2);
                            affichage_danse_fin(personnage, buffer, 2, joueur_vic_tr, joueur_def_tr);
                            frame_count(personnage, &frame1_counter, &frame1_counter2);
                            exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                            show_mouse(buffer);
                        }

                        frame_counteur++;
                        if (frame_counteur >= 10)
                        {
                            if (joueurs[jeu.tour].deplacement == 1)
                            {
                                joueurs[jeu.tour].frame = ((joueurs[jeu.tour].frame + 1) % 9);
                            }
                            else joueurs[jeu.tour].frame = 1;
                            frame_counteur = 0;
                        }
                        blit(buffer, screen, 0, 0, 0, 0, 900, 650);
                    }
                    break;

                case 3: /////////////// jackpot (octave)
                    blit(template_jackpot, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if (mouse_x > 590 && mouse_x < 770 && mouse_y > 420 && mouse_y < 475 && mouse_b || clic == 1) {
                        if (clic == 0) {
                            loading(&rat, buffer);
                            clic = 1;
                        }
                        blit(BG_casino, buffer, 0, 0, 0, 0, BG_casino->w, BG_casino->h);

                        if (symbolesCasino.dans_la_partie == true) {
                            frame_counter_jackpot++;
                            if (symbolesCasino.en_deroulement == true) {
                                deplacement_symboles_casino(&symbolesCasino, &frame_counter_jackpot, buffer,
                                                            &deplacement_g, &deplacement_m, &deplacement_d,
                                                            taille_hauteur_j, nb_rand_1, nb_rand_2, nb_rand_3);
                                affichage_jackpot(&symbolesCasino, buffer, deplacement_g, deplacement_m,
                                                  deplacement_d, taille_hauteur_j);
                            }
                        } else affichage_avant_debut(&symbolesCasino, buffer, Message_attente_casino);

                        if (symbolesCasino.dans_la_partie == true && symbolesCasino.en_deroulement == false) {
                            frame_counter_jackpot++;
                            affichage_jackpot(&symbolesCasino, buffer, 25 + ((deplacement_g) / 75) * 75,
                                              25 + ((deplacement_m) / 75) * 75, 25 + ((deplacement_d) / 75) * 75,
                                              taille_hauteur_j);
                            verif_tirage_gagnant(25 + ((deplacement_g) / 75) * 75, 25 + ((deplacement_m) / 75) * 75,
                                                 25 + ((deplacement_d) / 75) * 75, &symbolesCasino);

                            if (frame_counter_jackpot >= 300) {
                                stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,
                                             buffer->h);
                                if (symbolesCasino.victory_casino == true) {
                                    vic_ou_def = 1;
                                    affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,
                                                         &depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);
                                    affichage_danse_fin(personnage, buffer, 3, joueur_tour, joueur_2);
                                    rest(1);
                                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                                    gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1,
                                                           &gestion_vie, -1);
                                } else if (symbolesCasino.victory_casino == false) {
                                    vic_ou_def = 2;
                                    affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,
                                                         &depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);
                                    affichage_danse_fin(personnage, buffer, vic_ou_def, joueur_tour, joueur_2);
                                    rest(1);
                                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                                    gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1,
                                                           &gestion_vie, 1);
                                }
                            }
                        }
                    }
                    break;

                case 4: //////////// flappy bird (marina)
                    blit(template_fp, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    show_mouse(buffer);

                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if (mouse_x > 570 && mouse_x < 700 && mouse_y > 470 && mouse_y < 520 && mouse_b || clic == 1) {
                        if (clic == 0) {
                            loading(&rat, buffer);
                            clic = 1;
                            temps_1_fp = clock(); // debut temps premier joueur
                        }
                        if(re_fp==0) re_fp = 1;

                        stretch_blit(fond_flappy, buffer, 0, 0, fond_flappy->w, fond_flappy->h, 0, 0, buffer->w,
                                     buffer->h);

                        /// deplacement tuyaux
                        for (int i = 0; i < 4; ++i) {
                            masked_blit(img_tuyaux, buffer, 0, 0, tuyaux[i].x, tuyaux[i].y, img_tuyaux->w,
                                        img_tuyaux->h);
                            draw_sprite_v_flip(buffer, img_tuyaux, tuyaux[i].x, tuyaux[i].y - 865 - ecartement);
                            if (bird.x == 0) {
                                for (int i = 0; i < 4; ++i) {
                                    tuyaux[i].x = 170 + i * 200;
                                    tuyaux[i].y = 300 + rand() % 200;
                                }
                            }
                        }

                        /// deplacement oiseau
                        maj_bird(&bird, 3);
                        dessiner_bird(&bird, buffer);
                        deplacer_bird(&bird, (float) 2.5);

                        /// collision -> fin de partie
                        collision_bird(&bird, buffer);
                        if (bird.vie == 1) {
                            if (round_fb == 2) {
                                if (re_fp == 1) {
                                    re_fp = 2;
                                    temps_2bis_fp = clock(); // fin temps deuxieme joueur

                                    temps_final1_fp = (float)(temps_1bis_fp - temps_1_fp)/CLOCKS_PER_SEC;
                                    temps_final2_fp = (float)(temps_2bis_fp - temps_2_fp)/CLOCKS_PER_SEC;
                                    stat.presence;
                                    if(stat.presence==0){
                                        statistique(fichier,personnage,choix_jeu,joueur_tour,temps_final1_fp);
                                        statistique(fichier,personnage,choix_jeu,joueur_tour,temps_final2_fp);
                                        stat.presence=1;
                                    }

                                    if (temps_final1_fp >= temps_final2_fp) {
                                        gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1,&gestion_vie, 0);
                                        joueur_vic_fp = joueur_tour;
                                        joueur_def_fp = inv_joueur_tour;
                                    } else {
                                        gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1,&gestion_vie, 0);
                                        joueur_def_fp = joueur_tour;
                                        joueur_vic_fp = inv_joueur_tour;
                                    }
                                }
                                vic_ou_def = 1;
                                stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,
                                             buffer->h);
                                affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,
                                                     &depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);
                                affichage_danse_fin(personnage, buffer, vic_ou_def, joueur_vic_fp, joueur_def_fp);
                                rest(1);
                                show_mouse(buffer);
                                exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                            }
                            if (round_fb == 1) {
                                temps_1bis_fp = clock(); // fin temps premier joueur
                                rectfill(screen, 0, 0, 900, 650, makecol(40, 40, 40));
                                textprintf_ex(buffer, font, 200, SCREEN_H/2, makecol(255, 255, 255), -1, "Le tour du prochain joueur va commencer prochainement preparez vous");
                                init_flappy_bird(&bird, &joueur_def_fp, &joueur_vic_fp, &re_fp, &round_fb);
                                round_fb = 2;
                                rest(5000);
                                temps_2_fp = clock(); // debut temps deuxieme joueur
                            }
                        }

                        rest(1);
                        frame_counter_bird++;
                        if (frame_counter_bird == 20) {
                            bird.frame += 1;
                            frame_counter_bird = 0;

                            if (bird.frame == 4) bird.frame = 0;
                        }
                    }
                    break;
                case 5: ////////////// surprise
                    rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));

                    surprise.taille += 11;
                    depart1 = depart1 - 5;
                    depart2 = depart2 - 6;

                    stretch_blit(surprise.surpris, buffer, 0, 0, surprise.surpris->w, surprise.surpris->h, depart1,depart2, surprise.surpris->w + surprise.taille,surprise.surpris->h + surprise.taille);
                    if (surprise.surpris->w + surprise.taille >= 900) // retour menu
                    {
                        choix_jeu = 0;
                        clic_dans_accueil = 4;
                        depart1 = 330;
                        depart2 = 250;
                        surprise.taille = 0;
                        home_pos(personnage);
                    }
                    rest(1);
                    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
                    break;
                case 6: //////////// street fighter (octave)
                    blit(template_st, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    show_mouse(buffer);
                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if (mouse_x > 600 && mouse_x < 760 && mouse_y > 470 && mouse_y < 520 && mouse_b || clic == 1) {
                        if (clic == 0) {
                            loading(&rat, buffer);
                            clic = 1;
                        }
                        blit(background_st, buffer, 0, 0, 0, 0, background_st->w, background_st->h);

                        deplacement_street(&personnageStreetF[joueur_1], KEY_L, KEY_UP, KEY_DOWN, KEY_LEFT,
                                           KEY_RIGHT, ecart, &frame_counter_street, buffer,
                                           &personnageStreetF[joueur_2]);
                        deplacement_street(&personnageStreetF[joueur_2], KEY_F, KEY_W, KEY_S, KEY_A, KEY_D, ecart,
                                           &frame_counter_street, buffer, &personnageStreetF[joueur_1]);

                        collision_street_f(&personnageStreetF[joueur_1], &personnageStreetF[joueur_2], buffer,
                                           &frame_counter_street2);

                        masked_stretch_blit(
                                personnageStreetF[joueur_1].STREET_FIGHTER_droite[personnageStreetF[joueur_1].en_deplacement],
                                buffer, 0, 0, taille_w, taille_h, personnageStreetF[joueur_1].x,
                                personnageStreetF[joueur_1].y, 275, 275);
                        masked_stretch_blit(
                                personnageStreetF[joueur_2].STREET_FIGHTER_gauche[personnageStreetF[joueur_2].en_deplacement],
                                buffer, 0, 0, taille_w, taille_h, personnageStreetF[joueur_2].x,
                                personnageStreetF[joueur_2].y, 275, 275);

                        hadoken(&personnageStreetF[joueur_1], &personnageStreetF[joueur_2], buffer, hadoken_sprite);

                        affichage_vie_street_f(buffer, &personnageStreetF[joueur_1], &personnageStreetF[joueur_2]);
                        if (personnageStreetF[joueur_1].vie == 0 || personnageStreetF[joueur_2].vie == 0) {
                            vic_ou_def = 1;
                            stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,
                                         buffer->h);
                            affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def, &depart_vx,
                                                 &depart_vy, &departdx, &departdy, vic_ou_def);

                        }
                        if (personnageStreetF[joueur_1].vie == 0) {
                            affichage_danse_fin(personnage, buffer, vic_ou_def, joueur_2, joueur_1);
                            rest(1);
                            show_mouse(buffer);
                            exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                        }
                        if (personnageStreetF[joueur_2].vie == 0) {
                            affichage_danse_fin(personnage, buffer, vic_ou_def, joueur_1, joueur_2);
                            rest(1);
                            show_mouse(buffer);
                            exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                        }

                        frame_counter_street++;
                        frame_counter_street2++;
                    }
                    break;
                case 7: ////////// paris zombique (chloe)
                    blit(template_pz, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    show_mouse(buffer);
                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if (mouse_x > 570 && mouse_x < 700 && mouse_y > 470 && mouse_y < 520 && mouse_b || clic == 1) {
                        if (clic == 0) {
                            loading(&rat, buffer);
                            clic = 1;
                        }
                        if (deplacement_zombies == 1) {
                            while (pari_joueur1 == 0 || pari_joueur2 == 0) {
                                stretch_sprite(buffer, paris_zombique, 0, 0, screen->w, screen->h);
                                show_mouse(buffer);

                                if (mouse_b & 1) {
                                    int x = mouse_x;
                                    int y = mouse_y;

                                    if (y >= 560 && y < 650) {
                                        if (x >= 20 && x < 120) {
                                            if (joueur_actif == 1 && pari_joueur1 == 0) {
                                                pari_joueur1 = COUREUR1 + 1;
                                                joueur_actif = 2;
                                                printf("Joueur 1 a parié sur le coureur  %d\n", pari_joueur1);
                                                allegro_message("Joueur 1 a parié sur le coureur  %d",
                                                                pari_joueur1);
                                            } else if (joueur_actif == 2 && pari_joueur2 == 0 &&
                                                       pari_joueur1 != COUREUR1 + 1) {
                                                pari_joueur2 = COUREUR1 + 1;
                                                joueur_actif = 1;
                                                printf("Joueur 2 a parié sur le coureur  %d\n", pari_joueur2);
                                                allegro_message("Joueur 2 a parié sur le coureur  %d",
                                                                pari_joueur2);
                                            }
                                        } else if (x >= 140 && x < 190) {
                                            if (joueur_actif == 1 && pari_joueur1 == 0) {
                                                pari_joueur1 = COUREUR2 + 1;
                                                joueur_actif = 2;
                                                printf("Joueur 1 a parié sur le coureur  %d\n", pari_joueur1);
                                                allegro_message("Joueur 1 a parié sur le coureur  %d",
                                                                pari_joueur1);

                                            } else if (joueur_actif == 2 && pari_joueur2 == 0 &&
                                                       pari_joueur1 != COUREUR2 + 1) {
                                                pari_joueur2 = COUREUR2 + 1;
                                                joueur_actif = 1;
                                                printf("Joueur 2 a parié sur le coureur  %d\n", pari_joueur2);
                                                allegro_message("Joueur 2 a parié sur le coureur  %d",
                                                                pari_joueur2);

                                            }
                                        } else if (x >= 200 && x < 235) {
                                            if (joueur_actif == 1 && pari_joueur1 == 0) {
                                                pari_joueur1 = COUREUR3 + 1;
                                                joueur_actif = 2;
                                                printf("Joueur 1 a parié sur le coureur  %d\n", pari_joueur1);
                                                allegro_message("Joueur 1 a parié sur le coureur  %d",
                                                                pari_joueur1);

                                            } else if (joueur_actif == 2 && pari_joueur2 == 0 &&
                                                       pari_joueur1 != COUREUR3 + 1) {
                                                pari_joueur2 = COUREUR3 + 1;
                                                joueur_actif = 1;
                                                printf("Joueur 2 a parié sur le coureur  %d\n", pari_joueur2);
                                                allegro_message("Joueur 1 a parié sur le coureur  %d",
                                                                pari_joueur2);

                                            }
                                        } else if (x >= 245 && x < 295) {
                                            if (joueur_actif == 1 && pari_joueur1 == 0) {
                                                pari_joueur1 = COUREUR4 + 1;
                                                joueur_actif = 2;
                                                printf("Joueur 1 a parié sur le coureur  %d\n", pari_joueur1);
                                                allegro_message("Joueur 1 a parié sur le coureur  %d",
                                                                pari_joueur1);

                                            } else if (joueur_actif == 2 && pari_joueur2 == 0 &&
                                                       pari_joueur1 != COUREUR4 + 1) {
                                                pari_joueur2 = COUREUR4 + 1;
                                                joueur_actif = 1;
                                                printf("Joueur 2 a parié sur le coureur  %d\n", pari_joueur2);
                                                allegro_message("Joueur 2 a parié sur le coureur  %d",
                                                                pari_joueur2);

                                            }
                                        }
                                    }
                                }
                                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                            }
                            clear_to_color(buffer, makecol(255, 255, 255));

                            allegro_message("Démarrer la course");
                               

                            stretch_blit(paris_zombique, buffer, 0, 0, paris_zombique->w, paris_zombique->h, 0, 0,
                                         buffer->w, buffer->h);
                            show_mouse(buffer);

                            textprintf_ex(buffer, font, 450, 550, makecol(255, 255, 255), -1, "Joueur 1 vous avez parié sur le coureur n°%d", pari_joueur1);
                            textprintf_ex(buffer, font, 450, 580, makecol(255, 255, 255), -1, "Joueur 2 vous avez parié sur le coureur n°%d", pari_joueur2);
                            textprintf_ex(buffer, font, 450, 610, makecol(255, 255, 255), -1, "appuyez sur entrer pour demarrer la course");

                            ///course
                            if (key[KEY_ENTER]) {
                                zombie_avance_ou_pas = 1;
                            }
                            if (zombie_avance_ou_pas == 1) {
                                maj_zombbie(&fille, &garcon, &squelette, &zombie);
                            }
                            dessiner_zombie(&fille, &garcon, &squelette, &zombie, buffer);
                            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
                            zombie_compteur++;
                            if (zombie_compteur >= 10) {
                                if (fille.zombie_qui_court) {
                                    fille.frameZombie = (fille.frameZombie + 1) % 3;
                                } else {
                                    fille.frameZombie = 0;
                                }
                            }
                            if (zombie_compteur >= 10) {
                                if (garcon.zombie_qui_court) {
                                    garcon.frameZombie = (garcon.frameZombie + 1) % 3;
                                } else {
                                    garcon.frameZombie = 0;
                                }
                            }
                            if (zombie_compteur >= 10) {
                                if (squelette.zombie_qui_court) {
                                    squelette.frameZombie = (squelette.frameZombie + 1) % 3;
                                } else {
                                    squelette.frameZombie = 0;
                                }
                            }
                            if (zombie_compteur >= 10) {
                                if (zombie.zombie_qui_court) {
                                    zombie.frameZombie = (zombie.frameZombie + 1) % 3;
                                } else {
                                    zombie.frameZombie = 0;
                                }
                                zombie_compteur = 0;
                            }
                            ///victoire_zombie
                            zombieGagnant = victoire_zombie(&fille, &garcon, &squelette, &zombie,
                                                            &deplacement_zombies);
                        }

                        vic_ou_def = 1;
                        if (deplacement_zombies == 0) {

                            if (zombieGagnant == pari_joueur1) {
                                joueur_vic_pz = joueur_1;
                                joueur_def_pz = joueur_2;

                                stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,
                                             buffer->h);


                                affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,
                                                     &depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);
                                affichage_danse_fin(&personnage[joueur_tour], buffer, vic_ou_def, joueur_vic_pz,
                                                    joueur_def_pz);
                                rest(1);
                                show_mouse(buffer);
                                exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);

                            } else if (zombieGagnant == pari_joueur2) {
                                joueur_vic_pz = joueur_2;
                                joueur_def_pz = joueur_1;

                                stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,
                                             buffer->h);

                                affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,
                                                     &depart_vx, &depart_vy, &departdx, &departdy, vic_ou_def);

                                gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1, &gestion_vie, 1);


                                affichage_danse_fin(&personnage[joueur_tour], buffer, vic_ou_def, joueur_vic_pz,
                                                    joueur_def_pz);
                                rest(1);
                                show_mouse(buffer);
                                exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                            } else {

                                stretch_blit(fond_fin, buffer, 0, 0, fond_fin->w, fond_fin->h, 0, 0, buffer->w,
                                             buffer->h);

                                affichage_vic_ou_def(buffer, victoire, defaite, &taille_vic, &taille_def,
                                                     &depart_vx, &depart_vy, &departdx, &departdy, 2);

                                gestion_vie_personnage(buffer, personnage, joueur_tour, image_vie, 1, &gestion_vie, 1);

                                affichage_danse_fin(&personnage[joueur_tour], buffer, 4, joueur_1,
                                                    joueur_2);
                                rest(1);
                                show_mouse(buffer);
                                exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 1);
                            }
                        }
                        rest(10);
                    }
                    break;
                case 8: ////////// tir au ballon
                    blit(template_tb, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                    show_mouse(buffer);
                    exit_mini_jeu(personnage, &clic, &clic_dans_accueil, &tour, 0);
                    if (mouse_x > 570 && mouse_x < 700 && mouse_y > 470 && mouse_y < 520 && mouse_b || clic == 1)
                    {
                        if (clic == 0)
                        {
                            //loading(&rat, buffer);
                            clic = 1;
                        }
                        blit(fond_tir, buffer, 0, 0, 0, 0, buffer->w, buffer->h);

                        plusDeBallons(buffer, mesActeurs);
                        blit(fond_tir, buffer, 0, 0, 0, 0, buffer->w, buffer->h);
                        show_mouse(buffer);
                        textprintf_ex(buffer, font, 20, 40, makecol(128, 128, 128), -1, "TEMPS: %d", temps / 60);
                        actuTabBallons(tab_acteurs);
                        dessinerTabBallons(buffer, tab_acteurs);
                        TabPlusDeBallons(buffer, tab_acteurs);
                        rest(10);
                        if (tab_acteurs[0]->posx == -35 && tab_acteurs[1]->posx == -35 &&
                            tab_acteurs[2]->posx == -35 &&
                            tab_acteurs[3]->posx == -35 && tab_acteurs[4]->posx == -35 &&
                            tab_acteurs[5]->posx == -35 && tab_acteurs[6]->posx == -35 &&
                            tab_acteurs[7]->posx == -35 &&
                            tab_acteurs[8]->posx == -35 && tab_acteurs[9]->posx == -35)
                        {
                            show_mouse(buffer);
                            textprintf_ex(buffer, font, 400, 400, makecol(128, 128, 128), -1, "TEMPS: %d", temps / 60);
                            break;
                        }
                        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        temps += 1;

                    }


                    break;
                case 10:
                    exit(1);
                    break;


            }
        }
        else if (clic_dans_accueil == 6)
        {
            if(vaincqueur == 1)
            {
                joueur_def = joueur_1;
                joueur_vic = joueur_2;
            }
            if(vaincqueur == 2)
            {
                joueur_def = joueur_2;
                joueur_vic = joueur_1;
            }
            blit(fin_jeu, buffer, 0, 0, 0, 0, buffer->w, buffer->h);
            affichage_danse_fin(personnage, buffer, 5, joueur_def, joueur_vic);
            rest(10);
        }


        if (clic_dans_accueil == 1) marche = choix_perso;
        if (clic_dans_accueil == 4)  marche = joueur_tour;

        /// tous les frame counters

        if (frame_counter>=10)
        {
            if(personnage[marche].en_deplacement == 1) personnage[marche].frame = ((personnage[marche].frame + 1) %9);
            else personnage[marche].frame = 1;
            frame_counter = 0;
        }
        frame_counter++;

        // pour animation fin mini jeu
        frame_count(personnage, &frame1_counter, &frame1_counter2);

        show_mouse(buffer);
        blit(buffer,screen,0,0,0,0,screen->w,screen->h);
    }

    //////////    Destroy BITMAP
    for (int i = 0; i < 11; i++)
    {
        destroy_bitmap(fille.droite[i]);
        destroy_bitmap(garcon.droite[i]);
        destroy_bitmap(squelette.droite[i]);
        destroy_bitmap(zombie.droite[i]);
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int k = 0; k < 9; ++k)
        {
            destroy_bitmap(personnage[i].haut[k]);
            destroy_bitmap(personnage[i].bas[k]);
            destroy_bitmap(personnage[i].gauche[k]);
            destroy_bitmap(personnage[i].droite[k]);
        }

        for (int k = 0; k < 6; ++k)
        {
            destroy_bitmap(personnage[i].defaite[k]);
            destroy_bitmap(personnage[i].danse[k]);
        }
    }
    destroy_bitmap(sprite_octave);
    destroy_bitmap(sprite_marina);
    destroy_bitmap(sprite_mathis);
    destroy_bitmap(sprite_chloe);


    for (int i = 0; i < 4; ++i)
    {
        destroy_bitmap(rat.sprites[i]);
        destroy_bitmap(bird.droite[i]);
    }
    destroy_bitmap(sprite);
    destroy_bitmap(sprite2);
    destroy_bitmap(sprite3);
    destroy_bitmap(sprite4);
    destroy_bitmap(paris_zombique);

    destroy_bitmap(BG_accueil);
    destroy_bitmap(BG_choix_du_joueur);
    destroy_bitmap(regles);

    destroy_bitmap(map);
    destroy_bitmap(collision);
    destroy_bitmap(image_vie);

    destroy_bitmap(template_gh);
    destroy_bitmap(template_jackpot);
    destroy_bitmap(template_fp);
    destroy_bitmap(template_pz);
    destroy_bitmap(template_tr);
    destroy_bitmap(template_st);

    destroy_bitmap(fond_fin);
    destroy_bitmap(victoire);
    destroy_bitmap(defaite);


    for (int i = 0; i < TAILLE; ++i)
    {
        for (int k = 0; k < 5; ++k)
        {
            destroy_bitmap(touche[i].couleur[k]);
        }
    }
    destroy_bitmap(fond_gh);
    destroy_bitmap(fond_collision_gh);
    destroy_bitmap(touches);

    destroy_bitmap(BG_accueil);
    destroy_bitmap(Message_attente_casino);
    destroy_bitmap(symbolesCasino.image);


    destroy_bitmap(fond_flappy);
    destroy_bitmap(sprite_oiseau);
    destroy_bitmap(img_tuyaux);

    destroy_bitmap(background_st);
    destroy_bitmap(hadoken_sprite);
    for (int i = 0; i < 4; ++i)
    {
        for (int k = 0; k < 3; ++k) {
            destroy_bitmap(personnageStreetF[i].STREET_FIGHTER_droite[k]);
            destroy_bitmap(personnageStreetF[i].STREET_FIGHTER_gauche[k]);
        }
    }

    destroy_bitmap(buffer);

    allegro_exit();
    return 0;
}END_OF_MAIN()