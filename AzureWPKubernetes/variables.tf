variable "rg_name" {
  description = "The resource group for the AKS cluster"
  default     = "example-rg"
}

variable "location" {
  description = "The physical location for the AKS cluster"
  default     = "northeurope"
}

variable "vm_size" {
  description = "The VM size for the AKS cluster"
  default     = "standard_b2s"
}

variable "cluster_name" {
  description = "The name for the AKS cluster"
  default     = "example-aks"
}

variable "dns_prefix" {
  description = "Prefix for hostnames that are created"
  default     = "example"
}
