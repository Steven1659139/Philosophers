# Philosophers

Philosophers est un projet de l'école 42. Le but est de résoudre le problème du dîner des philosophes en utilisant les threads et les mutex ou les sémaphores.

## Description

Dans ce projet, nous avons un certain nombre de philosophes assis autour d'une table ronde, mangeant des spaghettis. Il y a un bol de spaghettis au milieu de la table et une fourchette entre chaque philosophe. Un philosophe a besoin de deux fourchettes pour manger, et ils doivent penser quand ils ne mangent pas.

Notre programme simule ce scénario en créant un thread pour chaque philosophe. Chaque philosophe alterne entre penser, prendre des fourchettes, manger et déposer des fourchettes.

## Bonus

Pour le bonus, nous avons ajouté le support pour les sémaphores et nous avons également implémenté une protection contre la mort de deux philosophes en même temps.

## Compilation

Utilisez `make` pour compiler le projet. Cela générera deux exécutables, `philo` et `philo_bonus`.

```bash
make
```
## Utilisation

1. **Compilation** :
   Pour compiler Philosophers, naviguez jusqu'au répertoire du projet et utilisez la commande `make`. Cela créera deux exécutables : `philo` et `philo_bonus`.

    ```bash
    make
    ```

2. **Exécution** :
   
    - Pour exécuter `philo`, utilisez l'exécutable suivi de quatre ou cinq arguments numériques :

        ```bash
        ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
        ```

        Les arguments représentent respectivement le nombre de philosophes, le temps avant qu'un philosophe ne meure s'il n'a pas mangé, le temps que prend un philosophe pour manger, le temps que passe un philosophe à dormir, et (facultatif) le nombre de fois que chaque philosophe doit manger.

    - Pour exécuter `philo_bonus`, utilisez l'exécutable de la même manière que `philo` :

        ```bash
        ./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
        ```

## Licence

Ce projet est sous licence [MIT](LICENSE).
