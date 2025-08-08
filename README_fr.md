[![Développé en C](https://img.shields.io/badge/Made%20with-C-blue.svg)](#)
[![MiniLibX](https://img.shields.io/badge/Lib-MiniLibX-lightgrey.svg)](#)
[![Plateforme](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-brightgreen.svg)](#)
[![Licence](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![English](https://img.shields.io/badge/lang-English-blue)](README.md)
[![Français](https://img.shields.io/badge/lang-Français-red)](README_fr.md)

---

## 📑 Table des matières
- [Particularités techniques](#-particularités-techniques-mlx-x11-et-bas-niveau)
- [Concepts et compétences](#-concepts--compétences-déployés)
- [Fonctionnalités](#-fonctionnalités-et-interactions)
- [Installation](#%EF%B8%8F-installation)
- [Exemples de lancement](#-exemples-de-lancement)
- [Prérequis](#-prérequis)
- [Objectifs atteints](#-objectifs-atteints)
- [Galerie](#-galerie)
- [Améliorations futures](#-améliorations-futures)
- [Licence](#-licence)

---

# 🦠 Fractol — Visualisation interactive de fractales en C avec MiniLibX

<p align="center">
  <img src="assets/Preview.png" alt="Aperçu Fractol" width="100%">
</p>

Visualisation interactive et temps réel de fractales mathématiques (Mandelbrot, Julia, Sierpiński Carpet) en C.  
Rendu graphique natif via la **MiniLibX (MLX)**.  
Deux architectures internes : version séquentielle et version optimisée multi-threading (choix laissé à l'utilisateur de le désactiver au lancement).

---

## 🖥️ Particularités techniques : MLX, X11 et bas niveau

**Fractol** s’appuie exclusivement sur la **MiniLibX (MLX)** :  
- Manipulation directe du framebuffer.
- Contrôle manuel de la fenêtre, des événements clavier et souris, du rafraîchissement.
- Aucun moteur graphique ni framework intermédiaire : gestion explicite des pixels, buffers, et cycles de rendu.
- Portabilité sur Unix (Linux, macOS selon la version MLX).


💡 **Note technique :**  
Sur Linux, la MLX repose sur **X11** (*X Window System*), l’API graphique historique des systèmes Unix.  
Cela implique :
- Une compréhension implicite du fonctionnement des événements et du rafraîchissement de fenêtres dans un environnement **très bas niveau**.
- Une exposition aux concepts utilisés par de nombreux outils graphiques, environnements de bureau et applications professionnelles depuis des décennies.
- Une compatibilité large et éprouvée : tout programme maîtrisant X11 peut fonctionner sur la quasi-totalité des distributions Linux (serveur graphique standard).
- Une architecture simple et minimaliste, idéale pour comprendre les bases du rendu 2D sans surcouche inutile.
  
  
En résumé, même si l’on code avec la MLX, on **touche indirectement aux fondamentaux d’X11** — ce qui donne une meilleure compréhension des couches logicielles basses qui font tourner la majorité des applications graphiques Unix/Linux.


---

## 🚀 Concepts & compétences déployés

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
	Elles sont changeables à tout moment via le raccourci clavier dédié (`S`).

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
    - Itérations maximales.
    - Coordonnées de la souris.
    - Mode de couleur actif.
    - Mode de rendu actif.
    - Niveau de zoom actuel.
    - Position courante dans le plan complexe.

- **Navigation et raccourcis :**
    - `J` + `[1-9]` : Accès direct à des zones célèbres de Mandelbrot  
      (*ex. : Elephant Valley, Seahorse Valley…*).
    - **Presets Julia** : lancement rapide avec alias prédéfinis.  
      Ex. : `./fractol julia dendrite`, `./fractol julia 1`, `./fractol julia d`.

- **Export d’images :**
    - `E` : Exporte la fractale courante en **PNG** plein écran,  
      même si le programme est lancé en mode fenêtré.
    - Le nom du fichier inclut automatiquement les paramètres actuels  
      (fractal, coordonnées, zoom, mode couleur…).

---

## ⚙️ Installation

Cloner et compiler :
```bash
git clone https://github.com/Matisse-Krn/Fract-ol.git
cd Fract-ol
make
```

Exécuter:
```bash
./fractol mandelbrot
```

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

<table>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=-0.73536_y=0.00085_z=0.78276_iter=200_mode=Normal_psy=off_color=B.png" width="420" alt="Vue d'ensemble Mandelbrot"><br>
  <em>Vue d'ensemble Mandelbrot</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=0.28470_y=-0.01180_z=500.00000_iter=200_mode=Cyclic_psy=on_color=C.png" width="420" alt="Elephant Valley"><br>
  <em>Elephant Valley</em>
</td>
</tr>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=-0.74402_y=0.11768_z=343.98536_iter=10000_mode=Normal_psy=on_color=Y.png" width="420" alt="Seahorse Valley"><br>
  <em>Seahorse Valley</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=-1.60944_y=0.00158_z=14.36038_iter=200_mode=Cyclic_psy=on_color=Y.png" width="420" alt="Zoom profond"><br>
  <em>Zoom profond</em>
</td>
</tr>
</table>

<p><i>Astuce :</i> utilisez <code>J</code> + <code>[1-9]</code> pour sauter vers certaines zones en un clic.</p>
</details>

<details>
  <summary><b>Julia — presets & alias</b></summary>

<table>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.07929_y=-0.00118_z=1.27402_iter=200_mode=Fixed_Log_psy=off_color=R.png" width="420" alt="Julia - Dendrite"><br>
  <em>Julia - Dendrite</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=-0.00779_y=0.02024_z=1.20000_iter=300_mode=Cyclic_psy=off_color=P.png" width="420" alt="Julia - Airplane"><br>
  <em>Julia - Airplane</em>
</td>
</tr>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.00875_y=-0.00503_z=1.06168_iter=200_mode=Cyclic_psy=off_color=O.png" width="420" alt="Julia - Tuning Fork"><br>
  <em>Julia - Tuning Fork</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.00875_y=-0.00503_z=1.06168_iter=200_mode=Cyclic_psy=on_color=G.png" width="420" alt="Julia - Tuning Fork psychedelic"><br>
  <em>Julia - Tuning Fork psychedelic</em>
</td>
</tr>
</table>

<p>Exemples : <code>./fractol julia dendrite</code>, <code>./fractol julia 1</code>, <code>./fractol julia d</code></p>
</details>

<details>
  <summary><b>Modes de rendu (Logarithmic / Adaptive / Fixed Log / Cyclic Modulo / Exponential)</b></summary>

<table>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.17329_y=0.48554_z=14.12109_iter=200_mode=Logarithmic_psy=off_color=G.png" width="420" alt="Logarithmic"><br>
  <em>Logarithmic</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.17329_y=0.48554_z=14.12109_iter=200_mode=Adaptive_psy=off_color=G.png" width="420" alt="Adaptive"><br>
  <em>Adaptive</em>
</td>
</tr>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.17329_y=0.48554_z=14.12109_iter=200_mode=Fixed_Log_psy=off_color=G.png" width="420" alt="Fixed Log"><br>
  <em>Fixed Log</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=0.17329_y=0.48554_z=14.12109_iter=200_mode=Cyclic_psy=off_color=G.png" width="420" alt="Cyclic Modulo"><br>
  <em>Cyclic Modulo</em>
</td>
</tr>
<tr>
<td align="center" colspan="2">
  <img src="assets/fractol_julia_x=0.17329_y=0.48554_z=14.12109_iter=200_mode=Normal_psy=off_color=G.png" width="420" alt="Exponential"><br>
  <em>Exponential</em>
</td>
</tr>
</table>

<p>
  <small>
  Les modes modifient l’échelle et la progression du dégradé en fonction du nombre d’itérations.
  </small>
</p>
</details>

<details>
  <summary><b>HUD — infos en direct & raccourcis</b></summary>

<table>
<tr>
<td align="center">
  <img src="assets/hud_live_info.png" width="840" alt="HUD - Live info"><br>
  <em>HUD - Live info</em>
</td>
</tr>
</table>

<ul>
  <li>Nombre max d'itérations</li>
  <li>Coordonnées de la souris</li>
  <li>Mode de couleur actif</li>
  <li>Mode de rendu actif</li>
  <li>Niveau de zoom</li>
  <li>Position dans le plan complexe</li>
</ul>
</details>

<details>
  <summary><b>Sierpiński Carpet — profondeurs</b></summary>

<table>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_sierpinski_1042x1042_depth=4_color=N.png" width="420" alt="Profondeur 4"><br>
  <em>Profondeur 4</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_sierpinski_1042x1042_depth=6_color=N.png" width="420" alt="Profondeur 6"><br>
  <em>Profondeur 6</em>
</td>
</tr>
</table>
</details>

<details>
  <summary><b>Export PNG (touche <code>E</code>) — exemples</b></summary>

<table>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=-0.00827_y=0.01902_z=1.52882_iter=100000_mode=Cyclic_1.png" width="420" alt="Export 1"><br>
  <em>Export 1</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=-0.48738_y=-0.18523_z=3471993472.50087_iter=100000_mode=Cyclic.png" width="420" alt="Export 2"><br>
  <em>Export 2</em>
</td>
</tr>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=-1.60944_y=0.00158_z=14.36038_iter=200_mode=Cyclic_psy=on_color=C.png" width="420" alt="Export 3"><br>
  <em>Export 3</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=-0.00852_y=0.02971_z=1.65888_iter=10000_mode=Logarithmic.png" width="420" alt="Export 4"><br>
  <em>Export 4</em>
</td>
</tr>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=-0.14731_y=1.03374_z=36.69177_iter=200_mode=Cyclic_psy=off_color=R.png" width="420" alt="Export 5"><br>
  <em>Export 5</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_julia_x=-0.00546_y=0.03935_z=1.44000_iter=100000_mode=Cyclic.png" width="420" alt="Export 6"><br>
  <em>Export 6</em>
</td>
</tr>
<tr>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=-0.74500_y=0.11500_z=500.00000_iter=10000.png" width="420" alt="Export 7"><br>
  <em>Export 7</em>
</td>
<td align="center" width="50%">
  <img src="assets/fractol_mandelbrot_x=0.28470_y=-0.01180_z=500.00000_iter=10000_mode=Logarithmic_4.png" width="420" alt="Export 8"><br>
  <em>Export 8</em>
</td>
</tr>
</table>

<p>
  Chaque export est en <b>plein écran</b> (même si la fenêtre ne l’est pas), et le nom du fichier contient les paramètres
  (fractal, coordonnées, zoom, itérations, mode, etc.).
</p>
</details>

---

## 🔮 Améliorations futures

- Support pour d’autres fractales (Burning Ship, Newton, Buddhabrot…)
- Anti-aliasing pour des contours plus lisses
- Fichier de configuration pour les paramètres de lancement
- Personnalisation avancée de la palette de couleurs
- HUD multilingue intégré
- Mode benchmark optionnel pour mesurer les performances de rendu

---

## 📜 Licence

Ce projet est sous licence MIT — voir le fichier [LICENSE](LICENSE) pour plus de détails.
