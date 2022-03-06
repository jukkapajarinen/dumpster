# WordPress Docker-Starter

My personal starter for WordPress theme and plugin development with Docker. 

You might find it useful if you prefer hiding "unnecessary" core-files into docker volumes and focus only on plugin/theme specific files.

## Usage

Start docker containers.

```
docker-compose up
```

(**OR**) Rebuild and clean docker containers.

```
docker-compose up --build --remove-orphans
```

After all the docker containers are running, go to: 
- [localhost:8080](http://localhost:8080) (for WordPress)
- [localhost:8000](http://localhost:8000) (for phpmyadmin)

(Optional) Install WP-CLI tool to the WordPress container.
```
docker exec -it $(docker ps -aqf "name=^.*_wordpress_[0-9]*$") apt update && apt install less;
docker exec -it $(docker ps -aqf "name=^.*_wordpress_[0-9]*$") curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar;
docker exec -it $(docker ps -aqf "name=^.*_wordpress_[0-9]*$") chmod +x wp-cli.phar;
docker exec -it $(docker ps -aqf "name=^.*_wordpress_[0-9]*$") mv wp-cli.phar /usr/local/bin/wp;
docker exec -it $(docker ps -aqf "name=^.*_wordpress_[0-9]*$") sh -c "echo \"alias wp='wp --allow-root'\" >> /root/.bashrc";
```

(Optional) Launch interactive shell to the WordPress container. You can access `/var/www/html` and use `wp` (WP-CLI) there.

```
docker exec -it $(docker ps -aqf "name=^.*_wordpress_[0-9]*$") bash
```
