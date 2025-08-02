# Fractol

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
    - Déplacement par clic/drag.
    - Ajustement du nombre d’itérations (définition/calcul).
    - Réglage dynamique du contraste et du lissage.
- **Palette et affichage interactifs :**
    - Changement de gamme de couleurs (R/G/B, raccourcis clavier).
    - Inversion instantanée des couleurs.
    - Activation du mode "psychédélique".
    - Affichage d’informations : nombre d’itérations max, coordonnées souris, mode actif, palette courante.
- **Navigation fluide :**
    - Réactivité garantie par le moteur graphique natif.
    - Pas de latence lors des zooms ou déplacements, même en multi-thread.

---

## 🧮 Fractales implémentées

- **Mandelbrot**  
    - Zoom extrême sur la frontière, réglage d’itération, rendu couleur dynamique.
- **Julia**  
    - Modification en temps réel des paramètres par la souris, visualisation instantanée.
- **Sierpinski Carpet**  
    - Algorithme récursif, ajustement du niveau de profondeur, contrôle du détail.

---

## 🛠️ Exemples de lancement

```bash
# Mandelbrot en multi-threading
./fractol mandelbrot --threads

# Julia, mono-thread
./fractol julia

# Sierpinski carpet, multi-thread forcé
./fractol sierpinski --threads

