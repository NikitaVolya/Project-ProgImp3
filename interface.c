#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "points_list.h"
#include "point.h"
#include "interface.h"
#include "save.h"
#include "stack.h"

/* ********************************************************************************************************************
 *                                                CONSTANTE
 ******************************************************************************************************************** */

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 700

#define COULEUR_FOND MLV_COLOR_WHITE
#define COULEUR_PANNEAU MLV_COLOR_PINK
#define COULEUR_BORDURE MLV_COLOR_PURPLE
#define COULEUR_TEXTE MLV_COLOR_BLACK
#define COULEUR_OMBRE MLV_COLOR_GRAY
#define COULEUR_SURFACE MLV_COLOR_WHITE
#define CLASSE_VOISIN_SELECTIONNE -1

#define ZONE_X 40
#define ZONE_Y 100
#define ZONE_LARGEUR 510
#define ZONE_HAUTEUR 510


#define DELETE_POINT_X 560
#define DELETE_POINT_Y 110
#define DELETE_POINT_LARGEUR 210
#define DELETE_POINT_HAUTEUR 40

#define BOUTON_MODE_X 40
#define BOUTON_MODE_Y 30
#define BOUTON_MODE_LARGEUR 220
#define BOUTON_MODE_HAUTEUR 40

#define BOUTON_K_X 320
#define BOUTON_K_Y 30
#define BOUTON_K_LARGEUR 140
#define BOUTON_K_HAUTEUR 40

#define BOUTON_REINIT_X 800
#define BOUTON_REINIT_Y 30
#define BOUTON_REINIT_LARGEUR 250
#define BOUTON_REINIT_HAUTEUR 40

#define BOUTON_CLASSE_X 800
#define BOUTON_CLASSE_Y 100
#define BOUTON_CLASSE_LARGEUR 250
#define BOUTON_CLASSE_HAUTEUR 70

#define ZONE_OPTIONS_X 800
#define ZONE_OPTIONS_Y 240
#define ZONE_OPTIONS_LARGEUR 250
#define ZONE_OPTIONS_HAUTEUR 140

#define BOUTON_CHARGER_X 800
#define BOUTON_CHARGER_Y 430
#define BOUTON_CHARGER_LARGEUR 250
#define BOUTON_CHARGER_HAUTEUR 50

#define BOUTON_SAUVEGARDER_X 800
#define BOUTON_SAUVEGARDER_Y 500
#define BOUTON_SAUVEGARDER_LARGEUR 250
#define BOUTON_SAUVEGARDER_HAUTEUR 50

#define BOUTON_MESSAGE_X 500
#define BOUTON_MESSAGE_Y 30
#define BOUTON_MESSAGE_LARGEUR 250
#define BOUTON_MESSAGE_HAUTEUR 50

#define ZONE_VOISINS_X 570
#define ZONE_VOISINS_Y 140
#define ZONE_VOISINS_LARGEUR 210
#define ZONE_VOISINS_HAUTEUR 470
#define ZONE_VOISINS_LIGNE_HAUTEUR 18

/* ********************************************************************************************************************
 *                                              STATIQUE DECLARATION
 ******************************************************************************************************************** */

static char* input_box(char * text);
static void dessiner_interface(PointsList * list, size_t classe,int mode, int k,int * option_voisinage,int * option_descision,size_t nb_classe, Point * point_selectionne);
static void dessiner_fond(size_t classe,int mode, int k,size_t nb_classe);
static void dessiner_zone_affichage(PointsList *list, Point * point_selectionne, int k, int option_voisinage);
static void dessiner_options_affichage(int * option_voisinage,int * option_descision);
static void dessiner_point(Point * P,int classe);
static void dessiner_bouton(int x, int y, int largeur, int hauteur, const char *texte);

static void dessiner_titre(void);
static void dessiner_petit_coeur(int x, int y, MLV_Color couleur);
static void dessiner_fleur(int x, int y, MLV_Color couleur);
static void dessiner_checkbox(int x, int y, int active);
static void dessiner_grille_douce(void);
static void dessiner_liste_voisins(PointsList * list, Point * point_selectionne, int k, int option_voisinage, int mode);

static MLV_Color classe_color(int i);
static char classe_symbole(int i);

static Point* select_point(PointsList * list, int x, int y);
static int point_dans_rectangle(int x, int y, int rx, int ry, int rw, int rh);

static void animer_sparkle(PointsList * list, size_t classe, int mode, int k, int * option_voisinage, int * option_descision, size_t nb_classe, Point * point_selectionne, int x, int y);
static void dessiner_sparkle(int x, int y, int etape);


/* ********************************************************************************************************************
 *                                              FONCTION PUBLIQUE
 ******************************************************************************************************************** */

