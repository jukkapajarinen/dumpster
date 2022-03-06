# Drupal Docker-Compose

My personal starter for `Drupal` theme and module development with `Docker` using `Bitnami Drupal Docker Stack`.

If you prefer hiding "unnecessary" core-files into docker volumes and focus only on module/theme specific files, feel free to try this out.

**Note:** You'll have to implement more templates to make the `hello_theme` functional! You can copy the core-templates from `core/modules/system/templates`. You can also add Gulp with CSS preprocessing and JavaScript bundling to handle optimized builds into `build` directory.

## Usage

Start docker containers.

```
docker-compose up
```

(**OR**) Rebuild and clean docker containers.

```
docker-compose up --build --remove-orphans
```

After containers are built, install module and theme inside Drupal container.

```
docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") ln -sv /opt/hello_module /opt/bitnami/drupal/modules/hello_module;

docker exec -it $(docker ps -aqf "name=^.*_drupal_[0-9]*$") ln -sv /opt/hello_theme /opt/bitnami/drupal/themes/hello_theme;
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
