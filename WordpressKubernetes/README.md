# WordPress Kubernetes

My personal starter for WordPress theme and plugin development with Docker and Kubernetes.  
You might find it useful if you prefer hiding "unnecessary" core-files into kubernetes volumes and focus only on plugin/theme specific files.  

**Tip:** Find and replace all **my-isolated-ns** strings from configs and launch new isolated WP instances. 

## Usage (locally)

```
minikube start --vm=true &&
minikube addons enable ingress &&
eval $(minikube docker-env) &&
docker build . -t custom-wordpress &&
kubectl apply -Rf ./kubernetes/
```

Wait and check that each pod **STATUS** is: **Running**.

```
kubectl config set-context --current --namespace=my-isolated-ns &&
kubectl get pods
```

After all the pods are running, get ip address and append `/etc/hosts`: 
```
kubectl get ingress
sudo echo "<ip_address_here> http://my-isolated-site.com" >> /etc/hosts
```

## Launch interactive shell

Launch interactive shell to the WordPress container. You can access `/var/www/html` and use `wp` (WP-CLI) there.

```
kubectl get pods
kubectl exec -it <pod_name_here> -- bash
wp --info
```