int interface_lancer(PointsList * list) {
    int k;
    int option_voisin;
    int option_descision;
    int last_point;
    int mode;
    int continuer;

    int classe_new_point;
    char * fichier;
    size_t classe;
    size_t nb_classe;
    int souris_x;
    int souris_y;
    Point * p , *point_selectionne;
    MLV_Keyboard_button touche;
    int resultat;
    FILE * File;
    int saved_nb_classes;
    int saved_dimensions; 
    p = NULL;
    point_selectionne = NULL ;
    option_voisin = 0;
    option_descision = 0;
    last_point = 0;
    k = 10;
    mode = 1 ;
    classe = 0;
    continuer = 1;
    souris_x = 0;
    souris_y = 0;
    resultat = 1;
    nb_classe = list->nb_classes;
    MLV_create_window(
        "Projet PROG S4",
        "interface",
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE
    );

    while (continuer) {
        dessiner_interface(list, classe,mode, k,&option_voisin,&option_descision,nb_classe, point_selectionne);
        MLV_actualise_window();

        touche = MLV_KEYBOARD_NONE;
        MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &souris_x, &souris_y);

        if (touche == MLV_KEYBOARD_ESCAPE) {
            continuer = 0;
        }
        else if (touche == MLV_KEYBOARD_NONE) {
            
            animer_sparkle(list, classe, mode, k, &option_voisin, &option_descision, nb_classe, point_selectionne, souris_x, souris_y); 
            
            if (point_dans_rectangle(souris_x, souris_y, BOUTON_REINIT_X, BOUTON_REINIT_Y, BOUTON_REINIT_LARGEUR, BOUTON_REINIT_HAUTEUR)) {
                if (list != NULL) {
                    int saved_nb_classes = list->nb_classes;
                    int saved_dimensions = list->dimensions;
                    free_points_list(list);
                    list = create_points_list(10, saved_nb_classes, saved_dimensions);
                    point_selectionne = NULL;
                }
            }

            if (point_dans_rectangle(souris_x, souris_y, BOUTON_K_X, BOUTON_K_Y, BOUTON_K_LARGEUR, BOUTON_K_HAUTEUR)) {
                fichier = input_box("Valeur de k :");
                if (fichier != NULL) {
                    k = atoi(fichier);
                    free(fichier);
                }
            }

            if (point_dans_rectangle(souris_x, souris_y, BOUTON_CHARGER_X, BOUTON_CHARGER_Y, BOUTON_CHARGER_LARGEUR, BOUTON_CHARGER_HAUTEUR)) {
                fichier = input_box("nom du fichier :");
                if (fichier != NULL) {
                    File = fopen(fichier,"r");
                    if (File != NULL) {
                        PointsList * newList = load_points_from_file(File);
                        if (newList == NULL) {
                            dessiner_bouton(BOUTON_MESSAGE_X, BOUTON_MESSAGE_Y, BOUTON_MESSAGE_LARGEUR, BOUTON_MESSAGE_HAUTEUR, "erreur lors du chargement veillez recommancer");
                            MLV_actualise_window();
                            MLV_wait_milliseconds(1000);
                        }
                        else {
                            if (list != NULL) free_points_list(list);
                            list = newList;
                            nb_classe = list->nb_classes;
                            point_selectionne = NULL;
                            dessiner_bouton(BOUTON_MESSAGE_X, BOUTON_MESSAGE_Y, BOUTON_MESSAGE_LARGEUR, BOUTON_MESSAGE_HAUTEUR, "chargement reussi");
                            MLV_actualise_window();
                            MLV_wait_milliseconds(1000);
                        }
                        fclose(File);
                    }
                    free(fichier);
                }
            }
            if (point_dans_rectangle(souris_x, souris_y, BOUTON_SAUVEGARDER_X, BOUTON_SAUVEGARDER_Y, BOUTON_SAUVEGARDER_LARGEUR, BOUTON_SAUVEGARDER_HAUTEUR)) {
                fichier = input_box("nom du fichier :");
                if (fichier != NULL) {
                    File = fopen(fichier,"w");
                    if (File != NULL) {
                        if (save_data_to_file(list, File)!=0) {
                            dessiner_bouton(BOUTON_MESSAGE_X, BOUTON_MESSAGE_Y, BOUTON_MESSAGE_LARGEUR, BOUTON_MESSAGE_HAUTEUR, "erreur lors de la sauvegarde veillez recommancer");
                            MLV_actualise_window();
                            MLV_wait_milliseconds(1000);
                        }
                        else {
                            dessiner_bouton(BOUTON_MESSAGE_X, BOUTON_MESSAGE_Y, BOUTON_MESSAGE_LARGEUR, BOUTON_MESSAGE_HAUTEUR, "sauvegarde reussi");
                            MLV_actualise_window();
                            MLV_wait_milliseconds(1000);
                        }
                        fclose(File);
                    }
                    free(fichier);
                }
            }

            if (point_dans_rectangle(souris_x, souris_y, ZONE_OPTIONS_X + 15, ZONE_OPTIONS_Y + 45, 15, 15)) {
                option_voisin = !option_voisin;

            }
            if (point_dans_rectangle(souris_x, souris_y, ZONE_OPTIONS_X + 15, ZONE_OPTIONS_Y + 75, 15, 15)) {
                option_descision = !option_descision;
            }
            if (mode == 2 ) {
                p = NULL;
                if (point_dans_rectangle(souris_x, souris_y, ZONE_X, ZONE_Y, ZONE_LARGEUR, ZONE_HAUTEUR)) {
                    p = select_point(list, souris_x, souris_y);
                    if (p != NULL) {
                        point_selectionne = p;
                        classe = (size_t)get_point_classe(p);
                    }
                }
                if (point_dans_rectangle(souris_x, souris_y, BOUTON_MODE_X, BOUTON_MODE_Y, BOUTON_MODE_LARGEUR, BOUTON_MODE_HAUTEUR)) {
                    mode = 1;
                    point_selectionne = NULL;
                }
            }
            else {
                if (point_dans_rectangle(souris_x, souris_y, BOUTON_MODE_X, BOUTON_MODE_Y, BOUTON_MODE_LARGEUR, BOUTON_MODE_HAUTEUR)) {
                    mode = 2;
                }
                if (point_dans_rectangle(souris_x, souris_y, ZONE_X+5, ZONE_Y+5, ZONE_LARGEUR-5, ZONE_HAUTEUR-5)) {
                    if (option_descision) {
                        p = select_point(list,souris_x,souris_y);
                        if (p != NULL)
                            classe_new_point = select_class_bf(list,p,k);
                        else
                            classe_new_point = 1; // Default class if list is empty
                    }
                    else {
                        fichier = input_box("donner la classe du point : ");
                        if (fichier != NULL) {
                            classe_new_point = atoi(fichier);
                            free(fichier);
                        } else {
                            classe_new_point = 1;
                        }

                    }
                    if (list != NULL) {
                        points_list_add_point(list,create_point(classe_new_point,create_vector2_with_values((souris_x - 255-ZONE_X)/250.,(souris_y - 255-ZONE_Y)/250.)));
                        last_point = 1;
                    }
                }
                if (last_point == 1) {
                    if (point_dans_rectangle(souris_x, souris_y, DELETE_POINT_X, DELETE_POINT_Y, DELETE_POINT_LARGEUR, DELETE_POINT_HAUTEUR)) {
                        if (list != NULL && list->count > 0) {
                            points_list_remove_point(list,list->count-1);
                        }
                        last_point = 0 ;
                    }
                }


            }

        }
    }


    MLV_free_window();
    return resultat;
}
/* ********************************************************************************************************************
 *                                              FONCTION PRIVÉ
 ******************************************************************************************************************** */

