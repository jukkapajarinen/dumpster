FROM mcr.microsoft.com/dotnet/core/sdk:3.1-buster AS build-env
WORKDIR /app

# Copy csproj and restore as distinct layers
COPY *.csproj ./
RUN dotnet restore

# Copy everything else and build
COPY . ./
RUN dotnet publish -c Release -o out

# Build runtime image
FROM mcr.microsoft.com/dotnet/core/runtime:3.1-buster-slim
WORKDIR /app
COPY --from=build-env /app/out .

# Install cron
RUN apt-get update
RUN apt-get install -y cron

# Create cronjob
RUN echo "* */1 * * * root . /root/env.sh && dotnet /app/Robin.dll > /proc/1/fd/1 2>/proc/1/fd/2" >> /etc/cron.d/robin-cron
RUN chmod 0644 /etc/cron.d/robin-cron
RUN crontab /etc/cron.d/robin-cron

# Entrypoint for the container
ENTRYPOINT env | sed 's/^\(.*\)$/export \1/g' > /root/env.sh && cron -f
