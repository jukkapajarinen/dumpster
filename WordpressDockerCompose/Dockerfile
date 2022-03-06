FROM wordpress:5.7

# Update apt and install various tools
RUN apt-get update && \
  apt-get upgrade -y && \
  apt-get autoremove && \
  apt-get install -y less vim curl zip;

# Install WP-CLI tool
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
  chmod +x wp-cli.phar && \
  mv wp-cli.phar /usr/local/bin/wp && \
  sh -c "echo \"alias wp='wp --allow-root'\" >> /root/.bashrc";

# Pre-install general plugins
RUN curl -o /tmp/wordpress-seo.16.0.2.zip https://downloads.wordpress.org/plugin/wordpress-seo.16.0.2.zip
RUN unzip /tmp/wordpress-seo.16.0.2.zip -d /usr/src/wordpress/wp-content/plugins