static char* input_box(char * text) {
    char * res;
    MLV_Input_box * box;
    box = MLV_create_input_box(
        BOUTON_MESSAGE_X,
        BOUTON_MESSAGE_Y,
        BOUTON_MESSAGE_LARGEUR,
        BOUTON_MESSAGE_HAUTEUR,
        MLV_COLOR_BLACK,
        MLV_COLOR_BLACK,
        MLV_COLOR_WHITE,
        text
    );

    MLV_draw_all_input_boxes();
    MLV_actualise_window();

    MLV_wait_particular_input_box(box, &res);


    if (res == NULL) {
        printf("input box error\n");
        res = NULL;
    }

    MLV_free_input_box(box);
    return res;
}

static void dessiner_interface(PointsList * list, size_t classe,int mode, int k,int * option_voisinage,int * option_descision,size_t nb_classe, Point * point_selectionne) {
    dessiner_fond(classe,mode,k,nb_classe);
    dessiner_zone_affichage(list, point_selectionne, k, *option_voisinage);
    dessiner_options_affichage(option_voisinage,option_descision);
    dessiner_liste_voisins(list, point_selectionne, k, *option_voisinage, mode);
}

static void dessiner_fond(size_t classe,int mode,int k,size_t nb_classe) {

    char text[100];
    char textk[100];
    MLV_clear_window(COULEUR_FOND);

        /* Decoration de fond visuelle. */
    MLV_draw_filled_rectangle(0, 0, LARGEUR_FENETRE, 18, MLV_COLOR_PINK);
    MLV_draw_filled_rectangle(0, HAUTEUR_FENETRE - 18, LARGEUR_FENETRE, 18, MLV_COLOR_PINK);
    dessiner_fleur(1120, 80, MLV_COLOR_PINK);
    dessiner_fleur(1135, 610, MLV_COLOR_PURPLE);
    dessiner_fleur(700, 620, MLV_COLOR_PINK);

    dessiner_titre();
    if (mode == 1) {
        dessiner_bouton(BOUTON_MODE_X, BOUTON_MODE_Y, BOUTON_MODE_LARGEUR, BOUTON_MODE_HAUTEUR, "Mode creation");
        dessiner_bouton(DELETE_POINT_X, DELETE_POINT_Y, DELETE_POINT_LARGEUR, DELETE_POINT_HAUTEUR, "Suprimmer le dernier point");
    }
    else {
        dessiner_bouton(BOUTON_MODE_X, BOUTON_MODE_Y, BOUTON_MODE_LARGEUR, BOUTON_MODE_HAUTEUR, "Mode kpp");
    }

    sprintf(textk, "Valeur de k : %d", k);
    dessiner_bouton(BOUTON_K_X, BOUTON_K_Y, BOUTON_K_LARGEUR, BOUTON_K_HAUTEUR, textk);

    dessiner_bouton(BOUTON_REINIT_X, BOUTON_REINIT_Y, BOUTON_REINIT_LARGEUR, BOUTON_REINIT_HAUTEUR, "Reinitialisation");

    if (classe > 0) {
        sprintf(text, "classe du point : %ld / max classe : %ld  ", classe,nb_classe);
    } else {
        sprintf(text, "classe du point :  / max classe : %ld  ",nb_classe);
    }
    dessiner_bouton(BOUTON_CLASSE_X, BOUTON_CLASSE_Y, BOUTON_CLASSE_LARGEUR, BOUTON_CLASSE_HAUTEUR, text);

    dessiner_bouton(BOUTON_CHARGER_X, BOUTON_CHARGER_Y, BOUTON_CHARGER_LARGEUR, BOUTON_CHARGER_HAUTEUR, "Chargement fichier");
    dessiner_bouton(BOUTON_SAUVEGARDER_X, BOUTON_SAUVEGARDER_Y, BOUTON_SAUVEGARDER_LARGEUR, BOUTON_SAUVEGARDER_HAUTEUR, "Sauvegarde fichier");
}

