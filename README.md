# 🦠 Fractol — Visualisation interactive de fractales en C avec MiniLibX

Visualisation interactive et temps réel de fractales mathématiques (Mandelbrot, Julia, Sierpiński Carpet) en C.  
Rendu graphique natif via la **MiniLibX (MLX)**.  
Deux architectures internes : version séquentielle et version optimisée multi-threading (choix laissé à l'utilisateur au lancement).

---

## 🖥️ Particularités techniques : MLX et bas niveau

**Fractol** s’appuie exclusivement sur la **MiniLibX (MLX)** :  
- Manipulation directe du framebuffer.
- Contrôle manuel de la fenêtre, des événements clavier et souris, du rafraîchissement.
- Aucun moteur graphique ni framework intermédiaire : gestion explicite des pixels, buffers, et cycles de rendu.
- Portabilité sur Unix (Linux, macOS selon la version MLX).

Utilisation de la MLX implique :  
- Écriture manuelle de chaque pixel de l’image.
- Gestion fine des événements utilisateur et de la réactivité.
- Optimisation obligatoire pour garantir la performance, surtout lors de zooms et changements de paramètres en temps réel.
- Traitement asynchrone et synchronisation des threads (dans la version multi-threadée).

---

## 🚀 Concepts & Compétences déployés

- **Mathématiques appliquées :** manipulation d’ensembles fractals, arithmétique complexe, calcul itératif précis.
- **Programmation C bas-niveau :** gestion de la mémoire, structuration modulaire, gestion fine des buffers et des accès concurrents.
- **Rendu graphique natif :** écriture et lecture directe dans le buffer MLX, contrôle total du rendu pixel par pixel.
- **Conception interactive :** gestion avancée des entrées (clavier, souris), interface réactive et modifiable à la volée.
- **Parallélisation :** utilisation manuelle de POSIX threads pour accélérer le rendu sur multi-cœurs.
- **Optimisation :** séparation stricte entre logique de calcul, rendu graphique, gestion des threads et des entrées.
- **Robustesse :** contrôle des erreurs, stabilité mémoire, gestion des cas limites et prévention des races conditions.

---

## 🎨 Fonctionnalités et Interactions

- **Choix de la fractale** au lancement :  
    - `mandelbrot`, `julia`, `sierpinski` (Serpinski carpet).
    - Option d’activation/désactivation du multi-threading.
- **Contrôle total du rendu en temps réel :**
    - Zoom fin ou rapide (molette, clic).
    - Zoom suivant le curseur.
    - Déplacement par clic/molette ou flèches.
    - Ajustement du nombre d’itérations (définition/calcul).
    - Réglage dynamique du contraste et du lissage.
- **Palette et affichage interactifs :**
    - Changement de gamme de couleurs (raccourcis clavier R/G/B/Y/...).
    - Inversion instantanée des couleurs.
    - Activation du mode "psychédélique".
    - Affichage d’informations : nombre d’itérations max, coordonnées souris, mode actif, palette courante.
- **Navigation fluide :**
    - Réactivité garantie par le moteur graphique natif.
    - Pas de latence lors des zooms ou déplacements, même en multi-thread.

---

## 🎨 Fonctionnalités et Interactions

- **Choix de la fractale** au lancement :  
    - `mandelbrot`, `julia`, `sierpinski` (Sierpiński carpet).
    - **Paramètres de lancement** :
        - `-f` : Active le mode plein écran (*fullscreen*).  
          ⚠️ Non compatible avec les configurations multi-écrans (limitation de la MLX).  
          Sans ce paramètre, la taille de la fenêtre est codée en dur dans le programme.
        - Multi-threading activé par défaut. Pour le désactiver : `-mt=no`.
        - `-h` ou `--help` : Affiche la documentation complète dans le terminal.

- **Contrôle total du rendu en temps réel :**
    - Zoom fin ou rapide (molette, clic).
    - Zoom centré sur le curseur.
    - Déplacement par clic/molette ou flèches.
    - Ajustement dynamique du nombre d’itérations.
    - Réglage dynamique du contraste et du lissage.

- **Modes de calcul des couleurs :**
	Plusieurs méthodes de calcul des couleurs sont disponibles, modifiant l’apparence visuelle des fractales.  
	Elles sont changeables à tout moment via les raccourcis clavier dédiés.

	- **Logarithmic** :  
	  Accentue les variations de couleur dans les zones proches de la frontière en appliquant un logarithme sur le nombre d’itérations.
	- **Adaptive** :  
	  Ajuste dynamiquement l’échelle des couleurs en fonction du nombre d’itérations réellement rencontré à l’écran, optimisant le contraste global.
	- **Fixed Log** :  
	  Variante logarithmique utilisant une base fixe et constante, produisant un rendu plus homogène quelle que soit la zone explorée.
	- **Cyclic Modulo** :  
	  Applique un cycle répétitif de couleurs basé sur un modulo, créant des motifs visuels périodiques et très marqués.
	- **Exponential** :  
	  Amplifie les différences de couleur en utilisant une progression exponentielle, générant des dégradés plus vifs et contrastés.

- **Palette et affichage interactifs :**
    - Changement de gamme de couleurs (R/G/B/Y/...).
    - Inversion instantanée des couleurs.
    - Activation du mode "psychédélique".

- **Affichage d’informations en direct (HUD) :**
    - Position courante dans le plan complexe.
    - Niveau de zoom actuel.
    - Mode de rendu couleur actif.
    - Itérations maximales.
    - Coordonnées de la souris.

- **Navigation et raccourcis :**
    - `J` + [1-9] : Accès direct à des zones célèbres de Mandelbrot  
      (*ex. : Elephant Valley, Seahorse Valley…*).
    - **Presets Julia** : lancement rapide avec alias prédéfinis.  
      Ex. : `./fractol julia dendrite`, `./fractol julia 1`, `./fractol julia d`.

- **Export d’images :**
    - `E` : Exporte la fractale courante en **PNG** plein écran,  
      même si le programme est lancé en mode fenêtré.
    - Le nom du fichier inclut automatiquement les paramètres actuels  
      (fractal, coordonnées, zoom, mode couleur…).

---

## 🛠️ Exemples de lancement

```bash
# Mandelbrot
./fractol mandelbrot

# Mandelbrot en plein écran
./fractol mandelbrot -f

# Mandelbrot sans multi-threading
./fractol mandelbrot -mt=no

# Julia standard
./fractol julia

# Julia avec preset "dendrite"
./fractol julia dendrite

# Sierpinski carpet (mono-thread uniquement)
./fractol sierpinski

# Aide / manuel
./fractol --help```

---

## 📋 Prérequis

- C99+
- MiniLibX (MLX)
- POSIX Threads (pour l’option multi-thread)
- Linux ou macOS (selon la version de la MLX)

---

## 🎯 Objectifs atteints

- Moteur de rendu fractal interactif, rapide (compte-tenu de la MLX), optimisé et flexible.
- Maîtrise de la MLX et du rendu graphique bas-niveau.
- Implémentation robuste de l’arithmétique complexe.
- Optimisation concrète via multi-threading (pool de threads manuel).
- Interface contrôlée en temps réel, avec de multiples options.
- Extension des fonctionnalités interactives :  
  export PNG, navigation vers des points d’intérêt prédéfinis, presets Julia,  
  et affichage temps réel des paramètres de rendu.
- Structuration modulaire du code C, orientée maintenabilité et performance.

---

Aucune dépendance à d’autres frameworks que la MiniLibX.  
Projet centré sur l’algorithmique, la maîtrise de la programmation bas-niveau, et l’optimisation des rendus mathématiques en temps réel.
