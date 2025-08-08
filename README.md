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

## 🎨 Fonctionnalités et interactions

- **Choix de la fractale** au lancement :  
    - `mandelbrot`, `julia`, `sierpinski` (Sierpiński carpet).
    - **Paramètres de lancement** :
        - `-f` : Active le mode plein écran (*fullscreen*).  
          ⚠️ Sur une configuration multi-écrans, la taille totale des écrans sera utilisée (limitation de la MLX).  
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
./fractol --help
```

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

----

## 🖼 Galerie

> Cliquez pour dérouler chaque volet. Les médias sont stockés dans `assets/`.

<details>
  <summary><b>Mandelbrot — zooms & régions célèbres</b></summary>

  <p>
    <img src="assets/fractol_mandelbrot_x=-0.73536_y=0.00085_z=0.78276_iter=200_mode=Normal_psy=off_color=B.png" width="420" alt="Vue d'ensemble Mandelbrot">
    <img src="assets/fractol_mandelbrot_x=0.28470_y=-0.01180_z=500.00000_iter=200_mode=Cyclic_psy=on_color=C.png" width="420" alt="Elephant Valley">
  </p>

  <p>
    <img src="assets/mandelbrot_seahorse_valley.png" width="420" alt="Seahorse Valley">
    <img src="assets/mandelbrot_deep_zoom.png" width="420" alt="Zoom profond">
  </p>

  <p><i>Astuce :</i> utilisez <code>J</code> + <code>[1-9]</code> pour sauter vers certaines zones en un clic.</p>
</details>

<details>
  <summary><b>Julia — presets & alias</b></summary>

  <p>
    <img src="assets/julia_dendrite.png" width="420" alt="Julia - Dendrite">
    <img src="assets/julia_preset1.png" width="420" alt="Julia - Preset 1">
  </p>

  <p>
    <img src="assets/julia_preset2.png" width="420" alt="Julia - Preset 2">
    <img src="assets/julia_interactive.png" width="420" alt="Julia - Interaction">
  </p>

  <p>Exemples : <code>./fractol julia dendrite</code>, <code>./fractol julia 1</code>, <code>./fractol julia d</code></p>
</details>

<details>
  <summary><b>Modes de rendu (Logarithmic / Adaptive / Fixed Log / Cyclic Modulo / Exponential)</b></summary>

  <p>
    <img src="assets/mode_logarithmic.png" width="420" alt="Logarithmic">
    <img src="assets/mode_adaptive.png"   width="420" alt="Adaptive">
  </p>
  <p>
    <img src="assets/mode_fixedlog.png"   width="420" alt="Fixed Log">
    <img src="assets/mode_cyclic.png"     width="420" alt="Cyclic Modulo">
  </p>
  <p>
    <img src="assets/mode_exponential.png" width="420" alt="Exponential">
  </p>

  <p>
    <small>
    Les modes modifient l’échelle et la progression du dégradé en fonction du nombre d’itérations.
    </small>
  </p>
</details>

<details>
  <summary><b>HUD — infos en direct & raccourcis</b></summary>

  <p>
    <img src="assets/hud_live_info.png" width="840" alt="HUD - Live info">
  </p>

  <ul>
    <li>Position dans le plan complexe</li>
    <li>Niveau de zoom</li>
    <li>Mode de rendu couleur actif</li>
    <li>Itérations & coordonnées souris</li>
  </ul>
</details>

<details>
  <summary><b>Sierpiński Carpet — profondeurs</b></summary>

  <p>
    <img src="assets/sierpinski_depth4.png" width="420" alt="Profondeur 4">
    <img src="assets/sierpinski_depth6.png" width="420" alt="Profondeur 6">
  </p>
</details>

<details>
  <summary><b>Export PNG (touche <code>E</code>) — exemples</b></summary>

  <p>
    <img src="assets/export_example_1.png" width="420" alt="Export 1">
    <img src="assets/export_example_2.png" width="420" alt="Export 2">
  </p>

  <p>
    Chaque export est en <b>plein écran</b> (même si la fenêtre ne l’est pas), et le nom du fichier contient les paramètres
    (fractal, coordonnées, zoom, itérations, mode, etc.).
  </p>
</details>