static void dessiner_zone_affichage(PointsList * list, Point * point_selectionne, int k, int option_voisinage) {
    size_t i;
    Point * temp;
    Stack * kvoisin;
    Point ** neighbors = NULL;
    size_t neighbor_count = 0;
    PointDistance * pd; 
    int color_to_use;
    size_t j;
    
    MLV_draw_filled_rectangle(ZONE_X + 10, ZONE_Y + 12, ZONE_LARGEUR, ZONE_HAUTEUR, COULEUR_OMBRE);
    MLV_draw_filled_rectangle(ZONE_X - 4, ZONE_Y - 4, ZONE_LARGEUR + 8, ZONE_HAUTEUR + 8, MLV_COLOR_PINK);
    MLV_draw_filled_rectangle(ZONE_X, ZONE_Y, ZONE_LARGEUR, ZONE_HAUTEUR, COULEUR_SURFACE);
    MLV_draw_rectangle(ZONE_X, ZONE_Y, ZONE_LARGEUR, ZONE_HAUTEUR, COULEUR_BORDURE);
    MLV_draw_rectangle(ZONE_X + 5, ZONE_Y + 5, ZONE_LARGEUR - 10, ZONE_HAUTEUR - 10, COULEUR_PANNEAU);
    dessiner_grille_douce();
    
    if (list != NULL) {
        // 1. Si l'option voisinage est active, on identifie les voisins d'abord
        if (option_voisinage && point_selectionne != NULL) {
            kvoisin = point_list_select_k_nearby(list, point_selectionne, k);
            if (kvoisin != NULL) {
                neighbor_count = get_stack_size(kvoisin);
                neighbors = malloc(sizeof(Point*) * neighbor_count);
                for (i = 0; i < neighbor_count; i++) {
                    PointDistance * pd = (PointDistance *) stack_pop(kvoisin);
                    neighbors[i] = pd->point;
                    free(pd);
                }
                free_stack(kvoisin);
            }
        }

        // 2. On dessine chaque point une seule fois avec la bonne couleur
        for (i = 0; i < list->count; i++) {
            temp = points_list_get_point(list, i);
            int color_to_use = get_point_classe(temp);
            
            if (temp == point_selectionne) {
                color_to_use = 0; // Noir pour le point sélectionné
            } else if (neighbors != NULL) {
                // Vérifier si ce point est dans la liste des voisins
                for (size_t j = 0; j < neighbor_count; j++) {
                    if (temp == neighbors[j]) {
                        color_to_use = CLASSE_VOISIN_SELECTIONNE;
                        break;
                    }
                }
            }
            dessiner_point(temp, color_to_use);
        }

        if (neighbors != NULL) free(neighbors);
    }
}

