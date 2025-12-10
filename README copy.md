# ft_printf

*Ce projet a été créé dans le cadre du cursus 42 par abnassir.*

## Description

**ft_printf** est une réimplémentation de la fonction `printf` de la bibliothèque standard C (`libc`). L'objectif est de comprendre en profondeur le fonctionnement des fonctions variadiques et de la gestion du formatage de chaînes de caractères.

Le projet consiste à créer une bibliothèque `libftprintf.a` contenant une fonction `ft_printf` capable de gérer les conversions suivantes :
- `%c` : caractère unique
- `%s` : chaîne de caractères
- `%p` : pointeur en hexadécimal
- `%d` / `%i` : entier décimal
- `%u` : entier non signé
- `%x` : hexadécimal minuscule
- `%X` : hexadécimal majuscule
- `%%` : symbole pourcentage

## Instructions

### Compilation

Pour compiler la bibliothèque :
```bash
make
```

Cela génère `libftprintf.a` à la racine du projet.

### Commandes disponibles

- `make` ou `make all` : Compile la bibliothèque
- `make clean` : Supprime les fichiers objets (.o)
- `make fclean` : Supprime les fichiers objets et la bibliothèque
- `make re` : Recompile entièrement le projet (fclean + all)

### Utilisation

Pour utiliser la bibliothèque dans votre projet :

1. Incluez le header :
```c
#include "ft_printf.h"
```

2. Compilez avec la bibliothèque :
```bash
cc main.c libftprintf.a
```

3. Exemple d'utilisation :
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s!\n", "World");
    ft_printf("Nombre: %d\n", 42);
    ft_printf("Hexadécimal: %x\n", 255);
    ft_printf("Pointeur: %p\n", &main);
    return (0);
}
```

## Architecture et choix techniques

### Structure du projet

Le projet est organisé en modules, chaque fichier gérant une conversion spécifique :
```
ft_printf/
├── ft_printf.h          # Header principal
├── ft_printf.c          # Fonction principale
├── ft_putchar.c         # Gestion %c
├── ft_putstr.c          # Gestion %s
├── ft_putnbr.c          # Gestion %d et %i
├── ft_puthex.c          # Gestion %x, %X et %p
├── ft_strlen.c          # Fonction utilitaire
└── Makefile
```

### Algorithme et structures de données

#### 1. Fonction principale (`ft_printf`)

**Algorithme :**
- Parcours séquentiel de la chaîne `format` caractère par caractère
- Détection des spécificateurs `%` et appel de la fonction appropriée
- Accumulation du nombre de caractères affichés

**Justification :** Cette approche linéaire (O(n)) est la plus simple et efficace pour ce cas d'usage. Pas besoin de structure de données complexe car chaque caractère est traité une seule fois.

#### 2. Gestion des arguments variadiques

**Structure utilisée :** `va_list` (fournie par `<stdarg.h>`)

**Macros utilisées :**
- `va_start()` : Initialise la liste d'arguments
- `va_arg()` : Récupère l'argument suivant du type spécifié
- `va_end()` : Libère les ressources

**Justification :** C'est le mécanisme standard C pour gérer les fonctions à nombre variable d'arguments. Aucune alternative n'existe dans le cadre des contraintes du projet.

#### 3. Conversion en hexadécimal

**Algorithme récursif :**
```
fonction hex(nombre, format):
    si nombre >= 16:
        appeler hex(nombre / 16)
        appeler hex(nombre % 16)
    sinon:
        afficher le chiffre correspondant
```

**Justification :** 
- La récursivité permet un code élégant et compact
- Division par 16 pour extraire chaque chiffre hexadécimal
- Utilisation d'un tableau de correspondance `"0123456789abcdef"` pour la conversion

**Choix de type :** `size_t` pour gérer à la fois les `unsigned int` (32 bits) et les pointeurs (64 bits sur systèmes modernes).

#### 4. Gestion des nombres négatifs

**Algorithme :**
- Utilisation d'un `long` pour éviter l'overflow avec `INT_MIN` (-2147483648)
- Si négatif : afficher `-`, puis convertir en positif
- Réutilisation de la fonction `put_nbr_unsigned` pour l'affichage

**Justification :** `-(-2147483648)` dépasse la capacité d'un `int` (max: 2147483647), d'où l'utilisation d'un `long` (64 bits).

#### 5. Comptage des caractères

**Structure :** Simple compteur `int`

Chaque fonction retourne le nombre de caractères qu'elle a affiché, permettant l'accumulation dans `ft_printf`.

### Optimisations

- **Réutilisation de code** : `ft_putnbr` réutilise `put_nbr_unsigned`
- **Fonction dispatch** : `ft_case_stady` centralise la logique de choix de conversion
- **Pas de buffer** : Conformément au sujet, pas de gestion de buffer (contrairement au vrai `printf`)

## Resources

### Documentation officielle
- [man printf](https://man7.org/linux/man-pages/man3/printf.3.html) - Documentation Linux de printf
- [stdarg.h](https://man7.org/linux/man-pages/man3/stdarg.3.html) - Documentation des fonctions variadiques
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language) - Référence classique sur le C

### Tutoriels et articles
- [printf implementation tutorial](https://www.cypress.com/file/54761/download) - Guide détaillé
- [Variadic functions in C](https://www.geeksforgeeks.org/variadic-functions-in-c/) - Explication des va_list

### Utilisation de l'IA

**Claude AI (Anthropic)** a été utilisé pour :
- **Debugging** : Identification et correction d'erreurs (problème de cast `unsigned long` → `unsigned int`, gestion du retour de `ft_putstr` avec NULL)
- **Explications pédagogiques** : Compréhension approfondie des fonctions variadiques, des conversions de types, et de la gestion de l'overflow
- **Revue de code** : Vérification de la logique des algorithmes récursifs et suggestions d'optimisation
- **Documentation** : Aide à la structuration de ce README

**Parties écrites par moi-même :**
- Toute l'implémentation du code (100%)
- Architecture et organisation du projet
- Choix des algorithmes et structures de données
- Tests et validation

L'IA a joué un rôle de tuteur technique, mais n'a jamais généré de code complet pour moi. Chaque fonction a été écrite, testée et comprise par mes soins.

## Tests

Pour tester la conformité avec le vrai `printf` :
```c
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    int r1, r2;
    
    r1 = printf("Vrai : %d %s %x\n", 42, "test", 255);
    r2 = ft_printf("Moi  : %d %s %x\n", 42, "test", 255);
    printf("Retours : %d vs %d\n", r1, r2);
    
    return (0);
}
```

## Auteur

**abnassir** - Étudiant à 42