#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>

#include "interface.h"

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 700

#define COULEUR_FOND MLV_COLOR_GRAY
#define COULEUR_PANNEAU MLV_COLOR_WHITE
#define COULEUR_BORDURE MLV_COLOR_BLACK
#define COULEUR_TEXTE MLV_COLOR_BLACK

#define ZONE_X 40
#define ZONE_Y 100
#define ZONE_LARGEUR 720
#define ZONE_HAUTEUR 540

#define BOUTON_MODE_X 40
#define BOUTON_MODE_Y 30
#define BOUTON_MODE_LARGEUR 220
#define BOUTON_MODE_HAUTEUR 40

#define BOUTON_K_X 320
#define BOUTON_K_Y 30
#define BOUTON_K_LARGEUR 120
#define BOUTON_K_HAUTEUR 40

#define BOUTON_REINIT_X 900
#define BOUTON_REINIT_Y 30
#define BOUTON_REINIT_LARGEUR 220
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

static void dessiner_interface(void);

static void dessiner_fond(void);

static void dessiner_zone_affichage(void);

static void dessiner_bouton(
    int x,
    int y,
    int largeur,
    int hauteur,
    const char *texte
);
static void dessiner_options_affichage(void);

static int point_dans_rectangle(
    int x,
    int y,
    int rx,
    int ry,
    int rw,
    int rh
);

int interface_lancer(void) {
    int continuer;
    int souris_x;
    int souris_y;
    MLV_Keyboard_button touche;
    int resultat;

    continuer = 1;
    souris_x = 0;
    souris_y = 0;
    resultat = 1;

    MLV_create_window(
        "Projet PROG S4",
        "interface",
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE
    );

    while (continuer) {
        dessiner_interface();
        MLV_actualise_window();

        MLV_wait_keyboard_or_mouse(
            &touche,
            NULL,
            NULL,
            &souris_x,
            &souris_y
        );

        if (touche == MLV_KEYBOARD_ESCAPE) {
            continuer = 0;
        }

        if (point_dans_rectangle(
                souris_x,
                souris_y,
                BOUTON_REINIT_X,
                BOUTON_REINIT_Y,
                BOUTON_REINIT_LARGEUR,
                BOUTON_REINIT_HAUTEUR
            )) {
            continuer = 0;
        }
    }

    MLV_free_window();

    return resultat;
}

static void dessiner_interface(void) {
    dessiner_fond();
    dessiner_zone_affichage();
    dessiner_options_affichage();
}

static void dessiner_fond(void) {
    MLV_clear_window(COULEUR_FOND);

    dessiner_bouton(
        BOUTON_MODE_X,
        BOUTON_MODE_Y,
        BOUTON_MODE_LARGEUR,
        BOUTON_MODE_HAUTEUR,
        "Mode creation"
    );

    dessiner_bouton(
        BOUTON_K_X,
        BOUTON_K_Y,
        BOUTON_K_LARGEUR,
        BOUTON_K_HAUTEUR,
        "Valeur K"
    );

    dessiner_bouton(
        BOUTON_REINIT_X,
        BOUTON_REINIT_Y,
        BOUTON_REINIT_LARGEUR,
        BOUTON_REINIT_HAUTEUR,
        "Reinitialisation"
    );

    dessiner_bouton(
        BOUTON_CLASSE_X,
        BOUTON_CLASSE_Y,
        BOUTON_CLASSE_LARGEUR,
        BOUTON_CLASSE_HAUTEUR,
        "Classe du point"
    );

    dessiner_bouton(
        BOUTON_CHARGER_X,
        BOUTON_CHARGER_Y,
        BOUTON_CHARGER_LARGEUR,
        BOUTON_CHARGER_HAUTEUR,
        "Chargement fichier"
    );

    dessiner_bouton(
        BOUTON_SAUVEGARDER_X,
        BOUTON_SAUVEGARDER_Y,
        BOUTON_SAUVEGARDER_LARGEUR,
        BOUTON_SAUVEGARDER_HAUTEUR,
        "Sauvegarde fichier"
    );
}

static void dessiner_zone_affichage(void) {
    MLV_draw_filled_rectangle(
        ZONE_X,
        ZONE_Y,
        ZONE_LARGEUR,
        ZONE_HAUTEUR,
        COULEUR_PANNEAU
    );

    MLV_draw_rectangle(
        ZONE_X,
        ZONE_Y,
        ZONE_LARGEUR,
        ZONE_HAUTEUR,
        COULEUR_BORDURE
    );

    MLV_draw_text(
        ZONE_X + 210,
        ZONE_Y + 250,
        "Zone d'affichage des K-PPV",
        COULEUR_TEXTE
    );
}

static void dessiner_bouton(
    int x,
    int y,
    int largeur,
    int hauteur,
    const char *texte
) {
    MLV_draw_filled_rectangle(
        x,
        y,
        largeur,
        hauteur,
        COULEUR_PANNEAU
    );

    MLV_draw_rectangle(
        x,
        y,
        largeur,
        hauteur,
        COULEUR_BORDURE
    );

    MLV_draw_text(
        x + 10,
        y + 12,
        texte,
        COULEUR_TEXTE
    );
}

static void dessiner_options_affichage(void) {
    MLV_draw_filled_rectangle(
        ZONE_OPTIONS_X,
        ZONE_OPTIONS_Y,
        ZONE_OPTIONS_LARGEUR,
        ZONE_OPTIONS_HAUTEUR,
        COULEUR_PANNEAU
    );

    MLV_draw_rectangle(
        ZONE_OPTIONS_X,
        ZONE_OPTIONS_Y,
        ZONE_OPTIONS_LARGEUR,
        ZONE_OPTIONS_HAUTEUR,
        COULEUR_BORDURE
    );

    MLV_draw_text(
        ZONE_OPTIONS_X + 45,
        ZONE_OPTIONS_Y + 15,
        "Options d'affichage",
        COULEUR_TEXTE
    );

    MLV_draw_rectangle(
        ZONE_OPTIONS_X + 15,
        ZONE_OPTIONS_Y + 45,
        15,
        15,
        COULEUR_BORDURE
    );

    MLV_draw_text(
        ZONE_OPTIONS_X + 40,
        ZONE_OPTIONS_Y + 42,
        "voisinage",
        COULEUR_TEXTE
    );

    MLV_draw_rectangle(
        ZONE_OPTIONS_X + 15,
        ZONE_OPTIONS_Y + 75,
        15,
        15,
        COULEUR_BORDURE
    );

    MLV_draw_text(
        ZONE_OPTIONS_X + 40,
        ZONE_OPTIONS_Y + 72,
        "prise de decision",
        COULEUR_TEXTE
    );
}

static int point_dans_rectangle(
    int x,
    int y,
    int rx,
    int ry,
    int rw,
    int rh
) {
    int resultat;

    resultat = 0;

    if (x >= rx && x <= rx + rw && y >= ry && y <= ry + rh) {
        resultat = 1;
    }

    return resultat;
}