static void dessiner_liste_voisins(PointsList * list, Point * point_selectionne, int k, int option_voisinage, int mode) {
    Stack * kvoisin;
    PointDistance * pd;
    Point * voisin;
    size_t nb_voisins;
    size_t i;
    size_t dimension;
    size_t dimensions;
    int y;
    int max_lignes;
    int ligne_y;
    MLV_Color couleur_ligne;
    char ligne[160];
    char coords[96];
    char morceau[32];

    /* Liste visuelle : seulement en mode KPP + voisinage actif. */
    if (mode != 2 || option_voisinage == 0) {
        return;
    }

    MLV_draw_filled_rectangle(ZONE_VOISINS_X + 5, ZONE_VOISINS_Y + 6, ZONE_VOISINS_LARGEUR, ZONE_VOISINS_HAUTEUR, COULEUR_OMBRE);
    MLV_draw_filled_rectangle(ZONE_VOISINS_X - 2, ZONE_VOISINS_Y - 2, ZONE_VOISINS_LARGEUR + 4, ZONE_VOISINS_HAUTEUR + 4, MLV_COLOR_PINK);
    MLV_draw_filled_rectangle(ZONE_VOISINS_X, ZONE_VOISINS_Y, ZONE_VOISINS_LARGEUR, ZONE_VOISINS_HAUTEUR, COULEUR_SURFACE);
    MLV_draw_rectangle(ZONE_VOISINS_X, ZONE_VOISINS_Y, ZONE_VOISINS_LARGEUR, ZONE_VOISINS_HAUTEUR, COULEUR_BORDURE);
    MLV_draw_rectangle(ZONE_VOISINS_X + 4, ZONE_VOISINS_Y + 4, ZONE_VOISINS_LARGEUR - 8, ZONE_VOISINS_HAUTEUR - 8, COULEUR_PANNEAU);

    MLV_draw_text(ZONE_VOISINS_X + 14, ZONE_VOISINS_Y + 14, "Voisins KPP", COULEUR_BORDURE);
    MLV_draw_line(ZONE_VOISINS_X + 12, ZONE_VOISINS_Y + 35, ZONE_VOISINS_X + ZONE_VOISINS_LARGEUR - 12, ZONE_VOISINS_Y + 35, COULEUR_PANNEAU);

    if (point_selectionne == NULL || list == NULL) {
        MLV_draw_text(ZONE_VOISINS_X + 12, ZONE_VOISINS_Y + 52, "Clique un point", COULEUR_TEXTE);
        MLV_draw_text(ZONE_VOISINS_X + 12, ZONE_VOISINS_Y + 70, "pour voir ses voisins", COULEUR_TEXTE);
        return;
    }

    coords[0] = '\0';
    dimensions = get_point_dimensions(point_selectionne);
    for (dimension = 0; dimension < dimensions && dimension < 3; dimension++) {
        if (dimension == 0) {
            sprintf(morceau, "%.2f", get_point_position(point_selectionne, dimension));
        } else {
            sprintf(morceau, ", %.2f", get_point_position(point_selectionne, dimension));
        }
        if (strlen(coords) + strlen(morceau) < sizeof(coords) - 1) {
            strcat(coords, morceau);
        }
    }
    if (dimensions > 3 && strlen(coords) + 5 < sizeof(coords) - 1) {
        strcat(coords, ", ...");
    }

    sprintf(ligne, "Point: classe %d", get_point_classe(point_selectionne));
    MLV_draw_text(ZONE_VOISINS_X + 12, ZONE_VOISINS_Y + 52, ligne, COULEUR_TEXTE);
    sprintf(ligne, "pos: [%s]", coords);
    MLV_draw_text(ZONE_VOISINS_X + 12, ZONE_VOISINS_Y + 69, ligne, COULEUR_TEXTE);

    kvoisin = point_list_select_k_nearby(list, point_selectionne, k);
    if (kvoisin == NULL) {
        MLV_draw_text(ZONE_VOISINS_X + 12, ZONE_VOISINS_Y + 94, "Aucun voisin", COULEUR_TEXTE);
        return;
    }

    nb_voisins = get_stack_size(kvoisin);
    max_lignes = (ZONE_VOISINS_HAUTEUR - 116) / (ZONE_VOISINS_LIGNE_HAUTEUR + 16);
    y = ZONE_VOISINS_Y + 96;

    for (i = 0; i < nb_voisins; i++) {
        pd = (PointDistance *) stack_pop(kvoisin);
        if (pd != NULL) {
            voisin = pd->point;
            if ((int)i < max_lignes && voisin != NULL) {
                couleur_ligne = classe_color(get_point_classe(voisin));

                if (i == 0) {
                    MLV_draw_filled_rectangle(ZONE_VOISINS_X + 8, y - 3, ZONE_VOISINS_LARGEUR - 16, 31, MLV_COLOR_LIGHT_PINK);
                    MLV_draw_rectangle(ZONE_VOISINS_X + 8, y - 3, ZONE_VOISINS_LARGEUR - 16, 31, MLV_COLOR_ORANGE);
                }

                coords[0] = '\0';
                dimensions = get_point_dimensions(voisin);
                for (dimension = 0; dimension < dimensions && dimension < 3; dimension++) {
                    if (dimension == 0) {
                        sprintf(morceau, "%.2f", get_point_position(voisin, dimension));
                    } else {
                        sprintf(morceau, ", %.2f", get_point_position(voisin, dimension));
                    }
                    if (strlen(coords) + strlen(morceau) < sizeof(coords) - 1) {
                        strcat(coords, morceau);
                    }
                }
                if (dimensions > 3 && strlen(coords) + 5 < sizeof(coords) - 1) {
                    strcat(coords, ", ...");
                }

                MLV_draw_filled_circle(ZONE_VOISINS_X + 17, y + 8, 6, couleur_ligne);
                MLV_draw_circle(ZONE_VOISINS_X + 17, y + 8, 6, COULEUR_BORDURE);

                sprintf(ligne, "%lu. classe %d  dist %.2f", (unsigned long)(i + 1), get_point_classe(voisin), get_point_distance_value(pd));
                MLV_draw_text(ZONE_VOISINS_X + 30, y, ligne, COULEUR_TEXTE);

                ligne_y = y + 16;
                sprintf(ligne, "pos: [%s]", coords);
                MLV_draw_text(ZONE_VOISINS_X + 30, ligne_y, ligne, COULEUR_TEXTE);

                y += ZONE_VOISINS_LIGNE_HAUTEUR + 16;
            }
            free(pd);
        }
    }

    if ((int)nb_voisins > max_lignes) {
        fprintf(ligne, "+%lu autres voisins", (unsigned long)(nb_voisins - (size_t)max_lignes));
        MLV_draw_text(ZONE_VOISINS_X + 16, ZONE_VOISINS_Y + ZONE_VOISINS_HAUTEUR - 24, ligne, COULEUR_BORDURE);
    }

    free_stack(kvoisin);
}

