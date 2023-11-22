# Drupal-JukkaPajarinen

My personal website and blog crafted with Drupal and Bitnami Drupal Docker Stack.

## Usage

Start docker containers.

```
docker-compose up
```

(**OR**) Rebuild and clean docker containers.

```
docker-compose up --build --remove-orphans
```

After containers are built, install theme inside Drupal container.

```
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") ln -sv /opt/jukkapajarinen /opt/bitnami/drupal/themes/jukkapajarinen
```

After all the docker containers are running, go to: 
- [localhost:8080](http://localhost:8080) (for Drupal)
- [localhost:8443](https://localhost:8443) (for Drupal with SSL)
- [localhost:8888](http://localhost:8888) (for phpmyadmin)

(Optional) Disable Drupal cache systems for development

```
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") cp /opt/bitnami/drupal/sites/example.settings.local.php /opt/bitnami/drupal/sites/default/settings.local.php;
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") sh -c "echo 'include \"/opt/bitnami/drupal/sites/default/settings.local.php\";' >> /opt/bitnami/drupal/sites/default/settings.php";
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") sh -c "apt update && apt install -y vim && vim /opt/bitnami/drupal/sites/default/settings.local.php";
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") drush cr;
```

(Optional) Launch interactive shell to the drupal container. You can access `/opt/bitnami/drupal` and use `composer` and `drush` there.

```
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") bash
```

## License

Copyright (C) Jukka Pajarinen - All Rights Reserved

Unauthorized copying of this project, via any medium is strictly prohibited proprietary and confidential

Written by Jukka Pajarinen <jukka.pajarinen@lumitum.com>, Nov 2020