static void dessiner_options_affichage(int * option_voisinage, int * option_descision) {
    MLV_draw_filled_rectangle(ZONE_OPTIONS_X + 8, ZONE_OPTIONS_Y + 10, ZONE_OPTIONS_LARGEUR, ZONE_OPTIONS_HAUTEUR, COULEUR_OMBRE);
    MLV_draw_filled_rectangle(ZONE_OPTIONS_X - 3, ZONE_OPTIONS_Y - 3, ZONE_OPTIONS_LARGEUR + 6, ZONE_OPTIONS_HAUTEUR + 6, MLV_COLOR_PINK);
    MLV_draw_filled_rectangle(ZONE_OPTIONS_X, ZONE_OPTIONS_Y, ZONE_OPTIONS_LARGEUR, ZONE_OPTIONS_HAUTEUR, COULEUR_SURFACE);
    MLV_draw_rectangle(ZONE_OPTIONS_X, ZONE_OPTIONS_Y, ZONE_OPTIONS_LARGEUR, ZONE_OPTIONS_HAUTEUR, COULEUR_BORDURE);
    MLV_draw_rectangle(ZONE_OPTIONS_X + 4, ZONE_OPTIONS_Y + 4, ZONE_OPTIONS_LARGEUR - 8, ZONE_OPTIONS_HAUTEUR - 8, COULEUR_PANNEAU);

    dessiner_petit_coeur(ZONE_OPTIONS_X + 24, ZONE_OPTIONS_Y + 22, COULEUR_PANNEAU);
    MLV_draw_text(ZONE_OPTIONS_X + 45, ZONE_OPTIONS_Y + 15, "Options d'affichage", COULEUR_TEXTE);
    MLV_draw_line(ZONE_OPTIONS_X + 18, ZONE_OPTIONS_Y + 36, ZONE_OPTIONS_X + ZONE_OPTIONS_LARGEUR - 18, ZONE_OPTIONS_Y + 36, COULEUR_PANNEAU);

    dessiner_checkbox(ZONE_OPTIONS_X + 15, ZONE_OPTIONS_Y + 48, *option_voisinage);
    MLV_draw_text(ZONE_OPTIONS_X + 42, ZONE_OPTIONS_Y + 46, "voisinage", COULEUR_TEXTE);

    dessiner_checkbox(ZONE_OPTIONS_X + 15, ZONE_OPTIONS_Y + 80, *option_descision);
    MLV_draw_text(ZONE_OPTIONS_X + 42, ZONE_OPTIONS_Y + 78, "prise de decision", COULEUR_TEXTE);
}

static void dessiner_point(Point * P,int classe) {
    int x, y;
    MLV_Color c;
    MLV_Color symbole; 
    
    if (P == NULL || get_point_dimensions(P) < 2) return;

    x = ZONE_X + get_point_position(P, 0) * 250 + 255 ;
    y = ZONE_Y + get_point_position(P, 1) * 250 + 255 ;

    if (classe == CLASSE_VOISIN_SELECTIONNE) {
        /* Voisin KPP selectionne : couleur speciale pour qu'il ressorte clairement. */
        MLV_draw_filled_circle(x + 4, y + 5, 13, MLV_COLOR_GRAY);
        MLV_draw_filled_circle(x, y, 13, MLV_COLOR_YELLOW);
        MLV_draw_circle(x, y, 13, MLV_COLOR_ORANGE);
        MLV_draw_circle(x, y, 11, MLV_COLOR_ORANGE);
        MLV_draw_circle(x, y, 9, MLV_COLOR_BLACK);
        MLV_draw_text(x - 4, y - 7, "%c", MLV_COLOR_BLACK, classe_symbole(get_point_classe(P)));
        return;
    }

    c = classe_color(classe);
    symbole = MLV_COLOR_WHITE;
    if (classe == 3 || classe == 10) {
        symbole = MLV_COLOR_BLACK;
    }

    /* Points normaux : remplissage colore au lieu d'un simple contour. */
    MLV_draw_filled_circle(x + 3, y + 4, 10, MLV_COLOR_GRAY);
    MLV_draw_filled_circle(x, y, 10, c);
    MLV_draw_circle(x, y, 10, MLV_COLOR_BLACK);
    MLV_draw_circle(x, y, 8, MLV_COLOR_WHITE);
    MLV_draw_text(x - 4, y - 7, "%c", symbole, classe_symbole(get_point_classe(P)));
}

static void dessiner_bouton(int x, int y, int largeur, int hauteur, const char *texte) {
    MLV_draw_filled_rectangle(x + 5, y + 6, largeur, hauteur, COULEUR_OMBRE);
    MLV_draw_filled_rectangle(x - 2, y - 2, largeur + 4, hauteur + 4, MLV_COLOR_PINK);
    MLV_draw_filled_rectangle(x, y, largeur, hauteur, COULEUR_SURFACE);
    MLV_draw_rectangle(x, y, largeur, hauteur, COULEUR_BORDURE);
    MLV_draw_line(x + 8, y + hauteur - 8, x + largeur - 8, y + hauteur - 8, COULEUR_PANNEAU);
    dessiner_petit_coeur(x + largeur - 18, y + hauteur / 2 - 3, COULEUR_PANNEAU);
    MLV_draw_text(x + 12, y + hauteur / 2 - 6, texte, COULEUR_TEXTE);
}

static void dessiner_titre(void) {
    MLV_draw_filled_rectangle(514, 28, 250, 58, MLV_COLOR_WHITE);
    MLV_draw_rectangle(514, 28, 250, 58, COULEUR_PANNEAU);
    MLV_draw_text(560, 42, "k plus proches voisins", COULEUR_BORDURE);
    MLV_draw_text(570, 63, "interface graphique", COULEUR_TEXTE);
    dessiner_petit_coeur(536, 51, COULEUR_PANNEAU);
    dessiner_petit_coeur(742, 51, COULEUR_PANNEAU);
}

static void dessiner_petit_coeur(int x, int y, MLV_Color couleur) {
    MLV_draw_filled_circle(x, y, 4, couleur);
    MLV_draw_filled_circle(x + 7, y, 4, couleur);
    MLV_draw_filled_rectangle(x - 1, y + 3, 10, 6, couleur);
    MLV_draw_line(x - 1, y + 8, x + 3, y + 12, couleur);
    MLV_draw_line(x + 10, y + 8, x + 3, y + 12, couleur);
}

static void dessiner_fleur(int x, int y, MLV_Color couleur) {
    MLV_draw_filled_circle(x - 7, y, 7, couleur);
    MLV_draw_filled_circle(x + 7, y, 7, couleur);
    MLV_draw_filled_circle(x, y - 7, 7, couleur);
    MLV_draw_filled_circle(x, y + 7, 7, couleur);
    MLV_draw_filled_circle(x, y, 5, MLV_COLOR_WHITE);
}

static void dessiner_checkbox(int x, int y, int active) {
    MLV_draw_filled_rectangle(x + 2, y + 2, 17, 17, COULEUR_OMBRE);
    MLV_draw_filled_rectangle(x, y, 17, 17, MLV_COLOR_WHITE);
    MLV_draw_rectangle(x, y, 17, 17, COULEUR_BORDURE);
    if (active != 0) {
        MLV_draw_line(x + 3, y + 9, x + 7, y + 13, COULEUR_BORDURE);
        MLV_draw_line(x + 7, y + 13, x + 14, y + 4, COULEUR_BORDURE);
    }
}

static void dessiner_grille_douce(void) {
    int i;
    for (i = 1; i < 10; i++) {
        MLV_draw_line(ZONE_X + i * 51, ZONE_Y + 6, ZONE_X + i * 51, ZONE_Y + ZONE_HAUTEUR - 6, MLV_COLOR_GRAY);
        MLV_draw_line(ZONE_X + 6, ZONE_Y + i * 51, ZONE_X + ZONE_LARGEUR - 6, ZONE_Y + i * 51, MLV_COLOR_GRAY);
    }
}

static MLV_Color classe_color(int i) {
    MLV_Color color;
    if (i == 0) {
        color = MLV_COLOR_BLACK;
    }
    else {
        switch (i % 10 ) {
            case 1:
                color = MLV_COLOR_BLUE;
                break;
            case 2:
                color = MLV_COLOR_ORANGE;
                break;
            case 3:
                color = MLV_COLOR_GREEN;
                break;
            case 4:
                color = MLV_COLOR_MAGENTA;
                break;
            case 5:
                color = MLV_COLOR_CYAN;
                break;
            case 6:
                color = MLV_COLOR_RED;
                break;
            case 7:
                color = MLV_COLOR_PURPLE;
                break;
            case 8:
                color = MLV_COLOR_YELLOW;
                break;
            case 9:
                color = MLV_COLOR_BROWN;
                break;
            case 10:
                color = MLV_COLOR_PINK;
                break;
            default:
                color = MLV_COLOR_BLACK;
                break;
        }
    }
    return color ;
}

static char classe_symbole(int i) {
    char symbole;
    if (i == 0) {
        symbole = '*';
    }
    else {
        switch (i % 10 ) {
            case 1:
                symbole = 'X';
                break;
            case 2:
                symbole = '+';
                break;
            case 3:
                symbole = '*';
                break;
            case 4:
                symbole = 'X';
                break;
            case 5:
                symbole = '+';
                break;
            case 6:
                symbole = '*';
                break;
            case 7:
                symbole = 'X';
                break;
            case 8:
                symbole = '+';
                break;
            case 9:
                symbole = '*';
                break;
            case 10:
                symbole = 'X';
                break;
            default:
                symbole = '*';
                break;
        }
    }
    return symbole;
}

static void animer_sparkle(PointsList * list, size_t classe, int mode, int k, int * option_voisinage, int * option_descision, size_t nb_classe, Point * point_selectionne, int x, int y) {
    int i;
    for (i = 0; i < 7; i++) {
        dessiner_interface(list, classe, mode, k, option_voisinage, option_descision, nb_classe, point_selectionne);
        dessiner_sparkle(x, y, i);
        MLV_actualise_window();
        MLV_wait_milliseconds(35);
    }
}

static void dessiner_sparkle(int x, int y, int etape) {
    int r;
    int d;
    MLV_Color c;

    r = 4 + etape * 3;
    d = 8 + etape * 4;
    if (etape % 2 == 0) {
        c = MLV_COLOR_YELLOW;
    }
    else {
        c = MLV_COLOR_PINK;
    }

    MLV_draw_circle(x, y, r, c);
    MLV_draw_line(x - d, y, x - d / 2, y, c);
    MLV_draw_line(x + d / 2, y, x + d, y, c);
    MLV_draw_line(x, y - d, x, y - d / 2, c);
    MLV_draw_line(x, y + d / 2, x, y + d, c);
    MLV_draw_line(x - d / 2, y - d / 2, x - d / 4, y - d / 4, c);
    MLV_draw_line(x + d / 4, y - d / 4, x + d / 2, y - d / 2, c);
    MLV_draw_line(x - d / 2, y + d / 2, x - d / 4, y + d / 4, c);
    MLV_draw_line(x + d / 4, y + d / 4, x + d / 2, y + d / 2, c);

    MLV_draw_filled_circle(x - d, y - d / 3, 2, MLV_COLOR_WHITE);
    MLV_draw_filled_circle(x + d, y + d / 3, 2, MLV_COLOR_WHITE);
    MLV_draw_filled_circle(x - d / 3, y + d, 2, MLV_COLOR_WHITE);
    MLV_draw_filled_circle(x + d / 3, y - d, 2, MLV_COLOR_WHITE);
}

static Point* select_point(PointsList * list, int x, int y) {
    size_t i;
    Point *proche = NULL;
    double dist_min = 100.0;
    int px, py;
    double dist;

    if (list == NULL) return NULL;

    for (i = 0; i < list->count; i++) {
        Point *P = points_list_get_point(list, i);
        if (get_point_dimensions(P) < 2) continue;

        px = ZONE_X + get_point_position(P, 0) * 250 + 250 + 5;
        py = ZONE_Y + get_point_position(P, 1) * 250 + 250 + 5;

        dist = (double)((x - px) * (x - px) + (y - py) * (y - py));

        if (dist < dist_min) {
            dist_min = dist;
            proche = P;
        }
    }
    return proche;
}

static int point_dans_rectangle(int x, int y, int rx, int ry, int rw, int rh) {
    return (x >= rx && x <= rx + rw && y >= ry && y <= ry + rh);
}
